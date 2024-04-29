# I/O Pipes for SYCL Kernels on Intel FPGAs oneAPI ASP
This project aims at analysing and evaluating the implementation of `I/O Pipes for SYCL Kernels on Intel FPGAs oneAPI ASP` and it is devided into three steps:
* Setup a local environment.
* Run a I/O Pipes example in emulation.
* Explore the undelying implementation of IO Pipes in the BSP's RTL.

## Table of Contents
1. [Intel oneAPI Base Toolkit](doc/intel_oneAPI.md)
    * [oneAPI](doc/intel_oneAPI.md#ch_oneapi)
    * [Intel oneAPI FPGA Development Flows](doc/intel_oneAPI.md#ch_fpga_flow)
    * [Intel oneAPI ASP](doc/intel_oneAPI.md#ch_oneapi_asp)
    * [I/O Pipes](doc/intel_oneAPI.md#ch_pipes)
    * [Glossary](doc/intel_oneAPI.md#ch_glossary)
1. [Environment Setup](doc/setup.md)
    * [Tools](doc/setup.md#tool)
1. [Troubleshooting](doc/troubleshooting.md)
1. [References](doc/references.md)
    * [Further References](doc/references.md#fref)



# Cose da fare
* Diagramma architetturale dei moduli:
    * top-level module afu (https://github.com/OFS/oneapi-asp/blob/ofs-2023.2-1/n6001/hardware/ofs_n6001_iopipes/build/rtl/afu.sv)
    * bsp_logic
    * kernel_wrapper
    * mem_if_vtp