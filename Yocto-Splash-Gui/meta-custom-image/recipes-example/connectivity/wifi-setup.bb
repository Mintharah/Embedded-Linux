DESCRIPTION = "WiFi setup with wpa_supplicant and systemd-networkd"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = " \
    file://wpa_supplicant.conf \
    file://wlan0.network \
    file://wifi-setup.service \
"

inherit systemd

SYSTEMD_SERVICE:${PN} = "wifi-setup.service"
SYSTEMD_AUTO_ENABLE = "enable"

RDEPENDS:${PN} = "wpa-supplicant"

do_install() {
    # wpa_supplicant config
    install -d ${D}${sysconfdir}/wpa_supplicant
    install -m 0600 ${WORKDIR}/wpa_supplicant.conf ${D}${sysconfdir}/wpa_supplicant/

    # systemd-networkd config
    install -d ${D}${sysconfdir}/systemd/network
    install -m 0644 ${WORKDIR}/wlan0.network ${D}${sysconfdir}/systemd/network/

    # systemd service
    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/wifi-setup.service ${D}${systemd_unitdir}/system/
}

FILES:${PN} = " \
    ${sysconfdir}/wpa_supplicant/ \
    ${sysconfdir}/systemd/network/ \
    ${systemd_unitdir}/system/wifi-setup.service \
"