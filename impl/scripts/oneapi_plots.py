import os
import pandas
import numpy as np
from matplotlib import pyplot as plt
import matplotlib.gridspec as gridspec 

###################
# Plot parameters #
###################
# x-axis valus
x_values = [1024,4096,8192,16384,65536,262144,1048576,2097152,8388608,33554432]
# Axis Labels
x_label = 'Array Size (B)'
y_label_latency = 'Latency (ms)'
y_label_throughput= 'Throughput (MB/s)'
# Legend Labels
legend_label_pipes = 'Pipes'
legend_label_memch = 'Memory Channel'
# Plots titles
latency_plot_title = 'Comparison between Latencies'
throughputs_plot_title = 'Comparison between Throughputs'
# Number of indipendent factors
number_if = 10

test_result_columns = ('array_size','latency','throughput')
sample_names = ['pipes','memory_channel']



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
def line_plot(ax, x, y, x_label, y_label, color ,legend_label):  

    # Set the logarithmic scale 
    ax.set_xscale("log", base=2); 
    ax.set_yscale("log", base=10); 
    
    # Set labels and grid
    ax.set_xlabel(x_label)                 
    ax.set_ylabel(y_label)
    ax.grid(linestyle='--', color='0.85')     

    # Plot the result                                             
    ax.plot(x, y, marker='o', markerfacecolor ='black', markersize='6', color=color, label = legend_label)


# Plot latencies values
def latencies_plot(latency_pipes, latency_memch):

    # Define the figure
    fig=plt.figure(figsize=(12,7))   
    ax = plt.axes()  
    plt.suptitle(latency_plot_title, size=20)

    # Plot the values
    line_plot(ax, x_values, latency_pipes, '', '', 'red', legend_label_pipes)
    line_plot(ax, x_values, latency_memch, x_label, y_label_latency, 'green', legend_label_memch)

    # Show the legend
    ax.legend()

    # Save plot as image
    fig.savefig('latencies_plot.png')



# Plot throughputs values
def throughputs_plot(throughput_pipes, throughput_memch):

    # Define the figure
    fig=plt.figure(figsize=(12,7))   
    ax = plt.axes()  
    plt.suptitle(throughputs_plot_title, size=20)

    # Plot the values
    line_plot(ax, x_values, throughput_pipes, '', '', 'red', legend_label_pipes)
    line_plot(ax, x_values, throughput_memch, x_label, y_label_throughput, 'green', legend_label_memch)

    # Show the legend
    ax.legend()

    # Save plot as image
    fig.savefig('throughputs_plot.png')


# Plot all values in one figure
def plots(latency_pipes, latency_memch,throughput_pipes, throughput_memch):

    # Define the figure
    #fig, ax = plt.subplots(1,2,figsize=(16,8))
    fig, ax = plt.subplots(2,1,figsize=(16,8))       
    ax[0].set_title(latency_plot_title, size = 20) 
    ax[1].set_title(throughputs_plot_title, size = 20)

    # Plot latency values
    line_plot(ax[0], x_values, latency_pipes, '', '', 'red', legend_label_pipes)
    line_plot(ax[0], x_values, latency_memch, '', y_label_latency, 'green', legend_label_memch)

    # Plot throughput values
    line_plot(ax[1], x_values, throughput_pipes, '', '', 'red', legend_label_pipes)
    line_plot(ax[1], x_values, throughput_memch, x_label, y_label_throughput, 'green', legend_label_memch)

    # Show the legend
    ax[0].legend()
    ax[1].legend()

    # Save plot as image
    fig.savefig('latencies_throughputs_plot2.png')


if __name__=='__main__':

    # Define samples csv files paths
    pipes_path =        os.getcwd() + '/' + sample_names[0] + '_test_result.csv'
    memchannel_path =   os.getcwd() + '/' + sample_names[1] + '_test_result.csv'

    # Read results from samples csv files
    pipes_df = pandas.read_csv(pipes_path)
    memchannel_df = pandas.read_csv(memchannel_path)

    # Sort the dataframes on array_size
    pipes_df =      pipes_df.sort_values(by=['array_size'])
    memchannel_df = memchannel_df.sort_values(by=['array_size'])

    # Generate latencies median or mean values
    latency_pipes = find_measurements_ct(pipes_df,      test_result_columns[1], number_if)
    latency_memch = find_measurements_ct(memchannel_df, test_result_columns[1], number_if)

    # Generate throughputs median or mean values
    throughput_pipes = find_measurements_ct(pipes_df,      test_result_columns[2], number_if)
    throughput_memch = find_measurements_ct(memchannel_df, test_result_columns[2], number_if)

    # Plot latencies values
    #latencies_plot(latency_pipes, latency_memch)

    # Plot throughputs values
    #throughputs_plot(throughput_pipes, throughput_memch)

    # Plot all values in one figure
    plots(latency_pipes, latency_memch,throughput_pipes, throughput_memch)

    # Show plot
    #plt.show()