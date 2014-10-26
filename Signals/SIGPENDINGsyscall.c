/*
* When the kernel raises a blocked signal, it is not delivered. We call such signals
* pending. When a pending signal is unblocked, the kernel then passes it off to the process
* to handle.
* A successful call to sigpending() places the set of pending signals in set and returns
* 0 . On failure, the call returns −1 and sets errno to EFAULT , signifying that set is an invalid
* pointer.*/
#include<unistd.h>
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
	else if(signumber == SIGTSTP)
		printf("SIGTSTP signal caught successfully \n");
	fflush(stdout);
	fflush(stdin);
        exit(EXIT_SUCCESS);
}

int main()
{
	sigset_t mask; // set which is to be initialized 
	sigset_t wait_mask; // set in which pending signal will be added 
	int ret;

	ret = sigemptyset(&mask); // initializes the signal set
	if(ret == -1)
		perror("sigemptyset");

	ret = sigaddset(&mask,SIGINT); // Add signo to the signal set
	if(ret == -1)
		perror("sigaddset");
	ret = sigaddset(&mask,SIGTSTP); // Add signo to the signal set
        if(ret == -1)
                perror("sigaddset");

	ret = sigprocmask(SIG_BLOCK,&mask,NULL); // added signal set for blocking
        if(ret == -1)
                perror("sigprocmask");

        if(signal(SIGINT,myHandler) == SIG_ERR)
                perror("signal");

        if(signal(SIGTSTP,myHandler) == SIG_ERR)
                perror("signal");

     /* Block user interrupts while doing other processing. */
/*===============================================================*/
/*In this block you can do other work for example I am putting sleep of
	10 secs in the meantime SIGINT AND SIGTSTP will not work*/
	sleep(10);
/*===============================================================*/
     /* After a while, check to see whether any signals are pending. */
	ret = sigpending (&wait_mask);
	if(ret == -1)
		perror("sigpending");
	printf("\n");
	ret = sigismember(&wait_mask,SIGINT);
	if(ret == -1)
		perror("sigismember");
	else if(ret == 1)
       		puts("User has tried to kill the process");
	else
		puts("SIGINT is not added in the pending signsl set");

	ret = sigismember(&wait_mask,SIGTSTP);
        if(ret == -1)
                perror("sigismember");
        else if(ret == 1)
                puts("User has tried to stop the process");
        else
                puts("SIGTSTP is not added in the pending signsl set");
        return 0;

}

/*OUTPUT :- 
while running the code press ctrl+c after that ctrl+z
then wait for completion of the program execution you can see
the output below 
$ ./a.out
^C^C^C^C^C^C^C^Z^Z^Z^Z^Z^Z^Z^Z
User has tried to kill the process
User has tried to stop the process
*/ 
