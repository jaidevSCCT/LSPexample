/*Program to get pagesize of your current system 
sysconf() - POSIX defines _SC_PAGESIZE to be the size of page in bytes
getpagesize() - Not all Unix system support this function */

#include<stdio.h>
#include<unistd.h>

int main()
{
	long page_size;
	int pagesize;

	page_size = sysconf(_SC_PAGESIZE);
	pagesize = getpagesize();


	printf("sysconf = %ld , getpagesize = %d \n",page_size,pagesize);
	return 0;
}

/* OUTPUT :- 
$ ./executable 
sysconf = 4096 , getpagesize = 4096 */
