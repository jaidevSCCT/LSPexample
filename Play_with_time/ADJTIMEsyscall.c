/*
	Referred from RFC1305
     Network Time Protocol (Version 3)
======================================================================

The Unix/Linux clock model is based on two system calls, settimeofday
and adjtime, together with two kernel variables tick and tickadj. The
settimeofday call unceremoniously resets the kernel clock to the value
given, while the adjtime call slews the kernel clock to a new value
numerically equal to the sum of the present time of day and the (signed)
argument given in the adjtime call.

The Unix clock model assumes an interrupt produced by an onboard
frequency source, such as the clock counter and prescaler described
previously, to deliver a pulse train in the 100-Hz range. In priniciple,
the power grid frequency can be used, although it is much less stable
than a crystal oscillator. Each interrupt causes an increment called
tick to be added to the clock counter. The value of the increment is
chosen so that the clock counter, plus an initial offset established by
the settimeofday call, is equal to the time of day in microseconds.
===============================xx======================================
The adjtime() function gradually adjusts the system clock 
(as returned by gettimeofday(2)).  The amount of time by which the clock 
is to be adjusted is specified in the structure pointed to by delta.
  This structure has the following form:

           struct timeval {
               time_t      tv_sec;     // seconds 
               suseconds_t tv_usec;    // microseconds
           };

If the adjustment in delta is positive, then the system clock is speeded up by 
some small percentage (i.e., by adding a small amount of time to the clock value in each second) 
until the adjustment has been completed.  If the adjustment in delta is negative,
then the clock is slowed down in a similar fashion.
If a clock adjustment from an earlier adjtime() call is already in progress 
at the time of a later adjtime() call, and delta is not NULL for the later call, 
then the earlier adjustment is stopped, but any already completed part of that adjustment is not undone.
If  olddelta  is not NULL, then the buffer that it points to is used to return the
 amount of time remaining from any previous adjustment that has not yet been completed.

*/
#define _BSD_SOURCE
#include<stdio.h>
#include<sys/time.h>

int main()
{
	struct timeval delta;
	struct timeval olddelta;
	int retadj;

	/* speed up the clock by 1.5 seconds*/
	delta.tv_sec = 1; // 1 seconds
	delta.tv_usec = 500000; // .5 seconds 

	retadj = adjtime(&delta,&olddelta);
	if(retadj == -1)
		perror("adjtime");
	else
		printf("adjtime() successfully %d and the olddelta value is %u.%06u seconds \n",retadj,
				(unsigned int)olddelta.tv_sec,(unsigned int)olddelta.tv_usec);
	return 0;	
}

/*
OUTPUT:- 
Need root permission 
# sudo ./a.out
adjtime() successfully 0 and the olddelta value is 0.000000 seconds
Again run to check clock is adjusted or not you will get change in olddelta
# sudo ./a.out
adjtime() successfully 0 and the olddelta value is 1.487000 seconds
*/
