/* This function works the same as atexit(), 
but the registered function's prototype is different */
#include<stdio.h>
#include<stdlib.h>

void myFunc(int Estatus,void *arg)
{
   printf("This is myFunc exit status = %d and arg = %d\n",Estatus,(int)arg);
}

int main ()
{
   /* register the termination function */
   on_exit(myFunc,(void *)10);
   
   printf("Starting  main program  \n");

   printf("Exiting main program    \n");

   return 0;
}

/*OUTPUT :- 
$ ./executable
Starting  main program  
Exiting main program    
This is myFunc exit status = 0 and arg = 10 
*/


