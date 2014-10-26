/*
* The  getgrnam() function returns a pointer to a structure containing
* the broken-out fields of the record in the group database (e.g.,
* the local group file /etc/group, NIS, and LDAP) that matches the group name name.
       The group structure is defined in <grp.h> as follows:

           struct group {
               char   *gr_name;       group name
               char   *gr_passwd;     group password
               gid_t   gr_gid;        group ID
               char  **gr_mem;        group members
           };
*/

#include<stdio.h>
#include<sys/types.h>
#include<grp.h>
int main(int argc,char *argv[])
{
	struct group *info;

	/* getgrnam() returns information on group give its name */
	
	info = getgrnam("Provide your group name here"); // example getgrnam("office");
	if(info == NULL)
	{
		perror("getgrnam");
		return -1;		
	}	
	
	printf(" grp name and grp password and grp gid :  %s : %s : %ld \n",info->gr_name,info->gr_passwd,(long)info->gr_gid);

	return 0;
}

/*OUTPUT :- 
$ ./a.out 
 grp name and grp password and grp gid :  office : x : 1000 */
