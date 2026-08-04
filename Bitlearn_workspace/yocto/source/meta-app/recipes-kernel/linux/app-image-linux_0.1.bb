DESCRIPTION = "Simple Kernel recipe for app-image"

LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit kernel

SRC_URI = "https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-6.6.147.tar.xz;name=kernel \
	   file://defconfig \
	  "

S = "${WORKDIR}/linux-6.6.147"

SRC_URI[kernel.sha256sum] = "e76329b7ee046883d55a1868253cffe67c526a6da6140ebecd3cd6ac44db4abb"



