/*Program to get seconds and useconds using gettimeofday() which extends time() function 
* A successful call to gettimeofday( ) places the current time in the timeval structure
* pointed at by tv, and returns 0. The timezone structure and the tz parameter are
* obsolete; neither should be used on Linux. Always pass NULL for tz.

* The timezone structure is obsolete because the kernel does not manage the time zone,
* and glibc refuses to use the timezone structure’s tz_dsttime field.
*/

#include<stdio.h>
#include<sys/time.h>

int main()
{
	int gettime;
	struct timeval tv;

	gettime = gettimeofday(&tv,NULL);
	if(gettime == -1)
	{
		perror("gettimeofday");
		return -1;
	}
	else
	{
	fprintf(stdout," Seconds ticking since unix epoch time : %ld  uSeconds : %ld\n",(long) tv.tv_sec,(long) tv.tv_usec);
	fflush(stdout);
	}
	return 0;
}

/* OUTPUT : -
$ ./executable
Seconds ticking since unix epoch time : 1404844568  uSeconds : 677747 
*/
