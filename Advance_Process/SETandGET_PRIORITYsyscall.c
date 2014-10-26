/*These calls operate on the process, process group, or user,
 *  as specified by which and who. 
 *  The value of which must be one of PRIO_PROCESS, PRIO_PGRP, 
 *  or PRIO_USER, in which case who specifies a process ID, 
 *  process group ID, or user ID, respectively. If who is 0, the call operates
 *  on the current process ID, process group ID, or user ID,respectively.

 *  A call to getpriority( ) returns the highest priority 
 *  (lowest numerical nice value) of any of the specified processes.
 *  A call to setpriority( ) sets the priority of all specified processes to prio.
 *  As with nice( ), only a process possessing CAP_SYS_NICE may raise a process’ priority
 *  (lower the numerical nice value). Further, only a process with
 *  this capability can raise or lower the priority of a process not owned 
 *  by the invoking user.
 *  Like nice( ), getpriority( ) returns -1 on error. As this is also a successful return
 *  value, programmers should clear errno before invocation if they want to handle error
 *  conditions. Calls to setpriority( ) have no such problem; setpriority( ) always
 *  returns 0 on success, and -1 on error.
 =============================================================================
 Taken from man page 
 *  The  actual priority range varies between kernel versions.
 *  Linux before 1.3.36 had -infinity..15.  Since kernel 1.3.43 Linux has the range -20..19.
 *  Within the kernel, nice values are actually represented using the corresponding
 *  range 40..1 (since  negative  numbers are  error codes)
 *  and these are the values employed by the setpriority() and getpriority() system calls.
 *  The glibc wrapper functions for these system calls handle the translations between the 
 *  user-land and kernel representations of the nice value according to the formula unice = 20 - knice.
 */


#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/time.h>
#include<sys/resource.h>

int main()
{
	int ret,Pid,input,prio = 0;
	extern int errno;
	pid_t pid;

myloop:
	fprintf(stdout,"Enter 1 to get your current process's priority \n");
	fprintf(stdout,"Enter 2 to get PIDs of other processes \n");
	fprintf(stdout,"Enter 3 to get other process's priority \n");
	fprintf(stdout,"Enter 4 to set your current process's priority \n");
	fprintf(stdout,"Enter 5 to set your other process's priority \n");
	fprintf(stdout,"Enter 6 to exit this program \n");

	scanf("%d",&input);	
	switch(input)
	{
		case 1 :
			errno = 0;
			ret = getpriority(PRIO_PROCESS,0); /*getpriority()*/
			if(ret == -1 && errno != 0)
				perror("getpriority");
			else 
				fprintf(stdout,"Priority is : %d \n",ret);
			//break;
			goto myloop;
		case 2 :
			if(system("ps -e") == -1)  /*system()*/
				perror("system");
			//break;
			goto myloop;
		case 3 :
			errno = 0;
			fprintf(stdout,"Enter the PID to get the priority \n");
			scanf("%d",&Pid);
			pid = Pid;
			ret = getpriority(PRIO_PROCESS,pid);  /*getpriority()*/
			if(ret == -1 && errno != 0)
				perror("getpriority");
			else 
				fprintf(stdout,"Priority is : %d \n",ret);
			//break;
			fflush(stdin);
			fflush(stdout);
			goto myloop;
		case 4 :  
			errno = 0;
			fprintf(stdout," Enter -20 to 19 to set the priority \n");
			scanf("%d",&prio);
			ret = setpriority(PRIO_PROCESS,0,prio); /*setpriority()*/
			if(ret == -1 && errno != 0)
				perror("setpriority");
			else
				fprintf(stdout,"Priority set successfull \n");
			fflush(stdin);
			fflush(stdout);
			goto myloop;
		case 5 :
			errno = 0;
			fprintf(stdout,"Enter the PID to set the priority \n");
			scanf("%d",&Pid);
			pid = Pid;
			fprintf(stdout," Enter -20 to 19 to set the priority \n");
			scanf("%d",&prio);
			ret = setpriority(PRIO_PROCESS,pid,prio); /*setpriority()*/
			if(ret == -1 && errno != 0)
				perror("setpriority");
			else
				fprintf(stdout,"Priority set successfull \n");
			fflush(stdin);
			fflush(stdout);
			goto myloop;
		case 6 :
			exit(EXIT_SUCCESS); /*to exit the program*/
		default:
			fprintf(stdout,"Wrong Selection \n");
	}
	return 0;
}

/*OUTPUT :-  To set highest priority(lowest nice value) root privileges is required
  $ ./a.out
  Enter 1 to get your current process's priority 
  Enter 2 to get PIDs of other processes 
  Enter 3 to get other process's priority 
  Enter 4 to set your current process's priority 
  Enter 5 to set your other process's priority 
  Enter 6 to exit this program 
  4
  Enter -20 to 19 to set the priority 
  5
  Priority set successfull
 */


