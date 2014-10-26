/*
Description for sigprocmask() 
* The behavior of sigprocmask() depends on the value of how , which is one of the following flags:
SIG_SETMASK
	The signal mask for the invoking process is changed to set .
SIG_BLOCK
	The signals in set are added to the invoking process’s signal mask. In other words,
	the signal mask is changed to the union (binary OR) of the current mask and set .
SIG_UNBLOCK
	The signals in set are removed from the invoking process’s signal mask. In other
	words, the signal is changed to the intersection (binary AND) of the current mask,
	and the negation (binary NOT) of set . It is illegal to unblock a signal that is not
	blocked.
* If oldset is non-NULL, the previous value of the signal mask is stored in oldset.
* If  set  is  NULL, then the signal mask is unchanged (i.e., how is ignored), but 
* the current value of the signal mask is nevertheless returned in oldset (if it is not NULL).
* The use of sigprocmask() is unspecified in a multithreaded process; see pthread_sigmask(3).

* Blocking SIGKILL or SIGSTOP is not allowed. sigprocmask() silently ignores any attempt
* to add either signal to the signal mask.
*/

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
	sigset_t set; // set which is to be initialized 
	int ret;

	ret = sigemptyset(&set); // initializes the signal set
	if(ret == -1)
		perror("sigemptyset");

	ret = sigaddset(&set,SIGINT); // Adds signo to the signal set
	if(ret == -1)
		perror("sigaddset");
	
/* Here with the help of sigprocmask we are trying to block SIGINT */
	ret = sigprocmask(SIG_BLOCK,&set,NULL); 
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
