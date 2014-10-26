/*
   Similar to strcmp() , memcmp() compares two chunks of memory for equivalence:
#include <string.h>
int memcmp (const void *s1, const void *s2, size_t n);
An invocation compares the first n bytes of s1 to s2 and returns 0 if the blocks of memory
are equivalent, a value less than zero if s1 is less than s2 , and a value greater than zero
if s1 is greater than s2 .

Because of structure padding (" Some alignment concerns for structure”), 
comparing two structures for equivalence via memcmp() or bcmp() is unreliable.
There can be uninitialized garbage in the padding that differs between two
otherwise identical instances of a structure. Consequently, code such as the following
is not safe:
are two mystruct identical? (BROKEN) ???
int compare_dinghies (struct mystruct *a, struct mystruct *b)
{
return memcmp (a, b, sizeof (struct mystruct));
}
Instead, programmers who wish to compare structures should compare each element
of the structures, one by one. This approach allows for some optimization, but it’s def‐
initely more work than the unsafe memcmp() approach.*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	char *strEqual = "EQUAL" ,*strEqual1 = "EQUAL";
	char *strSmall = "SMALL" , *strBig = "TOO_BIG";
	int ret = 0;

	ret = memcmp(strEqual,strEqual1,(size_t)12);
	if(ret == 0)
		fprintf(stdout,"\nBlock of memory are equivalent\n");
	else if(ret < 0)
		fprintf(stdout,"strEqual < strEqual1 \n");
	else if(ret > 0)
		fprintf(stdout,"strEqual > strEqual1 \n");

	ret = memcmp(strSmall,strBig,(size_t)12);
	if(ret == 0)
		fprintf(stdout,"\nBlock of memory are equivalent\n");
	else if(ret < 0)
		fprintf(stdout,"strSmall < strBig \n");
	else if(ret > 0)
		fprintf(stdout,"strSmall > strBig \n");

	ret = memcmp(strBig,strSmall,(size_t)12);
	if(ret == 0)
		fprintf(stdout,"\nBlock of memory are equivalent\n");
	else if(ret < 0)
		fprintf(stdout,"strBig < strSmall \n");
	else if(ret > 0)
		fprintf(stdout,"strBig > strSmall \n");
	return 0;
}

/*OUTPUT : - 
  $ ./a.out 
  Block of memory are equivalent
  strSmall < strBig 
  strBig > strSmall  
 */ 
