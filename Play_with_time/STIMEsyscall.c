/*
* stime() sets the system’s idea of the time and date. 
* Time, pointed to by t, is measured in seconds from 00:00:00 GMT January 1, 1970.
* stime() may only be executed by the superuser.
*/


#define _SVID_SOURCE
#include<stdio.h>
#include<time.h>

int main()
{
	time_t systime,t = 1;
        int ret;

        ret = stime(&t); // Set time 1 seconds after the epoch
        if(ret == -1)
                perror("stime");

	systime = time(&t);
	if(systime == (time_t)-1)
	{
		perror("time");
		return -1;
	}

	fprintf(stdout,"Get time since January 1, 1970 is %ld seconds \n",(long)systime);
	fflush(stdout);
	return 0;	
}

/* OUTPUT :- warning improper value for time leads to change your system time
$ ./a.out 
Get time since January 1, 1970 is 1 seconds
$ date
Thu Jan  1 05:30:15 IST 1970
 */
