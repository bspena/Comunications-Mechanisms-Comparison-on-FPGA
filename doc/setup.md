# Environment Setup

Virtual machine running `Ubuntu 22.04 LTS` :
  * 8 GB of RAM 
  * 6 cores
  * 150 GB of memory

## Tools <a name="ch_tools"></a>
### Intel oneAPI BAse Toolkit 2024.0.1
* [Download](https://registrationcenter-download.intel.com/akdlm/IRC_NAS/163da6e4-56eb-4948-aba3-debcec61c064/l_BaseKit_p_2024.0.1.46.sh)
* Install<sup>[[12]](references.md#ref_intel_install)</sup>:
```bash
sudo sh ./l_BaseKit_p_2024.0.1.46.sh -a --silent --eula accept
```

### OneAPI ASP OFS 2023.2-1
```bash
git clone --branch ofs-2023.2-1 https://github.com/OFS/oneapi-asp.git
```

### PR-tree template for n6001
* [Download](https://github.com/OFS/ofs-agx7-pcie-attach/releases/download/ofs-2023.2-1/pr_template-n6001.tar.gz)

### Python Modules
* Python 3.10.12
* pip 22.0.2
* pandas 2.2.2

### CMake
```bash
sudo apt install cmake
```

## Manage oneAPI Samples <a name="ch_samples"></a>
* Clone samples repository<sup>[[13]](references.md#ref_oneapi_asp_get)</sup>:
```bash
git clone --branch 2024.0.0 https://github.com/oneapi-src/oneAPI-samples.git
```
* Build the program:
```bash
source /opt/intel/oneapi/setvars.sh         # Set environment variables (on every new terminal window)
cd path-to-sample-location
mkdir build
cd build
cmake .. -DFPGA_DEVICE=full-path-to-oneapi-asp/platform-name:board_variant
```
>[!NOTE]
> Some samples do not support targeting an explicit FPGA board variant and BSP. In order to build the program for Intel Agilex 7 device family
>```bash
> cmake ..
>```

* Compile samples:
```bash
make fpga_emu     # Compiling for emulation
make fpga         # Compiling for FPGA hardware
make report
```

* Run samples:
```bash
./sample_name.fpga_emu    # Run for emulation
./sample_name.fpga        # FPGA hardware
```

* Generate the report:
```bash
make report
```
and read it bu opening `report.html` (with Mozilla Firefox) located in the `path-to-sample-location/build/pipes_report.prj/reports`.