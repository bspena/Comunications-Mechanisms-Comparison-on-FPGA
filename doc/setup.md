# Environment Setup

Virtual machine running `Ubuntu 22.04 LTS` :
  * 8 GB of RAM 
  * 6 cores
  * 150 GB of memory

## Tools <a name="ch_tools"></a>
### Intel oneAPI BAse Toolkit 2024.0.1
* [Download l_BaseKit_p_2024.0.1.46.sh](https://registrationcenter-download.intel.com/akdlm/IRC_NAS/163da6e4-56eb-4948-aba3-debcec61c064/l_BaseKit_p_2024.0.1.46.sh)
* Install<sup>[[]](references.md#ref_intel_install)</sup>
```bash
sudo sh ./l_BaseKit_p_2024.0.1.46.sh -a --silent --eula accept
```

### OneAPI ASP OFS 2023.2-1
```bash
git clone --branch ofs-2023.2-1 https://github.com/OFS/oneapi-asp.git
```

### PR-tree template for n6001
* [Download](https://github.com/OFS/ofs-agx7-pcie-attach/releases/download/ofs-2023.2-1/pr_template-n6001.tar.gz)

## Set Environment Variables 
```bash
source /opt/intel/oneapi/setvars.sh
```

> [!NOTE]
> It affects the current shell and its children, not the parent.


## Samples (da modificare)
* Clone repository
```bash
git clone --branch 2024.0.0 https://github.com/oneapi-src/oneAPI-samples.git
```
*
```bash
source /opt/intel/oneapi/setvars.sh
cd path-to-sample-location
mkdir build
cd build
cmake -DFPGA_DEVICE=/home/spena/oneapi-asp/n6001:ofs_n6001 ..
make
```