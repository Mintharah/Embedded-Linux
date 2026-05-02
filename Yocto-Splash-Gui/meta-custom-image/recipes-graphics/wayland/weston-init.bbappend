FILESEXTRAPATHS:prepend := "${THISDIR}/weston-init:"

SRC_URI:append = " \
    file://weston.ini \
    file://weston.service \
    file://weston.env \
    file://psplash-quit.service \
"

do_install:append() {
    install -D -p -m0644 ${WORKDIR}/psplash-quit.service \
        ${D}${systemd_system_unitdir}/psplash-quit.service
    install -d ${D}${systemd_system_unitdir}/multi-user.target.wants
    ln -sf ../weston.service ${D}${systemd_system_unitdir}/multi-user.target.wants/weston.service
}

FILES:${PN} += "${systemd_system_unitdir}/multi-user.target.wants/weston.service"

SYSTEMD_SERVICE:${PN} = "weston.service weston.socket psplash-quit.service"
SYSTEMD_AUTO_ENABLE:${PN} = "enable"
USERADD_PARAM:${PN} = "--home /home/weston --shell /bin/sh --user-group -G video,input,render,wayland weston"