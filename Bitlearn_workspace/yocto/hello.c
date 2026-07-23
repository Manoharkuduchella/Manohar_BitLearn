#include<stdio.h>
#include"hello.h"
int main()
{
	#ifdef USE_SYSCALL
	printf("####################hello from yocto c-app-%d######################\n",var);
	#endif
	printf("*********************hello from yocto c-app-%d**********************\n",var);
	printf("^^^^^^^^^^^^^^^^^^^^^hello from yocto-patch c-app-%d^^^^^^^^^^^^^^^^\n",var);
	return 0;
}
