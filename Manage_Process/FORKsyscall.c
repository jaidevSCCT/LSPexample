/* Simple example which distinguishes the parent from the child */
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>

void  ChildProcess(void);     
void  ParentProcess(void);    

int  main(void)
{
	int status;
	pid_t  pid,pid1;
     	pid = fork();
    	pid1 = wait(&status);

     	if (pid == 0) 
          	ChildProcess();
	if(WIFEXITED(status))
	{
        	if(WEXITSTATUS(status) == 0)
          		ParentProcess();
	}
	return 0;
}

void  ChildProcess(void)
{
	printf("Iam the child of main() %d and my parent's pid is  %d \n",getpid(),getppid());
}

void  ParentProcess(void)
{
     	printf("Iam main() %d and my parent Bash's pid is %d\n",getpid(),getppid());
}


/* OUTPUT :- 
Iam main() 25898 and my parent Bash's pis is 24378
Iam the child of main() 25899 and main() pid is  25898 

Note :- Answer may vary from system to system 

Due to the fact that these processes are run concurrently, their output 
lines are intermixed in a rather unpredictable way. 
Moreover, the order of these lines are determined by the CPU scheduler. 
Hence, if you run this program again, you may get a totally different result. 

*/
