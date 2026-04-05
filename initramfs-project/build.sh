#!/bin/bash
# =============================================================
# Build script for Initramfs-Based Root Filesystem Selection
# Target: Raspberry Pi 3 B+ (aarch64)
# =============================================================

set -e

INITRAMFS_DIR="$HOME/initramfs/rootfs"
OUTPUT_DIR="$HOME/initramfs"

echo "=== Building Initramfs ==="

# Verify busybox exists
if [ ! -f "$INITRAMFS_DIR/bin/busybox" ]; then
    echo "ERROR: busybox not found in $INITRAMFS_DIR/bin/"
    echo "Place a statically-linked aarch64 busybox there first."
    exit 1
fi

# Verify init script
if [ ! -f "$INITRAMFS_DIR/init" ]; then
    echo "ERROR: init script not found"
    exit 1
fi

chmod +x "$INITRAMFS_DIR/init"

# Create cpio archive
cd "$INITRAMFS_DIR"
find . | cpio -H newc -o | gzip > "$OUTPUT_DIR/initramfs.cpio.gz"

# Wrap for U-Boot
mkimage -A arm64 -T ramdisk -C gzip -n "Custom initramfs" \
    -d "$OUTPUT_DIR/initramfs.cpio.gz" \
    "$OUTPUT_DIR/initramfs.uboot"

echo "=== Build Complete ==="
echo "Output: $OUTPUT_DIR/initramfs.uboot"
echo ""
echo "Deploy with:"
echo "  sudo mount /dev/sda1 /mnt"
echo "  sudo cp $OUTPUT_DIR/initramfs.uboot /mnt/initramfs.uboot"
echo "  sudo umount /mnt"
