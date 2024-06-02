###############
# Args legend #
###############
# $1 = sample path
# $2 = path to oneAPI ASP
# $3 = board variant

echo "[INFO] Configure the build"
# Move to the sample directory
cd $1
mkdir build 
cd build 
cmake .. -DFPGA_DEVICE=$2:$3

#### NOTE ####
# Some samples do not support targeting an explicit FPGA board variant and BSP, so use
# cmake ..
############à


echo "[INFO] Compile the design"
# Compiling for emulation
#make fpga_emu
# Compiling for FPGA hardware
make fpga