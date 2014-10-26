/*
* The asctime() function converts the broken down time in the structure tm pointed at by *tm
* to the form shown in the example above.

* The asctime_r() function provides the same functionality as asctime() except the caller pro-
* vide the output buffer buf to store the result, which must be at least 26 characters long.

* Multithreaded programs (and developers who loathe poorly designed inter-faces) 
* should use asctime_r( ). Instead of returning a pointer to a statically allocated
* string, this function uses the string provided via buf, 
 */

#include<stdio.h>
#include<time.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	time_t rawtime;
	struct tm *mt;
	char buf[128];
	

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
			if((asctime_r(mt,buf)) == NULL) // Similarly asctime_r(localtime(&rawtime),buf);
                		perror("asctime_r");
			printf("Current time is : %s\n",buf);

		}
	}  
	return 0;
}

/*OUTPUT :- 
$ ./a.out 
Current time is : Sat Jul 19 12:31:51 2014
*/
