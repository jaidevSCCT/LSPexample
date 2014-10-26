/*This example is not file based mapping, it is an example of an anonymous based mapping 
* which you can say that creation of your own heap memory area instead of using malloc calloc etc
* Here we are using mmap() sys call with arguement MAP_ANONYMOUS */
/*The sources of this example and understanding is taken from linux system programming by love */

/*Perhaps because you want to force the use of a memory mapping over the heap for a
* specific allocation, or perhaps because you are writing your own memory allocation
* system, you may want to manually create your own anonymous memory mapping—
* either way, Linux makes it easy.The system call mmap() creates
* a memory mapping and the system call munmap() destroys a mapping:
#include <sys/mman.h>
void * mmap (void *start,
size_t length,
int prot,
int flags,
int fd,
off_t offset);
int munmap (void *start, size_t length);
* Creating an anonymous memory mapping is actually easier than creating a file-backed
* mapping, as there is no file to open and manage. The primary difference is the presence
* of a special flag, signifying that the mapping is anonymous.
* Let’s look at an example given below */
#include<stdio.h>
#include<stdlib.h>
#include<sys/mman.h>

int main()
{
	void *myHeap;
	int ret;
	myHeap = mmap(NULL,512*1024/*512KB*/,PROT_READ | PROT_WRITE,MAP_ANONYMOUS | MAP_PRIVATE,-1,0);
	if(myHeap == MAP_FAILED)
	{
		perror("mmap");\
		exit(EXIT_FAILURE);
	}
	
	/*Do your code now with myHeap points to 512KB of anonymous memory */

	/*Giving back the memory now after done with your code above  */
	ret = munmap(myHeap,512*1024);
	if(ret == -1)
		perror("munmap");
	return 0;
}


/*
* For most anonymous mappings, the parameters to mmap() mirror this  below example, with
* the exception, of course, of passing in whatever size (in bytes) the programmer desires.
* The other parameters are generally as follows:
• The first parameter, start , is set to NULL , signifying that the anonymous mapping
* may begin anywhere in memory that the kernel wishes. Specifying a non- NULL value
* here is possible, so long as it is page-aligned, but limits portability. Rarely does a
* program care where mappings exist in memory.
• The prot parameter usually sets both the PROT_READ and PROT_WRITE bits, making
* the mapping readable and writable. An empty mapping is of no use if you cannot
* read from and write to it. On the other hand, executing code from an anonymous
* mapping is rarely desired, and allowing execution opens up an attack vector.
• The flags parameter sets the MAP_ANONYMOUS bit, making this mapping 
* anonymous, and the MAP_PRIVATE bit, making this mapping private.
• The fd and offset parameters are ignored when MAP_ANONYMOUS is set. Some older
* systems, however, expect a value of −1 for fd , so it is a good idea to pass that if
* portability is a concern.
* Memory obtained via an anonymous mapping looks the same as memory obtained via
* the heap. One benefit to allocating from anonymous mappings is that the pages are
* already filled with zeros. This occurs at no cost, because the kernel maps the application’s
* anonymous pages to a zero-filled page via copy-on-write. Thus, there is no need to
* memset() the returned memory. Indeed, this is one benefit to using calloc() as opposed
* to malloc() followed by memset() : glibc knows that anonymous mappings are already
* zeroed, and that a calloc() satisfied from a mapping does not require explicit zeroing.
*/
