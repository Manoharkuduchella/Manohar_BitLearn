#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main()
{
    int fd = shm_open("/myshm", O_RDWR, 0666);

    char *ptr = mmap(NULL,
                     1024,
                     PROT_READ | PROT_WRITE,
                     MAP_SHARED,
                     fd,
                     0);

    printf("Received: %s\n", ptr);

    munmap(ptr, 1024);
    close(fd);

    return 0;
}