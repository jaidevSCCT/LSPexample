/*Program to check termination of child using wait3(), the child can be terminated by user only
Reference MAN page of wait3() and for more usage option refer MAN page  */
#include <sys/wait.h>
#include <sys/types.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/resource.h>

int main(int argc, char *argv[]) 
{
	pid_t pid, wpid; 
	int status;
	struct rusage usage;

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
			wpid = wait3(&status, WUNTRACED | WCONTINUED,&usage);
			if (wpid == -1) 
			{ 
				perror("waitpid"); 	
				exit(EXIT_FAILURE); 
			}
			
			printf("shared memory size : %ld \n",usage.ru_ixrss);
			printf("Maximum Resident set size : %ld \n",usage.ru_maxrss);
			printf("Unshared data size : %ld \n",usage.ru_idrss);
			printf("Unshared stack size : %ld \n",usage.ru_isrss);
			printf("page reclaims : %ld \n",usage.ru_minflt);
			printf("page Faults : %ld \n",usage.ru_majflt);
			printf("Swap operations  : %ld \n",usage.ru_nswap);
			printf("Block input operation : %ld \n",usage.ru_inblock);
			printf("Block output operation : %ld \n",usage.ru_oublock);	
			printf("Messages sent : %ld \n",usage.ru_msgsnd);
			printf("Messages recieved : %ld \n",usage.ru_msgrcv);
			printf("Signals Recieved: %ld \n",usage.ru_nsignals);
			printf("Voluntary context switches : %ld \n",usage.ru_nvcsw);		
			printf("InVoluntary context switches : %ld \n",usage.ru_nivcsw);			
	
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
shared memory size : 0 
Maximum Resident set size : 60 
Unshared data size : 0 
Unshared stack size : 0 
page reclaims : 53 
page Faults : 0 
Swap operations  : 0 
Block input operation : 0 
Block output operation : 0 
Messages sent : 0 
Messages recieved : 0 
Signals Recieved: 0 
Voluntary context switches : 2 
InVoluntary context switches : 0 
stopped by signal 19


$  kill -CONT 3860
shared memory size : 0 
Maximum Resident set size : 60 
Unshared data size : 0 
Unshared stack size : 0 
page reclaims : 53 
page Faults : 0 
Swap operations  : 0 
Block input operation : 0 
Block output operation : 0 
Messages sent : 0 
Messages recieved : 0 
Signals Recieved: 0 
Voluntary context switches : 3 
InVoluntary context switches : 0 
continued


$  kill -TERM 3860
shared memory size : 0 
Maximum Resident set size : 244 
Unshared data size : 0 
Unshared stack size : 0 
page reclaims : 53 
page Faults : 0 
Swap operations  : 0 
Block input operation : 0 
Block output operation : 0 
Messages sent : 0 
Messages recieved : 0 
Signals Recieved: 0 
Voluntary context switches : 4 
InVoluntary context switches : 0 
killed by signal 15
[2]+  Done                    ./a.out

*/
