/* Program to open file using fopen() with different modes 
	gcc -Wall filename.c -o filename 
	In this example we are not given example of mode (a+) and (b)*/
#include<stdio.h>
#include<string.h>
/*Program to open a file for reading content only  */ 
int main()
{
	FILE *stream; // File stream
	int fc; 
	stream = fopen("file.txt","r");
	if(stream == NULL)
	{
		perror("fopen");
		return 1;
	}
	fc = fclose(stream);
	if(fc ==EOF) 
	{
		perror("fclose");
		return 1;
	}
	return 0;	
}
/* OUTPUT :- 
	Open the file for reading, the stream is positioned at the start of the file 
*/

/*Program to open a file for writing  */   
int main()
{
        FILE *stream; // File stream
        int fc;
        stream = fopen("file.txt","w");
        if(stream == NULL)
	{
                perror("fopen");
		return 1;
	}
        fc = fclose(stream);
        if(fc ==EOF)
                perror("fclose");
        return 0;
}

/* OUTPUT :- 
	If file exist the file will truncated to zero
	If file does not exist newly file will created
*/


/*Program to open a file for both reading and writing   */                           
int main()
{
        FILE *stream; // File stream
        int fc;
        stream = fopen("file.txt","r+");
        if(stream == NULL)
                perror("fopen");

        fc = fclose(stream);
        if(fc ==EOF)
                perror("fclose");
        return 0;
}

/* OUTPUT :- 
	If file does not exist it will not create
	If file exist the stream is positioned at the start of the file 
*/


/*Program to open a file for both reading and writing   */
int main()
{
        FILE *stream; // File stream
        int fc;
        stream = fopen("file.txt","w+");
        if(stream == NULL)
                perror("fopen");

        fc = fclose(stream);
        if(fc ==EOF)
                perror("fclose");
        return 0;
}

/* OUTPUT :- 
        If file exist, it is truncated to zero lenght
	If the file doesnt exist ,it will be created .
	The stream is positioned at the start of the file 
*/

/*Program to open a file for writing in append mode  */
int main()
{
        FILE *stream; // File stream
        int fc;
        stream = fopen("file.txt","a");
        if(stream == NULL)
                perror("fopen");

        fc = fclose(stream);
        if(fc ==EOF)
                perror("fclose");
        return 0;
}

/* OUTPUT :- 
        If file does not exist it will be created
        The stream is positioned at the end of the file.
	All writes will append to the file  
*/



