/*A successful call to realloc() resizes the region of memory pointed at by ptr to a new
* size of size bytes. It returns a pointer to the newly sized memory, which may or may
* not be the same as ptr . When enlarging a memory region, if realloc() is unable to
* enlarge the existing chunk of memory by growing the chunk in situ, the function may
* allocate a new region of memory size bytes in length, copy the old region into the new
* one, and free the old region. On any operation, the contents of the memory region are
* preserved up to the minimum of the old and the new sizes. Because of the potentiality
* of a copy, a realloc() operation to enlarge a memory region can be a relatively costly operation.
* If size is 0 , the effect is the same as an invocation of free() on ptr .
* If ptr is NULL , the result of the operation is the same as a fresh malloc() . If ptr is non-
* NULL , it must have been returned via a previous call to malloc() , calloc() , or realloc() .
* On failure, realloc() returns NULL and sets errno to ENOMEM . The state of the memory
* pointed at by ptr is unchanged*/
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
	/*Allocating 5 blocks of memory whoose size is to hold struct student*/
	stu = calloc(5,sizeof(struct student));
	if(!stu)
	{
		perror("calloc");
		exit(EXIT_FAILURE);
	}
	/*Do your code here */
	struct student *re_stu;
	/*Reallocating the total 5 units of size to 1 units
	giving back 4 units of memory  */
	re_stu = realloc(stu,sizeof(struct student));
	if(!re_stu)
	{	
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	free(re_stu);	
	return 0; 
}
