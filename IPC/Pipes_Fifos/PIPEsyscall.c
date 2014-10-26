/*====================PIPES=========================*/
/*Pipes are provided with all flavors of unix.A pipe is created by the pipe
* function and provides a one-way (unidirectional) flow of data.
* Two file descriptors are returned fd[0] ,which is open for reading 
* fd[1] ,which is open writing.
* The S_ISFIFO macro can be used to determine if a descriptor or file is either a pipe of fifo.
* for pipe use fstat function and for fifo use fstat,stat or lstat. */


/*Example : client-server program using pipe
------> The main function creates two pipes and forks a child.
------> The client then runs into the parent process and server on child 
------> The first pipe is used to send the pathname from the client to the server
	, and the second pipe is used to send the contents of that file from the 
	server to the client. */

/* As per the below program we need two pipes for bidirectional flow 
Therefore, The actual steps are as follows 
------> create pipe1(fd[0] and fd[1]) and pipe2(fd[0] and fd[1])
------> Parent closes read end of pipe1(fd[0]) and write end for pipe2(fd[1])
------> Child closes write end of pipe1(fd[1] and read end of pipe2(fd[0])) */

/*=================HEADERS============================*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<errno.h>
/*====================================================*/

#define MAXSIZ 4096   /*4 kb*/
void client(int,int);
void server(int,int);

int main()
{
	int pipe1[2],pipe2[2]; // Two pipes 
	pid_t child_pid;
	int ret;

	/*Creating two pipes*/
	ret = pipe(pipe1);
	if(ret == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	ret = pipe(pipe2);
        if(ret == -1)
        {
                perror("pipe");
                exit(EXIT_FAILURE);
        }
	
	if((child_pid = fork()) == 0) /*Child*/
	{
		close(pipe1[1]);
		close(pipe2[0]);

		server(pipe1[0],pipe2[1]);
		exit(0);
	}

	/* parent */
	close(pipe1[0]);
	close(pipe2[1]);

	client(pipe1[1],pipe2[0]);

	ret = waitpid(child_pid,NULL,0); /*Wait for child to terminate*/
	if(ret == -1)
		perror("waitpid");
	return 0;
}


void client(int writefd, int readfd)
{
	size_t len,writelen,readlen;
	char buf[MAXSIZ];
	/*Read Pathname from the stdin*/
	fprintf(stdout,"Enter a pathname with file eg: /home/pc/file.txt \n");
	fflush(stdout);
	/*fgets guaranteed NULL byte at the end*/
	if((fgets(buf,MAXSIZ,stdin)) == NULL)  /* Reading from standard input*/
		perror("fgets");
	len = strlen(buf);
	if(buf[len-1] == '\n')	/*delete new line from fgets()*/
		len--;
	/*Write pathname to PIPE (IPC channel)*/
	writelen = write(writefd,buf,len);
	if(writelen == -1)
		perror("write");
	else
	{
		fprintf(stdout,"Written number of bytes to pipe1[1]  is %d \n",writelen);
		fflush(stdout);
	}
	
	/*Reading the error or content of the file from the pipe and writing it to stdout*/
	readlen = read(readfd,buf,MAXSIZ);
	if(readlen == -1)
		perror("read");
	else
		write(STDOUT_FILENO,buf,readlen);
}


void server(int readfd, int writefd)
{
	int fd;
        size_t len,readlen;
        ssize_t rdlen;
        char buf[MAXSIZ + 1];
        /*Read Pathname from the IPC channel*/
	readlen = read(readfd,buf,MAXSIZ);
	if(readlen == -1)
		perror("read");
	 else
        {
                fprintf(stdout,"Number of bytes Read %d \n",readlen);
                fflush(stdout);
        }

	buf[readlen] = '\0'; /*Null terminate pathname*/
	if( (fd = open(buf,O_RDONLY)) < 0)
	{
		/*error : must tell to client*/
		
		snprintf(buf+readlen,sizeof(buf)-readlen,": can't open , %s \n",strerror(errno));
		len = strlen(buf);
		if((write(writefd,buf,len)) == -1)
			perror("write");
	}
	else
	{
		/*open success then copy file content to IPC channel*/
		rdlen = read(fd,buf,MAXSIZ);
		if(rdlen == -1)
			perror("read");
		else
			write(writefd,buf,rdlen);
		if(close(fd) == -1)
			perror("close");
	}
}

/*OUTPUT :- 
$ ./a.out
 
Enter a pathname with file eg: /home/pc/file.txt 
/etc/network/interfaces
Written number of bytes to pipe1[1]  is 23 
Number of bytes Read 23 
# interfaces(5) file used by ifup(8) and ifdown(8)
auto lo
iface lo inet loopback
*/
