/*
*  A call to chdir( ) changes the current working directory to the pathname specified by
*  path, which can be an absolute or a relative pathname. Similarly, a call to fchdir( )
*  changes the current working directory to the pathname represented by the file
*  descriptor fd, which must be opened against a directory.
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	char *cwd;
	int ret;
	
	if(argc < 2)
	{
		fprintf(stderr,"Usage %s <PATH> \n",argv[0]);
		return 1;
	}

	cwd = getcwd(NULL,0);
	if(cwd == NULL)
		perror("getcwd");
	else
		fprintf(stdout,"My current directory is ---> %s\n",cwd);

	ret = chdir(argv[1]);
	if(ret == -1)
		perror("chdir");
	else
	{
		cwd = getcwd(NULL,0);
	        if(cwd == NULL)
                	perror("getcwd");
		fprintf(stdout,"My directory is changed to ---> %s\n",cwd);
	}
	free(cwd);
	return 0;
	
}

/*OUTPUT :- 
The results of the C program permanent on the terminal.
Like all other shell programs anything done within the program 
is destroyed when the program ends.

$ ./a.out <PATH>
My current directory is ---> /home/office/Documents/
My directory is changed to ---> /home
*/
