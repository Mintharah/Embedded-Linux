SUMMARY="Custom image for raspberry pi 3B+"
LICENSE="CLOSED"

inherit core-image
inherit extrausers


EXTRA_USERS_PARAMS = "\
    useradd -m -s /bin/sh -G sudo meow; \
    usermod -p '\$5\$cHnxpoJThLvjYAO7\$1MusjGwJ9LNNSm.aa4E188IMIyeLabijyXWm9FJppyD' meow; \
"
MACHINE_HOSTNAME = "meow"

IMAGE_FEATURES:append = " ssh-server-dropbear"

IMAGE_ROOTFS_SIZE ?= "2097152"
IMAGE_ROOTFS_EXTRA_SPACE ?= "524288"


IMAGE_INSTALL:append = " \
    python3 \
    python3-pip \
    tcpdump \
    sudo \
    linux-firmware-rpidistro-bcm43430 wpa-supplicant \
    wifi-setup \
    weston \
    weston-init \
    qtbase \
    qtdeclarative \
    qtwayland \
    psplash \
    psplash-raspberrypi \
    "