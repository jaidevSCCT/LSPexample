/* Program to use feof() function
* feof() = This function tests whether the EOF indicator is set on stream*/
#include <stdio.h>

int main ()
{
	FILE *stream;
 	int n = 0,fc;

	stream = fopen ("file.txt","r");
  	if(stream == NULL)
	{ 
		perror ("fopen");
		return 1;
	}
	else
	{
		while (fgetc(stream) != EOF) 
      			++n;
    	}

	if (feof(stream))
	{
		printf("End-of-File reached.\n");
		printf ("Total number of bytes read: %d\n", n);
    	}
    	else 
	printf("End-of-File was not reached.\n");

	fc = fclose (stream);
	if(fc == EOF)
		perror("fclose");
  return 0;
}

/* OUTPUT :- 
Assuming file.txt contains "I want to become great developer"	
$ ./executable
End-of-File reached.
Total number of bytes read: 33
*/
