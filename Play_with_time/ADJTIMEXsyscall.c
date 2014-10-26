/*
Linux uses David L. Mills’ clock adjustment algorithm (see RFC 1305).
 The system call adjtimex() reads and optionally sets adjustment parameters for this algorithm. 
It takes a pointer to a timex structure, updates kernel parameters from field values,
 and returns the same structure with current kernel values. This structure is declared as follows:

struct timex {
    int modes;           // mode selector
    long offset;         // time offset (usec) 
    long freq;           // frequency offset (scaled ppm) 
    long maxerror;       // maximum error (usec) 
    long esterror;       // estimated error (usec) 
    int status;          // clock command/status 
    long constant;       // pll time constant 
    long precision;      // clock precision (usec) (read only) 
    long tolerance;      // clock frequency tolerance (ppm)
                            (read only)
    struct timeval time; // current time (read only) 
    long tick;           // usecs between clock ticks 
};

The modes field determines which parameters, if any, to set. 
It may contain a bitwise-or combination of zero or more of the following bits:

#define ADJ_OFFSET            0x0001 // time offset 
#define ADJ_FREQUENCY         0x0002 // frequency offset 
#define ADJ_MAXERROR          0x0004 // maximum time error 
#define ADJ_ESTERROR          0x0008 // estimated time error 
#define ADJ_STATUS            0x0010 // clock status 
#define ADJ_TIMECONST         0x0020 // pll time constant 
#define ADJ_TICK              0x4000 // tick value
#define ADJ_OFFSET_SINGLESHOT 0x8001 // old-fashioned adjtime()

Ordinary users are restricted to a zero value for mode.
 Only the superuser may set any parameters.
RETURN VALUE

On success, adjtimex() returns the clock state:

#define TIME_OK   0 // clock synchronized 
#define TIME_INS  1 // insert leap second 
#define TIME_DEL  2 // delete leap second 
#define TIME_OOP  3 // leap second in progress 
#define TIME_WAIT 4 // leap second has occurred 
#define TIME_BAD  5 // clock not synchronized 

On failure, adjtimex() returns -1 and sets errno.
*/

#include<stdio.h>
#include<sys/timex.h>

int main()
{
	struct timex adj;
	struct timeval time;
	int ret_timex;

	/* Setting mode to zero so that no values will be set */
	adj.modes = 0;

	ret_timex = adjtimex(&adj);
	if(ret_timex == -1)
		perror("adjtimex");
	else if(ret_timex == TIME_OK)
		printf("The clock is syncronized \n");
	else if(ret_timex == TIME_INS)
		printf("A leap second will be inserted\n");
	else if(ret_timex == TIME_DEL)
		printf("A leap second will be deleted \n");
	else if(ret_timex == TIME_OOP)
		printf("A leap second is in progress\n");
	else if(ret_timex == TIME_WAIT)
		printf("A leap second just occured \n");
	else if(ret_timex == TIME_BAD)
		printf("The Clock is not Synchronized \n");
	else
		printf("None of the Above \n");
	printf("===================================================\n");
	printf("LETS CHECK AND PRINT ALL THE RETURN STRUCT MEMBERS \n");
	printf("mode selector ------------------> %d \n",adj.modes);
	printf("time offset usec ---------------> %ld \n",adj.offset);
	printf("Frequency offset scaled ppm ----> %ld \n",adj.freq);
	printf("maximum error usec -------------> %ld \n",adj.maxerror);
	printf("estimated error usec -----------> %ld \n",adj.esterror);
	printf("clock status -------------------> %d \n",adj.status);
	printf("PLL time constant --------------> %ld \n",adj.constant);
	printf("clock presicion usec -----------> %ld \n",adj.precision);
	printf("clock freq tolerance ppm -------> %ld \n",adj.tolerance);
	printf("time in %ld.%06ld seconds \n",adj.time.tv_sec,adj.time.tv_usec);
	printf("mode selector ------------------> %ld \n",adj.tick);
	fflush(stdout);
	return 0;
}

/*OUTPUT :- 
# ./a.out 
The Clock is not Synchronized 
===================================================
LETS CHECK AND PRINT ALL THE RETURN STRUCT MEMBERS 
mode selector ------------------> 0 
time offset usec ---------------> 0 
Frequency offset scaled ppm ----> 0 
maximum error usec -------------> 16000000 
estimated error usec -----------> 16000000 
clock status -------------------> 64 
PLL time constant --------------> 2 
clock presicion usec -----------> 1 
clock freq tolerance ppm -------> 32768000 
time in 1405771114.427115 seconds 
mode selector ------------------> 10000
*/
