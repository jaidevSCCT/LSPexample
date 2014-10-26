/*Program to change the permission of existing regions of memory using mprotect() system call*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>


int main(int argc , char *argv[])
{
	struct stat sb;
	char *p;
	int fd,fst,mp;

	if(argc < 2)
	{
		fprintf(stderr,"usage : %s <file>\n",argv[0]);
		return 1;
	}

	fd = open(argv[1],O_RDONLY);
	if(fd == -1)
	{
		perror("open");
		return 1;
	}

	fst = fstat(fd,&sb);	// fstat() returns information about the file 
	if(fst == -1)
	{
		perror("fstat");
		return 1;
	}
	
	if(!S_ISREG(sb.st_mode)) // checking whether the file is regular or not
	{
		fprintf(stderr,"%s is not a file \n",argv[1]);
		return 1;
	}

	p = mmap(0,sb.st_size,PROT_READ,MAP_SHARED,fd,0);
	if(p == MAP_FAILED)
	{
		perror("mmap");
		return 1;
	}
	
	if(close(fd) == -1)
	{
		perror("close");
		return 1;
	}
	
	mp = mprotect(p,sb.st_size,PROT_NONE);
	if(mp == -1)
		perror("mprotect");
	else
		printf("Permission changed \n");

	if(munmap(p,sb.st_size) == -1)
	{
		perror("munmap");
		return 1;
	}

	return 0;
}

/*OUTPUT - 
	$ ./executable file.txt
Permission changed
*/
