/*
sigqueue() function, defined by POSIX, allows a process to send a signal with this
payload:
#include <signal.h>
int sigqueue (pid_t pid,
int signo,
const union sigval value);
sigqueue() works similarly to kill() . On success, the signal identified by signo is
queued to the process or process group identified by pid , and the function returns 0 .
The signal’s payload is given by value , which is a union of an integer and a void pointer:
union sigval {
int sival_int;
void *sival_ptr;
};
On failure, the call returns −1 and sets errno */
#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	int ret;
	union sigval value;
	
	value.sival_int = 100; 
	if(argc < 2)
	{
		fprintf(stdout,"Usage %s <PID> \n",argv[0]);
		exit(EXIT_FAILURE);
	}	
	pid = atoi(argv[1]);  // Converting bytearray to pid_t type
	
	ret = sigqueue(pid,SIGUSR1,value);
	if(ret == -1)
		perror("sigqueue");
	else
		fprintf(stdout,"Payload send to this PID %d\n",pid);
	return 0;
}

/*OUTPUT :- 
Terminal 2
$ ./a.out 5475     // 5475 is pid 
Payload send to this PID 5475

Terminal 1 
$ ./a.out 
MY PID IS 5475 
PAYLOAD sent from other process is 100 
 The signal is sent by sigqueue()
*/
