/*  Processor affinity refers to the likelihood of a process to be scheduled consistently on
* the same processor. The term soft affinity refers to the scheduler’s natural propensity
* to continue scheduling a process on the same processor. As we’ve discussed, this is a
* worthwhile trait. The Linux scheduler attempts to schedule the same processes on
* the same processors for as long as possible, migrating a process from one CPU to
* another only in situations of extreme load imbalance. This allows the scheduler to
* minimize the cache effects of migration, but still ensure that all processors
* in a system are evenly loaded.
* Sometimes, however, the user or an application wants to enforce a process-to-processor
* bond. This is often because the process is strongly cache-sensitive, and desires to remain
* on the same processor. Bonding a process to a particular processor and having the kernel
* enforce the relationship is called setting a hard affinity.*/
/* FOR MORE INFO PLEASE SEE MAN PAGES OF man CPU_SET(3) AND man cpuset(7) */
/*  The cpu_set_t data structure represents a set of CPUs.
* 

* The cpu_set_t  data  type is implemented as a bitset.
* However, the data structure treated as considered opaque: all manipulation of
* CPU sets should be done via the macros described in this page.

       The following macros are provided to operate on the CPU set set:

       CPU_ZERO()       Clears set, so that it contains no CPUs.

       CPU_SET()        Add CPU cpu to set.

       CPU_CLR()        Remove CPU cpu from set.

       CPU_ISSET()      Test to see if CPU cpu is a member of set.

       CPU_COUNT()      Return the number of CPUs in set.

* Where a cpu argument is specified, it should not produce side effects, 
* since the above macros may evaluate the argument more than once.
* The  first available CPU on the system corresponds to a cpu value of 0,
*  the next CPU corresponds to a cpu value of 1, and so on.  The
* constant CPU_SETSIZE (currently 1024) specifies a value one greater than 
* the maximum CPU number that can be stored in cpu_set_t.*/

#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<sched.h>

int main()
{
	cpu_set_t set;
	int ret,i,cpu;

	CPU_ZERO(&set);

	ret = sched_getaffinity(0,sizeof(cpu_set_t),&set);
	if(ret == -1)
		perror("sched_getaffinity");

	cpu = CPU_COUNT(&set);
        printf("No . of CPUs in your system : %d \n",cpu);


	for(i=0;i < CPU_SETSIZE; i++)
	{
		cpu = CPU_ISSET(i,&set);
		printf("cpu = %i is %s \n",i,cpu ? "set" : "unset");
	}
	return 0;
}

/*OUTPUT :- 
$ ./a.out
No . of CPUs in your system : 2 (Since mine system is dual core) 
cpu = 0 is set 
cpu = 1 is set 
cpu = 2 is unset 
cpu = 3 is unset 
cpu = 4 is unset 
cpu = 5 is unset 
cpu = 6 is unset 
cpu = 7 is unset 
cpu = 8 is unset
..................
cpu = 1020 is unset 
cpu = 1021 is unset 
cpu = 1022 is unset 
cpu = 1023 is unset 
*/
