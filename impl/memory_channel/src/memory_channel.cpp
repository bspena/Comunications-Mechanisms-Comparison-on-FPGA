#include <iomanip>
#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>

#include <sycl/sycl.hpp>
#include <sycl/ext/intel/fpga_extensions.hpp>

#include "exception_handler.hpp"

using namespace sycl;

// Forward declare the kernel names in the global scope (reduces name mangling in the optimization reports)
class ConsumerTutorial;

// The producer function copy data from host memory to device memory
event Producer(queue &q, int* producer_input, int* device_buffer, size_t array_size) {
  std::cout << "Enqueuing producer...\n";

  auto host_to_device_event = q.memcpy(device_buffer, producer_input, array_size * sizeof(int));

  std::cout << "Producer returning...\n";

  return host_to_device_event;
}

// Simple work done by the consumer kernel
int ConsumerWork(int i) { return i * i; }

// The consumer kernel reads data from device memory, performs some work 
// and copies the results back to host memory
event Consumer(queue &q, int* consumer_output, int* device_buffer, event producer_event, size_t array_size) {  
  std::cout << "Enqueuing consumer...\n";

  auto kernel_event = q.submit([&](handler &h) {

    // using a device/host_ptr tells the compiler that a pointer lives in the device/hosts address space
    sycl::device_ptr<int> device_buffer_ptr(device_buffer);
    sycl::host_ptr<int> host_out_data(consumer_output);

    // Wait for Producer
    producer_event.wait();

    h.single_task<ConsumerTutorial>([=]() [[intel::kernel_args_restrict]]{
      for (size_t i = 0; i < array_size; ++i){
        // do work on the input
        [[intel::fpga_register]] int result = ConsumerWork(device_buffer_ptr[i]);
        // write the result to the output buffer (to host memory)
        // consumer_output[i] = result;
        *(host_out_data + i) = result;
      }
    });
  });

  // The kernel must complete before copy back to hsto memory is executed 
  kernel_event.wait();
  
  std::cout << "Consumer returning...\n";

  return kernel_event;
}

int main(int argc, char *argv[]) {
  // Default values for the buffer size is based on a reasonable runtime for 
  // different targets
#if defined(FPGA_SIMULATOR)
  size_t array_size = 1 << 7;
#elif defined(FPGA_EMULATOR)
  size_t array_size = 1 << 12;
#else
  size_t array_size = 1 << 20;
#endif

  // allow the user to change the buffer size at the command line
  if (argc > 1) {
    std::string option(argv[1]);
    if (option == "-h" || option == "--help") {
      std::cout << "Usage: \n./pipes <data size>\n\nFAILED\n";
      return 1;
    } else {
      array_size = atoi(argv[1]);
    }
  }

  std::cout << "Input Array Size: " << array_size << "\n";


  // Use make <target> CXX_DEFINES=-DMALLOC_HOST to define
#ifndef MALLOC_HOST
  std::cout << "Not using malloc_host\n";
  // Allocate host memory
  int* consumer_output = static_cast<int *>(malloc(array_size * sizeof(int)));
  int* producer_input  = static_cast<int *>(malloc(array_size * sizeof(int)));
  assert ( producer_input   );
  assert ( consumer_output  );
#else // ! MALLOC_HOST
  std::cout << "Using malloc_host\n";
#endif // ! MALLOC_HOST

  // For convenience, keep a copy of input data in USM 
  int* producer_input_usm = static_cast<int *>(malloc(array_size * sizeof(int)));
  int* consumer_output_usm = static_cast<int *>(malloc(array_size * sizeof(int)));

  // Initialize the input data with random numbers smaller than 46340.
  // Any number larger than this will have integer overflow when squared.
  constexpr int max_val = 46340;
  for (size_t i = 0; i < array_size; i++) {
    producer_input_usm[i] = rand() % max_val;
  }

#if FPGA_SIMULATOR
  auto selector = sycl::ext::intel::fpga_simulator_selector_v;
#elif FPGA_HARDWARE
  auto selector = sycl::ext::intel::fpga_selector_v;
#else  // #if FPGA_EMULATOR
  auto selector = sycl::ext::intel::fpga_emulator_selector_v;
#endif

  // event is used for task syncronization
  event producer_event, consumer_event;

  try {
    // property list to enable SYCL profiling for the device queue
    auto props = property_list{property::queue::enable_profiling()};

    // create the device queue with SYCL profiling enabled
    queue q(selector, fpga_tools::exception_handler, props);

#ifdef MALLOC_HOST
    // Allocate host memory
    // malloc_host allocates memory specifically in the host's address space
    // NOTE: device CAN access this
    int* consumer_output = sycl::malloc_host<int>(array_size, q);
    int* producer_input  = sycl::malloc_host<int>(array_size, q);
    assert ( producer_input   );
    assert ( consumer_output  );
#endif // MALLOC_HOST

    // Copy data from USM buffer
    memcpy(producer_input, producer_input_usm, array_size * sizeof(int) );

    // Allocate device memory
    // malloc_device allocates memory specifically in the device's address space
    // NOTE: host CANNOT access this!
    int* device_buffer = sycl::malloc_device<int>(array_size, q);
    assert ( device_buffer );

    auto device = q.get_device();

    std::cout << "Running on device: "
              << device.get_info<sycl::info::device::name>().c_str()
              << std::endl;

    // Run the two kernels concurrently
    producer_event = Producer(q, producer_input, device_buffer, array_size);
    consumer_event = Consumer(q, consumer_output, device_buffer, producer_event, array_size);

    // Copy data to USM buffer
    memcpy(consumer_output_usm, consumer_output, array_size * sizeof(int) );

    // Free USM
    sycl::free(device_buffer,q);
#ifdef MALLOC_HOST
    sycl::free(producer_input,q);
    sycl::free(consumer_output,q);
#endif // MALLOC_HOST

  } catch (exception const &e) {
    // Catches exceptions in the host code
    std::cerr << "Caught a SYCL host exception:\n" << e.what() << "\n";

    // Most likely the runtime couldn't find FPGA hardware!
    if (e.code().value() == CL_DEVICE_NOT_FOUND) {
      std::cerr << "If you are targeting an FPGA, please ensure that your "
                   "system has a correctly configured FPGA board.\n";
      std::cerr << "Run sys_check in the oneAPI root directory to verify.\n";
      std::cerr << "If you are targeting the FPGA emulator, compile with "
                   "-DFPGA_EMULATOR.\n";
    }
    std::terminate();
  }

  // At this point, the producer_buffer and consumer_buffer have gone out
  // of scope. This will cause their destructors to be called, which will in
  // turn block until the Producer and Consumer kernels are finished and the
  // output data is copied back to the host. Therefore, at this point it is
  // safe and correct to access the contents of the consumer_output vector.

  // start and end time of the Producer kernel
  double p_start =
      producer_event
          .get_profiling_info<sycl::info::event_profiling::command_start>();
  double p_end =
      producer_event
          .get_profiling_info<sycl::info::event_profiling::command_end>();

  // start and end time of the Consumer kernel
  double c_start =
      consumer_event
          .get_profiling_info<sycl::info::event_profiling::command_start>();
  double c_end =
      consumer_event
          .get_profiling_info<sycl::info::event_profiling::command_end>();

  // the total application time
  double total_time_ms = (c_end - p_start) * 1e-6;

  // the input size in MBs
  double input_size_mb = array_size * sizeof(int) * 1e-6;

  // the total application throughput
  double throughput_mbs = input_size_mb / (total_time_ms * 1e-3);

  // Print the start times normalized to the start time of the producer.
  // i.e. the producer starts at 0ms and the other start/end times are
  // reported as differences to that number (+X ms).
  std::cout << std::fixed << std::setprecision(3);
  std::cout << "\n";
  std::cout << "Profiling Info\n";
  std::cout << "\tProducer:\n";
  std::cout << "\t\tStart time: " << 0 << " ms\n";
  std::cout << "\t\tEnd time: +" << (p_end - p_start) * 1e-6 << " ms\n";
  std::cout << "\t\tKernel Duration: " << (p_end - p_start) * 1e-6 << " ms\n";
  std::cout << "\tConsumer:\n";
  std::cout << "\t\tStart time: +" << (c_start - p_start) * 1e-6 << " ms\n";
  std::cout << "\t\tEnd time: +" << (c_end - p_start) * 1e-6 << " ms\n";
  std::cout << "\t\tKernel Duration: " << (c_end - c_start) * 1e-6 << " ms\n";
  std::cout << "\tDesign Duration: " << total_time_ms << " ms\n";
  std::cout << "\tDesign Throughput: " << throughput_mbs << " MB/s\n";
  std::cout << "\n";

  // Verify the result
  for (size_t i = 0; i < array_size; i++) {
    if (consumer_output_usm[i] != ConsumerWork(producer_input_usm[i])) {
      std::cout << "input = "    << producer_input_usm[i]
                << " expected: " << ConsumerWork(producer_input_usm[i])
                << " got: "      << consumer_output_usm[i] 
                << "\n";
      std::cout << "FAILED: The results are incorrect\n";
      return 1;
    }
  }
  std::cout << "PASSED: The results are correct\n";

  // Clean-up
  free(producer_input_usm);
  free(consumer_output_usm);
#ifndef MALLOC_HOST
  sycl::free(producer_input);
  sycl::free(consumer_output);
#endif // ! MALLOC_HOST

  // Open file csv in append mode and saves result
  std::ofstream test_result;
  test_result.open("memory_channel_test_result.csv",std::ios::app);
  test_result << array_size << "," << total_time_ms << "," << throughput_mbs << "\n";

  return 0;
}