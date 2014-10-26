/*Program to check termination of child using watpid(), the child can be terminated by user only
Reference MAN page of waitpid() */
#include <sys/wait.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <stdio.h>

int main(int argc, char *argv[]) 
{
	pid_t pid, wpid; 
	int status;

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
	else 
	{ /* Code executed by parent */ 
		do 
		{ 
			wpid = waitpid(pid, &status, WUNTRACED | WCONTINUED);
			if (wpid == -1) 
			{ 
				perror("waitpid"); 	
				exit(EXIT_FAILURE); 
			}

			if (WIFEXITED(status)) 
				printf("exited, status=%d\n", WEXITSTATUS(status)); 
			else if (WIFSIGNALED(status)) 
			 	printf("killed by signal %d\n", WTERMSIG(status));
			else if (WIFSTOPPED(status))
			 	printf("stopped by signal %d\n", WSTOPSIG(status)); 
			else if (WIFCONTINUED(status)) 
				 printf("continued\n"); 
		 } while (!WIFEXITED(status) && !WIFSIGNALED(status)); 
		exit(EXIT_SUCCESS);
	} 
}

/*OUPUT :- 
$ ./a.out &
[1] 3859
Child PID is 3860

$  kill -STOP 3860
stopped by signal 19

$  kill -CONT 3860
continued

$  kill -TERM 3860
killed by signal 15
[1]+  Done                    ./a.out
*/
