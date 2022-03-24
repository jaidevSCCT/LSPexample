/* Program to open a file stream via file descriptor 
	gcc -Wall filename.c -o filename */
 
#include<stdio.h>
#include<fcntl.h>

int main()
{
	FILE *stream; // File stream
	int fc; 
	int fd;	// file descriptor

	fd = open("file.txt",O_RDONLY);
	if(fd == -1)
		perror("open");

	
	stream = fdopen(fd,"r"); // This call converts an already open (fd) to a stream
	if(stream == NULL)
		perror("fopen");
	else
		printf("Sucess\n");

	fc = fclose(stream);
	if(fc ==EOF) 
		perror("fclose");

	return 0;	
}
/* OUTPUT :- 
	On Success , fdopen() returns valid file pointer  
*/




