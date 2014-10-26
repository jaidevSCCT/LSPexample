/*Program to check termination of child using watid(), the child can be terminated by user only
Reference MAN page of waitpid() */
#include <sys/wait.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <stdio.h>

int main(int argc, char *argv[]) 
{
	pid_t pid, wpid; 
	siginfo_t infop;

	pid = fork(); 
	if(pid == -1) 
	{ 
		perror("fork"); 
		exit(EXIT_FAILURE);
	}
	if (pid == 0) 
	{ /* Code executed by child */ 
		printf("Child PID is %ld\n", (long) getpid()); 
		if (argc == 1) 
			pause(); /* Wait for signals */ 
		_exit(atoi(argv[1]));
	} 
	 
	 /* Code executed by parent */ 
		wpid = waitid(P_PID,pid,&infop, WEXITED | WSTOPPED | WCONTINUED);
		if (wpid == -1) 
		{ 
			perror("waitid"); 	
			exit(EXIT_FAILURE); 
		}
		printf("The Terminated child's PID is %ld \n ",(long)infop.si_pid);
		exit(EXIT_SUCCESS);
	 
}

/*OUPUT :- 
$ ./a.out &
[1] 3859
Child PID is 3860

 kill -STOP 3860
The Terminated child's PID is 3860 

*/
