/*
* Symbolic links, also known as symlinks or soft links, are similar to hard links in that
* both point at files in the filesystem. The symbolic link differs, however, in that it is
* not merely an additional directory entry, but a special type of file altogether. This
* special file contains the pathname for a different file, called the symbolic link’s target.
* The system call for creating a symbolic link is very similar to its hard link cousin:
* #include <unistd.h>
* int symlink (const char *oldpath, const char *newpath);
* A successful call to symlink( ) creates the symbolic link newpath pointing at the tar-
* get oldpath, and then returns 0.
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

	ret =  symlink(argv[1],argv[2]);
	if(ret == -1)
		perror("symlink");
	else
		printf("Symbolic Link has been created \n");
	return 0;
}

/*
OUTPUT : -
$ ./a.out /home/office/file.txt /home/office/Documents/file
Symbolic Link has been created
ls -l /home/office/Documents/
lrwxrwxrwx 1 root root   20 Jun  1 16:51 file -> /home/office/file.txt
*/
