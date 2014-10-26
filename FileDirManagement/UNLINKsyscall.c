/*
* The converse to linking is unlinking, the removal of pathnames from the filesystem.
* A single system call, unlink( ), handles this task:
* #include <unistd.h>
* int unlink (const char *pathname);
* A successful call to unlink( ) deletes pathname from the filesystem, and returns 0. If
* that name was the last reference to the file, the file is deleted from the filesystem. If,
* however, a process has the file open, the kernel will not delete the file from the file-
* system until that process closes the file. Once no process has the file open, it is deleted.
* If pathname refers to a symbolic link, the link, not the target, is destroyed
*/
#include<stdio.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
	int ret;

	if(argc < 2)
	{
		fprintf(stderr,"Usage : %s <filename1>\n",argv[0]);
		return 1;
	}

	ret =  unlink(argv[1]);
	if(ret == -1)
		perror("unlink");
	else
		printf("This file [%s] has been removed \n",argv[1]);
	return 0;
}

/*
OUTPUT : -
$ ./a.out /home/office/file.txt
This file [/home/office/file.txt] has been removed 
*/
