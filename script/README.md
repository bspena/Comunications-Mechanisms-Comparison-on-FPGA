# Script in Detail

* USM (vedi paragrafo 4.8 https://registry.khronos.org/SYCL/specs/sycl-2020/html/sycl-2020.html#_device_allocation_functions)
    * Explicit copy is needed to transfer data 

* ofs_n6001_iopipes: DMA-based ASP that supports local memory, host memory, and HSSI/IO Pipes interfaces for the kernel system.


## Script Structure <a name="script_struc"></a>
The Test Cases Script has 5 different files :
* `oneapi_test.py` : Python "main" script.
* `oneapi_test_utils.py` : Python file which holds the functions implementations.
* `oneapi_test_config.py` : Python file which holds the variables needed by the script.
* `system_build.sh` : Bash script which holds the line commnds to stop and start the hadoop cluster.
* `test_list.csv` : CSV file which holds the configuration paramters.