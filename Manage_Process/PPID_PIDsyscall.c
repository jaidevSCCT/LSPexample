/* Program to obtain ProcessID and Parent ProcessId using getpid() and getppid() */
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
	pid_t proID,parntProID;

	proID = getpid();

	parntProID = getppid();

	printf("My PID = %d \n",proID);

	printf("My Parent's PID = %d \n",parntProID);

	return 0;
}

/*OUTPUT
  $ ./executable
My PID = 24900 
My Parent's PID = 24378 
Here Parent's id is BASH in my system , it may different for your systems 
4 S root     24378 24369  0  80   0 -  1436 wait   11:32 pts/0    00:00:00 bash

getpid() - The getpid() system call returns the process ID of the invoking process.
getppid() - The getppid() returns the process ID of the invoking process's parent.
 */
