/* sched_setscheduler()  sets both the scheduling policy and the associated parameters 
*   for the process whose ID is specified in pid.If pid equals zero, the scheduling policy and 
*   parameters of the calling process will be set.  The interpretation of the  argument  param
*   depends on the selected policy.  Currently, Linux supports the following "normal"
*   (i.e., non-real-time) scheduling policies:

*   SCHED_OTHER   the standard round-robin time-sharing policy;

*   SCHED_BATCH   for "batch" style execution of processes; and

*   SCHED_IDLE    for running very low priority background jobs.

*   The  following "real-time" policies are also supported, for special time-critical applications
*   that need precise control over the way
*   in which runnable processes are selected for execution:

*   SCHED_FIFO    a first-in, first-out policy; and

*   SCHED_RR      a round-robin policy.

*   Setting a scheduling policy other than SCHED_OTHER requires the CAP_SYS_NICE capabil-
*   ity. Consequently, the root user typically runs real-time processes. Since the 2.6.12
*   kernel, the RLIMIT_RTPRIO resource limit allows nonroot users to set real-time poli-
*   cies up to a certain priority ceiling.*/

/*In this snippet policy has been hardcorded with SCHED_FIFO to know more about 
*  setting pther policies see man pages.So therefore priorities also been hardcorded with 10
*  you can change the priorities according to you 
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
	fprintf(stdout,"Enter 1 to set your current process's scheduling policies \n");
	fprintf(stdout,"Enter 2 to get PIDs of other processes \n");
	fprintf(stdout,"Enter 3 to set other process's scheduling policies \n");
	fprintf(stdout,"Enter 4 to exit this program \n");

	scanf("%d",&input);	
	switch(input)
	{
		case 1 :
			sp.sched_priority = 10;
			ret =  sched_setscheduler(0,SCHED_FIFO,&sp); /* sched_setscheduler()*/
			if(ret == -1)
			{
				perror("sched_setscheduler");
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
			sp.sched_priority = 10;
			fprintf(stdout,"Enter the PID to set the policy \n");
			scanf("%d",&Pid);
			pid = Pid;
			ret =  sched_setscheduler(pid,SCHED_FIFO,&sp); /* sched_setscheduler()*/
			if(ret == -1)
			{
				perror("sched_setscheduler");
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
Enter 1 to set your current process's scheduling policies 
Enter 2 to get PIDs of other processes 
Enter 3 to set other process's scheduling policies 
Enter 4 to exit this program 
1
sched_setscheduler: Operation not permitted

NEED ROOT PERMISSION 
# ./a.out
Enter 1 to set your current process's scheduling policies 
Enter 2 to get PIDs of other processes 
Enter 3 to set other process's scheduling policies 
Enter 4 to exit this program 
1
Success
 */
