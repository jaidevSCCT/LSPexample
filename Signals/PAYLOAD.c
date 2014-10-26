/*How to get the payload using signal? ,we are sending payload from other process to give you
more clarification about the SIQUEUE system call*/


/*You have to run this program first, then you have to send siqueue() with payload 
from the other program which is name sigqueue() in this chapter*/
#include<unistd.h>
#include<stdio.h>
#include<sys/signal.h>
#include<stdlib.h>
void myhandler(int signum,siginfo_t * info,void *context)
{
	fprintf(stdout,"PAYLOAD sent from other process is %d \n ",info->si_int);
	if(info->si_code == SI_QUEUE )
		puts("The signal is sent by sigqueue()\n");
	exit(0);
}


int main()
{
	struct sigaction act; 
	int ret;
	sigset_t mask;
	fprintf(stdout,"MY PID IS %d \n",getpid()); 
	ret = sigemptyset(&mask); 
	if(ret == -1)
		perror("sigemptyset");
	act.sa_mask = mask;
	act.sa_flags = SA_SIGINFO;  
	act.sa_sigaction = &myhandler;
	ret = sigaction(SIGUSR1,&act,NULL);
	if(ret == -1)
		perror("sigaction");
	while(1);
	return 0;
}

/*OUTPUT:-
for output see siqueue() syscall */
