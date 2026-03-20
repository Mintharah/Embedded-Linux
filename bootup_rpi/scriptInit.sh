#!/bin/bash

# Define paths
BASE_DIR="$HOME/bootup_rpi"
STAGING_DIR="$BASE_DIR/initramfs"
OUTPUT_CPIO="$BASE_DIR/rootramfs.cpio.gz"
OUTPUT_UBOOT="$BASE_DIR/rootramfs.uboot"

echo "--- Starting Initramfs Packaging ---"

# 1. Enter the staging directory
if [ -d "$STAGING_DIR" ]; then
    cd "$STAGING_DIR" || exit
else
    echo "Error: Staging directory $STAGING_DIR does not exist."
    exit 1
fi

# 2. Create the CPIO archive and Gzip it
# We use 'sudo' here to ensure file permissions (like the +x bit) are preserved
echo "Creating compressed CPIO archive..."
find . -print0 | sudo cpio --null -H newc -o | gzip -9 > "$OUTPUT_CPIO"

if [ $? -eq 0 ]; then
    echo "Successfully created $OUTPUT_CPIO"
else
    echo "Failed to create CPIO archive."
    exit 1
fi

# 3. Wrap with U-Boot header (mkimage)
echo "Generating U-Boot image..."
mkimage -A arm64 -O linux -T ramdisk -C gzip -n "initramfs" \
    -d "$OUTPUT_CPIO" "$OUTPUT_UBOOT"

if [ $? -eq 0 ]; then
    echo "DONE! Your file is ready at: $OUTPUT_UBOOT"
    ls -lh "$OUTPUT_UBOOT"
else
    echo "mkimage failed. Make sure u-boot-tools is installed."
    exit 1
fi