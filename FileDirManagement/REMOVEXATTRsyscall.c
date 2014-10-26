/*
* A successful call to removexattr() removes the extended key attribute
* associated with the file denoted by path. 
* the other system calls are lremovexattr() and fremovexattr() 
* This program is Linux (2.6 and later) specific.
*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/xattr.h>
#include<string.h>
#include<stdlib.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    	char *key;
	ssize_t sizee ;
	int ret;

	key = (char *)malloc(16 * sizeof(char *));
    	if (argc < 2)
	{
		fprintf(stderr,"Usage %s <file> \n",argv[0]);
		return 1;
	}

	sizee = listxattr(argv[1],key,64); 
    	if (sizee == -1)
		perror("listxattr");
	else if(sizee == 0)
	{
		printf("This file doesn't contain any extended attribute \n");
		printf("Use setxattr() to set the attributes\n");
		exit(EXIT_SUCCESS);
	}
	else
		ret = removexattr(argv[1],key);
		if(ret == -1)
			perror("removexattr");
		else
			printf("Key attributes has ben removed\n");
	
	free(key);	
	return 0;
}

/* OUTPUT :- 
$ ./a.out <filename>
Key attributes has been removed
*/
