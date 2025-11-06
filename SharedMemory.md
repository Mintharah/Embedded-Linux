##Process 1
```bash
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define KEY 0x1234u
#define SIZE 50u

int main()
{
    int key = shmget(KEY, SIZE, IPC_CREAT | 0666);
    if (key == -1)
    {
        perror("shmget failed");
        return 1;
    }
    else
    {
    }
    char *ptr = (char *)shmat(key, NULL, 0);
    if (ptr == (char *)-1)
    {
        perror("shmat failed");
        return 1;
    }
    else
    {
        while (1)
        {
            scanf("%s", &ptr[0]);
            ptr[SIZE - 1] = 1;
        }
    }

    return 0;
}
```

##Process 2
```bash
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define KEY 0x1234u
#define SIZE 50u

int main()
{
    int key = shmget(KEY, SIZE, 0666);
    if (key == -1)
    {
        perror("shmget failed");
        return 1;
    }
    else
    {
    }
    char *ptr = (char *)shmat(key, NULL, 0);
    if (ptr == (char *)-1)
    {
        perror("shmat failed");
        return 1;
    }
    else
    {
        while (1)
        {   
            if (ptr[SIZE - 1] == 1)
            {
                printf("%s\n", ptr);
                ptr[SIZE - 1] = 0;
            }
            else
            {
            }
        }
    }

    return 0;
}

```
