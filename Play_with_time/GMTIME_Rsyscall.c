/*
* The  gmtime()  function converts the calendar time timep to broken-down
* time representation, expressed in Coordinated Universal Time (UTC).  It
* may return NULL when the year does not fit into an integer.  The return
* value points to a statically allocated struct which might be  overwrit‐
* ten  by  subsequent  calls  to any of the date and time functions
* This function statically allocates the returned structure, and, again, is thus thread-
* unsafe. Threaded programs should use gmtime_r( ), which operates on the structure
* pointed at by result.

*/

#include<stdio.h>
#include<time.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	time_t rawtime,mk;
	struct tm *mt;
	struct tm gt;
	char *buf;

  	rawtime = time(NULL);
	if(rawtime == (time_t) -1)
	{
		perror("time");
		_exit(EXIT_FAILURE);
	}
	else
	{
		mt = gmtime_r(&rawtime,&gt);
		if(mt == NULL)
		{
			perror("gmtime_r");
			_exit(EXIT_FAILURE);
		}
		else
		{
			mk = mktime(mt);  // Similarly mktime(gmtime(&rawtime)); 
			if(mk == (time_t) -1)
			{
				perror("mktime");
				_exit(EXIT_FAILURE);
			}
			else
			{
				buf = ctime(&mk);
				if(buf == NULL)
					perror("ctime");
				printf("As per UTC time is : %s\n",buf);
				printf("Current time is as per our timezone:\n");
				system("date");
			}
		}
	}  
	return 0;
}

/*OUTPUT :- 
$ ./a.out 
As per UTC time is : Sat Jul 2 08:10:39 2014

Current time is as per our timezone:
Sat Jul 2 13:40:39 IST 2014
*/
