import pandas
import os
import subprocess
import oneapi_test_config as config

######################
# 0. Debug utilities #
######################

# Check if columns names in test list file are equal to columns names in test_list_columns tuple
def assert_config():
    df_test_list = pandas.read_csv(config.path_test_list)  
    for value in config.test_list_columns:
        assert ( value in list(df_test_list.columns) ), "Property " + value + " not in " + config.path_test_list


###########################
# 1. Initialization utils #
###########################

# Initialize the test
def initTest():
    
    # Read test_list.csv (number of test x indipendet factors) and create the dataframe
    df_test_list = pandas.read_csv(config.path_test_list)

    # Create custom indeces
    tests_number = []
    for i in range(1,len(df_test_list.index)+1):
        string = 'Test' + str(i)
        tests_number.append(string)

    df_test_list.index = tests_number

    return df_test_list


####################################
# 2. Build and compile the program #
####################################

# Build and compile:
def buildAndCompile():
    build_pipe_sample           = './system_build.sh ' + config.path_pipes_sample
    build_memory_channel_sample = './system_build.sh ' + config.path_memory_channel_sample
    
    #print(build_pipe_sample)

    #1) Pipes sample
    print(" 1) Pipes samples")
    subprocess.run(build_pipe_sample, shell=True, executable="/bin/bash")

    #2) Memory channel samples
    #print(" 2) Memory channel samples")
    subprocess.run(build_memory_channel_sample, shell = True, executable="/bin/bash")