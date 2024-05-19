echo "[INFO] Set environment variables for" $2 "sample"
source /opt/intel/oneapi/setvars.sh

echo "[INFO] Configure the build for" $2 "sample"
# Move to the sample directory
cd $1
mkdir build
cd build
cmake  -DFPGA_DEVICE=/home/spena/oneapi-asp/n6001:ofs_n6001_iopipes ..          ## Da modificare

echo "[INFO] Compiling for emulation of" $2 "sample"
make fpga_emu

echo "[INFO] Run" $2 "sample"
./$2.fpga_emu

