/* Program to see the use of fseek call*/
#include<stdio.h>
#include<string.h>
int main()
{
	FILE *stream;
	int fs,c,fp,fc;

	stream = fopen("file.txt","r");	// if file is not present it will give error
	if(stream == NULL)
		perror("fopen");
/* SEEK_CUR - The file position is set to the current position + offset */
	fs = fseek(stream,7,SEEK_CUR);
	if(fs == -1)
		perror("fseek");

	while((c = fgetc(stream)) != EOF)
	{
		fp = fputc(c,stdout);
		if(fp == EOF)
			perror("fputc");		
	}
	
	fc = fclose(stream);
	if(fc == EOF)
        	perror("fclose");

	return 0;	
}

/* OUTPUT :- 
Assuming file.txt contains "I want to become great developer"
	$ ./executable
	to become great developer
*/
	
