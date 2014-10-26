/*
* fpathconf, pathconf - get configuration values for files
* fpathconf() gets a value for the configuration option name for the open file descriptor fd.

* pathconf() gets a value for configuration option name for the filename path.

* The corresponding  macros  defined  in  <unistd.h> are minimum values;
* if an application wants to take advantage of values which may
* change, a call to fpathconf() or pathconf() can be made, which may yield more liberal results.

* Setting name equal to one of the following constants returns the following configuration options:

       _PC_LINK_MAX
	* returns the maximum number of links to the file.  
	* If fd or path refer to a directory, then the value applies to the whole directory.
	* The corresponding macro is _POSIX_LINK_MAX.

       _PC_MAX_CANON
	* returns  the  maximum length of a formatted input line, where fd or path must refer
	*  to a terminal.  The corresponding macro is _POSIX_MAX_CANON.

       _PC_MAX_INPUT
        * returns the maximum length of an input line, where fd  or  path  must 
	* refer  to  a  terminal.The  corresponding macro is _POSIX_MAX_INPUT.

       _PC_NAME_MAX
	* returns the maximum length of a filename in the directory path or fd that 
	* the process is allowed to create. The corresponding macro is _POSIX_NAME_MAX.

       _PC_PATH_MAX
        * returns the maximum length of a relative pathname when path or fd is the 
	* current working directory.  The  corresponding macro is _POSIX_PATH_MAX.

       _PC_PIPE_BUF
	* returns  the  size of the pipe buffer, where fd must refer to a pipe or FIFO
	* and path must refer to a FIFO.  The corresponding macro is _POSIX_PIPE_BUF.

       _PC_CHOWN_RESTRICTED
	* returns nonzero if the chown(2) call may not be used on this file. 
	* If fd or path refer to a directory, then this applies to all files in that directory.
	* The corresponding macro is _POSIX_CHOWN_RESTRICTED.

 	_PC_NO_TRUNC
        * returns  nonzero  if  accessing  filenames  longer than _POSIX_NAME_MAX  generates an error. 
	*  The  corresponding macro is  _POSIX_NO_TRUNC.

       _PC_VDISABLE
        * returns nonzero if special character processing can be disabled, where fd or path must refer to a terminal.

RETURN VALUE
	The limit is returned, if one exists.  If the system does not have a limit
	for the requested resource, -1 is returned, and  errno is unchanged. 
	If there is an error, -1 is returned, and errno is set to reflect the nature of the error.
SOURCES MAN PAGES
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char * argv[])
{
	long ret;
	int i=0;
	/*This macros arrays are taken only for printing purpose*/
	char *macros[]={"_PC_LINK_MAX","_PC_MAX_CANON","_PC_MAX_INPUT",
			"_PC_NAME_MAX","_PC_PATH_MAX","_PC_PIPE_BUF",
			"_PC_CHOWN_RESTRICTED","_PC_NO_TRUNC","_PC_VDISABLE"};

	/*This macro array are taken as a arguement to pass into pathconf*/
	int macro[] = {_PC_LINK_MAX,_PC_MAX_CANON,_PC_MAX_INPUT,_PC_NAME_MAX,
			_PC_PATH_MAX,_PC_PIPE_BUF,_PC_CHOWN_RESTRICTED,_PC_NO_TRUNC,_PC_VDISABLE};
	if(argc < 2)
	{
		fprintf(stdout,"Uasge %s <filepath>\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	while(i < (sizeof(macro)/sizeof(int)))
	{
		ret = pathconf(argv[1],macro[i]);
		if(ret == -1)
			perror("pathconf");
		printf(" %s max value is 	= %ld \n",macros[i],ret);
		i++;
	}
	return 0;	
}

/*OUTPUT :-
THIS RESULT MAY VARY FROM SYSTEM TO SYSTEM 
$ ./a.out <path/filename>
 _PC_LINK_MAX max value is 	= 65000 
 _PC_MAX_CANON max value is 	= 255 
 _PC_MAX_INPUT max value is 	= 255 
 _PC_NAME_MAX max value is 	= 255 
 _PC_PATH_MAX max value is 	= 4096 
 _PC_PIPE_BUF max value is 	= 4096 
 _PC_CHOWN_RESTRICTED max value is 	= 1 
 _PC_NO_TRUNC max value is 	= 1 
 _PC_VDISABLE max value is 	= 0 */
