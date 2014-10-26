/* 

*   Demonstrate the use of getxattr() to get a file extended attribute.
*   to get the extended value from file , you should know the extended key value 
*   This program is Linux (2.6 and later) specific.

*  Extended attributes are name:value pairs associated with inodes (files, directories, symbolic links, etc.). 
*  They are extensions to the normal attributes which are associated with all inodes in the system 
*  (i.e., the stat(2) data).

*  getxattr() retrieves the value of the extended attribute identified by name and associated with the given path in the file system. 
*  The length of the attribute value is returned. 
*  lgetxattr() retrieves from symbolic link file
*  fgetxattr() retrieves from regular file using fd .
Note :- 
----------------------------------------------------------------------------------------------------
*  if you dont know the file's key then before running this example kindly run the listxattr() example
----------------------------------------------------------------------------------------------------
*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/xattr.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    	char *value;
	char *key = "user.my_key";
	ssize_t sizee ;

	value = (char *)malloc(16 * sizeof(char *));
    	if (argc < 2)
	{
		fprintf(stderr,"Usage %s <file> \n",argv[0]);
		return 1;
	}

	sizee = getxattr(argv[1],key, value,64); 
    	if (sizee == -1)
		perror("getxattr");
        else if(sizee == 0)
        {
                printf("This file doesn't contain any extended attribute \n");
                printf("Use setxattr() to set the attributes\n");
        }
	else
	{
		value[sizee+1] = '\0';
		printf("The value is -->  %s\n",value);
	}
	free(value);	
	return 0;
}

/* OUTPUT :- 
$ ./a.out <filename>
The value is -->  This is my secret value
*/
