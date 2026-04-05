#!/bin/bash
# =============================================================
# NFS Server Setup Script
# Run on host PC to serve root filesystem to Raspberry Pi
# =============================================================

set -e

NFS_ROOT="/srv/nfs/rootfs"
NETWORK="192.168.1.0/24"

echo "=== Setting up NFS Server ==="

# Install NFS server
sudo apt install -y nfs-kernel-server

# Create export directory
sudo mkdir -p "$NFS_ROOT"

# Check if rootfs needs to be populated
if [ ! -f "$NFS_ROOT/sbin/init" ]; then
    echo "NFS rootfs is empty."
    echo "Mount your SD card partition and copy:"
    echo "  sudo mount /dev/sda2 /mnt"
    echo "  sudo cp -a /mnt/* $NFS_ROOT/"
    echo "  sudo umount /mnt"
    exit 1
fi

# Add export if not already present
if ! grep -q "$NFS_ROOT" /etc/exports 2>/dev/null; then
    echo "$NFS_ROOT $NETWORK(rw,sync,no_subtree_check,no_root_squash)" | sudo tee -a /etc/exports
fi

# Apply and restart
sudo exportfs -a
sudo systemctl restart nfs-kernel-server
sudo systemctl enable nfs-kernel-server

echo "=== NFS Server Ready ==="
sudo exportfs -v
