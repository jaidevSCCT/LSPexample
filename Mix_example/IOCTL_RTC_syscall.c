/*As per Kernel Doc
The newest non-PC hardware tends to just count seconds, like the time(2)
system call reports, but RTCs also very commonly represent time using
the Gregorian calendar and 24 hour time, as reported by gmtime(3).

Linux has two largely-compatible userspace RTC API families you may
need to know about:

    *	/dev/rtc ... is the RTC provided by PC compatible systems,
	so it's not very portable to non-x86 systems.

    *	/dev/rtc0, /dev/rtc1 ... are part of a framework that's
	supported by a wide variety of RTC chips on all systems
IOCTL INTERFACE
---------------

The ioctl() calls supported by /dev/rtc are also supported by the RTC class
framework.  However, because the chips and systems are not standardized,
some PC/AT functionality might not be provided.  And in the same way, some
newer features -- including those enabled by ACPI -- are exposed by the
RTC class framework, but can't be supported by the older driver.
For more info see kernel doc or man rtc(4) 
*/
/* Program to get time from RTC clock*/
#include<stdio.h>
#include<sys/ioctl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<linux/rtc.h>

int main()
{
	int timefd,ret;
	struct rtc_time rtc_tm;
	timefd = open("/dev/rtc0",O_RDONLY);
	if(timefd == -1)
		perror("open");

	ret = ioctl(timefd,RTC_RD_TIME,&rtc_tm);
	if(ret == -1)
		perror("ioctl");
	else
	{
		/* Read the RTC time/date */
	fprintf(stderr, "\n\nCurrent RTC date/time is %d-%d-%d, %02d:%02d:%02d.\n",rtc_tm.tm_mday, 
		rtc_tm.tm_mon + 1, rtc_tm.tm_year + 1900,rtc_tm.tm_hour, rtc_tm.tm_min, rtc_tm.tm_sec);
	}
		
	close(timefd);
	return 0;
}

/*OUTPUT :- 
# ./a.out    (NOTE :- NEED ROOT PERMISSION) 
Current RTC date/time is 10-8-2014, 17:18:19.
*/
