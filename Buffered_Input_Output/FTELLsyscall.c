/* Program to obtain the current postion of the stream */
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

	fc = fclose(stream);
	if(fc == EOF)
        	perror("fclose");

	return 0;	
}

/* OUTPUT :- 
Assuming file.txt contains "I want to become great developer"
	$ ./executable
Current Position : 33
*/
	
