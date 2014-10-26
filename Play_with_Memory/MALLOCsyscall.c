/*
refer more to get man page of malloc 
 
sources :- http://c-faq.com/malloc/cast.html
* Do I cast the result of malloc?
* Suppose that you call malloc but forget to #include <stdlib.h>. 
* The compiler is likely to assume that malloc is a function returning int, 
* which is of course incorrect, and will lead to trouble. 
* Now, if your call to malloc is of the form

	char *p = malloc(10);

* the compiler will notice that you're seemingly assigning an integer to a pointer,
*  and will likely emit a warning of the form ``assignment of pointer from integer lacks a cast'',
* which will alert you to the problem. 
* (The problem is of course that you forgot to #include <stdlib.h>, not that you forgot to use a cast.) 
* If, on the other hand, your call to malloc includes a cast:

	char *p = (char *)malloc(10);

* The compiler is likely to assume that you know what you're doing, 
* that you really do want to convert the int returned by malloc to a pointer,
*  and the compiler therefore probably won't warn you. But of course malloc 
* does not return an int, so trying to convert the int that it doesn't return 
* to a pointer is likely to lead to a different kind of trouble, which will be harder to track down.

* (Of course, compilers are increasingly likely--especially under C99--to emit warnings whenever 
* functions are called without prototypes in scope, and such a warning would alert you to the
* lack of <stdlib.h> whether casts were used or not.) */

/*Why does some code carefully cast the values returned by malloc to the pointer type being allocated? 
* Before ANSI/ISO Standard C introduced the void * generic pointer type, 
* these casts were typically required to silence warnings (and perhaps induce conversions) 
* when assigning between incompatible pointer types.

* Under ANSI/ISO Standard C, these casts are no longer necessary. 
* It can also be argued that they are now to be discouraged;
*  Furthermore, well-defined, low-risk implicit conversions 
* (such as those which C has always performed between integer 
* and floating-point types) can be considered a feature.

* On the other hand, some programmers prefer to make every conversion explicit,
*  to record that they have considered each case and decided exactly what should happen 
*  Also, the casts are typically seen in C code which for one reason or another 
* is intended to be compatible with C++, where explicit casts from void * are required.
*/

// Very simple example of malloc 

#include<stdio.h>
#include<stdlib.h>
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

	stu = malloc(sizeof(struct student));
	if(!stu)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	/*Do your code here */

	free(stu);	
	return 0; 
}
