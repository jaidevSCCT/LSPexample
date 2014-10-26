/*According to MAN page
* sched_get_priority_max() returns the maximum  priority  value that can be used with
* the scheduling algorithm identified by policy.sched_get_priority_min() returns the 
* minimum priority value that can be used with the  scheduling  algorithm identified by policy.
* Supported policy values are SCHED_FIFO, SCHED_RR, SCHED_OTHER, and SCHED_BATCH.  
* Further details about these policies can be found in sched_setscheduler(2).

* Processes with numerically higher priority values are scheduled before processes with
* numerically lower priority values.Thus,the value returned by sched_get_priority_max()
* will be greater than the value returned by sched_get_priority_min().

* Linux  allows the static priority value range 1 to 99 for SCHED_FIFO and SCHED_RR and the 
* priority 0 for SCHED_OTHER and SCHED_BATCH.
* Scheduling priority ranges for the various policies are not alterable.

* The range of scheduling priorities may vary on other POSIX systems, thus it is a good idea
* for portable applications to use a virtual priority  range  and  map it to the interval
* given by sched_get_priority_max() and sched_get_priority_min().  POSIX.1-2001 requires a
* spread of at least 32 between the maximum and the minimum values for SCHED_FIFO and SCHED_RR.
*/

#define _GNU_SOURCE  /*for SCHED_IDLE and SCHED_BATCH*/
#include<stdio.h>
#include<unistd.h>
#include<sched.h>

int main()
{
	int max,min;
	/*===============SCHED_FIFO=============*/
	max = sched_get_priority_max(SCHED_FIFO);
	if(max == -1)
		perror("sched_get_priority_max");
	min = sched_get_priority_min(SCHED_FIFO);
	if(min == -1)
		perror("sched_get_priority_min");
	printf("SCHED_FIFO MIN AND MAX PRIORITIES IS %d AND %d \n",min,max);
	/*=====================================*/

	/*===============SCHED_RR=============*/
        max = sched_get_priority_max(SCHED_RR);
        if(max == -1)
                perror("sched_get_priority_max");
        min = sched_get_priority_min(SCHED_RR);
        if(min == -1)
                perror("sched_get_priority_min");
        printf("SCHED_RR MIN AND MAX PRIORITIES IS %d AND %d \n",min,max);
        /*=====================================*/

	/*===============SCHED_OTHER=============*/
        max = sched_get_priority_max(SCHED_OTHER);
        if(max == -1)
                perror("sched_get_priority_max");
        min = sched_get_priority_min(SCHED_OTHER);
        if(min == -1)
                perror("sched_get_priority_min");
        printf("SCHED_OTHER MIN AND MAX PRIORITIES IS %d AND %d \n",min,max);
        /*=====================================*/

	/*===============SCHED_BATCH=============*/
        max = sched_get_priority_max(SCHED_BATCH);
        if(max == -1)
                perror("sched_get_priority_max");
        min = sched_get_priority_min(SCHED_BATCH);
        if(min == -1)
                perror("sched_get_priority_min");
        printf("SCHED_BATCH MIN AND MAX PRIORITIES IS %d AND %d \n",min,max);
        /*=====================================*/

	 /*===============SCHED_IDLE=============*/
        max = sched_get_priority_max(SCHED_IDLE);
        if(max == -1)
                perror("sched_get_priority_max");
        min = sched_get_priority_min(SCHED_IDLE);
        if(min == -1)
                perror("sched_get_priority_min");
        printf("SCHED_IDLE MIN AND MAX PRIORITIES IS %d AND %d \n",min,max);
        /*=====================================*/

	return 0;
}

/*OUTPUT :- 
$ ./a.out
SCHED_FIFO MIN AND MAX PRIORITIES IS 1 AND 99 
SCHED_RR MIN AND MAX PRIORITIES IS 1 AND 99 
SCHED_OTHER MIN AND MAX PRIORITIES IS 0 AND 0 
SCHED_BATCH MIN AND MAX PRIORITIES IS 0 AND 0 
SCHED_IDLE MIN AND MAX PRIORITIES IS 0 AND 0
*/
