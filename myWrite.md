```bash
#include <string.h>

long myWrite(unsigned int fd, char* buffer, unsigned int size);


int main(){
    char buffer[] = "halooooo\n";
    myWrite(1, buffer, strlen(buffer));
    return 0;
}

long myWrite(unsigned int fd, char* buffer, unsigned int size){
    long ret = 0;
asm volatile(
    "mov $1, %%rax\n\t"      // syscall number
    "mov %1, %%rdi\n\t"      // fd
    "mov %2, %%rsi\n\t"      // buffer pointer
    "mov %3, %%rdx\n\t"      // size
    "syscall\n\t"
    "mov %%rax, %0\n\t"
    : "=r"(ret)
    : "r"((long)fd), "r"(buffer), "r"((long)size) // casting to long cus system is  64-bit
    : "%rax", "%rdi", "%rsi", "%rdx"
);

    return ret;
}
```
