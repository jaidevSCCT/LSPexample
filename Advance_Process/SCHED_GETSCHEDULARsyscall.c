/*A successful call to sched_getscheduler( ) returns the scheduling policy of the pro-
* cess represented by pid. If pid is 0, the call returns the invoking process’ scheduling
* policy. An integer defined in <sched.h> represents the scheduling policy: the first in,
* first out policy is SCHED_FIFO; the round-robin policy is SCHED_RR; and the normal pol-
* icy is SCHED_OTHER. On error, the call returns -1 (which is never a valid scheduling
* policy), and errno is set as appropriate.*/

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<sched.h>
int main()
{
	int policy,input,Pid;
	extern int errno;
	pid_t pid;

myloop:
	fprintf(stdout,"Enter 1 to get your current process's scheduling policies \n");
	fprintf(stdout,"Enter 2 to get PIDs of other processes \n");
	fprintf(stdout,"Enter 3 to get other process's scheduling policies \n");
	fprintf(stdout,"Enter 4 to exit this program \n");

	scanf("%d",&input);	
	switch(input)
	{
		case 1 :
			policy =  sched_getscheduler(0); /* sched_getscheduler()*/
			if(policy == -1)
			{
				perror("sched_getscheduler");
				exit(EXIT_FAILURE);
			}
			else if(policy == SCHED_FIFO)
				printf("SCHED_FIFO\n");
			else if(policy == SCHED_RR)
				printf("SCHED_RR\n");
			else if(policy == SCHED_OTHER)
				printf("SCHED_OTHER\n");
			else
				fprintf(stderr,"UNKNOWN POLICY! \n");
			//break;
			fflush(stderr);
			goto myloop;
		case 2 :
			if(system("ps -e") == -1)  /*system()*/
				perror("system");
			//break;
			goto myloop;
		case 3 :
			fprintf(stdout,"Enter the PID to get the policy \n");
			scanf("%d",&Pid);
			pid = Pid;
			policy =  sched_getscheduler(pid); /* sched_getscheduler()*/
                        if(policy == -1)
			{
                                perror("sched_getscheduler");
				exit(EXIT_FAILURE);
			}
                        else if(policy == SCHED_FIFO)
                                printf("SCHED_FIFO\n");
                        else if(policy == SCHED_RR)
                                printf("SCHED_RR\n");
                        else if(policy == SCHED_OTHER)
                                printf("SCHED_OTHER\n");
                        else
                                fprintf(stderr,"UNKNOWN POLICY! \n");
                        //break;
			fflush(stdin);
			fflush(stderr);
			goto myloop;
		case 4 :
			exit(EXIT_SUCCESS); /*to exit the program*/
		default:
			fprintf(stdout,"Wrong Selection \n");
	}
	return 0;
}


/*OUTPUT :-
$ ./a.out
Enter 1 to get your current process's scheduling policies 
Enter 2 to get PIDs of other processes 
Enter 3 to get other process's scheduling policies 
Enter 4 to exit this program 
1
SCHED_OTHER */
