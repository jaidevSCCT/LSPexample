/*
*  mkdir() -- successful call to mkdir( ) creates the directory path, which may be relative or 
*  absolute, with the permission bits mode (as modified by the current umask), and returns 0.
*  The current umask modifies the mode argument in the usual way, plus any operating-
*  system-specific mode bits: in Linux, the permission bits of the newly created direc-
*  tory are (mode & ~umask & 01777). In other words, in effect, the umask for the process
*  imposes restrictions that the mkdir( ) call cannot override. 

*  A call to chdir( ) changes the current working directory to the pathname specified by
*  path, which can be an absolute or a relative pathname. Similarly, a call to fchdir( )
*  changes the current working directory to the pathname represented by the file
*  descriptor fd, which must be opened against a directory.
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(int argc,char *argv[])
{
	char *cwd;
	int ret,ret1;
	
	if(argc < 3)
	{
		fprintf(stderr,"Usage %s <PATH> <directory name> \n",argv[0]);
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
		umask(0);	
		ret1 = mkdir(argv[2],0755);
		if(ret1 == -1)
			perror("mkdir");
		else
			fprintf(stdout,"Directory created \n");
	}
	free(cwd);
	return 0;
	
}

/*OUTPUT :- 
$ ./a.out <PATH> <directory name>
My current directory is ---> /home/office/Documents
My directory is changed to ---> /home/
Directory created
--------------------------------------------
Now you can check your home directory...
*/
