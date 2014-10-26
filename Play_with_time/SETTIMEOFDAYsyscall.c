/*Note: timezone is no longer used; this information is kept outside the kernel.

     The system's notion of the current Greenwich time and the current time zone is obtained with
     the gettimeofday() system call, and set with the settimeofday() system call.  The time is
     expressed in seconds and microseconds since midnight (0 hour), January 1, 1970.  The resolu-
     tion of the system clock is hardware dependent, and the time may be updated continuously or
     in ``ticks''.  If tp or tzp is NULL, the associated time information will not be returned or
     set.
* settimeofday() may only be executed by the superuser.

*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
int main()
{
	/* The following example sets the current time to saturday 
	in the middle of december 1970*/
	int ret;
	struct timeval tv = { .tv_sec = 31415926,
			      .tv_usec = 271828 };

	ret = settimeofday(&tv,NULL);
	if(ret == -1)
		perror("settimeofday");
	else
	{
		if((system("date")) == -1)
			perror("system");
	}
	return 0;
}

/*OUTPUT :- 
$ ./a.out
Wed Dec 30 20:08:46 IST 1970
*/
