/*=================SYSTEM V IPC====================*/
/*System V IPC uses key_t values for their names.
The header <sys/types.h> defines the key_t datatype, as an integer,
normally at least 32-bit integer.These integer values are normally 
assigned by ftok function.
The function ftok converts an existing pathname and an integer identifier 
into key_t value (called an IPC key)
Typical implementation of ftok call the stat function and then combine 
------> Information about the filesystem on which pathname resides
	(the st_dev member of the stat structure  )
------> the file's i-node number within the filesystem 
	(the st_ino member of the stat structure )
------> the low-order 8 bits of the id.
*/
/*The combination of these three values normally produces a 32-bit keys.
No guarantee exits that two different pathnames combined with the same id 
generate different keys. */

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
typedef unsigned long ulong;

int main(int argc , char *argv[])
{
	if(argc < 2)
	{
		fprintf(stderr," Usage %s <pathame> \n",argv[0]);
		exit(EXIT_FAILURE);
	}
	struct stat mystat;
	int ret,id = 0x26;
	key_t IPCkey;

	ret = stat(argv[1],&mystat);
	if(ret == -1)
	{
		perror("stat");
		exit(EXIT_FAILURE);	
	}

	IPCkey = ftok(argv[1],id);
	if(IPCkey == -1)
		perror("ftok");

	printf(" st_dev : %lx , st_ino: %lx , IPCkey: %x \n",(ulong) mystat.st_dev,(ulong)mystat.st_ino,IPCkey );
	return 0;	
	
}

/*OUTPUT :- 
$ ./a.out /home
 st_dev : 806 , st_ino: 5767169 , IPCkey: 26060001 */


