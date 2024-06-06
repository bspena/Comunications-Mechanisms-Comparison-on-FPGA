BSpena_ROOT=$(pwd)

HTS_RELEASE=/home/vincenzo/AGILEX/c220/intel-ofs-2023.2-ubuntu-hitek/hitek_release/AG_C220_NC220_OFS_Release_v1_0_2024-01-22/htk_ofs_nc220
export OPAE_PLATFORM_ROOT=${HTS_RELEASE}/prebuild_images/agf014/release_v1.1/pr_build_template
# export OFS_ASP_ROOT=${HTS_RELEASE}/oneapi/oneapi-asp_agf014/nc220
export OFS_ASP_BOARD_VARIANT=ofs_nc220_usm
# export ONEAPI_ROOT=/opt/intel/oneapi
# source ${ONEAPI_ROOT}/setvars.sh
source ~/AGILEX/c220/intel-ofs-2023.2-ubuntu-hitek/settings.sh

cd $BSpena_ROOT
