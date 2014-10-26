/* Program to push character back onto a strean using ungetc 
	gcc -Wall filename.c -o filename */ 
#include<stdio.h>
#include<string.h>

int main()
{
	FILE *stream;
	int c,fput,unr1;
	stream = fopen("file.txt","r");
	if(stream == NULL)
		perror("fopen");
	c = fgetc(stream);	//reading one character from stream 
	if(c == EOF)
		perror("fgetc");
	else
	{
		// more info see man 3 ungetc
		unr1 = ungetc(c,stream); // Pushing one character back to stream 
		if(unr1 == EOF)
			perror("ungetc");
		else
		{	
			while((c = fgetc(stream)) != EOF)
			{
				fput = fputc(c,stdout);
				if(fput == EOF)
				{
					perror("fputc");
					break;
				}
				//printf("%c",r1);
			}
		}
	}

	if(fclose(stream) == EOF)
		perror("fclose");
	return 0;
}

/* NOTE :- 
IF multiple characters are pushed back using ungetc(), then they are returned in the reverse order
	that is the last pushed character is returned first.
*/
