# Comparison between two comunication mechanisms used to transfer data between SYCL kernels on Intel FPGAs
The project aims at analysing and evaluating the implementation of `two comunication mechanisms`:
* `Pipe`
* `Unified Shared Memory (USM) device allocation`

used to transfer data between `SYCL kernels on Intel FPGAs`, targeting the `oneAPI Accelerator Support Package (ASP)`.

## Repository Structure 
The project has the following strcuture:
* `doc folder`: Contains the project documentation
* `impl floder`: Contains the project source files

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
    * [How to Run](impl/README.md#ch_run)
    * [Python Script Control Flow](impl/README.md#ch_flow_control)
1. [References](doc/references.md)
    * [Further References](doc/references.md#fref)