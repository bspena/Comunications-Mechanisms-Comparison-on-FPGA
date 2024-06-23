# Overall Stack 
The overall `stack` is divided into:
* `Software Layer` which containts
  * The `software application`.
  * The open standard `oneAPI`.
  * The `Open FPGA Stack Software Components`.
* `Hardware Layer` which containts the `Open FPGA Stack Hardware Components`.

<p align="center">
  <img src="img/stack_sw_hw.png" width="500">
</p>


# Open FPGA Stack <a name="ch_ofs"></a>
The `Open FPGA Stack (OFS)`<sup>[[1]](references.md#ref_oneapi_asp_ref)</sup> is a set of `hardware platform components` and `open source software`, ensuring a standard and scalable model for AFU and software developers to optimize and reuse their designs.


## Accelerator Functional Unit <a name="ch_afu"></a>
The `Accelerator Functional Unit (AFU)`<sup>[[1]](references.md#ref_oneapi_asp_ref)</sup>  is a hardware accelerator implemented in FPGA logic which offloads a computational operation for an application from the CPU to improve performance. 

### Accelerator Support Package <a name="ch_asp"></a>
The `Accelerator Support Package (ASP)`<sup>[[1]](references.md#ref_oneapi_asp_ref)</sup>  is a set of hardware and software components which guarantees the comunication between `oneAPI kernel` (converted into a hardware circuit by the compiler) and the `oneAPI runtime` and `other OFS hardware/software components`. The ASP is equivalent to a `Board Support Package (BSP)`<sup>[[2]](references.md#ref_bsp)</sup>, which is a set of software layers and an FPGA hardware design used to target the FPGA through the Intel oneAPI DPC++/C++ Compiler.

ASP is made up of:
* `RTL Components`: Represent interface logic (host to kernel interface, etc..) to handle kernel control signals and perform Direct Memory Access (DMA).
* `XML Files`: To describe hardware interfaces and compilation environment.
* `Scripts`: To control compile flow.
* `Utilities`: Used to setup and diagnose the board.

Both ASP hardware components and kernels are placend in the `AFU region`. 
