/*
SIGCONT
The kernel sends this signal to a process when the process is resumed after being
stopped. By default, this signal is ignored, but processes can catch it if they want to
perform an action after being continued. This signal is commonly used by terminals
or editors that wish to refresh the screen.
*/

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>

void myHandler(int signumber)
{
	/*Technically ,you shouldn't use printf()
	in a signal handler (Reference linux system programming)
	please see note.txt for the answer */
	if(signumber == SIGCONT)
		printf("SIGCONT signal caught successfully \n");
	exit(EXIT_SUCCESS);	
}

int main()
{
	if((signal(SIGCONT,myHandler)) == SIG_ERR)
	{
		perror("signal");
		exit(EXIT_FAILURE);
	}
	printf("Press ctrl+z to stop your current process \n");
	printf("Your PID is == %d\n",getpid());
	printf("To start your process again give command kill -CONT %d\n",getpid());
	for(;;)
		pause();
	return 0;
}

/*OUTPUT :- 
$ ./a.out
Press ctrl+z to stop your current process 
Your PID is == 5144
To start your process again give command kill -CONT 5144
^Z
[1]+  Stopped                 ./a.out

$ kill -CONT 5144
SIGCONT signal caught successfully
 */
