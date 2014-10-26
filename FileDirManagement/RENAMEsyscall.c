/*
* Unlike for copying, Unix does provide a system call for moving files. The ANSI C
* standard introduced the call for files, and POSIX standardized it for both files and directories:

* #include <stdio.h>
* int rename (const char *oldpath, const char *newpath);

* A successful call to rename( ) renames the pathname oldpath to newpath. The file’s
* contents and inode remain the same. Both oldpath and newpath must reside on the
* same filesystem*; if they do not, the call will fail. Utilities such as mv must handle this
* case by resorting to a copy and unlink.
*/
#include<stdio.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
	int ret;

	if(argc < 3)
	{
		fprintf(stderr,"Usage : %s <Source> <Destination> \n",argv[0]);
		return 1;
	}

	ret =  rename(argv[1],argv[2]);
	if(ret == -1)
		perror("rename");
	else
		printf("Source = [%s]  \n Destination = [%s] \n Your file is moved \n",argv[1],argv[2]);
	return 0;
}

/*
OUTPUT : -
$ ./a.out /home/office/file.txt /home/office/Documents/file
Source = [/home/office/file.txt]  
 Destination = [/home/office/Documents/file] 
 Your file is moved

$ ls -l /home/office/Documents/file
-rw-r--r-- 2 root root  135 Feb 10 11:02 file 
*/
