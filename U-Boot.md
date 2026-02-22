## Part A: U-Boot build and deployment

1- a bootloader is a program that runs immediately after reset or power-on and often initializes the basic hardware, checks if new firmware is available, programs the firmware into flash memory and jumps to the main application.

2- firs the BootROM loads up (first stage BL) -> start.elf with config.txt as input -> bootcode.bin -> image is loaded up in DRAM (u-boot) -> cpu jumps to u-boot

3- U-Boot:
Universal Bootloader
Used in Embedded systems
Typical devices: ARM boards, RPI 4
Runs on: bare-metal hardware
Main purpose: initialize hardware + load kernel or image
Hardware init: YES
Interactive shell: YES (low-level commands, flash memory)

GRUB: 
Grand Unified Bootloader
Used in: PCs/servers
Typical devices: x86 laptops & desktops
Runs on: on top of BIOS
Main purpose: select and load OS
Hardware init: NO (already done by BIOS)
Interactive shell: YES (os selection menu)

4- bootcode.bin: the actual bootlaoder binary that runs
start.elf: GPU firmware that inits the hardware and loads up the bootloader
config.txt: bootloader configurations file
fixup.dat: memory configuration file used by start.elf

5- 
1) download u-boot:
git clone https://github.com/u-boot/u-boot.git
2) configure for cortexa9:
make vexpress_ca9x4_defconfig
3) customize:
make menuconfig
in bootoptions, you could edit the "default value for bootcmd" to run a script on a booting.
can also change the shell prompt to display your name in command line interface -> shell prompt
4) export CROSS_COMPILE=arm-linux-gnueabi-
5) make -j
6) run qemu:
qemu-system-arm -M vexpress-a9 -kernel u-boot -nographic

6- 
1) look for the config file for rpi:
cd config/
ls | grep rpi
cd ..
2) make rpi_3_b_plus_defconfig
3) export CROSS_COMPILE=~/x-tools/aarch64-rpi3-linux-gnu/bin//aarch64-rpi3-linux-gnu-
4) make -j
5) setup the sd card:
sudo losetup -f --partscan --show sd.img
6) add the file system to the partitions:
sudo mkfs.vfat /dev/loop9p1
sudo mkfs.ext4 /dev/loop9p2
7) mount the partitions:
mkdir mnt/boot
mkdir mnt/rootfs
sudo mount /dev/loop9p1 /mnt/boot
sudo mount /dev/loop9p2 /mnt/rootfs
8) download the bootcode.bin, start.elf, kernel8.img and fixup.dat from rpi firmware repo into the boot partition.
9) create a config.txt in boot partition including:
arm_64bit=1 : run AArch64
enable_uart=1 : serial console output
10) unmount and write image to phyical sd card: i cant plug it directly into my laptop </3

7-DTB: Device Tree Binary
it is loaded by the start.elf before uboot start executing and is passed to the uboot in memory.

8- the linux kernel reads the partition table (MBR) stored at the beginning of the image file and contains the starting sectors and sizes of the partitions. using this info it calculates the offsets and creates devices like /dev/loop9p1 and /dev/loop9p2.


## Part B: U-Boot commands environment

1- bdinfo: displays board information
it shows:
RAM start address & size
Flash location
Boot parameters address
CPU architecture info

2- printenv: displays all environment variables.
it shows:
bootcmd
bootargs
bootdelay
boot device settings 

3- DRAM start address: 0x60000000

4- ls [dev:part] [directory]

5- in the menuconfig:
general setup -> local version: change it to "Welcome to Our-Boot – Intake 46"
save and exit then make -j to build
run qemu:
qemu-system-arm -M vexpress-a9 -kernel u-boot -nographic

6- in menuconfig, edit command line interface -> shell prompt to display your name in the prompt

7- /usr/sbin/in.tftpd --listen --user tftp --address :69 --secure --create /srv/tftp
  restart: sudo systemctl restart tftpd-hpa
  check status: sudo systemctl status tftpd-hpa
  copy image and dtb to /srv/tftp
  in qemu:
  set client address: setenv ipaddr 10.0.2.50
  set server address: setenv serverip 10.0.2.2
  ping the server: ping 10.0.2.2 "host 10.0.2.2 is alive"
  
