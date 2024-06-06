###############
# Args legend #
###############
# $1 = sample path
# $2 = path to oneAPI ASP
# $3 = board variant

################
# Pipes sample #
################
echo "[INFO] Configure the build for pipes sample"
# Move to the sample directory
cd $1/pipes
mkdir -p build 
cd build 
cmake .. -DFPGA_DEVICE=$2:$3

echo "[INFO] Compile the design for pipes sample"
make fpga_emu 
make report
make fpga

#########################
# Memory channel sample #
#########################

echo "[INFO] Configure the build for memory_channel sample"
cd $1/memory_channel
mkdir -p build 
cd build 
cmake .. -DFPGA_DEVICE=$2:$3

echo "[INFO] Compile the design for memory_channel sample"
make fpga_emu CXX_DEFINES=-DMALLOC_HOST
make report CXX_DEFINES=-DMALLOC_HOST
make fpga CXX_DEFINES=-DMALLOC_HOST
