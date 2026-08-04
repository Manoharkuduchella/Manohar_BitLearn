DESCRIPTION = "Simple helloworld C application with cmake"

LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://hello.c \
	   file://CMakeLists.txt \
	  "

S = "${WORKDIR}"

inherit cmake

#bbnote "Compilation started"
#do_compile is called if not defined and oe_runmake calls Makefile(using make -j 6)
#if to pass arguments to cmake use "EXTRA_OECMAKE"

EXTRA_OECMAKE += "-DCMAKE_INSTALL_PREFIX:PATH=/"


#do_install() {
#	bbwarn "Installation started"
#	install -d ${D}${bindir}
#	install -m 0755 capp ${D}${bindir}
#	bbwarn "Installation ended"
#}

#can't remove do_install it adds nothings

#do_install() {

#	oe_runmake install DESTDIR=${D}${bindir}
	
#}
