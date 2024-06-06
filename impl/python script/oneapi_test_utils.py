import pandas
import os
import subprocess
import numpy as np
from matplotlib import pyplot as plt 
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
    test_list_df = pandas.concat([test_list_df]*config.test_list_num_repetitions, ignore_index=True)

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

    # Create bash command to run ./sample.fpga.emu
    bash_command = (config.sample_path + '/' + str(row['sample_name']) + '/build/' + 
                   str(row['sample_name']) + '.fpga_emu ' + str(row['array_size']))

    # Run command
    subprocess.run(bash_command, shell = True, executable="/bin/bash")


#############################
# 3. Save and plot results #
#############################

# Find results
def find_results():
    
    # Define samples csv files paths
    pipes_path =        os.getcwd() + '/' + config.sample_names[0] + '_test_result.csv'
    memchannel_path =   os.getcwd() + '/' + config.sample_names[1] + '_test_result.csv'

    # Read results from samples csv files
    pipes_df = pandas.read_csv(pipes_path)
    memchannel_df = pandas.read_csv(memchannel_path)

    if pipes_df.columns[0] != 'array_size':
        pipes_df = pandas.read_csv(pipes_path, names = [config.test_result_columns[0],
                                        config.test_result_columns[1],config.test_result_columns[2]])
    
        memchannel_df = pandas.read_csv(memchannel_path, names = [config.test_result_columns[0],
                                        config.test_result_columns[1],config.test_result_columns[2]])

        # Write back to csv 
        pipes_df.to_csv(pipes_path,index= False)
        memchannel_df.to_csv(memchannel_path,index= False)

    return pipes_df,memchannel_df


# Find measurements of central tendency
def find_measurements_ct(df, df_column, n):
    
    # Array whit median or mean values
    list = []

    # Split dataframe into n array 
    split_df = np.split(df, n)
    
    # Find the median or the mean for the specificated dataframe column
    for s in split_df:
        list.append(np.median(s[df_column]))
        #list.append(np.mean(s[df_column]))

    return list


# Plot the values
def line_plot(ax, x, y, x_label, y_label, legend_label):  

    # Set the logarithmic scale 
    ax.set_xscale("log", base=2); 
    
    # Set labels and grid
    ax.set_xlabel(x_label)                 
    ax.set_ylabel(y_label)
    ax.grid(linestyle='--', color='0.85')     

    # Plot the result                                             
    ax.plot(x, y, marker='o', markerfacecolor ='blue', markersize='6', color='red', label = legend_label)


# Plot latencies values
def latencies_plot(pipes_df,memchannel_df):

    # Generate latencies median or mean values
    latency_pipes = find_measurements_ct(pipes_df,      config.test_result_columns[1], config.number_if)
    latency_memch = find_measurements_ct(memchannel_df, config.test_result_columns[1], config.number_if)

    # Line Plots Latencies
    fig, ax = plt.subplots(2, 1, figsize=(12,6))
    plt.suptitle(config.latency_plot_title, size=20)

    # Plot the values
    line_plot(ax[0], config.x_values, latency_pipes,    '',          config.y_label_latency, config.legend_label_pipes)
    line_plot(ax[1], config.x_values, latency_memch, config.x_label, config.y_label_latency, config.legend_label_memch)

    # Show the legend
    ax[0].legend()
    ax[1].legend()

    # Save plot as figure
    fig.savefig('cmp_latencies.png')


# Plot throughputs values
def throughputs_plot(pipes_df,memchannel_df):

    # Generate throughputs median or mean values
    throughput_pipes = find_measurements_ct(pipes_df,      config.test_result_columns[2], config.number_if)
    throughput_memch = find_measurements_ct(memchannel_df, config.test_result_columns[2], config.number_if)


    # Line Plots Throughputs
    fig, ax = plt.subplots(2, 1, figsize=(12,6))
    plt.suptitle(config.throughputs_plot_title, size=20)

    # Plot the values
    line_plot(ax[0], config.x_values, throughput_pipes,    '',           config.y_label_throughput, config.legend_label_pipes)
    line_plot(ax[1], config.x_values, throughput_memch,  config.x_label, config.y_label_throughput, config.legend_label_memch)

    # Show the legend
    ax[0].legend()
    ax[1].legend()

    # Save plot as figure
    fig.savefig('cmp_throughputs.png')


def savesRusults():
        
    # Find latencies and throughputs
    pipes_df,memchannel_df = find_results()

    # Sort the dataframes on array_size
    pipes_df =      pipes_df.sort_values(by=['array_size'])
    memchannel_df = memchannel_df.sort_values(by=['array_size'])

    # Plot latencies values
    latencies_plot(pipes_df, memchannel_df)

    # Plot throughputs values
    throughputs_plot(pipes_df, memchannel_df)

    # Show plot
    #plt.show()
