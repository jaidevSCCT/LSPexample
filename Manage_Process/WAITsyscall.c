/* Program to test the termination of child properly ?*/
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
        int status;
        pid_t pid;

	pid = fork();
        if(pid == 0) /* child */
                return 1;

        pid = wait(&status);
        if(pid == -1)
                perror("wait");

        printf("pid == %d\n",pid);

        if(WIFEXITED(status))
                printf("Normal Termination with exit status = %d\n",WEXITSTATUS(status));

        if(WIFSIGNALED(status))
                printf("Killed by a signal = %d \n",WTERMSIG(status),
			WCOREDUMP(status) ? "(dumped core)" : "");

        if(WIFSTOPPED(status))
                printf("Stopped by a signal = %d\n",WSTOPSIG(status));

        if(WIFCONTINUED(status))
                printf("Continued \n");

        return 0;
}

/*OUTPUT :- 
$ ./executable
pid == 3131
Normal Termination with exit status = 1
*/
