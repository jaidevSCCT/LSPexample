/* times() stores the current process times in the struct tms that buf points to.  
* The struct tms is as defined in <sys/times.h>:

           struct tms {
               clock_t tms_utime;  // user time 
               clock_t tms_stime;  // system time
               clock_t tms_cutime; // user time of children 
               clock_t tms_cstime; // system time of children
           };


* The tms_utime field contains the CPU time spent executing instructions of the calling process. 
* The tms_stime field contains the CPU time spent in the system while executing tasks 
* on behalf of the calling process.The tms_cutime field contains the sum of the
* tms_utime  and  tms_cutime values for all waited-for terminated children. 
* The tms_cstime field contains the sum of the tms_stime and
* tms_cstime values for all waited-for terminated children.

* The call returns the number of clock ticks, monotonically
* increasing, since an arbitrary point in the past.

* A typical value of clock ticks per second is 100. 
* That is, in this case, there is a clock tick every 10 milliseconds or 0.01 second.
* To convert the clock_t values, returned by times, into seconds
* one has to divide by the number of clock ticks per second. 
*/


#include<stdio.h>
#include<sys/times.h>
#include<stdlib.h>

int main()
{
	struct tms buf;
	clock_t ret;
	int i = 0;

	while(i<10000000)
	{
		i++;
	}
	ret = times(&buf);
	if(ret == (clock_t) -1)
	{
		perror("times");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("user time consumed = %ld \n",(long)buf.tms_utime);
		printf("system time consumed = %ld \n",(long)buf.tms_stime); 
		printf("user time consumed by children = %ld \n",(long)buf.tms_cutime);
		printf("system time consumed by children = %ld \n ",(long)buf.tms_cstime);
	}
	return 0;
}

/*OUTPUT :- 
$ ./a.out

user time consumed = 3 
system time consumed = 0 
user time consumed by children = 0 
system time consumed by children = 0 

As per the above output, the system has spent 30 ms in executing instruction 
*/
