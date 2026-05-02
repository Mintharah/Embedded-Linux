# Recipe created by recipetool
# This is the basis of a recipe and may need further editing in order to be fully functional.
# (Feel free to remove these comments when editing.)

# WARNING: the following LICENSE and LIC_FILES_CHKSUM values are best guesses - it is
# your responsibility to verify that the values are complete and correct.
LICENSE = "MPL-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=9741c346eef56131163e13b9db1241b3"

SRC_URI = "git://github.com/COVESA/vsomeip.git;protocol=https;branch=master"

# Modify these as desired
PV = "1.0+git"
SRCREV = "c70ced40c75a9ad507c9a9142fa0052bc376f525"

S = "${WORKDIR}/git"

# NOTE: unable to map the following CMake package dependencies: benchmark Doxygen
# NOTE: unable to map the following pkg-config dependencies: libsystemd
#       (this is based on recipes that have previously been built and packaged)
DEPENDS = "boost"

inherit cmake pkgconfig

# Specify any options you want to pass to cmake using EXTRA_OECMAKE:
EXTRA_OECMAKE = ""

FILES:${PN} = "/usr/lib/* /usr/etc/* /usr/bin/"