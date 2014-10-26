/* stat() stats the file pointed to by path and fills in buf.
	Returns information about the file denoted by the path.
*/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h> // The stat structure is defined in <bits/stat.h>
#include<unistd.h>
#include<time.h>

int main(int argc,char *argv[])
{
	struct stat info;
	int ret;

	if(argc < 2)
	{
		fprintf(stderr,"Usage : %s <file> \n",argv[0]);
		return 1;
	}
	
	ret = stat(argv[1],&info);
	if(ret == -1)
	{
		perror("stat");
		return 1;
	}

	/*Lets check the total details of the file */

	printf("ID of device containing file %ld\n",(long)info.st_dev); // It will return zero if the file resides in NFS mount
	printf("Inode number of my file %s is %ld\n",argv[1],(long)info.st_ino);
	printf("Permission of my file %s is %o\n",argv[1],info.st_mode);
	printf("Number of hard links of my file %s is %ld\n",argv[1],(long)info.st_nlink);
	printf("User ID of Owner is %ld\n",(long)info.st_uid);
	printf("group ID of Owner is %ld\n",(long)info.st_gid);
	printf("Device ID if my file is special file  %s is %ld\n",argv[1],(long)info.st_rdev);
	printf("Total size in bytes of my file %s is %ld\n",argv[1],(long)info.st_size);
	printf("Block size for Filesystem I/O of my file %s is %ld\n",argv[1],(long)info.st_blksize);
	printf("Number of blocks allocated to  my file %s is %ld\n",argv[1],(long)info.st_blocks);
	printf("last access time of my file %s is %ld or %s\n",argv[1],(long)info.st_atime,ctime(&info.st_atime));
	printf("last modification time of my file %s is %ld or %s\n",argv[1],(long)info.st_mtime,ctime(&info.st_mtime));
	printf("last status change time of my file %s is %ld or %s\n",argv[1],(long)info.st_ctime,ctime(&info.st_ctime));	
	return 0;

}

/*OUTPUT :- 
Note :- Result may vary for your OS 
$ ./a.out <filename>
ID of device containing file 2054
Inode number of my file <filename> is 2518702
Permission of my file <filename> is 100644
Number of hard links of my file <filename> is 1
User ID of Owner is 0
group ID of Owner is 0
Device ID if my file is special file <filename> is 0
Total size in bytes of my file <filename> is 1715
Block size for Filesystem I/O of my file <filename> is 4096
Number of blocks allocated to  my file <filename> is 8
last access time of my file <filename> is 1401515531 or Sat May 31 11:22:11 2014

last modification time of my file <filename> is 1401515530 or Sat May 31 11:22:10 2014

last status change time of my file <filename> is 1401515530 or Sat May 31 11:22:10 2014 
*/
