/*There is no reason, however, that a programmer cannot use the stack for dynamic
* memory allocations. So long as the allocation does not overflow the stack, such an
* approach should be easy and should perform quite well. To make a dynamic memory
* allocation from the stack, use the alloca() system call:
#include <alloca.h>
void * alloca (size_t size);
* On success, a call to alloca() returns a pointer to size bytes of memory. This memory
* lives on the stack and is automatically freed when the invoking function returns. Some
* implementations return NULL on failure, but most alloca() implementations cannot
* fail or are unable to report failure. Failure is manifested as a stack overflow.
* Usage is identical to malloc() , but you do not need to (indeed, must not) free the
* allocated memory.*/
/*Note that you should not use alloca() -allocated memory in the parameters to a 
* function call because the allocated memory will then exist in the middle of the stack space
* reserved for the function parameters. For example, the following is off-limits:
** DO NOT DO THIS! **
ret = foo (x, alloca (10));
* The alloca() interface has a checkered history. On many systems, it behaved poorly
* or gave way to undefined behavior. On systems with a small and fixed-sized stack, using
* alloca() was an easy way to overflow the stack and kill your program. On still other
* systems, alloca() did not even exist. Over time, the buggy and inconsistent 
* implementations earned alloca() a bad reputation.
* So, if your program must remain portable, you should avoid alloca() . On Linux, how‐
* ever, alloca() is a wonderfully useful and underutilized tool. It performs exceptionally
* well—on many architectures, an allocation via alloca() does as little as increment the
* stack pointer—and handily outperforms malloc() . For small allocations in Linux-
* specific code, alloca() can yield excellent performance gains.*/
// Very simple example of alloco 

#include<stdio.h>
#include<stdlib.h>
#include<alloca.h>
struct student
{
	char name[10];
	int roll_no;
};

int main()
{
	struct student *stu;
	/*Allocate enough memmory to hold a student structure 
	and point stu at it*/

	stu = alloca(sizeof(struct student));
	if(!stu)
	{
		perror("alloca");
		exit(EXIT_FAILURE);
	}
	/*Do your code here */	
	return 0; 
}
