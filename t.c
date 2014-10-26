/*gcc test.c -lgomp*/
#define _GNU_SOURCE
#include<omp.h>
/* Includes */
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */
#include <sched.h>

/* prototype for thread routine */
void print_message_function ( void *ptr );

/* struct to hold data to be passed to a thread
   this shows how multiple data items can be passed to a thread */
typedef struct str_thdata
{
    int thread_no;
    char message[100];
} thdata;

int main()
{
    pthread_t thread1, thread2;  /* thread variables */
    thdata data1, data2;         /* structs to be passed to threads */
	struct sched_param param; 
	int tr;
    
    /* initialize data to pass to thread 1 */
    data1.thread_no = 1;
    strcpy(data1.message, "Hello!");

    /* initialize data to pass to thread 2 */
    data2.thread_no = 2;
    strcpy(data2.message, "Hi!");
               
//param.sched_priority = sched_get_priority_max(SCHED_RR);
if( pthread_setschedprio( thread2,0 ) == -1 )
{
      perror("pthread_setschedprio");
      return -1;
}  

if( pthread_setschedprio( thread1,19 ) == -1 )
{
      perror("pthread_setschedprio");
      return -1;
}  
    /* create threads 1 and 2 */    
    pthread_create (&thread1, NULL, (void *) &print_message_function, (void *) &data1);
    pthread_create (&thread2, NULL, (void *) &print_message_function, (void *) &data2);

    /* Main block now waits for both threads to terminate, before it exits
       If main block exits, both threads exit, even if the threads have not
       finished their work */ 
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

	tr = omp_get_thread_num();
	printf("tr == %d \n",tr);       
    /* exit */  
    exit(0);
} /* main() */

/**
 * print_message_function is used as the start routine for the threads used
 * it accepts a void pointer 
**/
void print_message_function ( void *ptr )
{
    thdata *data;            
    data = (thdata *) ptr;  /* type cast to a pointer to thdata */
    
    /* do the work */
    printf("Thread %d says %s \n", data->thread_no, data->message);
	sched_yield();
    pthread_exit(0); /* exit */
} /* print_message_function ( void *ptr ) */

