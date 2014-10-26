/* Program to see the use of rewind 
* rewind resets the position back to the start of the stream
* It is equivalent to fseek(stream,0,SEEK_SET)*/
#include<stdio.h>
#include<string.h>
#include<errno.h>
int main()
{
	FILE *stream;
	int fs,c,fp,fc;
	extern int errno;
	stream = fopen("file.txt","r");	// if file is not present it will give error
	if(stream == NULL)
	{
		perror("fopen");
		return 1;
	}
/* SEEK_CUR - The file position is set to the current position + offset */
	fs = fseek(stream,7,SEEK_CUR);
	if(fs == -1)
	{
		perror("fseek");
		return -1;
	}
	errno = 0;
	rewind(stream);	// Resets the position back to start
	if(errno)
		printf("Error in rewind \n");

	while((c = fgetc(stream)) != EOF)
	{
		fp = fputc(c,stdout);
		if(fp == EOF)
		{
			perror("fputc");
			return 1;
		}		
	}
	
	fc = fclose(stream);
	if(fc == EOF)
        	perror("fclose");

	return 0;	
}

/* OUTPUT :- 
Assuming file.txt contains "I want to become great developer"
	$ ./executable
	I want to become great developer
*/
	
