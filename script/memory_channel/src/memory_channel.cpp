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

// The Producer kernel reads data from input buffer and writes it to common buffer
// event is used for task syncronization
event Producer(queue &q, buffer<int, 1> &input_buffer,int *package) {
  std::cout << "Enqueuing producer...\n";

  // Submit the command group. 
  // Handler object define task operations
  auto e = q.submit([&](handler &h) {                                                                     

    // Accessor provides read-only access to input buffer
    accessor input_accessor(input_buffer, h, read_only);
    
    size_t num_elements = input_buffer.size();

    // Accessor provides write_only access to common buffer
    //accessor common_accessor(common_buffer, h, write_only, no_init);

    //int* package = sycl::malloc_device<int>(num_elements, q);

    // Is executed only one instance of the kernel
    h.single_task<ProducerTutorial>([=]() {
      for (size_t i = 0; i < num_elements; ++i) {
        //ProducerToConsumerPipe::write(input_accessor[i]);
        //int* package = sycl::malloc_device<int>(num_elements, q);
        package[i]=input_accessor[i];
      }
    });
  });

  return e;
}

// intel::kernel_args_restrict --> provide more time for the instructions to complete and getting better instruction scheduling


// Simple work done by the Consumer kernel
int ConsumerWork(int i) { return i * i; }

// The Consumer kernel reads data from common buffer, performs some work 
// and writes the results to an output buffer
event Consumer(queue &q, buffer<int, 1> &out_buf, int *package) {
  std::cout << "Enqueuing consumer...\n";

  auto e = q.submit([&](handler &h) {

    // Accessor provides write_only access to output buffer
    accessor out_accessor(out_buf, h, write_only, no_init);
    size_t num_elements = out_buf.size();

    // Accessor provides read-only access to common buffer
    //accessor common_accessor(common_buf, h, read_only);

    h.single_task<ConsumerTutorial>([=]() {
      for (size_t i = 0; i < num_elements; ++i) {
        // read the input from the pipe
        //int input = common_accessor[i];

        // do work on the input
        int answer = ConsumerWork(package[i]);

        // write the result to the output buffer (to global memory)
        out_accessor[i] = answer;
      }
    });
  });

  return e;
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

  // Arrays for SYCL producer (or input), common and consumer (or output) buffer
  std::vector<int> producer_input(array_size, -1);
  std::vector<int> consumer_output(array_size, -1);
  std::vector<int> prod_cons(array_size, -1);
  //int prod_cons[array_size];

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

  event producer_event, consumer_event;

  try {
    // property list to enable SYCL profiling for the device queue
    auto props = property_list{property::queue::enable_profiling()};

    // create the device queue with SYCL profiling enabled
    queue q(selector, fpga_tools::exception_handler, props);

    auto device = q.get_device();
    //auto context = q.get_context();

    std::cout << "Running on device: "
              << device.get_info<sycl::info::device::name>().c_str()
              << std::endl;

    // create the producer (or input) and consumer (or output) buffers
    buffer producer_buffer(producer_input);
    buffer consumer_buffer(consumer_output);

    // Common buffer used to transfer data from producer to consumer kernel.
    // It works in burst-interleaved manner
    //buffer common_buffer(prod_cons);
    //buffer<int> common_buffer(&prod_cons[0],array_size);

    // Allocate memory on the device
    //1) Specifying array dimension and the syclQueue
    int* package = sycl::malloc_device<int>(array_size, q);
    
    //2) Specifying array dimension and the syclDevice and sysclContext
    //int* package = sycl::malloc_device<int>(array_size, device,context);
    
    //3) Specifying total byte dimension of the array and the syclQueue
    //int* package = static_cast<int*>(sycl::malloc_device(array_size * sizeof(int),q));

    // Run the two kernels concurrently
    producer_event = Producer(q, producer_buffer, package);
    consumer_event = Consumer(q, consumer_buffer, package);
    //producer_event = Producer(q, producer_buffer);
    //consumer_event = Consumer(q, consumer_buffer, common_buffer);

    // Free USM
    sycl::free(package,q);
    //sycl::free(package,context);

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

  // Open file test_result.txt in append mode
  std::ofstream test_result;
  test_result.open("test_result.csv",std::ios::app);

  // Write data into the file
  std::cout << "Save results into test_result.csv" << "\n";
  test_result << throughput_mbs << "\n";

  return 0;
}