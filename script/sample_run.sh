###############
# Args legend #
###############
# $1 = path to setvars.sh (set environment variables)
# $2 = sample path
# $3 = sample name

echo "[INFO] Set environment variables"
source $1 

# Move to the sample directory
cd $2
cd build

echo "[INFO] Run sample"
./$3.fpga_emu