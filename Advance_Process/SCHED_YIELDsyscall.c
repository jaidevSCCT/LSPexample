/* Use of SCHED_YIELD() system call
* The sched_yield() function checks to see if other threads, at the same priority 
* as that of the calling thread, are READY to run. 
* If so, the calling thread yields to them and places itself at the end of the READY thread queue. 
* The sched_yield() function never yields to a lower-priority thread.

* A higher-priority thread always forces a lower-priority thread to yield (that is, preempt) 
* the instant the higher-priority thread becomes ready to run, 
* without the need for the lower-priority thread to give up the 
* processor by calling the sched_yield() or SchedYield() functions.

* The sched_yield() function calls the kernel function SchedYield(), 
* and may be more portable across realtime POSIX systems.
* Note: You should avoid designing programs that contain busy wait loops.
* If you can't avoid them, you can use sched_yield() to reduce the 
* system load at a given priority level. Note that a thread that 
* calls sched_yield() in a tight loop will spend a great deal of time in the kernel, 
* which will have a small effect on interrupt latency.
*/

/* compile with gcc -Wall file.c -lpthread -o file */

#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>
#include<stdio.h>
#include<pthread.h>
#include<sched.h>


void * thread_functionFIRST(void *arg)
{
	while(1)
	{
/*LINE 1*/	sched_yield();  // Blocking this function and it will wait for other threads to execute first  
  		printf(" Inside thread_funtionFIRST.....\n");
 		sleep(5);
    	}

}

void * thread_functionSECOND(void *arg)
{
	while(1) 
	{
		printf("Inside thread_functionSECOND\n");
		sleep(5);
	}
}


int main()
{

	pthread_t thread1;
	pthread_t thread2;


	pthread_create(&thread1, NULL, thread_functionFIRST,  NULL);
	pthread_create(&thread2, NULL,thread_functionSECOND,   NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	return 0;
}

/* OUTPUT :- 
Note - This program's behaviour varies system to system
For example :- In a single processor it will work fine but in 
multiple processors the phenomena will be different or undefined by me and by my test 
may be i will be wrong due to my shallow knowledge but the logic of sched_yield is same and 
this above example is behaved as correct in all systems.
Here below is the result 

$ Before understanding the behaviour of sched_yield()
comment "LINE 1" above and then run 
$ ./a.out  
 Inside thread_funtionFIRST.....
Inside thread_functionSECOND
 Inside thread_funtionFIRST.....
Inside thread_functionSECOND
 Inside thread_funtionFIRST.....
Inside thread_functionSECOND
 Inside thread_funtionFIRST.....
Inside thread_functionSECOND

Now remove the comment compiile and then run 

$ ./a.out
Inside thread_functionSECOND
 Inside thread_funtionFIRST.....
Inside thread_functionSECOND
 Inside thread_funtionFIRST.....
Inside thread_functionSECOND
 Inside thread_funtionFIRST.....
Inside thread_functionSECOND
 Inside thread_funtionFIRST.....

Note :- In the first output you can see that thread first is running, 
after addition of sched_yeild in first thread it will block to execute 
the second thread firstly.
*/
