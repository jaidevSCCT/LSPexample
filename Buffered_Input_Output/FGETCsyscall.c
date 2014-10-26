/* Program to reading one character at a time from file using fgetc()
	gcc -Wall filename.c -o filename */
#include<stdio.h>
#include<string.h>

int main()
{
	FILE *stream;
	int c,fput;		//
	stream = fopen("file.txt","r");
	if(stream == NULL)
		perror("fopen");
		
	while((c = fgetc(stream)) != EOF)	// more info on fgetc see man 3 fgetc
	{
		fput = fputc(c,stdout);		// redirecting the output to the stdout(terminal)
		if(fput == EOF)
		{	
			perror("fputc");
			break;
		}		
	}

	if(fclose(stream) == EOF)
		perror("fclose");
	return 0;
}

/* OUTPUT :-
Assuming file.txt having content "I Want to become great developer"
So the output will be the same on terminal "I Want to become great developer"
*/
