1. dd if=/dev/zero of=sd.img bs=1M count=1024
dd: device create/destroy, copies data.
if: input file, aka file to copy from.
of: output file, aka file copied to.
bs: block size copied per cycle.
count: number of blocks copied, if not specified, all data will be copied from source file.

losetup -f --partscan --show sd.img
attaches image to loop device

cfdisk

to specify size of partition, type and whether its bootable or not.

2. MBR/DOS:
   old partition scheme.
   max disk size is about 2TB.
   max 4 primary paritions.
   stores partition table in the first sector.

   GPT:
   modern standard.
   supports disks larger than 2TB.
   supports more than 128+ primary partitions.
   has backup partition table + CRC.

3. FAT16:
   older file system.
   FATs in general have bad security however all systems understand FAT.
   supports small partitions (up to 2 gb).
   very small structure.
   used in old systems, small usb drives, embedded systems.

   FAT32:
   improved FAT16.
   supports partition up to 2gb.
   max file size is 4gb.
   used in USB flash drives, SD cards.

   EXT4:
   modern linux file system, not typically understood by window OS's or older drives .
   supports very large files and partitions.
   more reliable and less corruptable.
   better performance and permissions support, more secure than FAT.
   used in linux system.

4. <img width="885" height="77" alt="image" src="https://github.com/user-attachments/assets/87e97dad-5cdf-4ce2-90e0-16450f9c9e29" />

5. a loop device is a virtual block device that maps a regular file to act like a real disk.
   a. command: losetup -f --partscan --show [file name]
   b. losetup -a
   c. sudo losetup -d /dev/loopX

6. cat /sys/module/loop/parameters/max_loop

7. sudo modprobe loop max_loop=64

8. <img width="885" height="77" alt="image" src="https://github.com/user-attachments/assets/f9e3363f-d153-4b11-be78-f40c0e444b2d" />

9. mkfs.vfat -n boot -F 16 /dev/loop7p1
  mkfs.vfat: creates a FAT file system.
  -n: name
  -F: FAT

  mkfs.ext4 -L rootfs /dev/loop26 (loop26 because you cant directly put an ext fs on an ext partition, there has to be a logical linux partition made in it?)

10. mount's purpose: attaches a file system or a storange to linux's directory tree so you can access its files.
    ex.: sudo mount [device] [mount_point]
    unmount: deattach a mounted filesystem from linux's directory tree safely.

11. block device:
    read/writes in blocks.
    ex.: hard disk, ssd, usb drives.
    can access any block directly.
    usually buffered/cached.
    use case: storange device.

    character device:
    read/writes byte by byte.
    ex.: keyboard, mouse, serial ports.
    usually sequential only.
    usually unbuffered.
    use case: devices that send/receive streams of data.

12. <img width="885" height="57" alt="image" src="https://github.com/user-attachments/assets/8db9134a-33ea-4342-b634-6228a981b5d5" />

<img width="885" height="57" alt="image" src="https://github.com/user-attachments/assets/f80d62a6-3819-4fd7-9a2e-c6bd80577a7e" />
