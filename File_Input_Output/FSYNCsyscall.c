/* EXAMPLE TO FSYNC SYSTEM CALL
A successful close does not guarantee that the data has been successfully saved to disk, as the kernel defers writes.
It is not common for a file system to flush the buffers when the stream is closed. 
If you need to be sure that the data is physically stored use fsync  
	gcc -Wall filename.c -o filename*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(int argc,char *argv[])
{
	int fd; // file descriptor 	
	ssize_t retlen; 	
	const char *buf = "I want to become great developer";
	if(argc < 2)
        {
                fprintf(stdout,"uage %s <filename> ",argv[0]);
                return 1;
        }
	fd = open(argv[1],O_RDWR | O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); // Reference man 2 open
	if(fd == -1)
	{
		perror("open");
		return 1;
	}
	
	retlen = write(fd,buf,strlen(buf));  // reference man 2 write 
	if(retlen == -1)
		perror("write");
	/* On success,the number of bytes written is returned,and the file position is updated*/

	if(fsync(fd) == -1)
		perror("fsync");

	if(close(fd) == -1)
		perror("close");
	return 0;
}

