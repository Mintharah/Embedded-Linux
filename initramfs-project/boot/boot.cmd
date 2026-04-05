setenv bootargs "earlycon=bcm2835aux,0x3f215040 console=tty1 console=ttyS0,115200 8250.nr_uarts=1 keep_bootcon rdinit=/init"

fatload mmc 0:1 ${kernel_addr_r} Image
fatload mmc 0:1 ${fdt_addr_r} bcm2837-rpi-3-b-plus.dtb
fatload mmc 0:1 ${ramdisk_addr_r} initramfs.uboot
setenv initrd_size ${filesize}

booti ${kernel_addr_r} ${ramdisk_addr_r}:${initrd_size} ${fdt_addr_r}
