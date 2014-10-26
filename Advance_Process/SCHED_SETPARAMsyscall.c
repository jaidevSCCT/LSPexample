/*
* sched_setparam()  sets  the scheduling parameters associated with the 
* scheduling policy for the process identified by pid.If pid is zero, 
* then the parameters of the calling process are set.  
* The interpretation of the argument param depends on the scheduling  policy
* of the process identified by pid.  
* See sched_setscheduler(2) for a description of the scheduling policies supported under Linux.

* sched_getparam()  retrieves  the scheduling parameters for the process identified by pid.  
* If pid is zero, then the parameters of the calling process are retrieved.

* sched_setparam() checks the validity of param for the scheduling policy of the process.
* The  value  param->sched_priority must lie within the range given by 
* sched_get_priority_min(2) and sched_get_priority_max(2).

struct sched_param {
           ...
           int sched_priority;
           ...
       };

This example assumes that 1 is a valid priority. It is, but portable applications
should make sure.
Note :- If you are getting an error of Invalid arguement then make sp.sched_priority=0
it will work.( EINVAL The argument param does not make sense for the current scheduling policy)
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
	fprintf(stdout,"Enter 1 to set your current process's scheduling priority \n");
	fprintf(stdout,"Enter 2 to get PIDs of other processes \n");
	fprintf(stdout,"Enter 3 to set other process's scheduling priority \n");
	fprintf(stdout,"Enter 4 to exit this program \n");

	scanf("%d",&input);	
	switch(input)
	{
		case 1 :
			sp.sched_priority = 1;
			ret =  sched_setparam(0,&sp); /* sched_setparam()*/
			if(ret == -1)
			{
				perror("sched_setparam");
				exit(EXIT_FAILURE);
			}
			else
				printf("Success\n");
			//break;
			goto myloop;
		case 2 :
			if(system("ps -e") == -1)  /*system()*/
				perror("system");
			//break;
			goto myloop;
		case 3 :
			sp.sched_priority = 1;
			fprintf(stdout,"Enter the PID to set the priority \n");
			scanf("%d",&Pid);
			pid = Pid;
			ret =  sched_setparam(pid,&sp); /* sched_setparam()*/
			if(ret == -1)
			{
				perror("sched_setparam");
				exit(EXIT_FAILURE);
			}
			else
				printf("Success\n");
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
$ ./a,out
Enter 1 to set your current process's scheduling priority 
Enter 2 to get PIDs of other processes 
Enter 3 to set other process's scheduling priority 
Enter 4 to exit this program 
1
Success
 */
