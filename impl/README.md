# Implementation in Detail

* ofs_n6001_iopipes: DMA-based ASP that supports local memory, host memory, and HSSI/IO Pipes interfaces for the kernel system.

* [[intel::kernel_args_restrict]] kernel attribute, which should be applied anytime you can guarantee that kernel arguments do not alias. This attribute enables more aggressive compiler optimizations and often improves kernel performance on FPGA.
