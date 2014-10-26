/*
* The  clock_settime() function shall set the specified clock, clock_id, to the value speci-
* fied by ts. Time values that are between two consecutive non-negative integer multiples of
* the  resolution of the specified clock shall be truncated down to the smaller multiple of
* the resolution.
* A clock may be system-wide (that is, visible to all processes) or  per-process  (measuring
* time  that  is  meaningful  only  within  a  process). All implementations shall support a
* clock_id of CLOCK_REALTIME as defined in <time.h>.  This  clock	represents  the  realtime
* clock for the system. For this clock, the values returned by clock_gettime() and specified
* by clock_settime() represent the amount of time (in seconds  and  nanoseconds)  since  the
* Epoch.  An  implementation  may also support additional clocks. The interpretation of time
* values for these clocks is unspecified.

* Setting the value of the CLOCK_REALTIME clock via clock_settime() shall have no effect on
* threads that are blocked waiting for a  relative  time  service based  upon  this  clock,
* including  the  nanosleep()  function; nor on the expiration of relative timers based upon
* this clock.  Consequently, these time services shall expire when  the  requested  relative
* interval elapses, independently of the new or old value of the clock.

* Setting the value of the CLOCK_REALTIME clock via clock_settime() shall have no effect on
* any thread that is blocked on a relative clock_nanosleep() call.  Consequently,	the  call
* shall return when the requested relative interval elapses, independently of the new or old
* value of the clock.

* On most systems, the only settable time source is CLOCK_REALTIME. Thus, the only
* advantage of this function over settimeofday( ) is that it offers nanosecond precision
* (along with not having to deal with the worthless timezone structure).
*/

/*  This program sets the clock forward 1 day. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main( void )
{
	struct timespec ts;

    	if( clock_gettime( CLOCK_REALTIME, &ts) == -1 ) 
	{
       		perror( "getclock" );
       		return EXIT_FAILURE;
    	}

    	ts.tv_sec += (60*60)*24L;  /* Add one day */
    	ts.tv_nsec = 0;
    	if( clock_settime( CLOCK_REALTIME, &ts) == -1 )
	{
       		perror( "setclock" );
       		return EXIT_FAILURE;
    	}
	else
	{
		printf(" the current time after forwaded to one day is :\n");
		system("date");		
	}
	return EXIT_SUCCESS;
}

/*OUTPUT :- 
$ ./a.out 
the current time after forwaded to one day is :
Sun Jul 2 12:17:56 IST 2014 */

