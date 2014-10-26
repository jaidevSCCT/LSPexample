/*For more info refer man sigaction or refer sigaction note provided in 
this chapter*/
#include<unistd.h>
#include<stdio.h>
#include<sys/signal.h>
#include<stdlib.h>
void myhandler(int signum,siginfo_t * info,void *context)
{
  	/* print the address that caused the fault */
	fprintf(stdout,"\nsigno == %d , fault addr = 0x%lX \n",info->si_signo,(long)info->si_addr);
	if(info->si_code == SEGV_MAPERR)
                puts("\n segmentation fault due to invalid region of memory \n");
	else if(info->si_code == SEGV_ACCERR)
                puts("\n segmentation fault due to violation of memory access permission \n");
	else 
		puts("\nUse more si_code Flags to check\n");
	exit(0);
}


int main()
{
	struct sigaction act; 
	int ret;
	sigset_t mask; // mask to set 
	ret = sigemptyset(&mask); // emptying the set see sigemptyset eg.
	if(ret == -1)
		perror("sigemptyset");
	act.sa_mask = mask;
	act.sa_flags = SA_SIGINFO;  
	act.sa_sigaction = &myhandler;
	ret = sigaction(SIGSEGV,&act,NULL);
	if(ret == -1)
		perror("sigaction");
/*open the below comment to get SEGV_MAPERR fault */
/*	char *ptr=NULL;
	*ptr = 'a';*/

/*Intentionally trying to get this error below will give us the SEGV_ACCERR fault*/
	char *ptr="example";
	*ptr='a';
	return 0;
}

/*OUTPUT : - 
$ ./a.out 
signo == 11 , fault addr = 0x80487D8 

segmentation fault due to violation of memory access permission 
*/
