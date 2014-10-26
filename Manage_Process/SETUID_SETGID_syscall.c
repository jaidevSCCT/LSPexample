/* Example of setuid() , setgid() , getuid and getgid() 
If the process has appropriate privileges, setgid() sets the real group ID, 
effective group ID  and the saved set-group-ID  to gid.

If the process does not have appropriate privileges, 
but gid is equal to the real group ID  or the saved set-group-ID, 
 setgid() function sets the effective group ID to gid; the real group ID  
and saved set-group-ID  remain unchanged. */
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<errno.h>
int main()
{
	uid_t uid;
	gid_t gid;
	int st1 , st2;

		st1 = setuid(25);
		if(st1 == -1)
			perror("seteuid");
		
		st2 = setgid(512);
		if(st2 == EPERM)
			fprintf(stderr,"%s","The calling process is not privileged \n");
		else if(st2 == EAGAIN)
			fprintf(stderr,"%s","uid is different from the real user id \n");
		else
		{
			perror("setgid");
			fprintf(stderr,"%s","Can't Able to change gid\n");
		}

	uid = getuid();
	gid = getgid();

	printf("uid = %d , gid = %d \n",uid,gid);
	return 0;
}

/* OUTPUT : - 
 $ ./a.out
setgid: Operation not permitted
Can't Able to change gid
uid = 25 , gid = 0  */



