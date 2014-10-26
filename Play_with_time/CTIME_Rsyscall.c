/*
* ctime_r( ) converts a time_t to its ASCII representation:
On failure, it returns NULL. For example:
time_t t = time (NULL);
printf ("the time a mere line ago: %s", ctime_r(&t,buf));
Like asctime( ), ctime( ) returns a pointer to a static string. As this is not thread-safe,
threaded programs should instead use ctime_r( ), which operates on the buffer pro-
vided by buf. The buffer must be at least 26 characters in length.
*/
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	time_t rawtime;
	char buf[128];

  	rawtime = time(NULL);
	if(rawtime == (time_t) -1)
	{
		perror("time");
		_exit(EXIT_FAILURE);
	}
	else
	{
		if((ctime_r(&rawtime,buf)) == NULL)
			perror("ctime_r");
		else
			printf("Current time is : %s\n",buf);
	}  
	return 0;
}

/*OUTPUT :- 
$ ./a.out 
Current time is : Sat Jul 2 12:31:51 2014
*/
