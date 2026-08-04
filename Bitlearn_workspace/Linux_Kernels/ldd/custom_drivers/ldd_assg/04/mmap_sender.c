#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

#define FILE_NAME "shared.dat"
#define SIZE 1024

int main(void)
{
    int fd = open(FILE_NAME, O_CREAT | O_RDWR, 0666);
    if(fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    /* Make file SIZE bytes long */
    if(ftruncate(fd, SIZE) == -1)
    {
        perror("ftruncate");
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

    strcpy(ptr, "Hello from Process 1");

    printf("Written: %s\n", ptr);

    getchar();     /* Keep process alive */

    munmap(ptr, SIZE);
    close(fd);

    return 0;
}