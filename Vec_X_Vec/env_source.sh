# export XILINX_VERSAL=/home/kmhatre/Vitis/versal_common_files/2022.1/installation
# source $XILINX_VERSAL/environment-setup-cortexa72-cortesxa53-xilinx-linux

# export ROOTFS=/home/kmhatre/Vitis/versal_common_files/2022.1/xilinx-versal-common-v2022.1/rootfs.ext4  
# export IMAGE=/home/kmhatre/Vitis/versal_common_files/2022.1/xilinx-versal-common-v2022.1/Image
# export PLATFORM_REPO_PATHS=/packages/apps/fpga/Vitis/2022.1/base_platforms


source /scratch/kmhatre/AMD_tools/Vitis/2022.1/settings64.sh
export XILINX_VERSAL=/home/kmhatre/Vitis/versal_common_files/2022.1/installation
source $XILINX_VERSAL/environment-setup-cortexa72-cortexa53-xilinx-linux

export ROOTFS=/home/kmhatre/Vitis/versal_common_files/2022.1/xilinx-versal-common-v2022.1/rootfs.ext4  
export IMAGE=/home/kmhatre/Vitis/versal_common_files/2022.1/xilinx-versal-common-v2022.1/Image
export PLATFORM_REPO_PATHS=/packages/apps/fpga/Vitis/2022.1/base_platforms


echo ""
echo "Aiecompiler:"
which aiecompiler

echo ""
echo "Vivado:"
which vivado

echo ""
echo "Vitis:"
which vitis

echo ""
echo "Vitis HLS:"
which vitis_hls
echo ""
