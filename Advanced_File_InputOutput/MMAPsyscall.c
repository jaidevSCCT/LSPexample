/* mmap() - A call to mmap() asks the kernel to map len bytes of the object 
* represented by the file descriptor fd, starting at offset bytes into the file/device into memory
* unmap() - This system call for removing a mapping created with mmap()*/
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
	off_t len;
	char *p;
	int fd,fst;

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
/*sb.st_size - It will map len bytes i.e the size of file 
PROT_READ - The pages may be read
MAP_SHARED - sharing the map with all other processes */

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
	
	for(len = 0 ; len < sb.st_size;len++)
		putchar(p[len]); // To print the content of file 
	
	printf("length = %ld\n",len);	// This length is mapped by the kernel
	if(munmap(p,sb.st_size) == -1)
	{
		perror("munmap");
		return 1;
	}

	return 0;
}

/*OUTPUT - 
Assuming file.txt contains "I want to become great developer"
	$ ./executable file.txt
I want to become great developer
length = 33
*/
