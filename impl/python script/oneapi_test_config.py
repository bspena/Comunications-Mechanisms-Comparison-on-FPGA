import os


###########
# Generic #
###########
# Bash script to build samples
build_script = './sample_build.sh'


#######################################
# Test configuration and result files #
#######################################
# Path to test_list and test_resut
test_list_path = os.getcwd() + '/test_list.csv'
#test_result_path = os.getcwd() + '/test_result.csv'
# Test list file columns
test_list_columns = ('sample_name','array_size')
# Test result file columns 
test_result_columns = ('array_size','latency','throughput')
# Number of repetitions for each test
test_list_num_repetitions = 2


###################
# oneAPI samples #
##################
# Path to samples
sample_path = '/home/spena/oneAPI-samples/DirectProgramming/C++SYCL_FPGA/Tutorials/Features'