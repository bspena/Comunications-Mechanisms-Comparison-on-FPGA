###############
# Args legend #
###############
# $1 = path to setvars.sh (set environment variables)
# $2 = sample path
# $3 = path to oneAPI ASP
# $4 = board variant

echo "[INFO] Set environment variables"
source $1 

echo "[INFO] Configure the build"
# Move to the sample directory
cd $2
mkdir build 
cd build 
cmake .. -DFPGA_DEVICE=$3:$4

#### NOTE ####
# Some samples do not support targeting an explicit FPGA board variant and BSP, so use
# cmake ..
############à


echo "[INFO] Compiling"
# Compiling for emulation
make fpga_emu
# Compiling for FPGA hardware
#make fpga