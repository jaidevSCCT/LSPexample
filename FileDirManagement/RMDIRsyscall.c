/*
* rmdir()- On success, rmdir( ) removes path from the filesystem, and returns 0. The directory
* specified by path must be empty, aside from the dot and dot-dot directories. There is
* no system call that implements the equivalent of a recursive delete, as with rm -r.
* Such a tool must manually perform a depth-first traversal of the filesystem, removing
* all files and directories starting with the leaves, and moving back up the filesystem;
* rmdir( ) can be used at each stage to remove a directory once its files have been removed.
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	int ret;
	
	if(argc < 2)
	{
		fprintf(stderr,"Usage %s <Path to directory> \n",argv[0]);
		return 1;
	}

	ret = rmdir(argv[1]);
		if(ret == -1)
			perror("rmdir");
		else
			fprintf(stdout,"%s removed  \n",argv[1]);
	return 0;
	
}

/*OUTPUT :- 
$ ./a.out <directory name>
/home/office/mydir removed
*/
