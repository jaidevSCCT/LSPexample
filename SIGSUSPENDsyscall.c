/* Help program need to understand sigsuspend */
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

void myHandler(int signumber)
{
	if(signumber == SIGINT)
		puts("SIGINT caught :");
	else if(signumber == SIGQUIT)
		puts("SIGQUIT caught :");
}


int main(void)
{
	sigset_t newmask, oldmask, waitmask;
	int ret;

	puts("program begins from here : ");

	if (signal(SIGINT, myHandler) == SIG_ERR)
		perror("signal");
	if(signal(SIGQUIT,myHandler) == SIG_ERR)
		perror("signal");
	ret = sigemptyset(&waitmask);
	if(ret == -1)
		perror("sigemptyset");
	ret = sigaddset(&waitmask, SIGTSTP);
	if(ret == -1)
		perror("sigaddset");
	ret = sigaddset(&waitmask, SIGINT);
        if(ret == -1)
                perror("sigaddset");
	ret = sigaddset(&waitmask, SIGQUIT);
        if(ret == -1)
                perror("sigaddset");



	ret = sigemptyset(&newmask);
	if(ret == -1)
		perror("sigemptyset");
	sigaddset(&newmask, SIGINT);
	if(ret == -1)
		perror("sigaddset");
	ret = sigaddset(&newmask,SIGQUIT);
	if(ret == -1)
		perror("sigaddset");
	/* Here i have added SIGQUIT and SIGINT to the set so that at the 
	   time of execution of the critical region user cannot interrupt the program */
	/*SIGTSTP is also added to another set which is waitmask so that sigsuspend will block 
	  with this signal if we provide interrupt with SIGTSTP the only sigsupend will return 
	  and the program execution flow will continue or else it if we generate interrupt 
	  with other signal except SIGTSTP then the sigsuspend will not return and the program get 
	  terminated. */    

	/*
	 * Block SIGINT and SIGQUIT and save current signal mask.
	 */
	if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
		perror("sigprocmask");

	/*
	 * Critical region of code.
	 */
	/*====================================================*/
	/*Here you can write your critical region code i am putting sleep */
	puts("In Critical region: ");
	sleep(10);
	puts("Critical region ended: ");
	/*=====================================================*/
	/*
	 * Pause, allowing all signals except SIGTSTP.
	 */
	if (sigsuspend(&waitmask) != -1)
		perror("sigsuspend");

	puts("After return from sigsuspend: ");

	/*
	 * Reset signal mask which unblocks SIGINT.
	 */
	if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
		perror("sigprocmask");

	/*
	 * And continue processing ...
	 */
	puts("program exit: ");

	return 0;
}

