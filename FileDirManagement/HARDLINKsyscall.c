/*
* The link( ) system call, one of the original Unix system calls, and now standardized
* by POSIX, creates a new link for an existing file:
* #include <unistd.h>
* int link (const char *oldpath, const char *newpath);
* A successful call to link( ) creates a new link under the path newpath for the existing
* file oldpath, and then returns 0. Upon completion, both oldpath and newpath refer to
* the same file—there is, in fact, no way to even tell which was the “original” link.
*/
#include<stdio.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
	int ret;

	if(argc < 3)
	{
		fprintf(stderr,"Usage : %s <filename1> <filename2> \n",argv[0]);
		return 1;
	}

	ret =  link(argv[1],argv[2]);
	if(ret == -1)
		perror("link");
	else
		printf("Hard Link has been created \n");
	return 0;
}

/*
OUTPUT : -
$ ./a.out /home/office/file.txt /home/office/Documents/file.txt
Hard Link has been created
*/
