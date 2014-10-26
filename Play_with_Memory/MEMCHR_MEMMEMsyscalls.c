/*The functions memchr() and memrchr() locate a given byte in a block of memory:
#include <string.h>
void * memchr (const void *s, int c, size_t n);

The memchr() function scans the n bytes of memory pointed at by s for the character
c , which is interpreted as an unsigned char :

#define _GNU_SOURCE
#include <string.h>
void * memrchr (const void *s, int c, size_t n);

The call returns a pointer to the first byte to match c , or NULL if c is not found.
The memrchr() function is the same as the memchr() function, except that it searches
backward from the end of the n bytes pointed at by s instead of forward from the front.
Unlike memchr() , memrchr() is a GNU extension and not part of the C language.

For more complicated search missions, the awfully named function memmem() searches
a block of memory for an arbitrary array of bytes:
#define _GNU_SOURCE
#include <string.h>
void * memmem (const void *haystack,
size_t haystacklen,
const void *needle,
size_t needlelen);
The memmem() function returns a pointer to the first occurrence of the subblock
needle , of length needlelen bytes, within the block of memory haystack , of length
haystacklen bytes. If the function does not find needle in haystack , it returns NULL .
This function is also a GNU extension.*/

#define _GNU_SOURCE // for memrchr 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	char *str = "SEARCHING";
	void *retStr;
	/*If the First 'R' will found on str then it will return pointer to 
	the first byte to match which is 'R' */
	retStr = memchr(str,'R',strlen(str));
	if(retStr == NULL)
		puts("Character not found \n");
	else
		printf(" Return string : %s \n",(char *)retStr); /*Printing retStr which to pointing the address returned by memchr */

	/*Similar to memchr the memrchr will search from backward eg .given below */
	retStr = memrchr(str,'C',strlen(str));
	if(retStr == NULL)
		puts("Character not found \n");
	else
        	printf(" Return string (memrchr): %s \n",(char *)retStr);
	printf("===================Example for MEMMEM==========================\n");
	fflush(stdout);
	char *haystack = "embedded linux system programming example fun";
	char *needle = "system";
	
	retStr = memmem(haystack,strlen(haystack),needle,strlen(needle));
	if(retStr == NULL)
		puts("Sub-String not found \n");
	else
	{
		printf("Returned Pointer to the first occurence of sub block is \n");
		puts(retStr);
	}
	return 0;
}

/*OUTPUT :- 
$ ./a.out
Return string : RCHING 
Return string (memrchr): CHING 
===================Example for MEMMEM==========================
Returned Pointer to the first occurence of sub block is 
system programming example fun system
*/
