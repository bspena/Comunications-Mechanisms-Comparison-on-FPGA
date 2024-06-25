# Overall Stack 
The overall `stack` is divided into:
* `Software Layer`:
  * `Software application`.
  * `oneAPI`: A programming model that provides portability and performance across `heterogeneous architectures`.
  * `Open Programmable Acceleration Engine (OPAE) SDK`<sup>[[5]](references.md#ref_oneapi_asp_ref)</sup>: Set of libraries and tools to facilitate the development of software applications and accelerators.
  * `Kernel Driver`: Linux Kernerl Driver.
* `Hardware Layer`:
  * `PCIe`.
  * `FPGA Interface Manager (FIM)`<sup>[[5]](references.md#ref_oneapi_asp_ref)</sup>: Provides standard interfaces to host and AFU.
  * `Accelerator Functional Unit (AFU)`.

<p align="center">
  <img src="img/stack_sw_hw.png" width="500">
</p>


# Open FPGA Stack <a name="ch_ofs"></a>
The `Open FPGA Stack (OFS)`<sup>[[6]](references.md#ref_ofs)</sup> is a set of  `open-source hardware and software components` used to create a custom FPGA platform.

## Accelerator Functional Unit <a name="ch_afu"></a>
The `Accelerator Functional Unit (AFU)`<sup>[[5]](references.md#ref_oneapi_asp_ref)</sup> is a hardware accelerator implemented in FPGA logic which offloads a computational operation for an application from the CPU to improve performance. 

### oneAPI Accelerator Support Package <a name="ch_asp"></a>
The `oneAPI Accelerator Support Package (ASP)`<sup>[[5]](references.md#ref_oneapi_asp_ref)</sup>  is a set of hardware and software components which guarantees the comunication between `oneAPI kernel` (converted into a hardware circuit by the compiler) and the `oneAPI runtime` and `other OFS hardware/software components`. 

The ASP is equivalent to a `Board Support Package (BSP)`<sup>[[7]](references.md#ref_bsp)</sup>, which is a set of software layers and an FPGA hardware design used to target the FPGA through the Intel oneAPI DPC++/C++ Compiler.

ASP is made up of:
* `RTL Components`: Represent interface logic (host to kernel interface, etc..) to handle kernel control signals and perform Direct Memory Access (DMA).
* `XML Files`: To describe hardware interfaces and compilation environment.
* `Scripts`: To control compile flow.
* `Utilities`: Used to setup and diagnose the board.