/*Linux provides several system calls for retrieving and setting a process’s nice value. 
* The simplest is nice() :
#include <unistd.h>
int nice (int inc);
* A successful call to nice() increments a process’s nice value by inc and returns the
* newly updated value. Only a process with the CAP_SYS_NICE capability (effectively, processes
* owned by root) may provide a negative value for inc , decreasing its nice value
* & and thereby increasing its priority. Consequently, nonroot processes may only lower
* their priorities (by increasing their nice values).
* On error, nice() returns −1 . However, because nice() returns the new nice value, −1
* is also a successful return value. To differentiate between success and failure, you can
* zero out errno before invocation and subsequently check its value.*/
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
int main()
{
	int ret,value;
	extern int errno;
	/*Get current nice value*/
	value = nice(0);
	printf("Current nice value is %d \n",value);
	
	/*Setting nice value of 5 */
	value = 5 - value;
	errno = 0;
	ret = nice(value);
	if(ret == -1 && errno != 0)
		perror("nice");
	else
		printf("Nice value is now %d \n",ret);
	return 0;
}

/*OUTPUT :-
$ ./a.out
Current nice value is 0 
Nice value is now 5 
*/
