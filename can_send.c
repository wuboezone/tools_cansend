/* ************************************************************************
 *       Filename:  vcan0_send.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2019年07月18日 18时02分10秒
 *       Revision:  0.0.1
 *       Compiler:  gcc
 *         Author:  ts 
 *        Company:  
 * ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<net/if.h>
#include<sys/ioctl.h>
#include<sys/socket.h>
#include<linux/can.h>
#include<linux/can/raw.h>
int main()
{
	int s,nbytes;
	struct sockaddr_can addr;
	struct ifreq ifr;
	struct can_frame frame[2] = {{0}};
	s = socket(PF_CAN,SOCK_RAW,CAN_RAW);
	printf("send_s = %d\n",s);
	strcpy(ifr.ifr_name,"can0");
	ioctl(s,SIOCGIFINDEX,&ifr);
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
	bind(s,(struct sockaddr *)&addr,sizeof(addr));
	
	setsockopt(s,SOL_CAN_RAW,CAN_RAW_FILTER,NULL,0);

	frame[0].can_id = 0x11;
	frame[0].can_dlc = 1;
	frame[0].data[0] = 'Y';
	frame[1].can_id = 0x410;
	frame[1].can_dlc = 1;
	frame[1].data[0] = 'N';

	while(1)
	{
		nbytes = write(s,&frame[0],sizeof(frame[0]));
		if (nbytes != sizeof(frame[0]))
		{
			printf("Send Error frame[0]!\n");
			break;
		}

		sleep(1);
		
		nbytes = write(s,&frame[1],sizeof(frame[1]));
		if (nbytes != sizeof(frame[1]))
		{
			printf("Send Error frame[1]!\n");
			break;
		}

		sleep(1);

	}

	close(s);

	return 0;
	
}



