/*Program to simultaneously check whether a read from stdin 
and a write to stdout will block*/
#include<stdio.h>
#include<unistd.h>
#include<sys/poll.h>

#define TIMEOUT 5	// Poll timeout in seconds

int main(void)
{
	struct pollfd fds[2]; // to see the structure refer man 2 poll 
	int ret;

	/*Watch stdin for input*/
	fds[0].fd = STDIN_FILENO;	// stdin
	fds[0].events = POLLIN;		//There is data to read
	
	/* Watch stdout for ability to write*/
	fds[1].fd = STDOUT_FILENO;	//stdout
	fds[1].events = POLLOUT;	// Writing will not block 

	ret = poll(fds,2,TIMEOUT*1000); 
	if(ret == -1)
	{
		perror("poll");
		return 1;
	}
	
	if(!ret)
	{
		printf("%d seconds elapsed. \n",TIMEOUT);
		return 0;
	}
/*The revent field is bitmask of events that wer witnessed on the file descriptor*/
	if(fds[0].revents & POLLIN) 	
		printf("stdin is readable \n");
	
        if(fds[1].revents & POLLOUT)
                printf("stdout is writable \n");

	return 0;
}

/*OUTPUT :- 
	$ ./poll
	stdout is writable

	$ ./poll < file.txt
	stdout is readable
	stdout is writable
*/


