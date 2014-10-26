
/*SIGACTION using normal signal handler 
see sigaction_note to see the details about sigaction 

* The sa_mask field provides a set of signals that the system should block for the duration
* of the execution of the signal handler. This allows programmers to enforce proper protection 
* from reentrancy among multiple signal handlers. The signal currently being
* handled is also blocked unless the SA_NODEFER flag is set in sa_flags . You cannot block
* SIGKILL or SIGSTOP ; the call will silently ignore either in sa_mask .
*/


#include<unistd.h>
#include<stdio.h>
#include<sys/signal.h>
#include<stdlib.h>

/*Oops!! Signal handler looks so messy */
void myHandler(int signum)
{
	if(signum == SIGTSTP)
		puts("SIGTSTP caught\n");
	puts("Going to sleep Inside signal handler for 10 sec\n");
	puts("This is the region where CTRL+C will not work as per signal mask set on sigaction()\n");
	fflush(stdin);
	int a = 0;
	puts("\nPress 1 to exit\n");
	fscanf(stdin,"%d",&a);
	if(a == 1)
	{
		fflush(stdout);
		exit(0);
	}
}

int main()
{
	struct sigaction act;
	int ret;
	sigset_t my_mask;
	
	ret = sigemptyset(&my_mask);
	if(ret == -1)
		perror("sigemptyset");

	ret = sigaddset(&my_mask,SIGINT);
	if(ret == -1)
		perror("sigaddset");

	act.sa_handler = &myHandler;
	act.sa_mask = my_mask;
	act.sa_flags = 0;	
	puts("\nPress CTRL+Z to switch to signal handler \n");
	ret = sigaction(SIGTSTP,&act,NULL);
	if(ret == -1)
		perror("sigaction");

	while(1);
	return 0;
}

/*OUTPUT :- 
$ ./a.out
Press CTRL+Z to switch to signal handler 

^ZSIGTSTP caught

Going to sleep Inside signal handler for 10 sec

This is the region where CTRL+C will not work as per signal mask set on sigaction()


Press 1 to exit

^C^C^C^C^C^C
1
*/
