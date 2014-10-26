/*DESCRIPTION
  The  strdup() function returns a pointer to a new string which is a duplicate of the string s. 
  Memory for the new string is obtained with malloc(3), and can be freed with free(3).

  The strndup() function is similar, but copies at most n bytes.  
  If s is longer than n, only n bytes are  copied,  and  a  terminating null byte ('\0') is added.

  strdupa()  and  strndupa()  are  similar,  but  use alloca(3) to allocate the buffer. 
  They are available only when using the GNU GCC suite, and suffer from the same limitations described in alloca(3).

  RETURN VALUE
  On success, the strdup() function returns a pointer to the duplicated string.
  It returns NULL if insufficient memory was  available, with errno set to indicate the cause of the error.

  ERRORS
  ENOMEM Insufficient memory available to allocate duplicate string.
 */
/*POSIX does not define the alloca() , strdupa() , or strndupa() functions, and their
record on other operating systems is spotty. If portability is a concern, use of these
functions is highly discouraged. On Linux, however, alloca() and friends perform
quite well and can provide an excellent performance boost, replacing the complicated
dance of dynamic memory allocation with a mere adjustment of the stack frame pointer*/

#define _GNU_SOURCE // for strdupa and strndupa
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	char *str = "MYSTRING";
	char *newstr;

	printf("===========================Memory allocated on heap==============================\n");

	newstr = strdup(str);
	if(newstr == NULL)
		perror("strdup");
	else
		fprintf(stdout,"String copied and memory allocated by malloc is %s \n",newstr);

	free(newstr);

	newstr = strndup(str,(size_t)3);
	if(newstr == NULL)
		perror("strndup");
	else
		fprintf(stdout,"String copied and memory allocated by malloc is %s \n",newstr);

	free(newstr);

	printf("===========================Memory allocated on stack==============================\n");

	newstr = strdupa(str);
	if(newstr == NULL)
		perror("strdupa");
	else
		fprintf(stdout,"String copied and memory allocated by alloca is %s \n",newstr);

	newstr = strndupa(str,(size_t)3);
	if(newstr == NULL)
		perror("strndupa");
	else
		fprintf(stdout,"String copied and memory allocated by alloca is %s \n",newstr);
	return 0;
}
/*OUTPUT : -
  $ ./a.out
  ===========================Memory allocated on heap==============================
  String copied and memory allocated by malloc is MYSTRING 
  String copied and memory allocated by malloc is MYS 
  ===========================Memory allocated on stack==============================
  String copied and memory allocated by alloca is MYSTRING 
  String copied and memory allocated by alloca is MYS 
 */
