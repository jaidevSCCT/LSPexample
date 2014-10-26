/* Program to use ferror
ferror() = This function tests whether the error indicator is set on stream*/
#include <stdio.h>

int main ()
{
	FILE *stream;
 	int f=65,fc,fp;

	stream = fopen ("file.txt","r");
  	if(stream == NULL)
	{ 
		perror ("fopen");
		return -1;
	}
	else
	{
		fp = fputc(f,stream);
		if(fp == EOF)
			perror("fputc");
		if (ferror (stream))
      			printf ("Error Writing to file.txt\n");		

		fc = fclose (stream);
		if(fc == EOF)
			perror("fclose");
	}
  return 0;
}

/* OUTPUT :- 
Assuming file.txt contains "I want to become great developer".	
This program opens an existing file called file.txt in read-only mode 
but tries to write a character to it, generating an error that is detected by ferror.
$ ./executable
fputc: Bad file descriptor
Error Writing to myfile.txt
*/
