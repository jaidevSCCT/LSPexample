/* These Program is to get interface name , interface index number , 
*  IP address for specific interface and MAC address and to check flags 
*  using ioctl calls 
*  Most of the flags you will get from man netdevice(7) */
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/ioctl.h>
#include<net/if.h>
#include<sys/types.h>  
#include<sys/socket.h>
#include<string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main()
{
	int sockfd,ret;
	struct ifreq ifr;
	char mac[14];
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd == -1)
		perror("socket");
	else
	{	
		/*===========SIOCGIFINDEX====================*/
		/* Interface name is necessary to get its index number or else this call will fail */
		strncpy(ifr.ifr_name,"eth0",IFNAMSIZ-1);      
		ret = ioctl(sockfd,SIOCGIFINDEX,&ifr); 
		if(ret == -1)
			perror("ioctl");
		else
			printf("Index number of %s is == %d\n",ifr.ifr_name,ifr.ifr_ifindex);
		/*===========================================*/

		/*===========SIOCGIFNAME====================*/
		/*Similary if you have index number from that you can get 
		  interface name if not known given below
		 *  memset to all zeros */
		memset(&ifr.ifr_name,0,sizeof(ifr.ifr_name)); 
		ret = ioctl(sockfd,SIOCGIFNAME,&ifr);  
		if(ret == -1)
			perror("ioctl");
		else
			printf("Interface name is  == %s\n",ifr.ifr_name);
		/*==========================================*/

		/*===========SIOCGIFADDR====================*/
		ret = ioctl(sockfd,SIOCGIFADDR,&ifr);
		if(ret == -1)
			perror("ioctl");
		else
			printf("IP ADDR is %s\n",inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
		/*===========================================*/


		/*===========SIOCGIFFLAGS====================*/
		/* checking only one flag which is IFF_UP( interface is running or not )*/
		ret = ioctl(sockfd,SIOCGIFFLAGS,&ifr);
		if(ret == -1)
			perror("ioctl");
		else if((ifr.ifr_flags & IFF_UP) == IFF_UP)
			printf("%s interface is running \n",ifr.ifr_name);
		else
			printf("Please Check for other flags\n");
		/*============================================*/
		
		/*===========SIOCGIFHWADDR====================*/
		int i;
		/*To get the mac address */
		ret = ioctl(sockfd,SIOCGIFHWADDR,&ifr);
		if(ret == -1)
			perror("ioctl");
		else
		{
			for(i=0;i<6;i++)
				mac[i] = ((struct sockaddr *)&ifr.ifr_hwaddr)->sa_data[i];
			printf("addr == %02x:%02x:%02x:%02x:%02x:%02x \n",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
		}
		/*============================================*/
		if(close(sockfd) == -1)
			perror("close");
	}
	return 0;
}

/*OUTPUT :- 
$./a.out 
Index number of eth0 is == 2
Interface name is  == eth0
IP ADDR is 1xx.28.1xx.xx
eth0 interface is running 
addr == xx:26:xx:xx:2d:xx
*/
