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

* afu.sv --> riga 26
* afu.sv --> riga 144


# Convenzioni Interfacce
* to_sink (to_slave): sta per master to slave, il modulo corrente è il master quindi l'interfaccia è di uscita
* to_source: sta per slave to master, il modulo corrente è lo slave quindi l'interfaccia è d'ingresso
* Identificare master/source/host e slave/sink/agent:
  *  Il master ha sempre read, write, writedata e address come output per dire allo slave cosa fare, cosa scrivere ed a che indirizzo.
  * Lo slave ha come output sempre waitrequest, readdatavalid, readdata, writeresponsevalid per le risposte ai segnali di cui sopra.
* In OFS e ASP, esiste una variante con "split read and write channel". Potresti trovare gli stessi segnali di un bus Avalon MM normale, ma replicati per due canali. Un canale di sola lettura (rd) e l'altro di sola scrittura (wr). Ovviamente il canale "rd" non avrà segnali per le scritture, e.g. write, writedata e writeresponsevalid, dato che non potrà usarli. Lo stesso vale per il canale "wr", che non avrà i segnali relativi alle scritture.