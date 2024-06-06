import os

#######################################
# Test configuration and result files #
#######################################
# Path to test_list and test_resut
test_list_path = os.getcwd() + '/test_list_r2.csv'
# Test list file columns
test_list_columns = ('sample_name','array_size')
# Test result file columns 
test_result_columns = ('array_size','latency','throughput')
# Number of repetitions for each test
test_list_num_repetitions = 1

###################
# Plot parameters #
###################
# x-axis valus
x_values = [1,16]
# Axis Labels
x_label = 'Array Size (B)'
y_label_latency = 'Latency (ms)'
y_label_throughput= 'Throughput (MB/s)'
# Legend Labels
legend_label_pipes = 'Pipes'
legend_label_memch = 'USM Device Allocation'
# Plots titles
latency_plot_title = 'Comparison between Latencies'
throughputs_plot_title = 'Comparison between Throughputs'
# Number of indipendent factors
number_if = 2

###################
# oneAPI samples #
##################
# Sample names
sample_names = ['pipes','memory_channel']
# Path to samples
sample_path = '/home/spena/oneAPI-samples/DirectProgramming/C++SYCL_FPGA/Tutorials/Features'