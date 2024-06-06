###############
# Args legend #
###############
# $1 = sample path
# $2 = path to oneAPI ASP
# $3 = board variant

echo "[INFO] Configure the build for pipes sample"
# Move to the sample directory
cd $1/pipes
mkdir build 
cd build 
cmake .. -DFPGA_DEVICE=$2:$3

#### NOTE ####
# Some samples do not support targeting an explicit FPGA board variant and BSP, so use
# cmake ..
############à

echo "[INFO] Compile the design for pipes sample"
make fpga


echo "[INFO] Configure the build for memory_channel sample"
cd $1/memory_channel
mkdir build 
cd build 
cmake .. -DFPGA_DEVICE=$2:$3

echo "[INFO] Compile the design for memory_channel sample"
make fpga
