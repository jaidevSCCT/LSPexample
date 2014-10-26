/* EXAMPLE TO READ THE CONTENT OF FILE IN BUFFER USING PREAD sys call  
	gcc -Wall filename.c -o filename*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

#define MYBUF 256

int main()
{
	int fd; // file descriptor 	
	ssize_t retlen; // return len bytes from read system calls	
	char buf[MYBUF];
	fd = open("filename.txt",O_RDONLY); // Reference man 2 open
	if(fd == -1)
		perror("open");
// This call reads up to count bytes into buf from the file descriptor fd at file position 22	
	retlen = pread(fd,buf,(size_t) 9,(off_t)22); 
	if(retlen == -1)
		perror("pread");

	buf[retlen] = '\0';
	printf("%s",buf);

	if(close(fd) == -1)
		perror("close");
	return 0;
}

/* OUTPUT 
Assuming filename.txt contains "I want to become great developer"

The buf will print on "developer" 
*/
