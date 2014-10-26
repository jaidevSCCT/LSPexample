/*Example to check whether the file resides on physical device or in any virtual device using fstat */

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc,char *argv[])
{
	int fd,ret;
	unsigned int dev;
	struct stat info;
	
	if(argc < 2)
	{	
		fprintf(stderr,"Usage : %s <file> \n",argv[0]);
		return 1;
	}

	fd = open(argv[1],O_RDONLY);
	if(fd == -1)
		perror("open");

	ret = fstat(fd,&info);
	if(ret == -1)
		perror("fstat");
	else
	{
		dev = gnu_dev_major(info.st_dev); // more info refer "man gnu_dev_major"
		if(dev == 0)
			printf("file Resides on VFS/NFS or Non-physical device  :  %d \n",dev);
		else
			printf("file resides on Physical Device %d \n",dev);
	}
	return 0;
	
}

/* OUTPUT :- 
$ ./a.out <filename>
file reside on physical device 8 */
