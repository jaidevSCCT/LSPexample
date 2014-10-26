/*Dynamic memory allocation may also be quite complex when the specified size is itself
* dynamic. One such example is the dynamic allocation of arrays, where the size of an
* array element may be fixed but the number of elements to allocate is dynamic. 
* To simplify this scenario, C provides the calloc() function:
#include <stdlib.h>
void * calloc (size_t nr, size_t size);
* A successful call to calloc() returns a pointer to a block of memory suitable for holding
* an array of nr elements, each of size bytes.
* The behavior, however, is not identical. Unlike malloc() , which makes no such 
* guarantees about the contents of allocated memory, calloc() zeros all bytes in the returned
* chunk of memory.
*/
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

	free(stu);	
	return 0; 
}
