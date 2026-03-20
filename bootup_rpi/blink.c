#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

// For Raspberry Pi 3 B+, the Peripheral Base is 0x3F000000
#define BCM2837_PERI_BASE 0x3F000000
#define GPIO_BASE (BCM2837_PERI_BASE + 0x200000)

#define BLOCK_SIZE (4*1024)

// GPIO Register Offsets
#define GPFSEL2 2  // Select register for GPIO 20-29
#define GPSET0  7  // Set register for GPIO 0-31
#define GPCLR0  10 // Clear register for GPIO 0-31

int main() {
    int mem_fd;
    void *gpio_map;
    volatile unsigned int *gpio;

    // 1. Open /dev/mem
    if ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0) {
        perror("Can't open /dev/mem (are you root?)");
        exit(-1);
    }

    // 2. Map GPIO registers into memory
    gpio_map = mmap(
        NULL,             // Any addres in our space will do
        BLOCK_SIZE,       // Map length
        PROT_READ | PROT_WRITE, // Enable reading & writing to mapped memory
        MAP_SHARED,       // Shared with other processes
        mem_fd,           // File to map
        GPIO_BASE         // Offset to GPIO peripheral
    );

    close(mem_fd);

    if (gpio_map == MAP_FAILED) {
        perror("mmap error");
        exit(-1);
    }

    gpio = (volatile unsigned int *)gpio_map;

    // 3. Set GPIO 21 as Output
    // GPIO 21 is in GPFSEL2, bits 3-5. 001 = Output
    gpio[GPFSEL2] &= ~(7 << 3); // Clear bits 3-5
    gpio[GPFSEL2] |= (1 << 3);  // Set bit 3 (Value 1)

    printf("--- Blinking GPIO 21 via MMAP ---\n");

    while (1) {
        // Set Pin High
        gpio[GPSET0] = (1 << 21);
        printf("HIGH\n");
        sleep(1);

        // Set Pin Low
        gpio[GPCLR0] = (1 << 21);
        printf("LOW\n");
        sleep(1);
    }

    return 0;
}