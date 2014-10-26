/* Program to block I/O using select system call , here we are block standard input(keyboard)
	Difference between STDIN and STDIN_FILENO ?
They both refer to standard input.

STDIN is a stream. You use this with stream functions, like fscanf().

STDIN_FILENO is a file descriptor. You use this with lower level functions like read().

	gcc -Wall finemane.c -o executablename*/

#include<stdio.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>

#define TIMEOUT 5 	/* select timeout in seconds*/
#define BUFSIZE 1024	/*read buffer in bytes*/

int main(void)
{
	struct timeval tv;
	fd_set readfds;
	int ret;
	
	/* Wait on stdin for input*/
	FD_ZERO(&readfds); // removes all file descriptor from the specified set
	FD_SET(STDIN_FILENO,&readfds); // adds a file descriptor to a given set
	
	/*Wait upto five seconds*/
	tv.tv_sec = TIMEOUT;
	tv.tv_usec = 0;

	/*Now Block */
	ret = select(STDIN_FILENO + 1,&readfds,NULL,NULL,&tv);
	if(ret == -1)
	{
		perror("select");
		return 1;
	}
	else
	{
		printf("%d seconds elapsed. \n",TIMEOUT);
		return 0;
	}

	/*Is our file descriptor ready to read?*/

	if(FD_ISSET(STDIN_FILENO,&readfds)) // to test whether a file descriptor is in the set
	{
		char buf[BUFSIZE+1];
		int len;
	
		/*Guaranteed to not block */

		len = read(STDIN_FILENO,buf,BUFSIZE);
		if(len == -1)
		{
			perror("read");
			return 1;
		}

		if(len)
		{
			buf[len] = '\0';
			printf("read : %s \n",buf);
		}
		return 0;
	}

	fprintf(stderr,"This should not happen \n");
	return 1;

}
