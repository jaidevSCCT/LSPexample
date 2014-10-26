/*For backward compatibilty with other UNIX type system instead of using 
mmap() with MAP_ANONYMOUS we will use mapping of /dev/zero */

/*Other Unix systems, such as BSD, do not have a MAP_ANONYMOUS flag. Instead, they
implement a similar solution by mapping a special device file, /dev/zero. This device file
provides identical semantics to anonymous memory. A mapping contains copy-on-
write pages of all zeros; the behavior is thus the same as with anonymous memory.*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
        void *myHeap;
        int ret,fd;

        fd = open("/dev/zero",O_RDWR);
        if(fd == -1)
        {
                perror("open");
                exit(EXIT_FAILURE);
        }
                
        myHeap = mmap(NULL,getpagesize(),PROT_READ | PROT_WRITE,MAP_PRIVATE,fd,0);
        if(myHeap == MAP_FAILED)
        {
                perror("mmap");
                if (close(fd) == -1)
                        perror("close");
                exit(EXIT_FAILURE);
        }
        
        /*Do your work here */
        ret = munmap(myHeap,getpagesize());
        if(ret == -1)
                perror("munmap");

        if(close(fd) == -1)
                perror("close");

        return 0;
}

