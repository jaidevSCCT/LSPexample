/*
* A successful call to listxattr() returns a list of the extended attribute
* keys associated with the file denoted by path. 
* the list is stored in the buffer provided by list,which is size bytes in length.
* the system call returns the actual size of the list, in bytes.
* the other system calls are llistxattr() and flistxattr() 
* This program is Linux (2.6 and later) specific.
*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/xattr.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    	char *key;
	ssize_t sizee ;

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
	}
	else
		printf("The key is -->  %s\n",key);
	
	free(key);	
	return 0;
}

/* OUTPUT :- 
$ ./a.out <filename>
The key  is -->  user.my_key
*/
