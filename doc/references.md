# References
1. <a id="ref_base_kit"></a> [Intel oneAPI Base Toolkit](https://www.intel.com/content/www/us/en/developer/tools/oneapi/base-toolkit.html)
1. <a id="ref_oneapi"></a> [Why oneAPI?](https://www.oneapi.io/)
1. <a id="ref_oneapi_arch"></a> [oneAPI Software Architecture](https://spec.oneapi.io/versions/latest/architecture.html)
1. <a id="ref_oneapi_sycl"></a> [SYCL](https://spec.oneapi.io/versions/latest/elements/sycl/source/index.html)
1. <a id="ref_sycl"></a> [What is SYCL?](https://www.khronos.org/sycl/)
1. <a id="ref_oneapi_asp_ref"></a> [oneAPI Accelerator Support Package(ASP) Reference Manual: Open FPGA Stack](https://ofs.github.io/ofs-2023.2/hw/common/reference_manual/oneapi_asp/oneapi_asp_ref_mnl/#14-introduction-to-oneapi-on-open-fpga-stackofs)
1. <a id="ref_bsp"></a> [FPGA BSPs and Boards](https://www.intel.com/content/www/us/en/docs/oneapi/programming-guide/2023-0/fpga-bsps-and-boards.html)
1. <a id="ref_pipes_sample"></a> [Pipes Samples](https://github.com/oneapi-src/oneAPI-samples/tree/2024.0.0/DirectProgramming/C%2B%2BSYCL_FPGA/Tutorials/Features/pipes)
1. <a id="ref_intel_install"></a> [Intel oneAPI Toolkits and Components Installation Guide for Linux* OS with Command LIne](https://www.intel.com/content/www/us/en/docs/oneapi/installation-guide-linux/2023-0/install-with-command-line.html)
1. <a id="ref_oneapi_asp_get"></a> [oneAPI Accelerator Support Package (ASP): Getting Started User Guide](https://ofs.github.io/ofs-2023.2/hw/common/user_guides/oneapi_asp/ug_oneapi_asp/)
* <a id="ref_explicit_sample"></a> [Explicit Data Movement Sample](https://github.com/oneapi-src/oneAPI-samples/tree/ccd57a1ff0245bf7b09c2a0b84fa35bce9412d88/DirectProgramming/C%2B%2BSYCL_FPGA/Tutorials/DesignPatterns/explicit_data_movement)
* <a id="ref_kernel_sample"></a> [kernel_args_restrict Sample](https://github.com/oneapi-src/oneAPI-samples/tree/2024.0.0/DirectProgramming/C++SYCL_FPGA/Tutorials/Features/kernel_args_restrict)
* https://www.intel.com/content/www/us/en/docs/oneapi/optimization-guide-gpu/2023-1/unified-shared-memory-allocations.html


## Further References <a name="fref"></a>
### Documentation <a name="fref_doc"></a>
* [SYCL 2020 Specification ](https://registry.khronos.org/SYCL/specs/sycl-2020/html/sycl-2020.html)
* [oneAPI DPC++ Compiler and Runtime architecture design](https://intel.github.io/llvm-docs/design/CompilerAndRuntimeDesign.html)
* [Characteristics of Pipes](https://www.intel.com/content/www/us/en/docs/oneapi-fpga-add-on/optimization-guide/2023-1/characteristics-of-pipes.html)
* [Intel oneAPI FPGA Handbook](https://www.intel.com/content/www/us/en/docs/oneapi-fpga-add-on/developer-guide/2024-0/intel-oneapi-fpga-handbook.html)
* [OFS Doc Modules](https://github.com/OFS/ofs.github.io/blob/main/docs/hw/n6001/doc_modules/links.md)
* [Avalon Memory Mapped Interface Signal Roles](https://www.intel.com/content/www/us/en/docs/programmable/683091/20-1/memory-mapped-interface-signal-roles.html)
* [Buffer Accessor Modes](https://www.intel.com/content/www/us/en/docs/oneapi/optimization-guide-gpu/2023-0/buffer-accessor-modes.html)
* [Memory Attributes Sample](https://github.com/oneapi-src/oneAPI-samples/tree/2024.0.0/DirectProgramming/C++SYCL_FPGA/Tutorials/Features/memory_attributes)
* [Global Memory Channels](https://github.com/oneapi-src/oneAPI-samples/tree/2024.0.0/DirectProgramming/C%2B%2BSYCL_FPGA/Tutorials/Features/mem_channel)
* https://github.com/oneapi-src/oneAPI-samples/tree/master/DirectProgramming/C++SYCL_FPGA/Tutorials/DesignPatterns/zero_copy_data_transfer
* https://github.com/oneapi-src/oneAPI-samples/blob/ccd57a1ff0245bf7b09c2a0b84fa35bce9412d88/DirectProgramming/C%2B%2BSYCL_FPGA/ReferenceDesigns/qri/src/qri.hpp#L72
* https://github.com/oneapi-src/oneAPI-samples/blob/ccd57a1ff0245bf7b09c2a0b84fa35bce9412d88/DirectProgramming/C%2B%2BSYCL_FPGA/ReferenceDesigns/matmul/src/matmul.hpp#L71


### SystemVerilog Modules/Interfaces <a name="fref_sv"></a>
* [afu.sv](https://github.com/OFS/oneapi-asp/blob/ofs-2023.2-1/n6001/hardware/ofs_n6001_iopipes/build/rtl/afu.sv)
* [ofs_plat_avalon_mem_if.sv](https://github.com/OFS/ofs-platform-afu-bbb/blob/ofs-2023.2-1/plat_if_develop/ofs_plat_if/src/rtl/base_ifcs/avalon/ofs_plat_avalon_mem_if.sv)
* [mpf_vtp_svc_ofs_avalon_mem_rdwr.sv](https://github.com/OPAE/intel-fpga-bbb/blob/ofs-2023.2-1/BBB_mpf_vtp/hw/rtl/svc_shims/mpf_vtp_svc_ofs_avalon_mem_rdwr.sv)
* [mpf_vtp_translate_ofs_avalon_mem_rdwr.sv](https://github.com/OPAE/intel-fpga-bbb/blob/ofs-2023.2-1/BBB_mpf_vtp/hw/rtl/translate/mpf_vtp_translate_ofs_avalon_mem_rdwr.sv)