/*
* readdir() - The  readdir() function returns a pointer to a dirent structure representing 
* the next directory entry in the directory stream pointed
* to by dirp.  It returns NULL on reaching the end of the directory stream or if an error occurred.

       On Linux, the dirent structure is defined as follows:

           struct dirent {
               ino_t          d_ino;        inode number 
               off_t          d_off;       offset to the next dirent
               unsigned short d_reclen;    length of this record
               unsigned char  d_type;      type of file; not supported
                                              by all file system types
               char           d_name[256];  filename
           };
* Applications successively invoke readdir( ), obtaining each file in the directory, until
* they find the file they are searching for, or until the entire directory is read, at which
* time readdir( ) returns NULL.
* On failure, readdir( ) also returns NULL. To differentiate between an error and having
* read all of the files, applications must set errno to 0 before each readdir( ) invoca-
* tion, and then check both the return value and errno. 
*/
#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<errno.h>

int main(int argc,char *argv[])
{
	DIR *opndir;
	int closdir;
	struct dirent *rddir;
	extern int errno;

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
	errno = 0;
	rddir = readdir(opndir);
	if(errno && !rddir)
		perror("readdir");
	else
	{
		fprintf(stdout,"Content of %s \n",argv[1]);
		while(rddir != NULL)
		{
			printf("Name  --> %s , inode no --> %ld  \n",rddir->d_name,(long)rddir->d_ino);
			rddir = readdir(opndir);
		}
	}
	closdir = closedir(opndir);
	if(closdir == -1)
		perror("closedir");
	else
		fprintf(stdout,"Directory stream has been closed successfully \n");
	return 0;
}

/*OUTPUT :- 
$ ./a.out / home/office/Documents

Directory stream has been created successfully 
Content of /home/office/Documents/ 
Name  --> GrubPasswd_30oct13.pdf , inode no --> 131414  
Name  --> .. , inode no --> 131074  
Name  --> ResetRootPasswdLiinux.pdf , inode no --> 131354  
Name  --> Semaphore_SysV_30oct13.pdf , inode no --> 131367  
Name  --> . , inode no --> 131089  
Directory stream has been closed successfully  
*/
