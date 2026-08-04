#include<stdio.h>
#include<sys/ioctl.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	int fd;
	unsigned long num_blocks;

	fd = open("/dev/sda1",O_RDONLY);
	perror("fd");

	ioctl(fd,BLKGETSIZE,&num_blocks);

	perror("ioctl");

	printf("Number of blocks: %lu, this make %.3f GB\n",num_blocks, num_blocks * 512.0 / (1024 * 1024 *1024));

	close(fd);

	return 0;
}

