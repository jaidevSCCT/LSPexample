/*madvise - A call to madvise() advises the kernel on how to behave w.r.t the pages
* int the memory map starting at addr, abd extending for len bytes 
* Note :- Before using madvise() you should know internels of kernel because sometime 
* this call makes burden on I/O. 
*/
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
	int fd,fst,madvs;

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
	
	madvs = madvise(p,sb.st_size,MADV_SEQUENTIAL);
	if(madvs == -1)
		perror("msync");
	else
		printf("Accessing pages Sequentially \n");

	if(munmap(p,sb.st_size) == -1)
	{
		perror("munmap");
		return 1;
	}

	return 0;
}

/*OUTPUT - 
	$ ./executable file.txt
Accessing pages Sequentially 
*/
