/* EXAMPLE TO CREATE A FILE USING OPEN SYSTEM CALL 
 gcc -Wall filename.c -o filename	*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	int fd; // file descriptor 		
	fd = open("filename.txt",O_RDWR | O_CREAT | O_EXCL);  // reference man 2 open
	if(fd == -1)
		perror("open");
	
	if(close(fd) == -1)
		perror("close");
	return 0;
}

/* OUTPUT 

filename.txt will be created 
Note :- The permissions of a created file are restricted by the process's current umask -- your current umask is 022
so file permission for newly created file will vary from system to system

*/
