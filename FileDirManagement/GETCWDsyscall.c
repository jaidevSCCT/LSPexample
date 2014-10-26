/*
* The getcwd() function copies an absolute pathname of the current working directory to the array 
* pointed to by buf, which is of length size.
* If  the  length  of  the absolute pathname of the current working directory,
* including the terminating null byte, exceeds size bytes, NULL is returned, 
* and errno is set to ERANGE; an application should check for this error, 
* and allocate a larger buffer if necessary. 
*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define BUF_LEN 128
int main()
{
	char *ret;
	char cwd[BUF_LEN];

	ret = getcwd(cwd,BUF_LEN);
	if(ret == NULL)
		perror("getcwd");

	printf("Current working directory == %s \n",cwd);
	return 0;
}

/* Imp Note :-
* POSIX dictates that the behavior of getcwd( ) is undefined if buf is NULL. Linux’s C
* library, in this case, will allocate a buffer of length size bytes, and store the current
* working directory there. If size is 0, the C library will allocate a buffer sufficiently
* large to store the current working directory. It is then the application’s responsibility
* to free the buffer, via free( ), when it’s done with it. Because this behavior is Linux-
* specific, applications that value portability or a strict adherence to POSIX should not
* rely on this functionality. This feature, however, does make usage very simple!
Here’s an example: 
int main()
{
        char *cwd;
        cwd = getcwd(NULL,0);
        if(cwd == NULL)
                perror("getcwd");

        printf("Current working directory == %s \n",cwd);
        free(cwd);
        return 0;
}
*/
