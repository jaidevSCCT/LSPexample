/*
* Both chmod() and fchmod() set a file's permission to mode.
* With chmod(), path denotes the relative or absolute pathname 
* of the file to modify.
* for fchmod(), the file is given by the file descriptor fd.

Note :-
------------------------------------------------------------------------------------------
* To change file's permission, the effective ID of the process calling chmod() or fchmod()
* must match the owner of the file, or the process must have the CAP_FOWNER capabilty 
------------------------------------------------------------------------------------------- 
*/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(int argc,char *argv[])
{
	int ret;

	if(argc < 2)
	{
		fprintf(stderr,"Usage : %s <file> \n",argv[0]);
		return 1;
	}
	ret = chmod(argv[1],S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
	if(ret == -1)
		perror("chown");
	return 0;
}


/*OUTPUT :- 
ls -l file.txt
-rw-r--r-- 1 root root 18 May 31 13:04 file.txt

$ ./a.out <filename> 
-rw-rw---- 1 root root 18 May 31 12:53 file.txt*/
