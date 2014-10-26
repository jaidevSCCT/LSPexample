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

	CPU_ZERO(&set);		/*Clear all CPUs*/
	CPU_SET(0,&set);	/*allow CPU #0*/
	CPU_CLR(1,&set);	/*forbid CPU #1*/

	ret = sched_setaffinity(0,sizeof(cpu_set_t),&set); /* 0 for current process */
	if(ret == -1)
		perror("sched_setaffinity");
	
	for(i = 0;i < CPU_SETSIZE; i++)
	{
		cpu = CPU_ISSET(i,&set);
		printf("cpu = %i is %s \n",i,cpu ? "set" : "unset");
	}
	
	printf("CPU = %d \n",sched_getcpu());
	return 0;
}

/*OUTPUT :- 
$ ./a.out
cpu = 0 is set 
cpu = 1 is unset 
cpu = 2 is unset 
cpu = 3 is unset 
cpu = 4 is unset 
cpu = 5 is unset 
----------------
cpu = 1023 is unset
CPU = 0
*/
