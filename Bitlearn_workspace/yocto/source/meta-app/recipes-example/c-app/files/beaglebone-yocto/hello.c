#include<stdio.h>
#include"hello.h"
int main()
{
	#ifdef USE_SYSCALL
	printf("####################hello from yocto c-app-%d######################\n",var);
	#endif
	printf("*********************hello from yocto c-app-%d**********************\n",var);

	//added for demonstrating DEPENDS for static lib(c-static-lib recipe)
	//print("hello form c-app\n",5);
	
	printf("Hello form beaglebone-yocto changed form filesoverides\n");

	return 0;
}
