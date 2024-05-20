###############
# Args legend #
###############
# $1 = sampla name
# $2 = sample path
# $3 = path to oneAPI ASP
# $4 = board variant

echo "[INFO] Set environment variables for" $1 "sample"
source /opt/intel/oneapi/setvars.sh

echo "[INFO] Configure the build for" $1 "sample"
# Move to the sample directory
cd $2
mkdir build 
cd build 
cmake  -DFPGA_DEVICE=$3:$4 ..          ## Da modificare

#### NOTE ####
# Some samples do not support targeting an explicit FPGA board variant and BSP, so use
# cmake ..
############à


echo "[INFO] Compiling for emulation of" $1 "sample"
make fpga_emu

echo "[INFO] Run" $1 "sample"
./$1.fpga_emu

