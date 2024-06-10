# ASP Architecture Analysis and Comparison between two data movement mechanisms between SYCL kernels on Intel FPGAs
The project aims to analysing the ASP architecture and evaluating the implementation of `two data movement mechanisms`:
* `Pipe`
* `Unified Shared Memory (USM) device allocation`

used to transfer data between `SYCL kernels on Intel FPGAs`, targeting the `oneAPI Accelerator Support Package (ASP)`.

## Repository Structure 
The project has the following strcuture:
* `doc folder`: Contains the project documentation.
* `impl floder`: Contains the project source files.

## Table of Contents
1. [Open FPGA Stack ](doc/ofs.md)
    * [oneAPI](doc/ofs.md#ch_oneapi)
    * [Accelerator Functional Unit](doc/ofs.md#ch_oneapi_afu)
        * [oneAPI Accelerator Support Package](doc/ofs.md#ch_oneapi_asp)
1. [oneAPI Samples](doc/samples.md)    
    * [Pipes](doc/samples.md#ch_pipes)
        * [Pipes Sample](doc/samples.md#ch_pipes_s)
    * [Unified Shared Memory](doc/samples.md#ch_usm)
        * [Memory Channel Sample](doc/samples.md#ch_usm_s)
1. [Architectural Diagram](doc/arch_diagram.md)
    * [Diagram Legend](doc/arch_diagram.md#ch_diagram_l)
    * [Modules Description](doc/arch_diagram.md#ch_modules)
    * [Standards](doc/arch_diagram.md#ch_standards)
1. [Environment Setup](doc/setup.md)
    * [Tools](doc/setup.md#ch_tools)
    * [Manage oneAPI Samples](doc/setup.md#ch_samples)
1. [Experiments](doc/experiments.md)
1. [References](doc/references.md)
    * [Further References](doc/references.md#fref)


# Cose da fare
* Aggionare documentazione/wiki
* Aggiustare diagramma arhcitetturale