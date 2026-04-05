# Initramfs-Based Root Filesystem Selection

## Overview

Custom initramfs for Raspberry Pi 3 B+ that prompts the user at boot to select between two root filesystem sources:

1. **SD Card** — mount `/dev/mmcblk0p2` as root
2. **NFS** — mount a remote NFS share as root

---

## Architecture

| Component | Detail |
|-----------|--------|
| **Target** | Raspberry Pi 3 Model B Plus (aarch64) |
| **Kernel** | Linux 6.12.77-v8+ |
| **Bootloader** | U-Boot |
| **Initramfs shell** | BusyBox (statically linked, aarch64) |

---

## Boot Flow
