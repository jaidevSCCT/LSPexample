/*
 * lstat() -  lstat() is identical to stat(), except that if path is a symbolic link,
 * then the link itself is stat-ed, not the file that it  refers
 * Note that if you change lstat() to stat() below, it will never say that
 * the target is a symlink ,it follows the symlink.
 * to use this code fist create a symbolic link or provide any symlink 
 */

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
	int ret;
	struct stat info;

    	if (argc < 2) 
	{
		fprintf(stderr, "usage: %s <file> ...\n", argv[0]);
		return 1;
    	}

	ret = lstat(argv[1],&info);
	if (ret == -1)
	{
	    perror("lstat");
	    return 1;
	} 
	else 
	{
	    /*
	     * Here we show various attributes of the file that we can find
	     * in the "stat" struct
	     */

	    	if (S_ISDIR(info.st_mode))
			printf("%s is a directory\n", argv[1]);
	    	if (S_ISREG(info.st_mode))
			printf("%s is a plain file\n", argv[1]);
	    	if (S_ISLNK(info.st_mode))
			printf("%s is a symlink\n", argv[1]);

		printf("%s has owner (uid) %ld and group %ld\n", argv[1],(long)info.st_uid,(long)info.st_gid);

	    	printf("%s has link count %d\n", argv[1],info.st_nlink);

	    	printf("%s has mode %o", argv[1],info.st_mode);

	}
	return 0;
}

/*OUTPUT :- 
$ ./a.out <symlink> 
stat is a symlink
stat has owner (uid) 0 and group 0
stat has link count 1
*/
