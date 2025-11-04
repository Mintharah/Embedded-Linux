```bash #include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    const char *path = "/sys/class/leds/input7::capslock/brightness";
    int fd = open(path, O_RDWR);
    if (argc > 1)
    {
        if (strcmp(argv[1], "1") == 0)
        {
            write(fd, "1", 1);
        }
        else if (strcmp(argv[1], "0") == 0)
        {
            write(fd, "0", 1);
        }
        else{}
        }
    else{}
    close(fd);
    return 0;
    }
```
