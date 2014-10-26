/*
* #define _XOPEN_SOURCE 600
* #define _GNU_SOURCE
* #include <stdlib.h>
* int posix_memalign (void **memptr,size_t alignment,size_t size);

* A successful call to posix_memalign() allocates size bytes of dynamic memory, 
* ensuring it is aligned along a memory address that is a multiple of alignment . 
* The parameter alignment must be a power of 2 and a multiple of the size of a void pointer.
* The address of the allocated memory is placed in memptr , and the call returns 0 .
* On failure, no memory is allocated, memptr is undefined, and the call returns one of the
* following error codes:
EINVAL
The parameter alignment is not a power of 2 or is not a multiple of the size of a
void pointer.
ENOMEM
There is insufficient memory available to satisfy the requested allocation.
* Note that errno is not set; the function directly returns these errors.*/


#define _XOPEN_SOURCE 600
#define _GNU_SOURCE 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	void *mybuf;
	int ret;

	/*Allocate 1KB along a 256-byte boundary */

	ret = posix_memalign(&mybuf,256,1024);
	if(ret)
	{
		fprintf(stderr,"posix_memalign : %s \n",strerror(ret));
		return -1;
	}
	/*Use mybuf infor your use */
	free(mybuf);
	return 0;
}
