/*For more info on mallopt se note in this chapter*/
/* M_CHECK_ACTION
   Setting this parameter controls how glibc responds when various 
   kinds of programming errors are detected  (e.g.,  freeing  the same  pointer  twice). 
   The 3 least significant bits (2, 1, and 0) of the value assigned to 
   this parameter determine the glibc behavior, as follows:

   Bit 0  
   If this bit is set, then print a one-line message on stderr 
   that provides details about the error.  The message  starts
   with  the  string "*** glibc detected ***", followed by the program name, 
   the name of the memory-allocation function in
   which the error was detected, a brief description of the error, 
   and the memory address where the error was detected.

   Bit 1 
   If this bit is set, then, after printing any error message 
   specified by bit 0, the program  is  terminated  by  calling abort(3). 
   In  glibc  versions since 2.4, if bit 0 is also set, then, between 
   printing the error message and aborting, the program also prints a stack trace
   in the manner of backtrace(3), and prints the process's  memory  mapping  in  the
   style of /proc/[pid]/maps (see proc(5)).

   Bit 2 (since glibc 2.4)
   This  bit  has an effect only if bit 0 is also set.  
   If this bit is set, then the one-line message describing the error
   is simplified to contain just the name of the function where the error 
   was detected and the brief  description  of  the error.

   The remaining bits in value are ignored.

   Combining the above details, the following numeric values are meaningful for M_CHECK_ACTION:

   0  Ignore error conditions; continue execution (with undefined results).

   1  Print a detailed error message and continue execution.

   2  Abort the program.

   3  Print detailed error message, stack trace, and memory mappings, and abort the program.

   5  Print a simple error message and continue execution.

   7  Print simple error message, stack trace, and memory mappings, and abort the program.

   Since  glibc  2.3.4, the default value for the M_CHECK_ACTION parameter is 3.  In glibc version 2.3.3 and earlier, the default
   value is 1.

   Using a nonzero M_CHECK_ACTION value can be useful because otherwise a crash may happen much later, and the true cause of  the
   problem is then very hard to track down.
 */
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

int main(int argc,char *argv[])
{
	int val=0;
	if(argc<2)
	{
		fprintf(stderr,"Usage %s <Any Number B/W 0 to 7> \n",argv[0]);
		exit(EXIT_FAILURE);
	}
	val = atoi(argv[1]);
	if(mallopt(M_CHECK_ACTION,val) == 0)
	{
		perror("mallopt");
		exit(EXIT_FAILURE);
	}

	 size_t mySize=25;
        char *myBuf;

        myBuf = malloc(mySize);
        if(myBuf == NULL)
        {
                perror("malloc");
                exit(EXIT_FAILURE);
        }

	/*Here doing double free to get the differences between the error resutl at stderr*/
	free(myBuf);
	free(myBuf);
	return 0;
}
/*OUTPUT :- 
$ ./a.out 0

$ ./a.out 1
*** Error in `./a.out': double free or corruption (fasttop): 0x09f5c008 ***
Aborted (core dumped)

$ ./a.out 2
Aborted (core dumped)

$ ./a.out 3
*** Error in `./a.out': double free or corruption (fasttop): 0x08507008 ***
======= Backtrace: =========
/lib/i386-linux-gnu/libc.so.6(+0x696de)[0xb75d56de]
/lib/i386-linux-gnu/libc.so.6(+0x73bca)[0xb75dfbca]
/lib/i386-linux-gnu/libc.so.6(+0x7483d)[0xb75e083d]
./a.out[0x8048631]
/lib/i386-linux-gnu/libc.so.6(__libc_start_main+0xf3)[0xb7585a83]
./a.out[0x8048481]
======= Memory map: ========
08048000-08049000 r-xp 00000000 08:06 5767226    /a.out
08049000-0804a000 r--p 00000000 08:06 5767226    /a.out
0804a000-0804b000 rw-p 00001000 08:06 5767226    /a.out
08507000-08528000 rw-p 00000000 00:00 0          [heap]
b7536000-b7552000 r-xp 00000000 08:06 2098192    /lib/i386-linux-gnu/libgcc_s.so.1
b7552000-b7553000 rw-p 0001b000 08:06 2098192    /lib/i386-linux-gnu/libgcc_s.so.1
b756b000-b756c000 rw-p 00000000 00:00 0 
b756c000-b7715000 r-xp 00000000 08:06 2098176    /lib/i386-linux-gnu/libc-2.19.so
b7715000-b7716000 ---p 001a9000 08:06 2098176    /lib/i386-linux-gnu/libc-2.19.so
b7716000-b7718000 r--p 001a9000 08:06 2098176    /lib/i386-linux-gnu/libc-2.19.so
b7718000-b7719000 rw-p 001ab000 08:06 2098176    /lib/i386-linux-gnu/libc-2.19.so
b7719000-b771c000 rw-p 00000000 00:00 0 
b7733000-b7736000 rw-p 00000000 00:00 0 
b7736000-b7737000 r-xp 00000000 00:00 0          [vdso]
b7737000-b7757000 r-xp 00000000 08:06 2098237    /lib/i386-linux-gnu/ld-2.19.so
b7757000-b7758000 r--p 0001f000 08:06 2098237    /lib/i386-linux-gnu/ld-2.19.so
b7758000-b7759000 rw-p 00020000 08:06 2098237    /lib/i386-linux-gnu/ld-2.19.so
bffbc000-bffdd000 rw-p 00000000 00:00 0          [stack]
Aborted (core dumped)
*/
