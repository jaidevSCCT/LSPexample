/* EXAMPLE TO CREATE A FILE USING OPEN SYSTEM CALL WITH PERMISSIONS  
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
	umask(0);
	fd = open("filename.txt",O_RDWR | O_CREAT | O_EXCL,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH); // Reference man 2 open
	if(fd == -1)
		perror("open");
	
	if(close(fd) == -1)
		perror("close");
	return 0;
}

/* OUTPUT 
-rw-rw-r-- 1 root root    0 Apr 30 22:32 filename.txt
filename.txt will be created with the given permission  
Note :- You can call umask(0); before using open() so that the mode you specify in open() won't be altered. 
*/
