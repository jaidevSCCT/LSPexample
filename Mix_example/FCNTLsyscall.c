/*  #include <sys/types.h>

* #include <unistd.h>

* #include <fcntl.h>

* int fcntl(int fildes, int cmd, ...);

struct flock {
	short l_type;
	short l_whence;
	off_t l_start;
	off_t l_len;
	pid_t l_pid;
};

* The fcntl() function provides control of open file descriptors. 
*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(int argc,char *argv[])
{
	int fd,dupfd,getfd,setfd,getfl,setfl,getlk;
	struct flock lock;
	if (argc < 2)
	{
		fprintf(stdout,"Usage : %s <filename>\n",argv[0]);
		exit(0);
	}
	
	fd = open(argv[1],O_RDONLY);
	if(fd == -1)
		perror("open");
	else
		printf("Current file descriptor is  == %d\n",fd);

	/* Duplicating a file descriptor */
	/* F_DUPFD -- >  
	Return a new file descriptor which is the lowest numbered available (that is, not already open) 
	file descriptor greater than or equal to the specified argument, which is of type int The new 
	file descriptor refers to the same open file description as the original file descriptor, 
	and shares any locks. The FD_CLOEXEC flag associated with the new file descriptor is cleared 
	to keep the file open across calls to one of the exec() family of functions.
	 The return value is the new file descriptor on success, or -1 on error.
	*/
	dupfd = fcntl(fd,F_DUPFD,5);  /* Providing 5 as a new FD */
	if(dupfd == -1)
		perror("fcntl");
	else
		printf("New File descriptor is  == %d\n",dupfd);

/*F_SETFD 

    	Set the file descriptor flags for the specified file descriptor. 
	The argument is the new set of flags, as a variable of type int. 
	File descriptor flags are associated with a single file descriptor
	 and do not affect other file descriptors that refer to the same file.
	 The return value is 0 on success, or -1 on error. The following file descriptor flags may be set.
	 Any additional bits set from the flags specified for F_GETFD are ignored. 
	If any bits not defined here are specified, behavior is undefined.
FD_CLOEXEC 

        If set, the file descriptor is closed when one of the exec() family of functions is called. 
	If not set, the file descriptor is inherited by the new process image.

F_GETFD 

    	Get the file descriptor flags for the specified file descriptor.
	 This command takes no argument. File descriptor flags are associated with 
	a single file descriptor and do not affect other file descriptors 
	that refer to the same file. The return value is the current 
	file descriptor flags on success, or -1 on error. */

	getfd = fcntl(fd,F_GETFD);
	if(getfd == -1)
		perror("fcntl");
	
	setfd = fcntl(fd,F_SETFD,getfd | FD_CLOEXEC);
	if(setfd == -1)
		perror("fcntl");
	else
		printf("FD_CLOEXEC flag has been set \n");	
/*F_GETFL

	Get the file status flags and file access modes for the specified file descriptor. 
	These flags are as specified for the oflag argument to open(), along with the additional
	values described for F_SETFL. File status flags and file access modes are associated with
	the file description and do not affect other file descriptors that refer to the same file
	with different open file descriptions. The return value is the current file status flags
	and file access modes on success, or -1 on error. 
	The following macros can be used to access fields of the return value:
O_ACCMODE 

        Extracts the access-mode field, which is one of O_RDONLY, O_RDWR, or O_WRONLY. 
	Refer to the documentation for open() for more information.
*/

/*F_SETFL

	Set the file status flags for the specified file descriptor. The argument is the
	new set of flags, as a variable of type int. These flags are as specified for the
	oflag argument to open(), along with the additional values specified later. 
	Bits corresponding to the file access mode and any other oflag bits not listed here are ignored.
	If any bits not defined here or in open() are set, behavior is undefined.
	 The return value is 0 on success, or -1 on error. The following file status flags can be changed with F_SETFL:

O_APPEND 

        Valid only for file descriptors that refer to regular files. 
	The file pointer is moved to the end of the file before each write.
    
O_NONBLOCK 

        Sets the file descriptor to non-blocking mode. The distinction between non-blocking mode
	and no-delay mode is relevant only for a few types of special files such as pipes and FIFOs. 
	Refer to read() and write() for more information.
O_SYNC
        Sets the file descriptor to synchronous-write mode. 
	Writes do not return until file buffers have been flushed to disk.
*/


	getfl = fcntl(fd,F_GETFL);
	if(getfl == -1)
		perror("fcntl");
	else if(getfl == O_RDONLY)
		printf("RDONLY \n");
	else if(getfl == O_WRONLY)
		printf("WRONLY \n");
	else if(getfl == O_RDWR)
		printf("RDWR \n");
	else
		printf("No Flags are found\n");

	getfl |= (O_APPEND | O_SYNC | O_NONBLOCK);

	setfl = fcntl(fd,F_SETFL,getfl);
	if(setfl == -1)
		perror("fcntl");
	else
		printf("Flags are set \n"); 

	lock.l_type 	= F_WRLCK;   /* Test for any lock on any part of file. */
  	lock.l_start   	= 0;
  	lock.l_whence  	= SEEK_SET;
  	lock.l_len     	= 0;        
/*********************  Critical Points About File Locking  ******************

1.  A write lock on any region prevents ANY kind of lock on even a single
    byte of that region.   

2.  A read lock on any region prevents a write lock on even a single byte
    of that region.

3.  Fcntl with F_GETLK or F_SETLK return -1 on an "error".  However, an
    error with F_GETLK means that it cannot obtain the desired lock
    information.  With F_SETLK it means that the desired lock cannot be
    obtained.

3.  When using fcntl with F_GETLK, the l_type component of the flock
    struct is overwritten by any existing lock which would prevent the
    lock whose attributes are in the struct flock * third argument.
    If nothing will prevent the lock given in this struct, the l_type
    component will have the value F_UNLCK.

4.  If the value of the l_len component of a struct flock is 0 then the
    length of the region to be tested/locked is the rest of the file
    starting at the value given in the l_start component.

5.  The l_start component's meaning is relative to the l_whence component
    of the flock struct.  The l_whence component can be SEEK_SET (beginning
    of file), SEEK_CUR (current position of file pointer), or SEEK_END
    (end of file).  Thus, l_start must be zero or positive if l_whence is
    SEEK_SET and zero or negative if l_whence is SEEK_END.

6.  Read locks do not prevent other read locks on the same region.  

7.  You must remember to F_UNLCK a region after your need for a read or
    write lock has expired.  

8.  With descriptors, there is no fseek/ftell.  There is only lseek which
    returns the same value as ftell and whose prototype is:

          #include <sys/types.h>
          #include <unistd.h> 
          off_t lseek(int fd, off_t offset, int whence);

     Lseek's return value is the offset after the move of the file pointer.
     Lseek(fd, 0, SEEK_CUR) is like ftell.

9.   If you want to create a lock, do NOT call fcntl with F_GETLK first.
     Just try for the lock with F_SETLK and if fcntl returns a negative
     value then you couldn't get the lock.  F_GETLK is an "info only please"
     request.
*/

	lock.l_type     = F_WRLCK;   /* Test for any lock on any part of file. */
        lock.l_start    = 0;
        lock.l_whence   = SEEK_SET;
        lock.l_len      = 0;   
	getlk = fcntl(fd,F_GETLK,&lock);
	if(getlk == -1)
		perror("fcntl");
	else if (lock.l_type == F_WRLCK)
  	{
     		printf("file has a write lock already!\n");
     		exit(1);
  	}
  	else if (lock.l_type == F_RDLCK)
  	{
     		printf("File has read lock already \n");
     		exit(1);
  	}
	else if(lock.l_type == F_UNLCK)
			printf("File is Unlocked already \n");
/* for setting a lock on a file refer this link (http://voyager.deanza.edu/~perry/lock.html)*/

	if(close(fd) == -1)
		perror("close");
	return 0;		
}


/*OUTPUT :- 
$ ./a.out
Current file descriptor is  == 4
New File descriptor is  == 5
FD_CLOEXEC flag has been set 
RDONLY 
Flags are set 
File is Unlocked already */
