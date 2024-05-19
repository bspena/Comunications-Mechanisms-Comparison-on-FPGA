echo "[INFO] Setting environment variables"
source /opt/intel/oneapi/setvars.sh

echo "[INFO] Configuring the build system 1"
# Change directory to the example
cd $1
mkdir build
cd build
cmake  -DFPGA_DEVICE=/home/spena/oneapi-asp/n6001:ofs_n6001_iopipes ..          ## Da modificare

echo "[INFO] Compiling for emulation 1"
make fpga_emu



