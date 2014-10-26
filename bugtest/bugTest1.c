/*Why not to use sprintf instead use only snprintf ? */
/*sprintf cannot check for overflow of the destination buffer. 
snprintf,on the otherhand , requires that the second argument 
be the size of the destination buffer and this buffer will not be overflowed*/

/*Lets check an example below */
/*Compile this program with gcc -Wall fno-stack-protector filename.c 
execute with ./a.out */
#include<stdio.h>

int main()
{
	char buf[4];
	sprintf(buf,"%s","jaidev");
	printf("%s\n",buf);
	return 0;
}

/*So the output is jaidev only omg what the fish why jaidev if i have taken 
buffer(buf) of size 4 its a bug in C 
so the answer is given above that sprintf cannot check buffer overflow which will do havoc 
which can do smash or corrupt your stack also if the data is too long and large.
Hurray We have solution ,Now instead of using sprintf we will use snprintf given below 
	snprintf(buf,4,"%s","jaidev");
The output will come ----  jai */
