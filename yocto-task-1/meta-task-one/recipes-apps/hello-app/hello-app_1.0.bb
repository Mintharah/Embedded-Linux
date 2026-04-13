DESCRIPTION = "Simple hello world C app"
AUTHOR = "Yasmine"
LICENSE = "CLOSED"

SRC_URI = "git://github.com/Mintharah/Embedded-Linux.git;protocol=https;branch=main"
SRCREV = "6d6ea76e3fe07ac79632fa5ccec1b8d4c9a3a04c"

S = "${WORKDIR}/git/yocto-task-1"

do_compile(){
    ${CC} ${CFLAGS} ${LDFLAGS} -o hello main.c
}

do_install(){
    install -D -m 755 ${B}/hello ${D}${bindir}/hello
}

FILES:${PN} = "${bindir}/hello"