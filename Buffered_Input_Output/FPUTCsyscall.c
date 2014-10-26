/* The fputc function writes the byte specified by c (caste to an unsigned char)
	to the stream pointed at by stream
	gcc -Wall filename.c -o filename */
#include<stdio.h>
#include<string.h>

int main()
{
	FILE *stream;
	int c,fput;
	stream = fopen("file.txt","r");
	if(stream == NULL)
		perror("fopen");
		
	while((c = fgetc(stream)) != EOF)
	{
		fput = fputc(c,stdout);		// redirecting the output to the stdout(terminal)
		if(fput == EOF)			// more info on fputc see man 3 fputc
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
