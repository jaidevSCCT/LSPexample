/*console_ioctl - ioctl's for console terminal and virtual consoles
  The following Linux-specific ioctl(2) requests are supported.  Each
  requires a third argument, assumed here to be argp.

  KDGETLED
  Get state of LEDs.  argp points to a char.  The lower three
  bits of *argp are set to the state of the LEDs, as follows:

  LED_CAP    0x04   caps lock led
  LEC_NUM    0x02   num lock led
  LED_SCR    0x01   scroll lock led

  KDSETLED
  Set the LEDs.  The LEDs are set to correspond to the lower
  three bits of argp.  However, if a higher order bit is set,
  the LEDs revert to normal: displaying the state of the
  keyboard functions of caps lock, num lock, and scroll lock.

  Before 1.1.54, the LEDs just reflected the state of the corresponding
  keyboard flags, and KDGETLED/KDSETLED would also change the keyboard
  flags.  Since 1.1.54 the LEDs can be made to display arbitrary
  information, but by default they display the keyboard flags.  The
  following two ioctls are used to access the keyboard flags.
  FOR INFO man console_ioctl(4)
 */
/* IMP NOTE - 
This description:

>       KDGETLED
>	      Get state of LEDs.  argp points to a long.  The lower three bits
>	      of *argp are set to the state of the LEDs, as follows:
>
>		  LED_CAP	0x04   caps lock led
>		  LEC_NUM	0x02   num lock led
>		  LED_SCR	0x01   scroll lock led

is wrong. The kernel only stores a single byte *argp, so if you give it the
address of a long, you won't necessarily find the results in the low 3 bits
of the long. (It happens to work out that way if you are little-endian.)
Change "long" to "char" and the description will be correct.*/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<sys/kd.h>
#include<unistd.h>
#include<stdlib.h>

#define ERROR -1

int main()
{
	int fd,ret;
	int i = 0;
	char orig = 0;

	if ((fd = open("/dev/console", O_NOCTTY)) == ERROR) {
		perror("open");
		exit(ERROR);
	}

	ret = ioctl(fd, KDGETLED, &orig);
	if(ret == -1)
		perror("ioctl");
	else
		printf("ret=%d orig=%08x\n",ret,orig);

	if (orig == LED_SCR) printf("Scroll Lock LED is on.\n");
	else if (orig == LED_NUM) printf("Numeric Lock LED is on.\n");
	else if (orig == LED_CAP) printf("Caps Lock LED is on.\n");

	else if (orig == LED_NUM + LED_CAP)
		printf("Numeric Lock and Caps Lock LEDs are on.\n");

	else if (orig == LED_NUM + LED_SCR)
		printf("Numeric Lock and Scroll Lock LEDs are on.\n");

	else if (orig == LED_CAP + LED_SCR)
		printf("Caps Lock and Scroll Lock LEDs are on.\n");

	else if (orig == LED_NUM + LED_SCR + LED_CAP)
		printf("Numeric Lock, Scroll Lock, and Caps Lock LEDs are on.\n");

	i |= LED_NUM;
	ret = ioctl(fd, KDSETLED, i);
	if(ret == -1)
		perror("ioctl");
	else
		printf("i = %d \n",i);
	sleep( 2 );

	i = 0;
	i |= LED_CAP;
	ret = ioctl(fd, KDSETLED, i);
	if(ret == -1)
		perror("ioctl");
	else
		printf("i = %d \n",i);

	sleep( 2 );

	i = 0;
	i |= LED_SCR;
	ret = ioctl(fd, KDSETLED, i);
	if(ret == -1)
		perror("ioctl");
	else
		printf("i = %d \n",i);

	sleep( 2 );

	ret = ioctl(fd, KDSETLED, orig);
	if(ret == -1)
		perror("ioctl");

	if(close(fd) == -1)
		perror("close");
	return 0;
}

/*OUTPUT : -
$ ./a.out
ret=0 orig=2
Numeric Lock LED is on.
i = 2 
i = 4 
i = 1 
 */
