/*This program is to define the correct directory for the location of Posix 
IPC name . This program is provide portablity issues to different linux system.
The other easiet way to provide portablity by using #define the name in a header 
that is easy to change if we move application to other system. */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"config.h"
#include<linux/limits.h>
int main()
{
	char *dir,*dst,*slash,*name="MY_NAME";

	if( (dst = malloc(PATH_MAX)) == NULL )
		return NULL;

	if( (dir = getenv("PX_IPC_NAME")) == NULL ) 
	{
		#ifdef POSIX_IPC_PREFIX
			dir = POSIX_IPC_PREFIX;
		#else
			dir = "/tmp/";
		#endif
	}

	slash = (dir[strlen(dir) - 1] == '/') ? "" : "/";
	snprintf(dst,PATH_MAX,"%s%s%s",dir,slash,name);
	printf("%s\n",dst);
	return 0;
}

/*OUTPUT : -
$ ./a.out 
/tmp/MY_NAME
*/
