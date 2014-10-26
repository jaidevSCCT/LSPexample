/*For more info refer man sigaction or refer sigaction note provided in 
this chapter as a note */

/* Usage example
 * 
 * First, compile and run this program:
 *     $ gcc -Wall file.c
 *     $ ./a.out
 * 
 * It will print out its pid and uid . Use it from another terminal to send signal
 *     $ kill -2 <pid>  (signal sent from user)
 *     $ kill -20 <pid>
	or
	CTRL+c		(signal sent from kernel)
 */
#include<unistd.h>
#include<stdio.h>
#include<sys/signal.h>
#include<stdlib.h>
#include<time.h>
void myhandler(int signum,siginfo_t * info,void *context)
{
	/*Here printing the information from the signal caught */
	/*Refer sigaction note for more info  */
	fprintf(stdout,"\nsigno == %d\nPID == %d\nUID == %d\n",info->si_signo,info->si_pid,info->si_uid);
	fprintf(stdout,"errno == %d\nStatus == %d\n",info->si_errno,info->si_status);
	if(info->si_code == SI_KERNEL)
		puts("\nsignal sent from kernel(SI_KERNEL)\n");
	else if(info->si_code == SI_USER)
                puts("\nsignal sent from user(SI_USER)\n");
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
	ret = sigemptyset(&mask);
	if(ret == -1)
		perror("sigemptyset");
	
	act.sa_mask = mask;
	act.sa_flags = SA_SIGINFO; // for 
	act.sa_sigaction = &myhandler;
	ret = sigaction(SIGINT,&act,NULL);
	if(ret == -1)
		perror("sigaction");
	ret = sigaction(SIGTSTP,&act,NULL);
        if(ret == -1)
                perror("sigaction");
	while(1);
	return 0;
}

/*OUTPUT :- 
$ ./a.out
My PID is : 3558
^C
signo == 2
PID == 0
UID == 0
errno == 0
Status == 0

signal sent from kernel(SI_KERNEL)

*/
