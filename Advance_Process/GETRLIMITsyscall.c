/*Linux provides two system calls for manipulating resource limits. POSIX standardized
* both interfaces, but Linux supports several limits in addition to those dictated by the
* standard. Limits can be checked with getrlimit() and set with setrlimit() :
#include <sys/time.h>
#include <sys/resource.h>
struct rlimit {
rlim_t rlim_cur;
rlim_t rlim_max;
}; 
 
int getrlimit (int resource, struct rlimit *rlim);
int setrlimit (int resource, const struct rlimit *rlim);

* Integer constants, such as RLIMIT_CPU , represent the resources. The rlimit structure
* represents the actual limits. The structure defines two ceilings: a soft limit and a hard
* limit. The kernel enforces soft resource limits on processes, but a process may freely
* change its soft limit to any value from 0 up to and including the hard limit. A process
* without the CAP_SYS_RESOURCE capability (i.e., any nonroot process) can only lower its
* hard limit. An unprivileged process can never raise its hard limit, not even to a previ‐
* ously higher value; lowering the hard limit is irreversible. A privileged process can set
* he hard limit to any valid value.
for more info see man getrlimit(2)*/


#include<stdio.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<string.h>
int main()
{
	int ret;
	struct rlimit rlm;
	
	printf(" -1 Denotes RLIM_INFINITY\n");

	/*========RLIMIT_AS===================*/
	ret = getrlimit(RLIMIT_AS,&rlm);
	if(ret == -1)
		perror("getrlimit");
	printf("RLIMIT_AS\n");
	printf("Soft limit = %ld , Hard limit = %ld\n",
			rlm.rlim_cur,rlm.rlim_max);

	/*=====================================*/

	memset(&rlm,0,sizeof(struct rlimit));

	/*========RLIMIT_CORE===================*/
	ret = getrlimit(RLIMIT_CORE,&rlm);
	if(ret == -1)
		perror("getrlimit");
	printf("RLIMIT_CORE\n");
	printf("Soft limit = %ld , Hard limit = %ld\n",
			rlm.rlim_cur,rlm.rlim_max);
	/*=======================================*/

	memset(&rlm,0,sizeof(struct rlimit));

        /*========RLIMIT_CPU===================*/
        ret = getrlimit(RLIMIT_CPU,&rlm);
        if(ret == -1)
                perror("getrlimit");
        printf("RLIMIT_CPU\n");
        printf("Soft limit = %ld , Hard limit = %ld\n",
                        rlm.rlim_cur,rlm.rlim_max);
        /*=======================================*/

        memset(&rlm,0,sizeof(struct rlimit));

        /*========RLIMIT_DATA===================*/
        ret = getrlimit(RLIMIT_DATA,&rlm);
        if(ret == -1)
                perror("getrlimit");
        printf("RLIMIT_DATA\n");
        printf("Soft limit = %ld , Hard limit = %ld\n",
                        rlm.rlim_cur,rlm.rlim_max);
        /*=======================================*/

        memset(&rlm,0,sizeof(struct rlimit));

        /*========RLIMIT_FSIZE===================*/
        ret = getrlimit(RLIMIT_FSIZE,&rlm);
        if(ret == -1)
                perror("getrlimit");
        printf("RLIMIT_FSIZE\n");
        printf("Soft limit = %ld , Hard limit = %ld\n",
                        rlm.rlim_cur,rlm.rlim_max);
        /*=======================================*/

        memset(&rlm,0,sizeof(struct rlimit));

        /*========RLIMIT_LOCKS===================*/
        ret = getrlimit(RLIMIT_LOCKS,&rlm);
        if(ret == -1)
                perror("getrlimit");
        printf("RLIMIT_LOCKS\n");
        printf("Soft limit = %ld , Hard limit = %ld\n",
                        rlm.rlim_cur,rlm.rlim_max);
        /*=======================================*/

        memset(&rlm,0,sizeof(struct rlimit));

        /*========RLIMIT_MEMLOCK===================*/
        ret = getrlimit(RLIMIT_MEMLOCK,&rlm);
        if(ret == -1)
                perror("getrlimit");
        printf("RLIMIT_MEMLOCK\n");
        printf("Soft limit = %ld , Hard limit = %ld\n",
                        rlm.rlim_cur,rlm.rlim_max);
        /*=======================================*/
        memset(&rlm,0,sizeof(struct rlimit));

        /*========RLIMIT_MSGQUEUE===================*/
        ret = getrlimit(RLIMIT_MSGQUEUE,&rlm);
        if(ret == -1)
                perror("getrlimit");
        printf("RLIMIT_MSGQUEUE\n");
        printf("Soft limit = %ld , Hard limit = %ld\n",
                        rlm.rlim_cur,rlm.rlim_max);
        /*=======================================*/
        memset(&rlm,0,sizeof(struct rlimit));

        /*========RLIMIT_NICE===================*/
        ret = getrlimit(RLIMIT_NICE,&rlm);
        if(ret == -1)
                perror("getrlimit");
        printf("RLIMIT_NICE\n");
        printf("Soft limit = %ld , Hard limit = %ld\n",
                        rlm.rlim_cur,rlm.rlim_max);
        /*=======================================*/

        memset(&rlm,0,sizeof(struct rlimit));

        /*========RLIMIT_NOFILE===================*/
        ret = getrlimit(RLIMIT_NOFILE,&rlm);
        if(ret == -1)
                perror("getrlimit");
        printf("RLIMIT_NOFILE\n");
        printf("Soft limit = %ld , Hard limit = %ld\n",
                        rlm.rlim_cur,rlm.rlim_max);
        /*=======================================*/

        memset(&rlm,0,sizeof(struct rlimit));

        /*========RLIMIT_NPROC===================*/
        ret = getrlimit(RLIMIT_NPROC,&rlm);
        if(ret == -1)
                perror("getrlimit");
        printf("RLIMIT_NRPOC\n");
        printf("Soft limit = %ld , Hard limit = %ld\n",
                        rlm.rlim_cur,rlm.rlim_max);
        /*=======================================*/

        memset(&rlm,0,sizeof(struct rlimit));

        /*========RLIMIT_RSS===================*/
        ret = getrlimit(RLIMIT_RSS,&rlm);
        if(ret == -1)
                perror("getrlimit");
        printf("RLIMIT_RSS\n");
        printf("Soft limit = %ld , Hard limit = %ld\n",
                        rlm.rlim_cur,rlm.rlim_max);
        /*=======================================*/

        memset(&rlm,0,sizeof(struct rlimit));

        /*========RLIMIT_RTPRIO===================*/
        ret = getrlimit(RLIMIT_RTPRIO,&rlm);
        if(ret == -1)
                perror("getrlimit");
        printf("RLIMIT_RTPRIO\n");
        printf("Soft limit = %ld , Hard limit = %ld\n",
                        rlm.rlim_cur,rlm.rlim_max);
        /*=======================================*/

        memset(&rlm,0,sizeof(struct rlimit));

        /*========RLIMIT_SIGPENDING===================*/
        ret = getrlimit(RLIMIT_SIGPENDING,&rlm);
        if(ret == -1)
                perror("getrlimit");
        printf("RLIMIT_SIGPENDING\n");
        printf("Soft limit = %ld , Hard limit = %ld\n",
                        rlm.rlim_cur,rlm.rlim_max);
        /*=======================================*/
        memset(&rlm,0,sizeof(struct rlimit));

        /*========RLIMIT_STACK==========================*/
        ret = getrlimit(RLIMIT_STACK,&rlm);
        if(ret == -1)
                perror("getrlimit");
        printf("RLIMIT_STACK\n");
        printf("Soft limit = %ld , Hard limit = %ld\n",
                        rlm.rlim_cur,rlm.rlim_max);
        /*=======================================*/

	return 0;
}

/*OUTPUT :-
$ ./a.out
-1 Denotes RLIM_INFINITY
RLIMIT_AS
Soft limit = -1 , Hard limit = -1
RLIMIT_CORE
Soft limit = 0 , Hard limit = -1
RLIMIT_CPU
Soft limit = -1 , Hard limit = -1
RLIMIT_DATA
Soft limit = -1 , Hard limit = -1
RLIMIT_FSIZE
Soft limit = -1 , Hard limit = -1
RLIMIT_LOCKS
Soft limit = -1 , Hard limit = -1
RLIMIT_MEMLOCK
Soft limit = 65536 , Hard limit = 65536
RLIMIT_MSGQUEUE
Soft limit = 819200 , Hard limit = 819200
RLIMIT_NICE
Soft limit = 0 , Hard limit = 0
RLIMIT_NOFILE
Soft limit = 1024 , Hard limit = 4096
RLIMIT_NRPOC
Soft limit = 14911 , Hard limit = 14911
RLIMIT_RSS
Soft limit = -1 , Hard limit = -1
RLIMIT_RTPRIO
Soft limit = 0 , Hard limit = 0
RLIMIT_SIGPENDING
Soft limit = 14911 , Hard limit = 14911
RLIMIT_STACK
Soft limit = 8388608 , Hard limit = -1
 */
