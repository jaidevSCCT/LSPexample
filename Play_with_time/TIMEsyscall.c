/*Program to obtain the current time of the system 
* using time() function. --> time_t time (time_t *t);
* The function time() returns the type time_t. 
* The time that is returned represents the number of seconds elapsed
* since 00:00 hours, Jan 1, 1970 UTC. It’s also called UNIX EPOCH time.
* Fun note: On February 13, 2009 at exactly 23:31:30 (UTC), UNIX time was equal to ’1234567890′.
 
* If the parameter t is not NULL, the function also writes the
* current time into the provided pointer.

* IMP Note :- time_t’s representation of “seconds elapsed since the epoch” is not 
* the actual number of seconds that have passed since that fateful moment in time.
* The Unix calculation assumes leap years are all years divisible by four, 
* and ignores leap seconds altogether.
* The point of the time_t representation is not that it is accurate, 
* but that it is consistent */

#include<stdio.h>
#include<time.h>

int main()
{
	time_t systime;
	time_t t ;
	
systime = time(&t);
	if(systime == (time_t)-1)
	{
		perror("time");
		return -1;
	}

	fprintf(stdout,"Number of hours since January 1, 1970 is %ld \n",(long)systime);
	fprintf(stdout,"Number of hours since January 1, 1970 using pointer is  : %ld \n",(long)t);
	fflush(stdout);
	return 0;	
}

/* OUTPUT :- 
$ ./executable 
Number of hours since January 1, 1970 is 1404843315 
Number of hours since January 1, 1970 using pointer is  : 1404843315
*/
