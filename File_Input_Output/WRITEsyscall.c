/* EXAMPLE TO WRTIE SOME CONTENT TO THE FILE USING BUFFER  
	gcc -Wall filename.c -o filename*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	int fd; // file descriptor 	
	ssize_t retlen; 	
	const char *buf = "I want to become great developer";
	fd = open("filename1.txt",O_RDWR | O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); // Reference man 2 open
	if(fd == -1)
		perror("open");
	
	retlen = write(fd,buf,strlen(buf));  // reference man 2 write 
	if(retlen == -1)
		perror("write");
	/* On success,the number of bytes written is returned,and the file position is updated*/
	if(close(fd) == -1)
		perror("close");
	return 0;
}

/* OUTPUT 
-rw-r--r-- 1 root root  32 Apr 30 23:39 filename1.txt
cat filename1.txt
I want to become great developer
*/
