/*
* time representation, expressed relative to the user’s  specified  time‐
* zone.  The function acts as if it called tzset(3) and sets the external
* variables tzname with information about the current timezone,  timezone
* with  the difference between Coordinated Universal Time (UTC) and local
* standard time in seconds, and daylight to a non-zero value if  daylight
* savings  time  rules  apply  during  some part of the year.  The return
* value points to a statically allocated struct which might be  overwritten
* by  subsequent  calls  to any of the date and time functions.  The
* localtime_r() function does the same, but stores the data  in  a  user-
* supplied struct.  It need not set tzname, timezone, and daylight.

* localtime() is not thread safe 
* localtime_r() is thread safe
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
	char *buf;

  	rawtime = time(NULL);
	if(rawtime == (time_t) -1)
	{
		perror("time");
		_exit(EXIT_FAILURE);
	}
	else
	{
		mt = localtime(&rawtime);
		if(mt == NULL)
		{
			perror("localtime");
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
				printf("Current time is : %s\n",buf);
			}
		}
	}  
	return 0;
}

/*OUTPUT :- 
$ ./a.out 
Current time is : Sat Jul 19 13:48:29 2014
*/
