/*For more info refer man sigaction or refer sigaction note provided in 
this chapter */
/*The following values are valid for SIGFPE only. They explain the type of arithmetic error
that occurred:
FPE_FLTDIV
	The process performed a floating-point operation that resulted in division by zero.
FPE_FLTOVF
	The process performed a floating-point operation that resulted in an overflow.
FPE_FLTINV
	The process performed an invalid floating-point operation.
FPE_FLTRES
	The process performed a floating-point operation that yielded an inexact or invalid result.
	FPE_FLTSUB
	The process performed a floating-point operation that resulted in an out-of-range
subscript.
FPE_FLTUND
	The process performed a floating-point operation that resulted in an underflow.
FPE_INTDIV
	The process performed an integer operation that resulted in division by zero.
FPE_INTOVF
	The process performed an integer operation that resulted in an overflow.*/
#include<unistd.h>
#include<stdio.h>
#include<sys/signal.h>
#include<stdlib.h>
void myhandler(int signum,siginfo_t * info,void *context)
{
	/*Here printing the information from the signal caught */
	/*Refer sigaction note for more info  */
	
  	/* print the address that caused the fault */
	fprintf(stdout,"\nsigno == %d , fault addr = 0x%lX\n",info->si_signo,(long)info->si_addr);
	if(info->si_code == FPE_INTDIV)
                puts("\n Floating point exception due to division by zero\n");
	else 
		puts("\nUse more si_code Flags to check\n");
	exit(0);
}


int main()
{
	struct sigaction act;
	int ret;
	sigset_t mask; // mask to set 
	fprintf(stdout,"My PID is : %d\n",getpid());
	ret = sigemptyset(&mask); // Emptying the set see sigemptyset eg.
	if(ret == -1)
		perror("sigemptyset");
	act.sa_mask = mask;
	act.sa_flags = SA_SIGINFO; 
	act.sa_sigaction = &myhandler;
	ret = sigaction(SIGFPE,&act,NULL);
	if(ret == -1)
		perror("sigaction");
	int a;
	/*Intentionally trying to get the exception below*/
	a = 1 / 0 ; // It will give floating point exception
	return 0;
}

/*OUTPUT : - 
$ ./a.out 
My PID is : 3910

signo == 8 , fault addr = 0x804868E

 Floating point exception due to division by zero
*/
