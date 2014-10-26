/*    This example creates a new session.
 */
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main() 
{
//	pid_t pid;
	
	printf("original process group is %d\n", (int) getpgrp());
  	if (setsid() == -1)
    			perror("setsid");
  	else                                                                   
    		printf("new process group id is %d\n", (int) getpgrp());
 
	return 0;
}


/*OUTPUT :- 
$ sudo ./a.out 
original process group is 9340
new process group id is 9341
*/
