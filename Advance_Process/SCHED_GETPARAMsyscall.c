/*
* sched_getparam() retrieves the scheduling parameters for the process identified by pid.  
* If pid is zero, then the parameters of the calling process are retrieved.
struct sched_param {
           ...
           int sched_priority;
           ...
       };
*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<sched.h>
int main()
{
	int ret,input,Pid;
	extern int errno;
	pid_t pid;
	struct sched_param sp;

myloop:
	fprintf(stdout,"Enter 1 to get your current process's scheduling priority \n");
	fprintf(stdout,"Enter 2 to get PIDs of other processes \n");
	fprintf(stdout,"Enter 3 to get other process's scheduling priority \n");
	fprintf(stdout,"Enter 4 to exit this program \n");

	scanf("%d",&input);	
	switch(input)
	{
		case 1 :
			ret =  sched_getparam(0,&sp); /* sched_getparam()*/
			if(ret == -1)
			{
				perror("sched_getparam");
				exit(EXIT_FAILURE);
			}
			else
				printf("sp.sched_priority(PRIORITY) is %d\n",sp.sched_priority);			
			fflush(stderr);
			fflush(stdout);
			goto myloop;
		case 2 :
			if(system("ps -e") == -1)  /*system()*/
				perror("system");
			//break;
			goto myloop;
		case 3 :
			fprintf(stdout,"Enter the PID to get the priority \n");
			scanf("%d",&Pid);
			pid = Pid;
			ret =  sched_getparam(pid,&sp); /* sched_getparam()*/
                        if(ret == -1)
			{
                                perror("sched_getparam");
				exit(EXIT_FAILURE);
			}
			else
                        	printf("sp.sched_priority(PRIORITY) is %d\n",sp.sched_priority); 
                        fflush(stderr);
                        fflush(stdout);
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
Enter 1 to get your current process's scheduling priority 
Enter 2 to get PIDs of other processes 
Enter 3 to get other process's scheduling priority 
Enter 4 to exit this program 
1
sp.sched_priority(PRIORITY) is 0
*/
