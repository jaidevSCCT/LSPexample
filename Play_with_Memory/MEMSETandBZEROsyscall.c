/*Among the collection of memory-manipulating functions, the most common is easily
memset() :
#include <string.h>
void * memset (void *s, int c, size_t n);
A call to memset() sets the n bytes starting at s to the byte c and returns s . A frequent
use is zeroing a block of memory:

bzero() is an older, deprecated interface introduced by BSD for performing the same
task. New code should use memset() , but Linux provides bzero() for backward com‐
patibility and portability with other systems:
#include <strings.h>
void bzero (void *s, size_t n);
Note that bzero() (along with the other b interfaces) requires the header <strings.h>
and not <string.h>.
Do Not Use memset() if You Can Use calloc()!
Avoid allocating memory with malloc() only to immediately zero the
provided memory with memset() . While the result may be the same,
foregoing the two functions for a single calloc() , which returns zeroed
memory, is superior. Not only will you make one less function call, but
calloc() may be able to obtain already zeroed memory from the kernel.
In that case, you avoid manually setting each byte to 0, improving
performance.
*/

#include<stdio.h>
#include<stdlib.h>
#include<strings.h> // For bzero
#include<string.h>

int main()
{
	char *str,*strZero;
	size_t mySize = 16;
	int i=0,ret=0;
	str = malloc(mySize); //Memory with some giberish value 
	if(str == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	strZero = calloc(1,mySize); // memory with zero value 
	if(strZero == NULL)
		perror("calloc");
	/*lets put some values */
	while(i < mySize)
	{
		str[i] = 'A';
		fprintf(stdout," %c ",str[i]);
		i++;
	}
	/*Now zeroing the memory with memset*/
	str = memset(str,0,mySize);
	/*Use bzero also to check memory zeroed or not uncomment below and comment above memeset*/
	// bzero(str,mySize);
	
	/*Now lets check the value and compare the memory  */
	
	ret = memcmp(str,strZero,mySize);
	if(ret == 0)
		fprintf(stdout,"\nMemory Zeroed succesfully\n");
	else
		puts("\nMemory Zeroed Unsuccesfull\n");
	free(str);
	free(strZero);
	return 0;	
}

/*OUTPUT : - 
$ ./a.out
 A  A  A  A  A  A  A  A  A  A  A  A  A  A  A  A 
Memory Zeroed succesfully
*/ 
