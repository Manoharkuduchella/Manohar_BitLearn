FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI += "file://0001-Add-changes-for-linux-yocto-with-bbappend.patch \
	    file://app-image-fragment.cfg \
	   "

LINUX_VERSION_EXTENSION = "-app-image-linux"
