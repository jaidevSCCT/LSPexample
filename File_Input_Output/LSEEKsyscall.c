/* EXAMPLE OF SEEKING FILE WITH LSEEK  
	gcc -Wall filename.c -o filename*/
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

#define MYBUF 256
/* Note :- Assuming filename.txt contains "I want to become great developer" but i want to read the file after become.*/
int main()
{
	int fd; // file descriptor 	
	ssize_t retlen; // return len bytes from read system calls
	off_t lsek;	// return value of lseek	
	char buf[MYBUF];
	fd = open("filename.txt",O_RDONLY); // Reference man 2 open
	if(fd == -1)
		perror("open");

	 lsek = lseek(fd,(off_t)1,SEEK_SET); // Setting the file position is at 1
        if(lsek == (off_t) -1)
                perror("lseek");	

	lsek = lseek(fd,(off_t)15,SEEK_SET); 
	if(lsek == (off_t) -1)
		perror("lseek");

	retlen = read(fd,buf,MYBUF);	// On Success return the no .of len read from the file
	if(retlen == -1)
		perror("read");
	buf[retlen] = '\0';
	printf("%s",buf);
	if(close(fd) == -1)
		perror("close");
	return 0;
}

/* OUTPUT 
The buf will print "e great developer"
The buf will print "great developer" if we use SEEK_CUR inspite of SEEK_SET used in second call of lseek see example below
*/

/* Example of SEEK_CUR 
int main()
{
        int fd; // file descriptor      
        ssize_t retlen; // return len bytes from read system calls
        off_t lsek;     // return value of lseek        
        char buf[MYBUF];
        fd = open("filename.txt",O_RDONLY); // Reference man 2 open
        if(fd == -1)
                perror("open");

         lsek = lseek(fd,(off_t)1,SEEK_SET); // Setting the file position is at 1
        if(lsek == (off_t) -1)
                perror("lseek");

        lsek = lseek(fd,(off_t)15,SEEK_CUR);
        if(lsek == (off_t) -1)
                perror("lseek");

        retlen = read(fd,buf,MYBUF);    // On Success return the no .of len read from the file
        if(retlen == -1)
                perror("read");
        buf[retlen] = '\0';
        printf("%s",buf);
        if(close(fd) == -1)
                perror("close");
        return 0;
}

*/
