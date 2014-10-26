/* mechanism for determining the system timer frequency at runtime */

#include<stdio.h>
#include<unistd.h>

int main()
{
	long Hz;
	Hz = sysconf(_SC_CLK_TCK);
	if(Hz == -1)
		perror("sysconf"); // should never occur
	else
		printf(" sytem timer frequency : %ld HZ \n",Hz);
	return 0;
}
/*OUTPUT :-
$ ./a.out
sytem timer frequency : 100 HZ 
*/
