# Initramfs-Based Root Filesystem Selection

## Overview
Custom initramfs for Raspberry Pi 3 B+ that prompts the user at boot
to select between two root filesystem sources:

1. **SD Card** — mount `/dev/mmcblk0p2` as root
2. **NFS** — mount a remote NFS share as root

## Architecture
- **Target:** Raspberry Pi 3 Model B Plus (aarch64)
- **Kernel:** Linux 6.12.77-v8+
- **Bootloader:** U-Boot
- **Initramfs shell:** BusyBox (statically linked, aarch64)

## Boot Flow
Power On
│
▼
U-Boot loads: Image + dtb + initramfs.uboot
│
▼
Kernel runs /init from initramfs
│
▼
/init mounts /proc, /sys, /dev
│
▼
Prompts user:
1) SD Card → mount /dev/mmcblk0p2 → switch_root
2) NFS → configure eth0, mount NFS → switch_root
│
▼
Selected root filesystem runs /sbin/init

## Project Structure
.
├── README.md
├── build.sh # Build initramfs image
├── setup_nfs.sh # Setup NFS server on host
├── initramfs/
│ ├── init # Main init script
│ └── rootfs_listing.txt # Contents of initramfs
├── boot/
│ ├── boot.cmd # U-Boot boot script source
│ ├── config.txt # RPi firmware config
│ └── cmdline.txt # Kernel command line
├── nfs_rootfs/
│ ├── exports.conf # NFS exports configuration
│ └── rootfs_listing.txt # Contents of NFS rootfs
└── docs/
└── setup_guide.md # Detailed setup instructions

## Configuration

### Network Settings (in initramfs/init)
| Parameter   | Value           |
|-------------|-----------------|
| NFS Server  | 192.168.1.2     |
| NFS Path    | /srv/nfs/rootfs |
| Device IP   | 192.168.1.50    |
| Gateway     | 192.168.1.1     |
| Interface   | eth0            |

### SD Card Layout
| Partition | Size  | Type | Contents          |
|-----------|-------|------|-------------------|
| sda1      | 256MB | FAT32| Boot (kernel, dtb, initramfs) |
| sda2      | 4GB   | ext4 | Root filesystem   |
| sda3      | 4GB   | ext4 | (unused)          |

## Building

```bash
# Build initramfs.uboot
./build.sh

# Deploy to SD card
sudo mount /dev/sda1 /mnt
sudo cp ~/initramfs/initramfs.uboot /mnt/initramfs.uboot
sudo umount /mnt
NFS Server Setup

# Run on host PC
./setup_nfs.sh
Boot Configuration
boot.cmd (U-Boot)
setenv bootargs "earlycon=bcm2835aux,0x3f215040 console=tty1 console=ttyS0,115200 8250.nr_uarts=1 keep_bootcon rdinit=/init"

fatload mmc 0:1 ${kernel_addr_r} Image
fatload mmc 0:1 ${fdt_addr_r} bcm2837-rpi-3-b-plus.dtb
fatload mmc 0:1 ${ramdisk_addr_r} initramfs.uboot
setenv initrd_size ${filesize}

booti ${kernel_addr_r} ${ramdisk_addr_r}:${initrd_size} ${fdt_addr_r}
config.txt

kernel=u-boot.bin
arm_64bit=1
enable_uart=1
dtoverlay=disable-bt
gpu_mem=64
init_uart_baud=115200
