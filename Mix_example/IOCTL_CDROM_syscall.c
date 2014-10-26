/* Program to eject CDROM using ioctl */
#include<stdio.h>
#include<sys/ioctl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<linux/cdrom.h>

int main(int argc , char *argv[])
{
	int fd,ret;
	if(argc < 2)
	{
		fprintf(stderr,"Usage %s <CDROM device to eject> \n",argv[0]);
		return -1;
	}
	fd = open(argv[1],O_RDONLY | O_NONBLOCK);
	if(fd == -1)
		perror("open");

	ret = ioctl(fd,CDROMEJECT,0);
	if(ret == -1)
		perror("ioctl");
	else
		printf("CDROM ejected succesfully \n");
		
	if(close(fd)==-1)
		perror("close");
	return 0;
}

/* $ ./a.out /dev/cdrom 
*/
