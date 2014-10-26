/*fwide - set and determine the orientation of a FILE stream 
*  When mode is zero, the fwide() function determines the current orientation of stream.
*  It returns a positive value if stream is wide-character oriented, that is, 
*  if wide-character I/O is permitted but char I/O is disallowed.
*  It returns a negative value if stream is byte oriented, i.e., if char I/O
*  is permitted but wide-character I/O is disallowed. It returns zero if stream has no orientation yet; 
*  in this case the next I/O operation might change the orientation
*  (to byte oriented if it is a char I/O operation, or to wide-character oriented
*  if it is a wide-character I/O operation).

*  Once a stream has an orientation, it cannot be changed and persists until the stream is closed.

*  When mode is nonzero, the fwide() function first attempts to set stream's orientation
*  (to wide-character oriented if mode is greater than 0, or to byte oriented if mode is less than 0). 
*  It then returns a value denoting the current orientation, as above.
*	For more info see man 3 fwide  */

#define _ISOC99_SOURCE 
#define _BSD_SOURCE
#define _XOPEN_SOURCE  500
#include<stdio.h>
#include<wchar.h>

int main()
{


	FILE * stream;
	int ret;

	stream = fopen ("myfile.txt","a");
	if(stream == NULL)
		perror("fopen");
	else if (stream)
	{
		fwide (stream,1);
		ret = fwide (stream,0);
		if (ret>0) 
			printf ("The stream is wide-oriented\n");
		else if (ret<0) 
			printf ("The stream is byte-oriented\n");
		else 
			printf ("The stream is not oriented");
		fclose (stream);
	}
	return 0;
}

/*OUTPUT : -
$ ./a.out
The stream is wide-oriented*/


