# oneAPI

## Introduction <a name="ch_intro"></a>
`oneAPI` is a multi-architecture cross-indutry open standard `programming model`<sup>[[1]](references.md#ref_oneapi)</sup> , which is based on `data parallelism` (the same computation is performed on each data element)<sup>[[2]](references.md#ref_oneapi_intro)</sup>. This programming model guarantees portability and performance across `heterogeneous processors and accelerators` (CPUs, GPUs, FPGAs, etc...), bringing all of them on a common ground.

<p align="center">
  <img src="img/img_oneapi_architecture.png" width="600">
</p>

oneAPI provides<sup>[[3]](references.md#ref_oneapi_sarch)</sup>: 
* Direct Programming (Data Parallel C++), where the application programmer writes the parallel algorithm.
* Libraries related to different domains (linear algebra, machine learning, video processing, etc..). 
* Analysis and Debug tools.


## oneAPI Platform <a name="ch_oneapi_platform"></a>
A `oneAPI platform`<sup>[[3]](references.md#ref_oneapi_sarch)</sup> contains on the hardware side:
* `Host`: Tipically a multi-core CPU, which can be seen as a device by the software. 
* `Devices`: One or more accelerators, each of them has an `command queue`. 

On the software side:
* `Host Application`: It uses oneAPI and runs on the host.
* `Function Object (or Kernel)`: It contains a function definition and its related variables. In order to run a kernel on the device, the host application submit a `command group`, with the kernel, to the device's command queue. 

The host application and kernels communicate through differnt types of `shared memory` and synchronize through events.


## Level Zero <a name="ch_oneapi_lzero"></a>
`oneAPI Level Zero`<sup>[[4]](references.md#ref_oneapi_lzero)</sup><sup>[[5]](references.md#ref_oneapi_lzero_spec)</sup> provides a `low-level direct-to-metal interfaces` related to the oneAPI platform devices and supports differnt language features (function pointers, I/O capabilities, etc...).

<p align="center">
  <img src="img/img_oneapi_stack_det.png" width="650">
</p>

Level Zero `core API` provides the lowest-level and fine-grain control over<sup>[[5]](references.md#ref_oneapi_lzero_spec)</sup>:
* Device discovery and partitioning
* Memory allocation, visibility and caching
* Kernels execution and scheduling
* Synchronization primitives
* Etc...

`Level Zero API architecture` displays:
* Physical Abstractions for device, sub-device, and memory.
* Logical Abstractions for command queues, events, and synchronization methods (related to to device-level physical capabilities).


## SYCL <a name="ch_sycl"></a>
oneAPI is an implementation of `Khronos SYCL 2020 Specification` and `SYCL extensions` (to add more functionality)<sup>[[6]](references.md#ref_oneapi_sycl)</sup>. SYCL is a proramming launguage based on `ISO C++` and an evolution of `OpenCL`. 

SYCL provides an abstraction and APIs<sup>[[6]](references.md#ref_oneapi_sycl)</sup><sup>[[7]](references.md#ref_sycl)</sup> :
* To programm both CPUs and accelerator devices (using at least C++ 17).
* To manage data resources.
* To launch parallel code on the devices.
* To mix both `host code` and `device code` in the same source file.

<p align="center">
  <img src="img/img_sycl_diagram.png" width="650">
</p>