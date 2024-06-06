BSpena_ROOT=$(pwd)

source settings.sh

cd $BSpena_ROOT

# $1 = sample path
# $2 = path to oneAPI ASP
# $3 = board variant
source impl/scripts/oneapi_sample_build.sh  \
    $(pwd)/impl                             \
    $OFS_ASP_ROOT                           \
    ofs_nc220_usm

cd $BSpena_ROOT
