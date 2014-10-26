/* Program to check execution time of the code using clock() function 
* The clock() function returns the number of clock ticks of processor time 
* used by the program since it started executing. 
* You can convert the number of ticks into seconds by dividing by the value CLOCKS_PER_SEC.
* Note: In a multithreaded program, clock() returns the time used by all threads in the application;
* clock() returns the time since the program started, not the time since a specific thread started. 
* execute your program with -->  gcc -Wall filename.c -lm -o executable-name */

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

void my_delay( void )
{
	int i, j;
	double x;

	x = 0.0;
	for( i = 1; i <= 10000; i++ ) 
	{
        	for( j = 1; j <= 10000; j++ )
            		x += sqrt( (double) i * j );
    	}
}

int main( void )
{
	clock_t start_time, end_time;
    	start_time = clock();
	if(start_time == (clock_t) -1)
	{
		perror("clock");
		return -1;
	}
    	my_delay();
    	end_time = clock();
	if(end_time == (clock_t) -1)
        {
                perror("clock");
                return -1;
        }
    	printf( "Execution time was %lu seconds\n",(long) ((end_time - start_time) / CLOCKS_PER_SEC));
    	return EXIT_SUCCESS;
}

/* OUTPUT :- 
$ ./executable 
Execution time was 1 seconds
*/
