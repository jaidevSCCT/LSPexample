/*
* difftime( ) returns the number of seconds that have elapsed between two time_t 
* values, cast to a double:
* #include <time.h>
* double difftime (time_t time1, time_t time0);
* On all POSIX systems, time_t is an arithmetic type, and difftime( ) is equivalent to
* the following, ignoring detection of overflow in the subtraction:
* (double) (time1 - time0)
* On Linux, because time_t is an integer type, there is no need for the cast to double.
* To remain portable, however, use difftime( )
*/
#include<unistd.h>
#include<stdio.h>
#include<time.h>
int main()
{
	time_t time1,time2;
	double dif_sec;

	time1 = time (NULL);
	if(time1 == (time_t) -1)
		perror("time");
	printf ("Process going for sleep for 3 seconds \n ");
	sleep((unsigned int)3);  // sleeping for 3 seconds

	time2 = time(NULL);
	if(time2 == (time_t) -1)
		perror("time");
	dif_sec = difftime (time2,time1);
	printf ("Program took %lf seconds to execute \n", dif_sec );
	return 0;
}

/*OUTPUT :- 
$ ./a.out 
Process going for sleep for 3 seconds 
 Program took 3.000000 seconds to execute
*/
