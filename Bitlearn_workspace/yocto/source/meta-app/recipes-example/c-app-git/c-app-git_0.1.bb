DESCRIPTION = "Simple helloworld C application from git"

LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "git://github.com/Manoharkuduchella/Manohar_BitLearn.git;protocol=https;branch=main \
	   file://0001-Add-patch-for-git-yocto.patch \
	  "

S = "${WORKDIR}/git"

#alias name to recipe(built-time)
PROVIDES += "myapp"


SRCREV = "${AUTOREV}"

#SRCREV = "2204888da36c3719b92ac1ce5883f49d00a886ba"

#bbnote "Compilation started"
#do_compile is called if not defined and oe_runmake calls Makefile(using make -j 6)
#if to pass arguments to Makfile use "EXTRA_OEMAKE"

EXTRA_OEMAKE += "V=1"


#for apply patch at right path do_compile is written
do_compile() {
	oe_runmake -C Bitlearn_workspace/yocto
}


#do_install() {
#	bbwarn "Installation started"
#	install -d ${D}${bindir}
#	install -m 0755 capp ${D}${bindir}
#	bbwarn "Installation ended"
#}

#can't remove do_install if removed it adds nothings

do_install() {

	oe_runmake -C Bitlearn_workspace/yocto install DESTDIR=${D}${bindir}
	
}
