# oneAPI
`oneAPI`<sup>[[1]](references.md#ref_oneapi)</sup> is an open standard, adopted by `Intel`, which defines an `unified programmig model` for different processors and accelerator architectures by bringing all the devices on a common ground.

<p align="center">
  <img src="img/oneapi_stack.png" width="300">
</p>

In this way code can be re-used and tools can work across the different architectures, no matter what kind of applications, workloads, middlware and frameworks are used. 

oneAPI provides: 
* Libraries related to different domains (linear algebra, machine learning, etc..). 
* Support for languages (DPC++/C++,Fortran) and their compilers.
* Analysis and Debug tools.


## oneAPI Level Zero <a name="ch_oneapi_lzero"></a>
oneAPI includes `Level Zero`<sup>[[2]](references.md#ref_oneapi_lzero)</sup>, a low level hardware abstraction layer inside the software stack, which provides a direct-to-metal interfaces to accelerator devices.

<p align="center">
  <img src="img/img_oneapi_stack.png" width="650">
</p>

This layer core APIs provide the lowest-level and fine-grain control over:
* Device Discovery and Partitioning.
* Memory Allocation, Visibility and Caching.
* `Kernels (programs runnging on the accelerators)` Execution and Scheduling.
* Peer-to-Peer Communication.
* Inter-Process Sharing.


## oneAPI Runtime <a name="ch_oneapi_runtime"></a> (da aggiustare)
`oneAPI runtime`, namely Accelerator Support Stack (ASP), basically is a BSP for a given board, supporting a subset of all the SYCL features.

## oneAPI and SYCL <a name="ch_sycl"></a>
oneAPI is the implementation of `SYCL`<sup>[[]](references.md#ref_sycl)</sup>, which is a cross-platform abstraction layer and an evolution of `OpenCL`.

SYCL provides an abstraction and APIs :
* To programm `heterogeneous processors` (CPUs, GPUs, FPGAs, etc...) using `standard ISO C++` (at least C++ 17).
* To find processors on which code can be executed.
* To manage data resources and code execution on those processors.
* To use those processors in a single application; so, in the same source file, are mixed both CPUs code (known as `host code`) and a accelerators code (known as `device code`).

<p align="center">
  <img src="img/" width="650">
</p>


## I/O Pipes <a name="ch_iopipe"></a> (da aggiustare)
<sup>[[]](references.md#ref_iopipe)</sup>
