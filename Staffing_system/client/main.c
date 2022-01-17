#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <strings.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <pthread.h>
#include "interface.h"

#define ERR_msg(msg) do{\
	printf("__%d__\n",__LINE__);\
	perror(msg);\
}while(0);
#define IP "192.168.1.123"
#define PORT 9999
#define N 228
int connect_server();  
int main(int argc, const char *argv[])
{
	connect_server();
	return 0;
}

int connect_server()
{
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd < 0)
	{
		ERR_msg("socket");
		return -1;
	}
	int reuse = 1;
	if(setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse))<0)
	{
		ERR_msg("setsockopt");
		return -1;
	}

	//填充ip和port信息
	struct sockaddr_in sin;
	sin.sin_family=AF_INET;
	sin.sin_port = htons(PORT);
	sin.sin_addr.s_addr = inet_addr(IP);

	if(connect(sfd,(struct sockaddr*)&sin,sizeof(sin)) < 0)
	{
		ERR_msg("connect");
		return -1;
	}
	char res =0;
	while(1)
	{
		res = do_menu(sfd);
		if(res > 0)
		{
			break;
		}
	}

	return 0;
}
