FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI:append = " \
    file://animation.patch \
    file://psplash.service \
    file://frame-000-img.h \
    file://frame-001-img.h \
    file://frame-002-img.h \
    file://frame-003-img.h \
    file://frame-004-img.h \
    file://frame-005-img.h \
    file://frame-006-img.h \
    file://frame-007-img.h \
    file://frame-008-img.h \
    file://frame-009-img.h \
    file://frame-010-img.h \
    file://frame-011-img.h \
    file://frame-012-img.h \
    file://frame-013-img.h \
    file://frame-014-img.h \
    file://frame-015-img.h \
    file://frame-016-img.h \
    file://frame-017-img.h \
    file://frame-018-img.h \
    file://frame-019-img.h \
    file://frame-020-img.h \
    file://frame-021-img.h \
    file://frame-022-img.h \
"

EXTRA_OECONF:append = " --disable-progress-bar"

do_configure:append() {
    cp ${WORKDIR}/frame-*-img.h ${S}/
}

do_install:append() {
    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${WORKDIR}/psplash.service ${D}${systemd_system_unitdir}/
}

inherit systemd

SYSTEMD_SERVICE:${PN} = "psplash.service psplash-systemd.service"
SYSTEMD_AUTO_ENABLE:${PN} = "enable"

FILES:${PN} += " \
    ${systemd_system_unitdir}/psplash-start.service \
    ${systemd_system_unitdir}/psplash-systemd.service \
    ${systemd_system_unitdir}/psplash.service \
"