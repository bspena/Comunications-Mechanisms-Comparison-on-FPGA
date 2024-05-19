import os

#######################################
# Test list and result files #
#######################################
# Path to test_list and test_resut
path_test_list = os.getcwd() + '/test_list.csv'
path_test_result = os.getcwd() + '/test_result.csv'
# Independent factors (Test list file columns) 
test_list_columns = ('array_size',)
# Response Variables (Test result file columns) 
test_result_columns = ('throughput',)

#######################################
# Path to oneAPI samples #
#######################################
path_pipes_sample = '/home/$(whoami)/'
path_device_memory_sample = '/home/$(whoami)/'



