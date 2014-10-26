#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/mman.h>
#define MYSIZ 32

int main( void )
{
	char src[MYSIZ] = "SOURCE";
	char dst[MYSIZ] = "DESTINATION";

	if(mlock(src,MYSIZ) == -1)
		perror("mlock");
	printf("=====================MEMMEMOVE=========================\n");
	printf(" Before memmove src = %s and dst = %s \n",src,dst);
	memmove(dst,src,strlen(dst));
	printf("After  memmove src = %s and dst = %s \n",src,dst);
	munlock(src,MYSIZ);
	return 0;
}


