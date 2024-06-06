import os

#######################################
# Test configuration and result files #
#######################################
# Path to test_list and test_resut
test_list_path = os.getcwd() + '/test_list_r.csv'
# Test list file columns
test_list_columns = ('sample_name','array_size')
# Test result file columns 
test_result_columns = ('array_size','latency','throughput')
# Number of repetitions for each test
test_list_num_repetitions = 3

###################
# Plot parameters #
###################
# x-axis valus
x_values = [1,16,256,1024,1048576,16777216]
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
number_if = 6

###################
# oneAPI samples #
##################
# Sample names
sample_names = ['pipes','memory_channel']
# Path to samples
sample_path = '/home/vincenzo/BSpena/ES/impl'