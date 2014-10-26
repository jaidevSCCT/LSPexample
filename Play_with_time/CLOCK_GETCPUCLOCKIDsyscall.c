/*
* The clock_getcpuclockid() function returns the clock ID 
* of the CPU-time clock of the process specified by pid. 
* If the process described by pid exists and the calling process has permission,
* the clock ID of this clock is stored in clock_id.
* If pid is zero, the clock ID of the CPU-time clock of the process marking the call is returned in clock_id.
* A process always has permission to obtain the CPU-time clock ID of another process. */

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	pid_t pid;
	int cpuclkid,input,Pid;
	clockid_t clockid;
	struct timespec ts;

myloop:
	fprintf(stdout,"Enter 1 to get your current program's process id \n");
	fprintf(stdout,"Enter 2 to get others process id \n");
	fprintf(stdout,"Enter 3 get clock ID of the CPU-time clock for specified process \n");
	scanf("%d",&input);
	
	switch(input)
	{
		case 1 : 
			fprintf(stdout,"Your PID %d \n",getpid());
			goto myloop;
			break;
		case 2 :
			if(system("ps -e") == -1)
			{
				perror("system");
				exit(EXIT_FAILURE);
			}
			else
			goto myloop;
			break;
		case 3 :
			fprintf(stdout,"Enter the PID to get the clock ID\n");
			scanf("%d",&Pid);
			pid = Pid;
			cpuclkid = clock_getcpuclockid(pid,&clockid);
			if(cpuclkid)
			{
				perror("clock_getcpuclockid");
				exit(EXIT_FAILURE);
			}
			else
			{
				if (clock_gettime(clockid, &ts) == -1) 
				{
               				perror("clock_gettime");
               				exit(EXIT_FAILURE);
           			}
				else
           				printf("CPU-time clock for PID %d is %ld.%09ld seconds\n",
                   				pid, (long) ts.tv_sec, (long) ts.tv_nsec);
			}
			break;
		default:
			fprintf(stdout,"Wrong Selection \n");
			break;
	}
	return 0;
}

/*OUTPUT :- 
$ ./a.out
Enter 1 to get your current program's process id 
Enter 2 to get others process id 
Enter 3 get clock ID of the CPU-time clock for specified process 
3
Enter the PID to get the clock ID
1
CPU-time clock for PID 1 is 3.951390093 seconds*/
