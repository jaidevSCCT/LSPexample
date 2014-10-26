/* The  mallinfo()  function  returns  a  copy of a structure containing information 
about memory allocations performed by malloc(3) and related functions.*/

/*
  The fields of the mallinfo structure contain the following information:

       arena     The total amount of memory allocated by means other than mmap(2) 
		 (i.e.,  memory  allocated  on  the  heap). 
		 This  figure includes both in-use blocks and blocks on the free list.

       ordblks   The number of ordinary (i.e., non-fastbin) free blocks.

       smblks    The number of fastbin free blocks (see mallopt(3)).

       hblks     The number of blocks currently allocated using mmap(2). 
		 (See the discussion of M_MMAP_THRESHOLD in mallopt(3).)

       hblkhd    The number of bytes in blocks currently allocated using mmap(2).

       usmblks   The "highwater mark" for allocated space—that is, the maximum amount of space that was ever allocated. 
		 This field is maintained only in nonthreading environments.

       fsmblks   The total number of bytes in fastbin free blocks.

       uordblks  The total number of bytes used by in-use allocations.

       fordblks  The total number of bytes in free blocks.

       keepcost  The total amount of releasable free space at the top of the heap. 
		 This is the maximum number of bytes that  could  ideally
       		 be released by malloc_trim(3).
*/


#include<stdio.h>
#include<malloc.h>
#include<sys/mman.h>
#include<stdlib.h>

void display_Mallinfo()
{
	struct mallinfo meminfo;
	meminfo = mallinfo();
        printf("Total mempry allocated using malloc (arena):  	%d\n", meminfo.arena);
        printf("No. of free chunks (ordblks):            	%d\n", meminfo.ordblks);
        printf("No. of free fastbin blocks (smblks):     	%d\n", meminfo.smblks);
        printf("No of Anonymous mappings (hblks):           	%d\n", meminfo.hblks);
        printf("Size of Anonymous mapping (hblkhd):      	%d\n", meminfo.hblkhd);
        printf("Max. total allocated space (usmblks):  		%d\n", meminfo.usmblks);
        printf("Size of available fastbins (fsmblks): 		%d\n", meminfo.fsmblks);
        printf("Total allocated space (uordblks):     		%d\n", meminfo.uordblks);
        printf("Total free space (fordblks):           		%d\n", meminfo.fordblks);
        printf("Topmost releasable block (keepcost):   		%d\n", meminfo.keepcost);
}


int main()
{
	char *buf;

	printf("============== Before allocating blocks ==============\n");
	display_Mallinfo();

	buf = malloc((size_t)24);
	if(buf == NULL)
	{
		perror("malloc");
		return -1;
	}

	printf("============== After allocating blocks ==============\n");
	display_Mallinfo();

	free(buf);

	printf("============== After freeing blocks ==============\n");
	display_Mallinfo();	
	return 0;
}

/*OUTPUT :- 
$ ./a.out
============== Before allocating blocks ==============
Total mempry allocated using malloc (arena):  	0
No. of free chunks (ordblks):            	1
No. of free fastbin blocks (smblks):     	0
No of Anonymous mappings (hblks):           	0
Size of Anonymous mapping (hblkhd):      	0
Max. total allocated space (usmblks):  		0
Size of available fastbins (fsmblks): 		0
Total allocated space (uordblks):     		0
Total free space (fordblks):           		0
Topmost releasable block (keepcost):   		0
============== After allocating blocks ==============
Total mempry allocated using malloc (arena):  	135168
No. of free chunks (ordblks):            	1
No. of free fastbin blocks (smblks):     	0
No of Anonymous mappings (hblks):           	0
Size of Anonymous mapping (hblkhd):      	0
Max. total allocated space (usmblks):  		0
Size of available fastbins (fsmblks): 		0
Total allocated space (uordblks):     		32
Total free space (fordblks):           		135136
Topmost releasable block (keepcost):   		135136
============== After freeing blocks ==============
Total mempry allocated using malloc (arena):  	135168
No. of free chunks (ordblks):            	1
No. of free fastbin blocks (smblks):     	1
No of Anonymous mappings (hblks):           	0
Size of Anonymous mapping (hblkhd):      	0
Max. total allocated space (usmblks):  		0
Size of available fastbins (fsmblks): 		32
Total allocated space (uordblks):     		0
Total free space (fordblks):           		135168
Topmost releasable block (keepcost):   		135136*/
