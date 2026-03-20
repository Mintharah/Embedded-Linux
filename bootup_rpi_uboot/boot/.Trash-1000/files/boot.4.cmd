setenv bootargs "console=ttyS0,115200 console=tty1 keep_bootcon rdinit=/sbin/init"

setenv bootargs "earlycon=bcm2835aux,0x3f215040 console=ttyS0,115200 8250.nr_uarts=1 ignore_loglevel keep_bootcon loglevel=8 rdinit=/sbin/init"
load mmc 0:1 ${kernel_addr_r} Image
load mmc 0:1 ${fdt_addr_r} bcm2837-rpi-3-b-plus.dtb
load mmc 0:1 ${ramdisk_addr_r} initramfs.uboot
setenv initrd_size ${filesize}

booti ${kernel_addr_r} ${ramdisk_addr_r}:${initrd_size} ${fdt_addr_r}
