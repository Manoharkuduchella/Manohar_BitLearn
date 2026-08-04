
SUMMARY = "App Packagegroup recipe"

inherit packagegroup

RDEPENDS:${PN} = "util-linux pciutils usbutils"

RRECOMMANDS_${PN} = "lshw"
