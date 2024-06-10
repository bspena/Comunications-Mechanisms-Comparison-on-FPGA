## Pipes <a name="ch_pipes"></a>
A `pipe`<sup>[[]](references.md#ref_pipes_sample)</sup> is an `unidirectional FIFO data structure` and allows comunication between two `endpoints`, an endpoint can be a kernel or an external I/O on the FPGA. There are three types of pipes:
* Kernel-Kernel
* Kernel-I/O
* I/O-Kernel

Into a pipe the data flows in a single direction, so the `bidirectional comunication` is obtained through two pipes. Through the pipe, kernels that exchange data can run concurrently. 

The communication takes place through `read and write operations`, they can be:
* `Blocking`: Operations may not return immediately but are always successful.
* `Non-blocking`: Operations takes an extra boolean parameter that is set to true if the operation happened successfull.

The `n` consecutive writes (without performing any reads) is defined by a `configurable capacity parameter`, the pipe is `full` when the number of consecutive writes executed is equal to n. If a write is performed with a full pipe, two cases can occur:
* With a blocking operation, it does not return until a read is performed by the other endpoint. Once the read is performed, the write takes place.
* With a non-blocking operation, it returns immediately (boolean parameter is set to false), the write does not have an effect.

The same goes for a read performed with an empty pipe.


<p align="center">
  <img src="img/img_pipes_model.png" width="550">
  <em>image_caption</em>
</p>


## Unified Shared Memory Allocation <a name="ch_usm"></a>
The `Unified Shared Memory (USM)`<sup>[[]](references.md#ref_explicit_sample)</sup> provides a C/C++ pointer-based memory management interfaces in SYCL. 

USM provides three types of allocations:
* `Device allocation`: Allocates device memory through `malloc_device` and is only accessible from the device.
* `Host allocation`: Allocates host memory through `malloc_host`. The pointer given to the FPGA actually lives in the host DDR, but the BSP implements the necessary functionalities to be able to read directly in this memory.
* `Shared allocation`: Allocates shared memory through `malloc_shared`. The memory can live on the host or on the FPGA and may be moved at runtime between the host and device depending on the memory access pattern.

With USM allocation, the programmer explicitly:
* Copies data to or from the FPGA DDR using `SYCL memcpy function`.
* Manages the `synchronization between kernels` accessing the same device pointers using `wait function of a SYCL event` or the `depends_on signal` between events.


<p align="center">
  <img src="img/img_memch_model.png" width="550">
  <em>image_caption</em>
</p>


### ???
Each sample implements the comunication between `SYCL Producer and Consumer kernels`. Each kernel uses:

* `kernel_args_restrict attribute`<sup>[[]](../doc/references.md#ref_karg_sample)</sup> to improve kernel performance by enabling more aggressive compiler optimizations.