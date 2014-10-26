/* Program to read whole string till /n or /0 from file using fgets() function 
	gcc -Wall filename.c -o filename	*/
#include<stdio.h>
#include<string.h>
#define SIZBUF 128
int main()
{
	FILE *stream;
	char buf[SIZBUF],*fget;
	int fp;

	stream = fopen("file.txt","r");
	if(stream == NULL)
	{
		perror("fopen");
		return 1;
	}

	fget = fgets(buf,SIZBUF,stream); // more info see man 3 fgets
	if(fget == NULL)
	{
		perror("fget");
		return 1;
	}

	fp = fputs(buf,stdout); // this will print on terminal(stdout)
	if(fp == EOF)
	{
		perror("fputs");
		return 1;
	}
	if(fclose(stream) == EOF)
		perror("fclose");
	return 0;
}
