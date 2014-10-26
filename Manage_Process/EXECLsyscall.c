/* A call to execl() replaces the current process image with a new one by loading
into memory, the program pointed at by path */

#include<stdio.h>
#include<unistd.h>

int main()
{
	int ret;

	ret = execl("/bin/nano","nano",NULL);
	if(ret == -1)
		perror("execl");

	return 0;
}

/*More Example 
If you want to edit your file 

1) int main()
{
        int ret;

        ret = execl("/bin/nano","nano","/home/name/filename.txt",NULL);
        if(ret == -1)
                perror("execl");

        return 0;
}

2) int main()
{
        int ret;
        ret = execl("/bin/ls", "/bin/ls", "-r", "-t", "-l", NULL);
        if(ret == -1)
                perror("execl");

        return 0;
}
*/
