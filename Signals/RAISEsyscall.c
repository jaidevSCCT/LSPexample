/*  The raise() function sends a signal to the calling process or thread. 
*  In a single-threaded program it is equivalent to

           kill(getpid(), sig);

       In a multithreaded program it is equivalent to

           pthread_kill(pthread_self(), sig);

If the signal causes a handler to be called, raise() will return only after the signal handler has returned.
  raise() returns 0 on success, and nonzero for failure.
*/
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void myHandler(int signumber)
{
	/*Technically ,you shouldn't use printf()
	in a signal handler (Reference linux system programming)
	please see note.txt for the answer */
	if(signumber == SIGINT)
		printf("%s is caught \n",sys_siglist[signumber]);
	exit(EXIT_SUCCESS);	
}

int main()
{
	if((signal(SIGINT,myHandler)) == SIG_ERR)
	{
		perror("signal");
		exit(EXIT_FAILURE);
	}
	printf("Sending interrupt to self after 5 sec\n");
	sleep(5);
	if(raise(2) > 0) // Sending signal to self with SIGINT
		perror("raise");
	return 0;
}

/* OUTPUT :- 
$ ./a.out
Sending interrupt to self after 5 sec
Interrupt is caught 
*/

