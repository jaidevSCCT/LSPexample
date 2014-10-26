/*
Linux’s C library also provides a get_current_dir_name( ) function, which has the
same behavior as getcwd( ) when passed a NULL buf and a size of 0: 
*/
#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	char *cwd;
	
	cwd = get_current_dir_name();
	if(cwd == NULL)
		perror("get_current_dir_name");

	printf("Current working directory == %s \n",cwd);
	free(cwd);
	return 0;
}

