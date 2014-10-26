/*
* Demonstrate the use of setxattr() to set a file extended attribute.

* This program is Linux (2.6 and later) specific.
* setxattr() sets the value of the extended attribute identified by name 
* and associated with the given path in the file system. 
* The size of the value must be specified.

* The flags field modifies the behaviour of the call.
* If flags XATTR_CREATE, the call will fail if the extended attribute already exits.
* If flags XATTR_REPLACE, the call will fail if the extended attribute does not exit.
* lsetxattr() - sets the value to symbolic links
* fsetxattr() - sets the value to regular file with fd.  

*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/xattr.h>
#include<string.h>


int main(int argc, char *argv[])
{
    	char *value;
	char *key = "user.my_key";
	int ret;

    	if (argc < 2)
	{
		fprintf(stderr,"Usage %s <file> \n",argv[0]);
		return 1;
	}

	value = "This is my secret value";
	ret = setxattr(argv[1],key, value, strlen(value),XATTR_CREATE); 
    	if (ret == -1)
		perror("setxattr");
	else
		printf("The key and value has been set \n");
	
	return 0;
}

/*OUTPUT :- 
$ ./a.out <filename>
The key and value has been set*/

