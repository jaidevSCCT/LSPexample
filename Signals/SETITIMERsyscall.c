/*The setitimer system call is a generalization of the alarm call. 
* It schedules the delivery of a signal at some point in the future after
* a fixed amount of time has elapsed.

* A program can set three different types of timers with setitimer:

*    If the timer code is ITIMER_REAL, the process is sent a SIGALRM signal 
* after the specified wall-clock time has elapsed.

*    If the timer code is ITIMER_VIRTUAL, the process is sent a SIGVTALRM signal
* after the process has executed for the specified time.
* Time in which the process is not executing (that is, when the kernel or another process is running) is not counted.

*    If the timer code is ITIMER_PROF, the process is sent a SIGPROF signal 
* when the specified time has elapsed either during the process's own execution or the 
* execution of a system call on behalf of the process.

* The first argument to setitimer is the timer code, specifying which timer to set. 
* The second argument is a pointer to a struct itimerval object specifying the new settings for that timer. 
* The third argument, if not null, is a pointer to another struct itimerval
* object that receives the old timer settings.

* A struct itimerval variable has two fields:

*    it_value is a struct timeval field that contains the time until the timer next expires 
* and a signal is sent. If this is 0, the timer is disabled.

*    it_interval is another struct timeval field containing the value to which the timer 
* will be reset after it expires. If this is 0, the timer will be disabled after it expires. 
* If this is nonzero, the timer is set to expire repeatedly after this interval.
*/


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
	
	 /*  the timeslice of this process is 5 secs 
	then it will expire and then generates an alarm
	which is catching by signal using handler*/
	curVal.it_value.tv_sec = 5;
	curVal.it_value.tv_usec = 0;

	curVal.it_interval.tv_sec = 0; /*to reset the time */
	curVal.it_interval.tv_usec = 0;
	printf("Wait for sometime that you have provided \n");
	ret = setitimer(ITIMER_VIRTUAL,&curVal,NULL);
	if(ret == -1)
		perror("setitimer");
	while(1);

	return 0;
}

/* OUTPUT :- 
$ ./a.out

Wait for sometime that you have provided 
SIGVTALRM is caught 
*/








