/*
Description for sigemptyset() , sigfillset() ........
* sigemptyset() initializes the signal set given by set , marking it empty (all signals 
* excluded from the set). sigfillset() initializes the signal set given by set , marking it
* full (all signals included in the set). Both functions return 0 . You should call one of these
* two functions on a signal set before further using the set.
* sigaddset() adds signo to the signal set given by set , while sigdelset() removes
* signo from the signal set given by set . Both return 0 on success or −1 on error, in which
* case errno is set to the error code EINVAL , signifying that signo is an invalid signal identifier.
* sigismember() returns 1 if signo is in the signal set given by set , 0 if it is not, and −1
* on error. In the latter case, errno is again set to EINVAL , signifying that signo is invalid.
*/

/*In this program SIGINT signal is added to the 'set' using sigaddset()
now this 'set' is used to block the added signal so you can block some of the signals 
like this example */

#include<stdio.h>
#include <stdlib.h>
#include <signal.h>

void myHandler(int signumber)
{
        /*Technically ,you shouldn't use printf()
        in a signal handler (Reference linux system programming)
        please see note.txt for the answer */
        if(signumber == SIGINT)
                printf("SIGINT signal caught successfully \n");
	fflush(stdout);
	fflush(stdin);
        exit(EXIT_SUCCESS);
}

int main()
{
	sigset_t mask; // set which is to be initialized 
	int ret;

	ret = sigemptyset(&mask); // initializes the signal set
	if(ret == -1)
		perror("sigemptyset");

	ret = sigaddset(&mask,SIGINT); // Adds signo to the signal set
	if(ret == -1)
		perror("sigaddset");
	
/* Here with the help of sigprocmask we are trying to block SIGINT */
	ret = sigprocmask(SIG_BLOCK,&mask,NULL); 
	if(ret == -1)
		perror("sigprocmask");

	if(signal(SIGINT,myHandler) == SIG_ERR)
		perror("signal");
	fprintf(stdout,"Press ctl+c\n");

	while(1);
	return 0;
}

/*OUTPUT :- 
$ ./a.out 
Press ctl+c
^C^C^C^C^C^C^C^C^C^C^C^C^C
(Here you can see that the SIGINT is blocked )
*/
    
