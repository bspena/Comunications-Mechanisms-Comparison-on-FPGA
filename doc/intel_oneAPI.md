# Intel oneAPI Base Toolkit
`Intel oneAPI Base Toolkit` (known as Base Kit)<sup>[[8]](references.md#ref_base_kit)</sup> is an implementation of the oneAPI specification and include a set of tools and libraries for developing high-performance applications across architectures. 

<p align="center">
  <img src="img/img_base_kit.png" width="600">
</p>


## oneAPI ASP <a name="ch_oneapi_asp"></a>
`oneAPI Accelerator Support Package (ASP)`<sup>[[9]](references.md#ref_oneapi_asp)</sup> is a collection of hardware and software components which guarantee the cominucation between oneAPI kernels and both oneAPI runtime and `Open FPGA Stack (OFS)` components. The hardware components of the ASP and the kernels are placend in the `Accelerator Functional Unit (AFU)` region.


## I/O Pipes <a name="ch_pipes"></a>
A `pipe` is an `unidirectional FIFO data structure` that allows comunication between two `endpoints`, which can be a kernel or an external I/O on the FPGA<sup>[[10]](references.md#ref_pipe)</sup>. 

There are three types of pipes:
* Kernel-kernel
* Kernel-I/O
* I/O-kerne

The communication takes place through `read and write operations`, they can be:
* `Blocking operation`: It may not return immediately but are always successful.
* `Non-blocking operation`: It takes an extra boolean parameter that is set to true if the operation happened successfull

Since the pipe is unidirectional, an endopoint performs the write operation and the other one performs read operation; instead, the `bidirectional comunication` is obtained through two pipes.

The `n` consecutive writes (without performing any reads) is defined by a `configurable capacity parameter`, the pipe is `full` if the `n` is equal to the parameter. If a write is performed with a full pipe, two cases can occur:
* With a blocking operation, it does not return until a read is performed by the other endpoint. Once the read is performed, the write takes place.
* With a non-blocking operation, it returns immediately (boolean parameter is set to false), the write does not have an effect.

The same goes for a read performed with an empty pipe.