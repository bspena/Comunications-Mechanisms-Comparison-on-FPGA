import os


###########
# Generic #
###########
# Bash script name to build samplee
build_script = './system_build.sh'


##############################
# Test list and result files #
##############################
# Path to test_list and test_resut
path_test_list = os.getcwd() + '/test_list.csv'
path_test_result = os.getcwd() + '/test_result.csv'
# Independent factors (Test list file columns) 
test_list_columns = ('array_size',)
# Response Variables (Test result file columns) 
test_result_columns = ['pipes_throughput','memory_channel_throughput']


##############
# oneAPI ASP #
##############
# Path to ASP
path_asp = '/home/spena/oneapi-asp/n6001'
# Board Variant
board_variant = 'ofs_n6001_iopipes'


###################
# oneAPI samples #
##################
# Samples names
samples_names = ('pipes','memory_channel')
# Path to samples
path_samples                = '/home/spena/oneAPI-samples/DirectProgramming/C++SYCL_FPGA/Tutorials/Features'
path_pipes_sample           = path_samples + '/pipes'
path_memory_channel_sample  = path_samples + '/memory_channel'
# Path to csv files with samples results
path_pipes_t_result             = path_samples + '/pipes/build/test_result_pipes.csv'
path_memory_channel_t_result    = path_samples + '/memory_channel/build/test_result_memory_channel.csv'

