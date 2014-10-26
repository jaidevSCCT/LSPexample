/*msync() - This system call flushes back to disk if any changes made to a file/device 
* mapped via mmap()
* Without invocation of this call , there is no guarantee that a dirty mapping 
* will be written back to disk until the file is unmapped*/
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
	int fd,fst,ms;

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
	
	ms = msync(p,sb.st_size,MS_SYNC);
	if(ms == -1)
		perror("msync");
	else
		printf("Dirty mappings are written to disk \n");

	if(munmap(p,sb.st_size) == -1)
	{
		perror("munmap");
		return 1;
	}

	return 0;
}

/*OUTPUT - 
	$ ./executable file.txt
Dirty mappings are written to disk 
*/
