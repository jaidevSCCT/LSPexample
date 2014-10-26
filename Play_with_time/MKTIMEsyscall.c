
/*Description taken from man page 
* The  mktime() function converts a broken-down time structure, expressed as local time, to calendar time representation.  The function
* ignores the values supplied by the caller in the tm_wday and tm_yday fields.  The value  specified  in  the  tm_isdst  field  informs
* mktime() whether or not daylight saving time (DST) is in effect for the time supplied in the tm structure: a positive value means DST
* is in effect; zero means that DST is not in effect; and a negative value means that mktime() should  (use  timezone  information  and
* system databases to) attempt to determine whether DST is in effect at the specified time.

* The  mktime()  function modifies the fields of the tm structure as follows: tm_wday and tm_yday are set to values determined from the
* contents of the other fields; if structure members are outside their valid interval, they will be normalized (so that,  for  example,
* 40  October is changed into 9 November); tm_isdst is set (regardless of its initial value) to a positive value or to 0, respectively,
* to indicate whether DST is or is not in effect at the specified time.  Calling mktime() also sets the external variable  tzname  with
* information about the current timezone.

* If  the specified broken-down time cannot be represented as calendar time (seconds since the Epoch), mktime() returns (time_t) -1 and
* does not alter the members of the broken-down time structure.

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
			mk = mktime(mt);  // Similarly mktime(localtime(&rawtime)); 
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
Current time is : Sat Jul 2 12:31:51 2014
*/
