/*
* confstr() gets the value of configuration-dependent string variables.
* The name argument is the system variable to be queried.  The following variables are supported:

*  _CS_GNU_LIBC_VERSION (GNU C library only; since glibc 2.3.2)
   A string which identifies the GNU C library version on this system (e.g, "glibc 2.3.4")

*  _CS_GNU_LIBPTHREAD_VERSION (GNU C library only; since glibc 2.3.2)
A string which identifies the POSIX implementation supplied by this C library (e.g, "NPTL 2.3.4" or "linuxthreads-0.10").

*  _CS_PATH
 A value for the PATH variable which indicates where all 
 the POSIX.2 standard utilities can be found.

* If buf is not NULL and len is not zero, confstr() copies the value of 
* the string to buf truncated to len - 1 bytes if necessary, with
* a null byte ('\0') as terminator.  This can be detected by comparing the return value of confstr() against len.

* If len is zero and buf is NULL, confstr() just returns the value as defined below.

RETURN VALUE
       	If name is a valid configuration variable, confstr() returns the number of bytes 
	(including the terminating null byte) that would  be required  to  hold the entire
	value of that variable.  
	This value may be greater than len, which means that the value in buf is truncated.

       	If name is a valid configuration variable, but that variable does not have a value,
	then confstr() returns 0.  If name does not  correspond to a valid configuration variable, 
	confstr() returns 0, and errno is set to EINVAL.
SOURCES MAN PAGE
*/

#include<unistd.h>
#include<stdio.h>
#include<errno.h>
int main()
{
	size_t size;
	char buf[128];
	/*This macros arrays are taken only for printing purpose*/
	char *name[] = {"_CS_GNU_LIBC_VERSION","_CS_GNU_LIBPTHREAD_VERSION", "_CS_PATH"};
	/*This macros arrays are taken for passing as an arg in confstr()*/
	int  nam[] = {_CS_GNU_LIBC_VERSION,_CS_GNU_LIBPTHREAD_VERSION, _CS_PATH};
	int i = 0;

	while(i < (sizeof(name)/sizeof(int)))
	{
		size = confstr(nam[i],buf,512);
		if( size == EINVAL)
			perror("confstr");
		printf("%s  	====   %s\n",name[i],buf);
		i++;
	}
	return 0;
}

/*OUTPUT :- 
THIS RESULT MAY VARY FROM SYSTEM TO SYSTEM 
% ./a.out 
_CS_GNU_LIBC_VERSION  	====   glibc 2.19
_CS_GNU_LIBPTHREAD_VERSION  	====   NPTL 2.19
_CS_PATH  	====   /bin:/usr/bin
*/
