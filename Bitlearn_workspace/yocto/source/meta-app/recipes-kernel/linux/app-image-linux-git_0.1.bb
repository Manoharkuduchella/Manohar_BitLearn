DESCRIPTION = "Simple Kernel recipe for app-image"

LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit kernel

SRC_URI = "git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git;protocol=git;branch=master; \
	   file://defconfig \
	   file://0001-Add-changes-for-kernel-git-patch.patch \
	  "

SRCREV = "${AUTOREV}"

S = "${WORKDIR}/git"




