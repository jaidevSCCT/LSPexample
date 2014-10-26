/*I have not found much difference between memcpy and memmove 
  as i am also not going to the internal implementation of these two functions 
  to know more on this topic you can see the link below rest difference 
  between the two is given below in the description 
http://stackoverflow.com/questions/4415910/memcpy-vs-memmove*/

/*     #include <string.h>

       void *memmove(void *dest, const void *src, size_t n);

       DESCRIPTION
       The memmove() function copies n bytes from memory area src to memory area dest. 
       The memory areas may overlap: copying takes place as
       though the bytes in src are first copied into a temporary array that does not 
       overlap src or dest, and the bytes are then copied from the temporary array to dest.

       RETURN VALUE
       The memmove() function returns a pointer to dest.
 */

/*#include <string.h>
  void * memcpy (void *dst, const void *src, size_t n);
  This function behaves identically to memmove() , except dst and src may not overlap. If
  they do, the results are undefined.

  Another safe copying function is memccpy() :
#include <string.h>
void * memccpy (void *dst, const void *src, int c, size_t n);

The memccpy() function behaves the same as memcpy() , except that it stops copying if
the function finds the byte c within the first n bytes of src . The call returns a pointer to
the next byte in dst after c , or NULL if c was not found.

Finally, you can use mempcpy() to step through memory:
#define _GNU_SOURCE
#include <string.h>
void * mempcpy (void *dst, const void *src, size_t n);
The mempcpy() function performs the same as memcpy() , except that it returns a pointer
to the next byte after the last byte copied. This is useful if a set of data is to be copied to
consecutive memory locations—but it’s not so much of an improvement because the
return value is merely dst + n . This function is GNU-specific.

 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MYSIZ 32

int main( void )
{
	char src[MYSIZ] = "SOURCE";
	char dst[MYSIZ] = "DESTINATION";
	printf("=====================MEMMEMOVE=========================\n");
	printf(" Before memmove src = %s and dst = %s \n",src,dst);
	memmove(dst,src,strlen(dst));
	printf("After  memmove src = %s and dst = %s \n",src,dst);

	strcpy(dst,"DESTINATION"); // Resetting the value of dst 
	printf("======================MEMCPY===========================\n");
	printf(" Before memcpy src = %s and dst = %s \n",src,dst);
	memcpy(dst,src,strlen(dst));
	printf("After  memcpy src = %s and dst = %s \n",src,dst);


	return 0;
}


