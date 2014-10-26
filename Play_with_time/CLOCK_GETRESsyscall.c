/* On Linux (and most other Unix systems), all of the functions that use POSIX clocks
require linking the resulting object file with librt. 
$ gcc -Wall -W -O2 –lrt -g -o snippet snippet.c */
/*
* clock_getres() function is used to get the resolution of the a given time source 
* The resolution of clocks depends on the implementation and cannot be configured by 
*  a particular process.
* for more info see man page of clock_getres  
*/


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
		ret = clock_getres(clocks[i],&getres);
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
clock = 0 , secs = 0 , nsecs = 1 
clock = 1 , secs = 0 , nsecs = 1 
clock = 2 , secs = 0 , nsecs = 1 
clock = 3 , secs = 0 , nsecs = 1 
*/
