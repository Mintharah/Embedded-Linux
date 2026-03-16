### Screenshot
![screenshot](images/initramfs.png)

### Questions
1) a temporary in-memory filesystem the kernel unpacks at in boot, used because kernel might need drivers or setup steps before mounting on the real rootfs, it is also faster.

2) the linux kernel has a built in cpio extractor, tar and zip are not supported natively, they need userspace tools to extract.

3) tells the compiler which binary to run at PID 1. wrong kernel path -> kernel panic "no working init fount"

4) dynamic libraries would fail immediately because it cant find libc or ld-linux.

5) initramfs:
format: cpio
mounting: kernel unpacks directly
status: modern standard

initrd:
format: block device image
mounting: mounted as disk
status: legacy

6) loaded by uboot to a ram address and decompressed by the kernel itself and unpacks during early boot.

7) via switch_root, mounts real rootfs, frees initramfs memory, then execs the real /sbin/init as PID1.
