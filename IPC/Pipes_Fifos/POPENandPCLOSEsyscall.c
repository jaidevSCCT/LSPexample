/*=================POPEN and PCLOSE=========================*/
/* The standard I/O library provides popen function that creates 
* a pipe and initiates another process that either reads from the pipe
* or writes to the pipe
* The value return by the popen is standard I/O FILE pointer that is 
* used for either input or output , depending on the second arg of popen i.e type.
------> If type is r , the calling process reads the standard output of the path/command
------> If type is w , the calling process writes to the standard input of the path/command 
* The pclose function closes standard I/O stream that was created by popen function.
*/

/*FILE *popen(const char *command,command char *type) 
* Here command is a shell command line .
* It is processed by the sh program(normally a bourne shell),
* so the PATH environment variable is used to locate the command.
* A pipe is created between the calling process and the specified command.
* This command is passed to /bin/sh using the -c flag; interpretation, 
* if any, is performed by the shell.*/

/*Example :- This program will work as a cat command*/
/*=================HEADERS============================*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<errno.h>
/*====================================================*/

#define MAXSIZ 4096   /*4 kb*/

int main()
{

	FILE *pstream;
	char buf[MAXSIZ],command[MAXSIZ];
	size_t len;

	  /*Read Pathname from the stdin*/
        fprintf(stdout,"Enter a pathname with file eg: /home/pc/file.txt \n");
        fflush(stdout);
        /*fgets guaranteed NULL byte at the end*/
        if((fgets(buf,MAXSIZ,stdin)) == NULL)  /* Reading from standard input*/
                perror("fgets");
        len = strlen(buf);
        if(buf[len-1] == '\n')  /*delete new line from fgets()*/
                len--;
	
	snprintf(command,sizeof(command),"cat %s",buf); /*basically we are sending cat command*/
	pstream = popen(command,"r");
	if(pstream == NULL)
		perror("popen");
		
	/*Copy from pipe to stdout(standard output)*/
	while((fgets(buf,MAXSIZ,pstream)) != NULL)
		fputs(buf,stdout);

	if(pclose(pstream) == -1)
		perror("pclose");
	return 0;
}

/*OUTPUT:- 
./a.out 
Enter a pathname with file eg: /home/pc/file.txt 
/etc/network/interfaces
# interfaces(5) file used by ifup(8) and ifdown(8)
auto lo
iface lo inet loopback

$ ./a.out 
Enter a pathname with file eg: /home/pc/file.txt 
/etc/sudoers
cat: /etc/sudoers: Permission denied
*/
