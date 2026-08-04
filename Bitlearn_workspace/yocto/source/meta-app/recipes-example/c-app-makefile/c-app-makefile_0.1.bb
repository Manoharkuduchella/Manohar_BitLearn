DESCRIPTION = "Simple helloworld C application"

LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://hello.c \
	   file://hello.h \
	   file://Makefile \
	  "

S = "${WORKDIR}"

#bbnote "Compilation started"
#do_compile is called if not defined and oe_runmake calls Makefile(using make -j 6)
#if to pass arguments to Makfile use "EXTRA_OEMAKE"

EXTRA_OEMAKE += "V=1"


#do_install() {
#	bbwarn "Installation started"
#	install -d ${D}${bindir}
#	install -m 0755 capp ${D}${bindir}
#	bbwarn "Installation ended"
#}

#can't remove do_install it adds nothings

do_install() {

	oe_runmake install DESTDIR=${D}${bindir}
	
}
