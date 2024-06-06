sudo pci_device ${PAC_PCIE_SBD}.0 vf 1
sudo opae.io -d ${PAC_PCIE_SBD}.5 init ${USER}:${USER}
aocl initialize acl0 ofs_nc220_usm