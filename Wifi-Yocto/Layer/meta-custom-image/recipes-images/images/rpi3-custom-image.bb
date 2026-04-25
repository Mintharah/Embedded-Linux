SUMMARY="Custom image for raspberry pi 3B+"
LICENSE="CLOSED"

inherit core-image

ENABLE_UART = "1"

IMAGE_FEATURES:append = " ssh-server-dropbear"

IMAGE_ROOTFS_SIZE ?= "2097152"
IMAGE_ROOTFS_EXTRA_SPACE ?= "524288"

IMAGE_INSTALL:append = " \
    python3 \
    python3-pip \
    tcpdump \
    linux-firmware-rpidistro-bcm43430 wpa-supplicant \
    wifi-setup \
    "