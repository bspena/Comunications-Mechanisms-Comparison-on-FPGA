# ASP Variants Architectures Analysis and Performance Comparison of Two Data Movement Mechanisms on Intel FPGAs
The project aims to:
* Analyse the architectures of two `oneAPI Accelerator Support Package (ASP) variants` and the data movement on them:
    * `ofs_n6001_iopipes`<sup>[[1]](references.md#ref_aspv_pipes)</sup>: ASP variant that supports `I/O Pipes abstraction`.
    * `ofs_n6001_usm_iopipes`<sup>[[2]](references.md#ref_aspv_usm_pipes)</sup>: ASP variant that supports both I/O Pipes abstraction and `Unified Shared Memory (USM)`.
* Compare the performance of `two data movement mechanisms`:
    * `Pipe`<sup>[[3]](references.md#ref_pipes_sample)</sup>
    * `USM`<sup>[[4]](references.md#ref_explicit_sample)</sup>

    used to transfer data between `SYCL kernels on Intel FPGAs`.


## Repository Structure 
The project has the following strcuture:
* `doc folder`: Contains the project documentation.
* `impl floder`: Contains the project source files.

## Table of Contents
1. [Overall Stack ](doc/ofs.md)
    * [Open FPGA Stack](doc/ofs.md#ch_ofs)
    * [Accelerator Functional Unit](doc/ofs.md#ch_afu)
        * [oneAPI Accelerator Support Package](doc/ofs.md#ch_asp)
1. [Data Movement Mechanisms](doc/samples.md)    
    * [Pipes Abstraction](doc/samples.md#ch_pipes)
        * [Pipes Sample](doc/samples.md#ch_pipes_s)
    * [Unified Shared Memory](doc/samples.md#ch_usm)
        * [Memory Channel Sample](doc/samples.md#ch_usm_s)
1. [Architectural Diagrams](doc/arch_diagram.md)
    * [ofs_n6001_iopipes ASP Variant](doc/arch_diagram.md#ch_iopipes_arch)
        * [Modules Description](doc/arch_diagram.md#ch_modules_iopipes)
    * [ofs_n6001_usm_iopipes ASP Variant](doc/arch_diagram.md#ch_usmiopipes_arch)
        * [Modules Description](doc/arch_diagram.md#ch_modules_usmiopipes)
    * [Terminology](doc/arch_diagram.md#ch_term)
1. [Environment Setup](doc/setup.md)
    * [Tools](doc/setup.md#ch_tools)
    * [Manage oneAPI Samples](doc/setup.md#ch_samples)
1. [Performance Analysis](doc/analysis.md)
1. [References](doc/references.md)
    * [Further References](doc/references.md#fref)