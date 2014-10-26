/*
* chown() and lchown() set the ownership of the file specified by the path path.
* They have the same effect, unless the file is symbolic link: the former follows
* symlink and changes the ownership of the link target rather than the link itself,
* while lchown() doesnt follow symbolic links and therefore changes the ownership of the 
* symbolic link file instead.
Note :-
------------------------------------------------------------------------------------------
* Only a process with CAP_CHOWN capability(usually a root) may change the owner of the file
------------------------------------------------------------------------------------------- 
* The original Linux chown(), fchown(), and lchown() system calls supported only 16-bit user and group IDs. 
* Subsequently,Linux 2.4 added  chown32(),  fchown32(),  and  lchown32(),  supporting 32-bit IDs.
* The glibc chown(), fchown(), and lchown() wrapper functions
* transparently deal with the variations across kernel versions.
*/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<grp.h>
int main(int argc,char *argv[])
{
	struct group *info;
	int ret;

	if(argc < 2)
	{
		fprintf(stderr,"Usage : %s <file> \n",argv[0]);
		return 1;
	}

	/* getgrnam() returns information on group give its name */
	
	info = getgrnam("Provide your group name here"); //example getgrnam("office");
	if(info == NULL)
	{
		fprintf(stderr,"%s","Invalid Group \n");
		perror("getgrnam");
		return -1;		
	}

	ret = chown(argv[1],0,info->gr_gid);
	if(ret == -1)
		perror("chown");
	return 0;
}


/*OUTPUT :- 
ls -l 
-rw-r--r-- 1 root root   18 May 31 12:53 file.txt
$ ./a.out <filename> 
-rw-r--r-- 1 root office   18 May 31 12:53 file.txt*/
