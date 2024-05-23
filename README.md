# Comparison between two comunication mechanisms used to transfer data between SYCL kernels on Intel FPGAs
The project aims at analysing and evaluating the implementation of `two comunication mechanisms` used to transfer data between `SYCL kernels on Intel FPGAs`, targeting the `oneAPI Accelerator Support Package (ASP)`. The project performs different test cases: given `indipendent factors`, it measures the `response variables`.

The comunication mechanisms are:
* `Pipe` which implements pipe abstraction.
* `Unified Shared Memory (USM) device allocation` explicit data movement to and from the FPGA DDR.

Instead, the ASP variant is `ofs_n6001_usm_iopipes`<sup>[[1]](doc/references.md#ref_asp)</sup> that supports both shared virtual memory between host and device and pipes interfaces for the kernel system.


## Repository Structure 
The project has the following strcuture:
* `doc folder`: Contains the project documentation
* `impl floder`: Contains all the source files

## Table of Contents
1. [Intel oneAPI Base Toolkit](doc/intel_oneAPI.md)
    * [oneAPI](doc/intel_oneAPI.md#ch_oneapi)
    * [Intel oneAPI ASP](doc/intel_oneAPI.md#ch_oneapi_asp)
    * [Pipes](doc/intel_oneAPI.md#ch_pipes)
    * [Unified Shared Memory Device Allocation](doc/intel_oneAPI.md#ch_usm)
    * [Intel oneAPI FPGA Development Flows](doc/intel_oneAPI.md#ch_fpga_flow)
1. [Architectural Diagram](doc/arch_diagram.md)
    * [Diagram Legend](doc/arch_diagram.md#ch_diagram_l)
    * [Modules Description](doc/arch_diagram.md#ch_modules)
    * [Standards](doc/arch_diagram.md#ch_standards)
1. [Environment Setup](doc/setup.md)
    * [Tools](doc/setup.md#ch_tools)
    * [Manage oneAPI Samples](doc/setup.md#ch_samples)
1. [Implementation in Detail](impl/README.md)
    * [Project Structure](impl/README.md#ch_pr_struct)
    * [How to Run](impl/README.md#ch_run)
    * [Control Flow](impl/README.md#ch_flow_control)
1. [Troubleshooting](doc/troubleshooting.md)
1. [References](doc/references.md)
    * [Further References](doc/references.md#fref)


# Cose da fare
* Progettare gli esperimenti
    * Confronto tra meccanismi di comunicazione tra kernel producer e consumer 
        * Pipe
        * Memoria device --> i dati sono inviati usando la memoria del device
    * Fattori
        * dimensioni del pacchetto
    * Variabili di risposta
        * latenza (numero di pacchetti) /throughput (numero di pacchetti/s)
* Fare gli esperimenti

* Vedere nell'RTL generato (ProducerConsumerPipedId) come sono implementate le interfacce (producer,consumer e pipe) e sviluppare un diagramma 

## Note
* tipo pacchetto con un solo parametro (array) --> volta per volta posso ridefinire
    * 2/3 dimenioni
* malloc_device per allocare alloca il buffer
    * buffer condiviso tra i due kernel