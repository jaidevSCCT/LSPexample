/* EXAMPLE TO CREATE A FILE USING CREAT SYSTEM CALL WITH PERMISSIONS  
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
	if(argc < 2)
	{
		fprintf(stdout,"uage %s <filename> ",argv[0]);
		return 1;
	}
	fd = creat(argv[1],0644); // Reference man 2 creat
	if(fd == -1)
		perror("creat");
	
	if(close(fd) == -1)
		perror("close");
	return 0;
}

/* OUTPUT 
-rw-r--r-- 1 root root    0 Apr 30 22:32 filename.txt
filename.txt will be created with the given permission  
*/
