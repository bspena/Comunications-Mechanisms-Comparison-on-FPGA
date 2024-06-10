import os

#######################################
# Test configuration and result files #
#######################################
# Path to test_list and test_resut
test_list_path = os.getcwd() + '/test_list.csv'
# Test list file columns
test_list_columns = ('sample_name','array_size')
# Test result file columns 
test_result_columns = ('array_size','latency','throughput')
# Number of repetitions for each test
test_list_num_repetitions = 5


###################
# oneAPI samples #
##################
# Sample names
sample_names = ['pipes','memory_channel']
# Path to samples
sample_path = '/home/vincenzo/BSpena/ES/impl'



###################
# Plot parameters #
###################
# x-axis values
x_values = [1024,4096,8192,16384,65536,262144,1048576,2097152,8388608,33554432]
x_custom_values = ['1 KB','4 KB','8 KB', '16 KB','64 KB',' 256 KB', '1 MB', '2 MB', '8 MB', '32 MB']

# Axis Labels
x_label = 'Array Size'
y_label_latency = 'Latency (ms)'
y_label_throughput= 'Throughput (MB/s)'

# Legend Labels
legend_label_pipes = 'Pipes'
legend_label_memch = 'Memory Channel'

# Plots titles
latency_plot_title = 'Comparison between Latencies'
throughputs_plot_title = 'Comparison between Throughputs'

# Number of levels of the indipendent factor
number_levels = 10