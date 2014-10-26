/* Example of five other exec family 
execlp() , execle() , execv() , execvp() , execve() */

#include<stdio.h>
#include<unistd.h>
//Using execvp
/*int main()
{
        int ret;
        char *const argv[] = {"vi","/home/user/filename.txt",NULL};
        ret = execvp("vi",argv);
        if(ret == -1)
                perror("execvp");
        return 0;

}*/

//====================================================================
/* using execv
int main()
{
        int ret;
	char *const argv[] = {"nano","/home/user/filename.txt",NULL};
        ret = execv("/bin/nano",argv);
        if(ret == -1)
                perror("execv");
        return 0;

}
*/
//===================================================================
/*Using execle()
The  following  example  is  similar to Using execl() . In addition, it
specifies the environment for the  new  process  image  using  the  env
argument.*/
int main()
{
	int ret;
        char *env[] = { "HOME=/home/user","LOGNAME=user",NULL};
	ret = execle ("/bin/ls", "ls", "-l",NULL, env);
	if(ret == -1)
		perror("execle");
	return 0;
}

//==================================================================

/*Using execve()
The  following  example  passes  arguments to the ls command in the cmd
array, and specifies the environment for the new  process  image  using
the env argument.

int main()
{
	int ret;
        char *cmd[] = { "ls", "-l",NULL};
        char *env[] = { "HOME=/usr/home", "LOGNAME=home",NULL};
        ret = execve("/bin/ls", cmd, env);
	if(ret == -1)}
		perror("execve");
	return 0;
*/

//==================================================================
/* Using execlp()
int main()
{
	int ret;
	ret = execlp("vi","vi",NULL);
        if(ret == -1)
                perror("execlp");
	return 0;

// Note :- The following example searches for the location of the vi command among
// the directories specified by the PATH environment variable.

}*/
