/* 
* asctime() converts a tm structure - broken downtime - to an ASCII string
* it returns a pointer to a statically allocated string. A subsequent call to any time func-
* tion may overwrite this string; asctime( ) is not thread-safe. */
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	time_t rawtime;
	struct tm *mt;
	char *retTime;
	

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
			retTime = asctime(mt); // Similarly asctime(localtime(&rawtime));
			if( retTime == NULL)
                		perror("asctime");
			printf("Current time is : %s\n",retTime);
		}
	}  
	return 0;
}

/*OUTPUT :- 
$ ./a.out
Current time is : Sat Jul 2 12:24:58 2014*/
