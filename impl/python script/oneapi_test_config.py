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
# oneAPI samples #
##################
# Sample names
sample_names = ['pipes','memory_channel']
# Path to samples
sample_path = '/home/spena/oneAPI-samples/DirectProgramming/C++SYCL_FPGA/Tutorials/Features'