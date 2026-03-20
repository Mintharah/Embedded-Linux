setenv bootargs "earlycon=uart8250,mmio32,0x3f215040 console=ttyAMA1,115200 root=/dev/ram0 rw rdinit=/sbin/init"

fatload mmc 0:1 ${kernel_addr_r} Image
fatload mmc 0:1 ${fdt_addr_r} bcm2710-rpi-3-b-plus.dtb
fatload mmc 0:1 0x03000000 uInitrd

booti ${kernel_addr_r} 0x03000000 ${fdt_addr_r}