# Intel oneAPI Base Toolkit
`Intel oneAPI Base Toolkit` (known as `Base Kit`) is an implementation of the oneAPI specification and provides tools and libraries for developing high-performance, data-centric applications across architectures<sup>[[1]](references.md#ref_base_kit)</sup>.

<p align="center">
  <img src="img/img_base_kit.png" width="600">
  <!-- 
  <em>image_caption</em> -->
</p>



## oneAPI <a name="ch_oneapi"></a>
`oneAPI` is a multi-architecture cross-indutry open standard `programming model`<sup>[[2]](references.md#ref_oneapi)</sup> , which guarantees portability and performance across `heterogeneous architectures` (CPUs, GPUs, FPGAs, etc...).

A oneAPI platform<sup>[[]](references.md#ref_oneapi_arch)</sup> includes:
* `Host`: Tipically a multi-core CPU. It runs the `host Application`.
* `Devices`: One or more accelerators, each of them has a `command queue`. A device runs a `function Object` (or `kernel`), which contains a function definition and its related variables. In order to run a kernel on the device, the host application submit a command group, with the kernel, to the device's command queue.

oneAPI is an implementation of `Khronos SYCL 2020 Specification`<sup>[[]](references.md#ref_oneapi_sycl)</sup>, which is a royalty-free proramming launguage based on `ISO C++` and an evolution of `OpenCL`<sup>[[]](references.md#ref_sycl)</sup>.

`SYCL` provides an abstraction and APIs:
* To programm both CPUs and accelerator devices, using at least `C++ 17`.
* To manage data resources.
* To launch parallel code on the devices.
* To mix both `host code (executed on the host)` and `device code (executed on the device)` in the same source file<sup>[[]](references.md#ref_oneapi_sycl)</sup>.



## Intel oneAPI ASP <a name="ch_oneapi_asp"></a>
`oneAPI Accelerator Support Package (ASP)`<sup>[[]](references.md#ref_oneapi_asp_ref)</sup> is used to ensure communication between [hardware circuit](#glos_hardware_cir) with the oneAPI runtime and FPGA board peripherals. It is equivalent to a [Board Support Package (BSP)](#glos_bsp).

ASP is comprised of:
* `Hardware Components`: Enable the hardware circuit to communicate with the host processor. The hardware components are divided into:
  * `RTL Components`: Represent interface logic (host to kernel interface, etc..) to handle kernel control signals and perform Direct Memory Access (DMA).
  * `XML Files`: To describe hardware interfaces and compilation environment.
  * `Scripts`: To control compile flow.
* `Software Components`: Enable the runtime to identify and communicate with the kernel. The software components are divided into:
  * `Memory Mapped Device (MMD) Layer`: Used by the host and oneAPI runtime to communicate with the oneAPI kernel and other oneAPI ASP hardware registers.
  * `oneAPI ASP Utilities`: Used to setup and diagnose the board.

Both ASP hardware components and kernels are placend in the [Accelerator Functional Unit region (AFU)](#glos_afu), Which in turn is placed inside the [Open FPGA Stack (OFS)](#glos_ofs) Hardware.

<p align="center">
  <img src="img/img_HLD_IntelOFS_Model.png" width="550">
</p>



## Pipes <a name="ch_pipes"></a>
A `pipe` is an `unidirectional FIFO data structure` and allows comunication between two `endpoints`, an endpoint can be a kernel or an external I/O on the FPGA<sup>[[]](references.md#ref_pipes_sample)</sup>. There are three types of pipes:
* Kernel-Kernel
* Kernel-I/O
* I/O-Kernel

Into a pipe the data flows in a single direction, so the `bidirectional comunication` is obtained through two pipes. Through the pipe, kernels that exchange data can run concurrently. 

The communication takes place through `read and write operations`, they can be:
* `Blocking`: It may not return immediately but are always successful.
* `Non-blocking`: It takes an extra boolean parameter that is set to true if the operation happened successfull

The `n` consecutive writes (without performing any reads) is defined by a `configurable capacity parameter`, the pipe is `full` if the `n` is equal to the parameter. If a write is performed with a full pipe, two cases can occur:
* With a blocking operation, it does not return until a read is performed by the other endpoint. Once the read is performed, the write takes place.
* With a non-blocking operation, it returns immediately (boolean parameter is set to false), the write does not have an effect.

The same goes for a read performed with an empty pipe.


## Unified Shared Memory (USM) <a name="ch_usm"></a>
* USM (vedi paragrafo 4.8 https://registry.khronos.org/SYCL/specs/sycl-2020/html/sycl-2020.html#_device_allocation_functions)
    * Explicit copy is needed to transfer data 


## Glossary <a name="ch_glossary"></a>
* <a id="glos_bsp"></a>`BSP`: Consists of software layers and an FPGA hardware scaffold design that makes it possible to target the FPGA through the Intel oneAPI DPC++/C++ Compiler<sup>[[]](references.md#ref_bsp)</sup>.
* <a id="glos_hardware_cir"></a>`Hardware Circuit`: It is generated by the oneAPI compiler from a SYCL kernel (FPGA application code), it is also known as `kernel system`<sup>[[]](references.md#ref_oneapi_asp_ref)</sup>.
* <a id="glos_afu"></a>`AFU`: Hardware Accelerator implemented in FPGA logic which offloads a computational operation for an application from the CPU to improve performance<sup>[[]](references.md#ref_oneapi_asp_ref)</sup>.
* <a id="glos_ofs"></a>`OFS`: A modular collection of hardware platform components, open source software, and broad ecosystem support that provides a standard and scalable model for AFU and software developers to optimize and reuse their designs.<sup>[[]](references.md#ref_oneapi_asp_ref)</sup>.