/*
#include<stdio.h>
#include<linux/ioctl.h>

//get unique numbers form linux/Documentation/userspace-api/ioctl/ioctl-number.rst
#define MAGIC_NUMBER1 0xF1
#define MAGIC_NUMBER2 0xF2 


int main()
{
	printf("_IO(MAGIC_NUMBER1, 1): %lx\n",_IO(MAGIC_NUMBER1, 1));//creating cmd from magicnumber
	printf("_IO(MAGIC_NUMBER2, 1): %lx\n",_IO(MAGIC_NUMBER2, 1));

	getchar();

	printf("_IO(MAGIC_NUMBER1, 2): %lx\n",_IO(MAGIC_NUMBER1, 2));
	printf("_IO(MAGIC_NUMBER2, 2): %lx\n",_IO(MAGIC_NUMBER2, 2));
	
	getchar();

	printf("_IOR(MAGIC_NUMBER1, 2, int): %lx\n",_IOR(MAGIC_NUMBER1, 2, int));
	printf("_IOR(MAGIC_NUMBER2, 2, int): %lx\n",_IOR(MAGIC_NUMBER2, 2, int));
	
	getchar();

	printf("_IOR(MAGIC_NUMBER1, 3, int): %lx\n",_IOR(MAGIC_NUMBER1, 3, int));
	printf("_IOR(MAGIC_NUMBER2, 3, int): %lx\n",_IOR(MAGIC_NUMBER2, 3, int));

	getchar();

	
	printf("_IOWR(MAGIC_NUMBER2, 4, int): %lx\n",_IOWR(MAGIC_NUMBER2, 4, int));



}
*/


#include<stdio.h>
#include<linux/ioctl.h>

#define MAGIC_NUMBER 0xF1


#define CMD1 _IO(MAGIC_NUMBER, 1)
#define CMD2 _IOW(MAGIC_NUMBER, 2, int)
#define CMD3 _IOWR(MAGIC_NUMBER, 3, char)

void printDirection(unsigned int cmd)
{
	switch(_IOC_DIR(cmd))
	{
		case _IOC_NONE:
			printf("_IOC_NONE\n");break;
		case _IOC_READ:
			printf("_IOC_READ\n");break;
		case _IOC_WRITE:
			printf("_IOC_WRITE\n");break;
		case _IOC_READ|_IOC_WRITE:
			printf("_IOC_READ\n");break;
				
	}

}


int main()
{
	//for getting the Number
	printf("Number:%u\n",_IOC_NR(CMD1));
	printf("Number:%u\n",_IOC_NR(CMD2));
	printf("Number:%u\n",_IOC_NR(CMD3));
	
	//for getting the Magic Number
	printf("Magic Number:%x\n",_IOC_TYPE(CMD1));
	printf("Magic Number:%x\n",_IOC_TYPE(CMD2));
	printf("Magic Number:%x\n",_IOC_TYPE(CMD3));
	
	//for getting the size
	printf("Size:%u\n",_IOC_SIZE(CMD1));
	printf("Size:%u\n",_IOC_SIZE(CMD2));
	printf("Size:%u\n",_IOC_SIZE(CMD3));
	
	printDirection(CMD1);
	printDirection(CMD2);
	printDirection(CMD3);

}
