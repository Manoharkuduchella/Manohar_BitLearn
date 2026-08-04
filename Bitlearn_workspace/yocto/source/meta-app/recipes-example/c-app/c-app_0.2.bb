DESCRIPTION = "Simple helloworld C application UPDATED Version"

LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://hello.c \
	   file://hello.h \
	   file://ReadMe.txt \
	   file://0001-Add-changes-in-hello.c-from-dev-shell.patch \
	  "
#alias name to recipe(built-time)
PROVIDES += "myapp"

#to skip the patch applying task
do_patch[noexec] = "1"

S = "${WORKDIR}"

#if this recipe depends(build-time) on other recipe
#DEPENDS = "c-static-lib"

#if this recipe depends(run-time) on other recipe
RDEPENDS:${PN} = "pciutils"

do_compile() {
	bbnote "Compilation started"
	#bberror "reports error and doesn't terminates"
	#bbfatal "Comilation gets terminated reports error"
	#${CC} -DUSE_SYSCALL hello.c ${LDFLAGS} -o capp -lcal_s #for staticlib
	${CC} -DUSE_SYSCALL hello.c ${LDFLAGS} -o capp
}


do_install() {
	bbwarn "Installation started"
	install -d ${D}${bindir}
	install -m 0755 capp ${D}${bindir}
	#install -d ${D}${docdir}
	#install -m 0644 ReadMe.txt ${D}${docdir}
	install -d ${D}${datadir}
	install -m 0644 ReadMe.txt ${D}${datadir}
	bbwarn "Installation ended"
}

FILES:${PN} += "${bindir}/capp"
#FILES:${PN}-doc += "${docdir}/ReadMe.txt" #ReadMe.txt can be added in doc or readme not both 
FILES:${PN}-readme = "${datadir}/ReadMe.txt"

PACKAGES += "${PN}-readme"
