/* sched_getcpu() 
 sched_getcpu - determine CPU on which the calling thread is running

sched_getcpu() returns the number of the CPU on which the calling thread is currently executing.*/
#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<sched.h>

int main()
{
	cpu_set_t set;
	int ret,i,cpu;

	printf("Current CPU = %d\n",sched_getcpu()); /*Lets check in which core current process is executing */

	CPU_ZERO(&set);		/*Clear all CPUs*/
	CPU_SET(0,&set);	/*allow CPU #0*/
	CPU_CLR(1,&set);	/*forbid CPU #1*/

	ret = sched_setaffinity(0,sizeof(cpu_set_t),&set); /* O for current process */
	if(ret == -1)
		perror("sched_setaffinity");

	for(i = 0;i < CPU_SETSIZE; i++)
	{
		cpu = CPU_ISSET(i,&set);
		printf("cpu = %i is %s \n",i,cpu ? "set" : "unset");
	}

	printf("After changing CPU = %d \n",sched_getcpu()); /*after forcing this process to run on core 0 or first lets check in which core it si executing */
	return 0;
}

/*OUTPUT :-
$ ./a.out
Current CPU = 1
cpu = 0 is set 
cpu = 1 is unset 
cpu = 2 is unset 
cpu = 3 is unset 
cpu = 4 is unset 
cpu = 5 is unset 
cpu = 6 is unset 
cpu = 7 is unset 
................
cpu = 1023 is unset
After changing CPU = 0
 */
