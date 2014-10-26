/*Program to check whether any event is occured in stdin using epoll syscall
	For more info refer man 7 epoll */
#include<stdio.h>
#include<sys/epoll.h>
#include<malloc.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>
#define MAX_EVENTS 64

int main()
{
	int epfd,ret,nr_ev,i;
	struct epoll_event event;
	struct epoll_event *event1;
	extern int errno;

	epfd = epoll_create(1);
	if(epfd < 0)
	{
		perror("epoll_create");
		return -1;
	}

	event.data.fd = STDIN_FILENO;
	event.events = EPOLLIN;

	ret = epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
	if(ret == -1)
	{
		perror("epoll_ctl");
		return -1;
	}

	event1 = malloc(sizeof(struct epoll_event)*MAX_EVENTS);
	if(!event1)
	{
		perror("malloc");
		return 1;
	}

	nr_ev = epoll_wait(epfd,event1,MAX_EVENTS,-1);
	if(nr_ev < 0)
	{
		perror("epoll_wait");
		return -1;
	}
	else
	{
	for(i=0;i<nr_ev;i++)
	{
		printf("event = %d on fd = %d\n",event1[i].events,event1[i].data.fd);
		if(event1[i].events & EPOLLIN )
		{
			printf("Event occured in stdin \n");
			close(event1[i].data.fd);
			break;
		}
	}
	}
	close(STDIN_FILENO);
	errno = 0;
	free(event1);
	if(errno)
		printf("error on free");
	return 0;

}

/* OUTPUT :-
 $ ./executable
It will go infinte loop so type something on your terminal and press enter 
12345 (Press enter after)
event = 1 on fd = 0
Event occured in stdin
	*/
