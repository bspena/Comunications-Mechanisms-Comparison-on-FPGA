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
    * [oneAPI Samples](doc/setup.md#ch_samples)
1. [Script in Detail](script/README.md)
1. [Troubleshooting](doc/troubleshooting.md)
1. [References](doc/references.md)
    * [Further References](doc/references.md#fref)
        * [Documentation](doc/references.md#fref_doc)
        * [SystemVerilog Modules/Interfaces](doc/references.md#fref_sv)


# Cose da fare
* Inserire inserimento risultati nel file test_result.csv anche nell'esempio pipe
    * Gestire path del file test_result.csv con i risulatati, facendo passando il path all'eseguibile

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
* Esempio paragrafo 4.8 (https://registry.khronos.org/SYCL/specs/sycl-2020/html/sycl-2020.html#_device_allocation_functions)