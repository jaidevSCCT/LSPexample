/* Simple program to change parent's variable using vfork() 
Warning - Don't use vfork without knowing it */
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>


int global = 9;       /* Global variable in initialized data  */

int main()
{
	int local;        /* automatic variable on the stack */
	pid_t pid;

	local = 99;
	printf("Before vfork\n");   /* we don't flush stdio */
	pid = vfork();
    	if (pid == -1)
        	perror("vfork");
	else if (pid == 0) /* Child */
	{      
        	global++;                 /* modify parent's variables */
        	local++;
        	_exit(0);               /* child terminates */
    	}
    	/*
     	 Parent continues here.
     	*/
   	 printf("pid = %d, global = %d, local = %d\n", getpid(), global,local);
    	return 0;
}

/* OUTPUT :- 
$ ./executable
Before vfork
pid = 27091, global = 10, local = 100
*/
