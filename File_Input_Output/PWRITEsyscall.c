/* EXAMPLE TO APPEND SOME CONTENT AT PARTICULAR POSITION USING PWRITE SYSTEM CALL  
	gcc -Wall filename.c -o filename*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
/* Assuming filename.txt contains some data and want to append more data after some position */
int main()
{
	int fd; // file descriptor 	
	ssize_t retlen; 	
	const char *buf = "APPENDING MY DATA";
	fd = open("filename.txt",O_RDWR); // Reference man 2 open
	if(fd == -1)
		perror("open");
	
	retlen = pwrite(fd,buf,strlen(buf),(off_t) 16);  // reference man 2 write 
	if(retlen == -1)
		perror("pwrite");
	/* On success,the number of bytes written is returned,and the file position is updated*/
	if(close(fd) == -1)
		perror("close");
	return 0;
}

/* OUTPUT 
-rw-r--r-- 1 root root  32 Apr 30 23:39 filename1.txt
cat filename1.txt
I want to becomeAPPENDING MY DATA
*/
