/*SCHED_RR processes behave the same as SCHED_FIFO processes except
that the scheduler assigns these processes timeslices.
When a SCHED_RR pro-
cess exhausts its timeslice, the scheduler moves the process to the end of the run list
for its current priority. In this manner, all SCHED_RR processes of the same priority are
executed in a round-robin rotation. Higher-priority processes (and SCHED_FIFO
processes of the same or higher priority) will always preempt a running SCHED_RR pro-
cess, regardless of whether it has any of its timeslice remaining.
POSIX defines an interface for retrieving the length of a given process’ timeslice:
#include <sched.h>
struct timespec {
time_t tv_sec;
long tv_nsec;
};

int sched_rr_get_interval (pid_t pid, struct timespec *tp);
*/


#include<stdio.h>
#include<sched.h>

int main()
{
	struct timespec tp;
	int ret;
	/* get the current task's timeslice length */
	ret = sched_rr_get_interval (0, &tp);
	if (ret == -1) {
		perror ("sched_rr_get_interval");
		return 1;
	}
	/* convert the seconds and nanoseconds to milliseconds */
	printf ("Our time quantum is %.2lf milliseconds\n",
			(tp.tv_sec * 1000.0f) + (tp.tv_nsec / 1000000.0f));
	return 0;
}

/*OUTPUT :-
$ ./a.out 
Our time quantum is 4.00 milliseconds
*/
