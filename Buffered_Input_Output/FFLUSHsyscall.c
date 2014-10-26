/* Program to use fflush
* On invocation of this function ,any unwritten data int the stream 
* pointed to by stream is flushed to the kernel.
* If stream is NULL, then all open input streams in the process are flushed */
#include<stdio.h>
#include<string.h>
int main()
{
	FILE *stream;
	int c,fp,fc;
	long curPos;
	stream = fopen("file.txt","r");	// if file is not present it will give error
	if(stream == NULL)
	{
		perror("fopen");
		return 1;
	}

	while((c = fgetc(stream)) != EOF)
	{
		fp = fputc(c,stdout);
		if(fp == EOF)
		{
			perror("fputc");
			return 1;
		}		
	}
	
	curPos = ftell(stream);
	if(curPos == -1)
	{
		perror("ftell");
		return -1;
	}
	else
		printf("Current Position : %ld \n",curPos);

	fc = fflush(stream);
	if(fc == EOF)
        	perror("fflush");

	return 0;	
}

/* OUTPUT :- 
Assuming file.txt contains "I want to become great developer"
	$ ./executable
Current Position : 33
*/
	
