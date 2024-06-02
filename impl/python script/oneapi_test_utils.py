import pandas
import os
import subprocess
import oneapi_test_config as config

######################
# 0. Debug utilities #
######################

# Check if columns names in test list file are equal to columns names in test_list_columns tuple
def assert_config():
    test_list_df = pandas.read_csv(config.test_list_path)  
    for value in config.test_list_columns:
        assert ( value in list(test_list_df.columns) ), "Property " + value + " not in " + config.test_list_path


###########################
# 1. Initialization utils #
###########################

# Initialize the test
def initTest():
    
    # Read test_list.csv (number of test x indipendet factors) and create the dataframe
    test_list_df = pandas.read_csv(config.test_list_path)

    # Expand by the number of repetition
    for i in range(1,config.test_list_num_repetitions):
        test_list_df = pandas.concat([test_list_df, test_list_df], ignore_index=True)

    # Reshuffle for randomness
    test_list_df = test_list_df.sample(frac=1).reset_index(drop=True)

    # Create custom indeces
    tests_number = []
    for i in range(1,len(test_list_df.index)+1):
        string = 'Test' + str(i)
        tests_number.append(string)

    test_list_df.index = tests_number

    return test_list_df


##################
# 2. Run samples #
##################
def runSamples(row):

    # Create bash command to run ./sample.fpga_emu
    #bash_command = (config.sample_path + '/' + str(row['sample_name']) + '/build/' + 
    #               str(row['sample_name']) + '.fpga_emu ' + str(row['array_size']))

    # Create bash command to run ./sample.fpga
    bash_command = (config.sample_path + '/' + str(row['sample_name']) + '/build/' + 
                   str(row['sample_name']) + '.fpga ' + str(row['array_size']))

    # Run command
    subprocess.run(bash_command, shell = True, executable="/bin/bash")


#######################################
# 3. Saves result in test_results.csv #
#######################################
def savesResults(sample_name):
        
    # Create test_result.csv path
    test_result_path = os.getcwd() + '/' + sample_name + '_test_result.csv'

    # Read results from samples csv files
    test_result_df = pandas.read_csv(test_result_path, names = [config.test_result_columns[0],
                                    config.test_result_columns[1],config.test_result_columns[2]])

    # Create custom indeces
    tests_number = []
    for i in range(1,len(test_result_df.index)+1):
        string = 'Test' + str(i)
        tests_number.append(string)

    test_result_df.index = tests_number   

    # Write to csv 
    test_result_df.to_csv(test_result_path,index= False)

