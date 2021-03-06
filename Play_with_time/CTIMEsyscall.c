/*
* ctime( ) converts a time_t to its ASCII representation:
On failure, it returns NULL. For example:
time_t t = time (NULL);
printf ("the time a mere line ago: %s", ctime (&t));
Note the lack of newline. Perhaps inconveniently, ctime( ) appends a newline to its
returned string.
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
	char *buf;

  	rawtime = time(NULL);
	if(rawtime == (time_t) -1)
	{
		perror("time");
		_exit(EXIT_FAILURE);
	}
	else
	{
		buf = ctime(&rawtime);
		if(buf == NULL)
			perror("ctime");
		printf("Current time is : %s\n",buf);
	}  
	return 0;
}

/*OUTPUT :- 
$ ./a.out 
Current time is : Sat Jul 2 12:31:51 2014
*/
