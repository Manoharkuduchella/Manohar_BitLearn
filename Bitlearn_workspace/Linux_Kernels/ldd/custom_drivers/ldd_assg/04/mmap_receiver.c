#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define FILE_NAME "shared.dat"
#define SIZE 1024

int main(void)
{
    int fd = open(FILE_NAME, O_RDWR);
    if(fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char *ptr = mmap(NULL,
                     SIZE,
                     PROT_READ | PROT_WRITE,
                     MAP_SHARED,
                     fd,
                     0);

    if(ptr == MAP_FAILED)
    {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    printf("Received: %s\n", ptr);

    munmap(ptr, SIZE);
    close(fd);

    return 0;
}