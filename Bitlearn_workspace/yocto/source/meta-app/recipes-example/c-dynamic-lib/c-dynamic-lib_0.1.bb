DESCRIPTION = "Simple helloworld dynamic library"

LICENSE = "MIT"

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://arith.c \
	   file://mylib.h \
	   file://print.c \
	  "

S = "${WORKDIR}"

do_compile() {

	${CC} -c -fPIC print.c 
	${CC} -c -fPIC arith.c
	${CC} ${LDFLAGS} -shared -Wl,-soname,libcal_d.so.1 -o libcal_d.so.1.0 print.o arith.o
}

do_install() {

	install -d ${D}${libdir}
	install -m 0755 libcal_d.so.1.0 ${D}${libdir}

	ln -s libcal_d.so.1.0 ${D}${libdir}/libcal_d.so.1
	ln -s libcal_d.so.1 ${D}${libdir}/libcal_d.so
	
	install -d ${D}${includedir}
	install -m 0644 mylib.h ${D}${includedir}
}
