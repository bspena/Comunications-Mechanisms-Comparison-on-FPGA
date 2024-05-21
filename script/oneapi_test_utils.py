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


################################
# 2. Build and compile samples #
################################
def buildCompileSamples():
    # Create commands
    pipes_sample_cmd          = ( config.build_script + ' ' + config.path_setvars + ' ' + 
                                    config.path_pipes_sample + ' ' + config.path_asp + ' ' + 
                                    config.board_variant )
    memory_channel_sample_cmd = ( config.build_script + ' ' + config.path_setvars + ' ' + 
                                    config.path_memory_channel_sample + ' ' + config.path_asp + ' ' + 
                                    config.board_variant )

    # Run build script
    print('[INFO] Build pipes sample')
    subprocess.run(pipes_sample_cmd, shell=True, executable="/bin/bash")
    print('\n')

    print('[INFO] Build memory_channel sample')
    subprocess.run(memory_channel_sample_cmd, shell = True, executable="/bin/bash")


##################
# 3. Run samples #
##################
def runSamples(row):
    # Create commands
    pipes_sample_cmd          = ( config.run_script + ' ' + config.path_setvars + ' ' + 
                                config.path_pipes_sample + ' ' + config.samples_names[0] + ' ' + 
                                str(row['array_size']) )
    memory_channel_sample_cmd = ( config.run_script + ' ' + config.path_setvars + ' ' + 
                                config.path_memory_channel_sample + ' ' + config.samples_names[1] + ' ' + 
                                str(row['array_size']) )

    print('[INFO] Run pipes sample')
    subprocess.run(pipes_sample_cmd, shell=True, executable="/bin/bash")
    print('\n')

    print('[INFO] Run memory_channel sample')
    subprocess.run(memory_channel_sample_cmd, shell = True, executable="/bin/bash")
    print('\n')



#######################################
# 4. Saves result in test_results.csv #
#######################################
def savesResults():
    # Read results from samples csv files
    pipes_df = pandas.read_csv(config.path_pipes_t_result, names = [config.test_result_columns[0]])
    memory_channel_df = pandas.read_csv(config.path_memory_channel_t_result, names = [config.test_result_columns[1]])

    # Concatenate pandas objects along a particular axis
    test_result_df = pandas.concat([pipes_df, memory_channel_df], axis=1)

    # Create custom indeces
    tests_number = []
    for i in range(1,len(test_result_df.index)+1):
        string = 'Test' + str(i)
        tests_number.append(string)

    test_result_df.index = tests_number   


    # Write to csv 
    test_result_df.to_csv(config.path_test_result,index= False)

    # Remove samples csv files
    #os.remove(config.path_pipes_t_result)
    #os.remove(config.path_memory_channel_t_result)

