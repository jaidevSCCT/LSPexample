/*This function causes the specified function func to be called when the program terminates. 
You can register your termination function anywhere you like,
 but it will be called at the time of program termination.*/

#include<stdio.h>
#include<stdlib.h>

void myFunc()
{
   printf("This is myFunc \n");
}

int main ()
{
   /* register the termination function */
   atexit(myFunc);
   
   printf("Starting  main program  \n");

   printf("Exiting main program    \n");

   return 0;
}

/*OUTPUT :- 
$ ./executable
Starting  main program  
Exiting main program    
This is myFunc 
*/


