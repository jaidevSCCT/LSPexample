/* readv() - This function reads count segments from the file descriptor 
* fd into the buffers described by iov 
* To use this program kindly run first writev() program,that will 
* creat file.txt with some data rest depends upto your manipulation
*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/uio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
	int fd,count,clos;
	struct iovec iov[2]; 
	ssize_t retRead;
	char buf0[100];	
	if(argc < 2)
	{
		fprintf(stdout,"usage %s <filename> \n",argv[0]);
		return 1;
	}
	fd = open(argv[1],O_RDONLY);
	if(fd == -1)
	{
		perror("open");
		return -1;
	}
	iov[0].iov_base = buf0;
	iov[0].iov_len = sizeof(buf0);

	count = sizeof(iov) / sizeof(struct iovec);

	retRead = readv(fd,iov,count);
	if(retRead == -1)
	{
		perror("readv");
		return -1;
	}
	else
	{
		buf0[retRead] = '\0';	
		printf("%s \n",buf0);
	}
	clos = close(fd);
	if(clos == -1)
		perror("close");
	return 0;	
}
/*OUTPUT :- 
	$ ./executable
THIS IS BUFFER NUM one 
THE IS BUFFER NUM 2 
THIS IS BUFFER NUM three
*/
