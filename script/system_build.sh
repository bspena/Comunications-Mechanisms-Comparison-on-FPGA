echo "[INFO] Configure the build system"
mkdir build
cd build
cmake  -DFPGA_DEVICE=/home/spena/oneapi-asp/n6001:ofs_n6001_iopipes ..          ## Da modificare

###### Da modificare
echo "[INFO] Compile for emulation"
make fpga_emu