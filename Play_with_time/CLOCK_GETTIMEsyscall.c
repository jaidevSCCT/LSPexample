/*
* POSIX provides the clock_gettime( ) interface for obtaining the time of a specific time
* source. More useful, however, is that the function allows for nanosecond precision: */

#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<time.h>

int main()
{
	int ret,i;
	struct timespec getres;
	clockid_t clocks[] = {
                             CLOCK_REALTIME,
                             CLOCK_MONOTONIC,
                             CLOCK_PROCESS_CPUTIME_ID,
                             CLOCK_THREAD_CPUTIME_ID,
                             (clockid_t) -1 };

	for(i=0;clocks[i]!= (clockid_t) -1;i++)
	{
		ret = clock_gettime(clocks[i],&getres);
		if(ret == -1)
		{
			perror("clock_getres");
			return -1;
		}
		else
			printf("clock = %d , secs = %ld , nsecs = %ld \n",clocks[i],getres.tv_sec,getres.tv_nsec);
	}	
	return 0;
}

/* OUTPUT :- 
$ ./a.out
clock = 0 , secs = 1405440866 , nsecs = 375567450 
clock = 1 , secs = 2430 , nsecs = 571938189 
clock = 2 , secs = 0 , nsecs = 1177078 
clock = 3 , secs = 0 , nsecs = 1184931
*/
