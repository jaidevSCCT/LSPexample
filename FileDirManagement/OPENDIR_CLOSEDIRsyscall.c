/*
* opendir() - The  opendir()  function opens a directory stream corresponding to the directory name, 
* and returns a pointer to the directory stream.
* The stream is positioned at the first entry in the directory.
* closedir() - The closedir() function closes the directory stream associated with dirp.
*  A successful call to closedir() also closes the underlying
* file descriptor associated with dirp.  The directory stream descriptor dirp is not available after this call.
*/
#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>

int main(int argc,char *argv[])
{
	DIR *opndir;
	int closdir;
	if(argc < 2)
	{
		fprintf(stderr,"Usage : %s <directory's path> \n",argv[0]);
		return 1;
	}
	opndir = opendir(argv[1]);
	if(opndir == NULL )
		perror("opendir");
	else
		fprintf(stdout,"Directory stream has been created successfully \n");

	closdir = closedir(opndir);
	if(closdir == -1)
		perror("closedir");
	else
		fprintf(stdout,"Directory stream has been closed successfully \n");
	return 0;
}

/*OUTPUT :- 
$ ./a.out / home/office/
Directory stream has been created successfully 
Directory stream has been closed successfully 
*/
