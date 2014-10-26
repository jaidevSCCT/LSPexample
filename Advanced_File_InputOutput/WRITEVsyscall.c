/*Program that writes out a vector of three segments ,each containing
* a string of different size .
* writev() - This function writes at most count segments from the buffers described by iov
* into the file descriptor for more info refer man 2 writev */
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/uio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
	int fd,count,cl;
// Each iovec structure describes an independent disjoint buffer,which is called segment
	struct iovec iov[3];  
	ssize_t Wr;	

	if(argc < 2)
	{
		fprintf(stdout,"usage %s <filename> \n",argv[0]);
		return 1;		
	}

	fd = open(argv[1],O_WRONLY | O_CREAT | O_EXCL | O_TRUNC,0644);
	if(fd == -1)
	{
		perror("open");
		return -1;
	}

	char *buf0 = "THIS IS BUFFER NUM one \n";
	char *buf1 = "THE IS BUFFER NUM two \n";
	char *buf2 = "THIS IS BUFFER NUM three \n\0";

/* iov_base - pointer to start of buffer
   iov_len - size of buffer in bytes */

	iov[0].iov_base = buf0; 
	iov[0].iov_len = strlen(buf0);
	iov[1].iov_base = buf1;
        iov[1].iov_len = strlen(buf1);
        iov[2].iov_base = buf2;
        iov[2].iov_len = strlen(buf2);

	count = sizeof(iov) / sizeof(struct iovec);

	Wr = writev(fd,iov,count); // 
	if(Wr == -1)
	{
		perror("writev");
		return -1;
	}
	printf(" wrote = %d bytes\n",Wr);

	cl = close(fd);
	if(cl == -1)
		perror("close");
	return 0;	
}

/*OUTPUT :- 
	$ ./executable
	wrote = 71 bytes
*/
