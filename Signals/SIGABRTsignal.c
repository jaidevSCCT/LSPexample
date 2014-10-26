/*SIGABRT
The abort() function sends this signal to the process that invokes it. The process
then terminates and generates a core file. In Linux, assertions such as assert() call
abort() when the conditional fails.
*/
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void myHandler(int signumber)
{
	/*Technically ,you shouldn't use printf()
	in a signal handler (Reference linux system programming)
	please see note.txt for the answer */
	if(signumber == SIGABRT)
		printf("%s signal caught \n",sys_siglist[signumber]);
		exit(EXIT_SUCCESS);	
}

int main()
{
	FILE *fp;
	if((signal(SIGABRT,myHandler)) == SIG_ERR)
	{
		perror("signal");
		exit(EXIT_FAILURE);
	}
   
  	printf("Going to open nofile.txt\n");
   	fp = fopen("nofile.txt","r");
   	if(fp == NULL)
   	{
      		printf("Going to abort the program\n");
      		abort();
   	}
   	printf("Going to close nofile.txt\n");
  	fclose(fp);
	for(;;)
		pause();
	return 0;
}

/*OUTPUT :- 
$ ./a.out
Going to open nofile.txt
Going to abort the program
SIGABRT signal caught  
*/
