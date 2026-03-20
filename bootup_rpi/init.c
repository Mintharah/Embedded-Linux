#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mount.h>
#include <stddef.h>

int main() {
    // 1. Essential Mounts
    mount("proc", "/proc", "proc", 0, NULL);
    mount("sysfs", "/sys", "sysfs", 0, NULL);
    mount("devtmpfs", "/dev", "devtmpfs", 0, NULL);

    // 2. Wait a heartbeat for the Framebuffer (/dev/fb0) to stabilize
    sleep(1);

    // 3. Start Jeff! 
    // We keep the '&' so the boot continues to the shell
    system("/usr/bin/psplash &");

    // 4. Setup Console (for your TTL cable)
    int fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
    if (fd < 0) fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY);
    if (fd < 0) fd = open("/dev/console", O_RDWR | O_NOCTTY);

    if (fd >= 0) {
        dup2(fd, 0); dup2(fd, 1); dup2(fd, 2);
    }

    // 5. Jump to Shell (Blink is NOT called here anymore)
    char *envp[] = { "PATH=/sbin:/usr/sbin:/bin:/usr/bin", "HOME=/", "TERM=linux", NULL };
    char *argv[] = { "sh", NULL }; 
    
    execve("/bin/sh", argv, envp);

    while(1) sleep(100);
    return 0;
}