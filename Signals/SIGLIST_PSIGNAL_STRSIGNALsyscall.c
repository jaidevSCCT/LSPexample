/*
* Signal numbers start at 1 (generally SIGHUP ) and proceed linearly upward. There
* are about 31 signals in total, but most programs deal regularly with only a handful of
* them. There is no signal with the value 0, which is a special value known as the null
* signal. There’s really nothing important about the null signal—it doesn’t deserve a special
* name—but some system calls (such as kill() ) use a value of 0 as a special case.*/
/*
* In our examples thus far, we have hardcoded the names of the signals. But sometimes
* it is more convenient (or even a requirement) that you be able to convert a signal number
* to a string representation of its name. There are several ways to do this. One is to retrieve
* the string from a statically defined list:
* extern const char * const sys_siglist[];
* sys_siglist is an array of strings holding the names of the signals supported by the
* system, indexed by signal number.
*/

/*A better interface is strsignal() . It is not standardized, but Linux and many non-Linux
* systems support it:
* #define _GNU_SOURCE
* #include <string.h>
* char * strsignal (int signo);
* A call to strsignal() returns a pointer to a description of the signal given by signo . If
* signo is invalid, the returned description typically says so (some Unix systems that
* support this function return NULL instead). The returned string is valid only until the
* next invocation of strsignal() , so this function is not thread-safe.*/

#define _GNU_SOURCE
#include<stdio.h>
#include<string.h>
#include<signal.h>

int main()
{
	int i;
	printf("Enter any number between 1 to 31 to get your corresponding signal \n");
	scanf("%d",&i);fflush(stdin);

	printf("Getting signal name using sys_siglist[%d] is %s\n",i,sys_siglist[i]);	

	printf("Getting signal name using strdignal(%d) is %s\n",i,strsignal(i));
	fflush(stdout);
	return 0;
}
