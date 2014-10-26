/*SIGVTALRM
The setitimer() function sends this signal when a timer created with the
ITIMER_VIRTUAL flag expires.
SIGPROF
The setitimer() function, when used with the ITIMER_PROF flag, generates this
signal when a profiling timer expires. The default action is to terminate the process.
SIGALRM
The alarm() and setitimer() (with the ITIMER_REAL flag) functions send this
signal to the process that invoked them when an alarm expires.*/

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/time.h>

void myHandler(int signumber)
{
	/*Technically ,you shouldn't use printf()
	in a signal handler (Reference linux system programming)
	please see note.txt for the answer */
	if(signumber == SIGALRM)
        	printf("%s is caught \n",sys_siglist[signumber]);
	else if(signumber == SIGVTALRM)
                printf("%s is caught \n",sys_siglist[signumber]);
	else if(signumber == SIGPROF)
                printf("%s is caught \n",sys_siglist[signumber]);
	exit(EXIT_SUCCESS);	
}

int main()
{
	int ret;
	struct itimerval curVal;

	if((signal(SIGVTALRM,myHandler)) == SIG_ERR)
	{
		perror("signal");
		exit(EXIT_FAILURE);
	}

	if((signal(SIGALRM,myHandler)) == SIG_ERR)
        {
                perror("signal");
                exit(EXIT_FAILURE);
        }

	if((signal(SIGPROF,myHandler)) == SIG_ERR)
        {
                perror("signal");
                exit(EXIT_FAILURE);
        }

	
	 /*  the timeslice of this process is 5 secs 
	then it will expire and then generates an alarm
	which is catching by signal using handler*/
	curVal.it_value.tv_sec = 5;
	curVal.it_value.tv_usec = 0;

	curVal.it_interval.tv_sec = 0; /*to reset the time */
	curVal.it_interval.tv_usec = 0;
	printf("Wait for sometime that you have provided \n");
	ret = setitimer(ITIMER_PROF,&curVal,NULL);  /*1st arguement can be ITIMER_PROF(SIGPROF),
							ITIMER_REAL(SIGLARM),ITIMER_VIRTUAL(SIGVTALRM)*/
	if(ret == -1)
		perror("setitimer");
	while(1);

	return 0;
}

/* OUTPUT :- 
$ ./a.out

Wait for sometime that you have provided 
SIGPROF is caught 
*/








