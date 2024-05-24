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
class ProducerTutorial;
class ConsumerTutorial;

// The producer function copy host's data to device memory
event Producer(queue &q, int* in_host_ptr, int * out_host_ptr,size_t array_size,std::vector<int> &producer_input) {
  std::cout << "Enqueuing producer...\n";

  // Event to copy host's data to device memory
  auto host_to_device =  q.memcpy(in_host_ptr, producer_input.data(), array_size * sizeof(int));

  // Crate the command group to issue commands to the queue
  // The handler object define task operations
  auto kernel_event = q.submit([&](handler &h) {                                                                     

    // The event of the copy of host's data must complete before command
    // group is executed
    h.depends_on(host_to_device);

    // Only one instance of the kernel is executed
    // intel::kernel_args_restrict is a kernel attribute, which should be applied anytime you can guarantee 
    // that kernel arguments do not alias. This attribute enables more aggressive compiler optimizations 
    // and often improves kernel performance on FPGA.
    h.single_task<ProducerTutorial>([=]() [[intel::kernel_args_restrict]]{

      // Create device pointers to access to the device memory
      sycl::device_ptr<int> in_d_ptr(in_host_ptr);
      sycl::device_ptr<int> out_d_ptr(out_host_ptr);

      for (size_t i = 0; i < array_size; ++i) {
        out_d_ptr[i]=in_d_ptr[i];
      }
    });
  });

  return kernel_event;
}

// Simple work done by the consumer kernel
int ConsumerWork(int i) { return i * i; }

// The consumer kernel reads data from device memory, performs some work 
// and copies the results back to host memory
event Consumer(queue &q, int* in_host_ptr, int * out_host_ptr, size_t array_size,std::vector<int> &consumer_output) {
  std::cout << "Enqueuing consumer...\n";

  auto kernel_event = q.submit([&](handler &h) {

    h.single_task<ConsumerTutorial>([=]() [[intel::kernel_args_restrict]]{

      // Create device pointers to access to the device memory
      sycl::device_ptr<int> in_d_ptr(in_host_ptr);
      sycl::device_ptr<int> out_d_ptr(out_host_ptr);

      for (size_t i = 0; i < array_size; ++i) {
        // Do work on the input
        out_d_ptr[i] = ConsumerWork(in_d_ptr[i]);
      }
    });
  });

  // Create a command group
  auto device_to_host = q.submit([&](handler &h) {

    // The kernel must complete before command group is executed
    h.depends_on(kernel_event);

    // Copy output data back from device to host
    h.memcpy(consumer_output.data(), out_host_ptr, array_size * sizeof(int));
  });

  // wait for copy back to finish
  device_to_host.wait();

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

  // Input and output array
  std::vector<int> producer_input(array_size, -1);
  std::vector<int> consumer_output(array_size, -1);

  // Initialize the input data with random numbers smaller than 46340.
  // Any number larger than this will have integer overflow when squared.
  constexpr int max_val = 46340;
  for (size_t i = 0; i < array_size; i++) {
    producer_input[i] = rand() % max_val;
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

    auto device = q.get_device();

    // Make sure the device supports USM device allocations
    if (!device.get_info<sycl::info::device::usm_device_allocations>()) {
      std::cerr << "ERROR: The selected device does not support USM device"
                << " allocations\n";
      return 1;
    }

    std::cout << "Running on device: "
              << device.get_info<sycl::info::device::name>().c_str()
              << std::endl;

    // Allocate memory on the device specifying the same buffer location
    // int_ptr and out_ptr are host pointers
    int *in_host_ptr = sycl::malloc_device<int>(
        array_size, q,
        sycl::ext::intel::experimental::property::usm::buffer_location(0));
    int *out_host_ptr = sycl::malloc_device<int>(
        array_size, q,
        sycl::ext::intel::experimental::property::usm::buffer_location(0));
  
    // Run the two kernels concurrently
    producer_event = Producer(q, in_host_ptr, out_host_ptr, array_size,producer_input);
    consumer_event = Consumer(q, in_host_ptr, out_host_ptr, array_size,consumer_output);

    // Free USM
    sycl::free(in_host_ptr,q);
    sycl::free(out_host_ptr,q);

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
    if (consumer_output[i] != ConsumerWork(producer_input[i])) {
      std::cout << "input = " << producer_input[i]
                << " expected: " << ConsumerWork(producer_input[i])
                << " got: " << consumer_output[i] << "\n";
      std::cout << "FAILED: The results are incorrect\n";
      return 1;
    }
  }
  std::cout << "PASSED: The results are correct\n";

  // Open file test_result_memory_channel.csv in append mode
  std::ofstream test_result;
  test_result.open("test_result_memory_channel.csv",std::ios::app);

  // Write data into the file
  std::cout << "Save results into test_result_memory_channel.csv" << "\n";
  test_result << total_time_ms << "," << throughput_mbs << "\n";

  return 0;
}