# Comparison between two comunication mechanisms used to transfer data between SYCL kernels on Intel FPGAs
The project aims at analysing and evaluating the implementation of `two comunication mechanisms` used to transfer data between `SYCL kernels on Intel FPGAs`, targeting the `oneAPI Accelerator Support Package (ASP)`. The comunication mechanisms are:
* `Pipe` which implements pipe abstraction.
* `Unified Shared Memory (USM) device allocation` explicit data movement to and from the FPGA DDR.

## Repository Structure 
The project has the following strcuture:
* `doc folder`: Contains the project documentation
* `impl floder`: Contains all the source files
    * `pipes`: cpp source files with the pipe abstraction 
    * `memory_channel`: cpp source files with USM allocations
    * `python script`: python source files which manages the test automatization

## Table of Contents
1. [Intel oneAPI Base Toolkit](doc/intel_oneAPI.md)
    * [oneAPI](doc/intel_oneAPI.md#ch_oneapi)
    * [Intel oneAPI ASP](doc/intel_oneAPI.md#ch_oneapi_asp)
    * [Pipes](doc/intel_oneAPI.md#ch_pipes)
    * [Unified Shared Memory (USM)](doc/intel_oneAPI.md#ch_usm)
    * [Glossary](doc/intel_oneAPI.md#ch_glossary)
1. [Architectural Diagram](doc/arch_diagram.md)
    * [Diagram Legend](doc/arch_diagram.md#ch_diagram_l)
    * [Modules Description](doc/arch_diagram.md#ch_modules)
    * [Standards](doc/arch_diagram.md#ch_standards)
1. [Environment Setup](doc/setup.md)
    * [Tools](doc/setup.md#ch_tools)
    * [oneAPI Samples](doc/setup.md#ch_samples)
1. [Implementation in Detail](script/README.md)
1. [Troubleshooting](doc/troubleshooting.md)
1. [References](doc/references.md)
    * [Further References](doc/references.md#fref)
        * [Documentation](doc/references.md#fref_doc)
        * [SystemVerilog Modules/Interfaces](doc/references.md#fref_sv)


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