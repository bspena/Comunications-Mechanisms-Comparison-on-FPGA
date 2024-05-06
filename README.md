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
1. [Architectural Diagram](doc/arch_diagram.md)
    * [Diagram Legend](doc/arch_diagram.md#ch_diagram_l)
    * [Modules Description](doc/arch_diagram.md#ch_modules)
    * [Standards](doc/arch_diagram.md#ch_standards)
1. [Environment Setup](doc/setup.md)
    * [Tools](doc/setup.md#ch_tools)
1. [Troubleshooting](doc/troubleshooting.md)
1. [References](doc/references.md)
    * [Further References](doc/references.md#fref)
        * [Documentation](doc/references.md#fref_doc)
        * [SystemVerilog Modules/Interfaces](doc/references.md#fref_sv)


# Cose da fare
* Setup macchina virtuale
* Valutare le differenze con la versione no-pipes, l'obiettivo è costruire una comprensione di quali sono i componenti hardware necessari per implementare le pipe.


# Dubbi 
* In https://ofs.github.io/ofs-2023.2/hw/common/user_guides/oneapi_asp/ug_oneapi_asp/#26-compile-and-run-oneapi-sample-applications, ogni bolta che eseguo un comando cmake il contenuto della cartella build viene sovrascritto ?