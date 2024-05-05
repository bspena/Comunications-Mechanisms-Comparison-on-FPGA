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
  $ sudo sh ./l_BaseKit_p_2024.0.1.46.sh -a --silent --eula accept
  ```
  * Add path of the DPC++/C++ compiler to PATH environment variable
  ```bash 
  $ nano ~/.bashrc
  export PATH=$PATH:/opt/intel/oneapi/compiler/latest/bin
  $ source ~/.bashrc
   ```

### OneAPI ASP OFS 2023.2-1
* https://github.com/OFS/oneapi-asp/tree/ofs-2023.2-1

### PR-tree template for n6001
* [Download](https://github.com/OFS/ofs-agx7-pcie-attach/releases/download/ofs-2023.2-1/pr_template-n6001.tar.gz)
