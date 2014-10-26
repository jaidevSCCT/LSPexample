
/*Program to catch SIGINT(CTRL + C) signal
* SIGINT
This signal is sent to all processes in the foreground process group when the user
enters the interrupt character (usually Ctrl-C). The default behavior is to terminate;
however, processes can elect to catch and handle this signal and generally do so to
clean up before terminating. 

* SIGQUIT
The kernel raises this signal for all processes in the foreground process group when
the user provides the terminal quit character (usually Ctrl-\). The default action is
to terminate the processes and generate a core dump.

* SIGTSTP
The kernel sends this signal to all processes in the foreground process group when
the user provides the suspend character (usually Ctrl-Z).

see note.txt for info about pause() 
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
		printf("%s(ctrl+c) is caught \n",sys_siglist[signumber]);
	else if(signumber == SIGQUIT)
        	printf("%s(ctrl+backslash) is caught \n",sys_siglist[signumber]);
	else if(signumber == SIGTSTP)
        	printf("%s(ctrl+z) is caught \n",sys_siglist[signumber]);
	exit(EXIT_SUCCESS);	
}

int main()
{
	printf("Press (ctrl+c) or (ctrl+backslash) or (ctrl+z) to terminate the program \n");
	if((signal(SIGINT,myHandler)) == SIG_ERR)
	{
		perror("signal");
		exit(EXIT_FAILURE);
	}

	if((signal(SIGQUIT,myHandler)) == SIG_ERR)
        {
                perror("signal");
                exit(EXIT_FAILURE);
        }

	if((signal(SIGTSTP,myHandler)) == SIG_ERR)
        {
                perror("signal");
                exit(EXIT_FAILURE);
        }
	
	for(;;)
		pause();
	return 0;
}

/* OUTPUT :- 
$ ./a.out
Press (ctrl+c) or (ctrl+backslash) or (ctrl+z) to terminate the program 
^CSIGINT(ctrl+c) is caught 
$ ./a.out 
Press (ctrl+c) or (ctrl+backslash) or (ctrl+z) to terminate the program 
^ZSIGTSTP(ctrl+z) is caught 
$ ./a.out 
Press (ctrl+c) or (ctrl+backslash) or (ctrl+z) to terminate the program 
^\SIGQUIT(ctrl+backslash) is caught*/

