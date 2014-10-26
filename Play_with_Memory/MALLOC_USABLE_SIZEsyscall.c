/*Linux provides a couple of functions that offer low-level control of glibc’s memory
*  allocation system. The first such function allows a program to ask how many usable bytes
* a given memory allocation contains:
#include <malloc.h>
size_t malloc_usable_size (void *ptr);
* A successful call to malloc_usable_size() returns the actual allocation size of the
* chunk of memory pointed to by ptr . Because glibc may round up allocations to fit within
* an existing chunk or anonymous mapping, the usable space in an allocation can be larger
* than requested. Of course, the allocation will never be smaller than requested. Here’s an
* example of the function’s use:*/
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

int main()
{
	size_t size,mySize=25;
	char *myBuf;
	
	myBuf = malloc(mySize);
	if(myBuf == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	size = malloc_usable_size(myBuf);
	if(size == 0)
		fprintf(stderr,"Please allocate some memory to myBuf \n");
	printf("Actual allocated size of the chunk of memory pointed by myBuf is %d\n",size);
	free(myBuf);
	return 0;
}
/*OUTPUT :- 
May your system have other output 
$ ./a.out
Actual allocated size of the chunk of memory pointed by myBuf is 28
*/
