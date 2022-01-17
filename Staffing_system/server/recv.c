#include "recv.h"
#include "operation.h"

int create_pthread_recv(sqlite3 *db)
{
	//创建字节流式套接字
	int sfd = socket(AF_INET,SOCK_STREAM,0);
		if(sfd < 0)
		{
			ERR_MSG("socket");
			return -1;
		}
	//允许端口快速重用
	int reuse = 1;
	if(setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse))<0)
	{
		ERR_MSG("setsockopt");
		return -1;
	}
	//绑定IP和端口
	struct sockaddr_in sin;
	sin.sin_family   =AF_INET;
	sin.sin_port     =htons(PORT);
	sin.sin_addr.s_addr = inet_addr(IP);

	if(bind(sfd,(struct sockaddr*)&sin,sizeof(sin))<0)
	{
		ERR_MSG("bing");
		return -1;
	}
	printf("绑定成功\n");

	if(listen(sfd,10) < 0)
	{
		ERR_MSG("listen");
		return -1;
	}

	struct sockaddr_in cin;
	socklen_t addrlen = sizeof(cin);

	int newfd = 0;
	pthread_t tid;
	struct CliMsg info;

	while(1)
	{
		newfd = accept(sfd,(struct sockaddr*)&cin,&addrlen);
		if(newfd < 0)
		{
			ERR_MSG("accept");
			return -1;
		}
		info.cin = cin;
		info.newfd = newfd;
		info.db=db;

		if(pthread_create(&tid,NULL,recv_cli_msg,(void*)&info) < 0)
		{
			ERR_MSG("pthread_create");
			return -1;
		}
	}
    
	sqlite3_close(db);
	close(sfd);
}

void* recv_cli_msg(void* arg)
{
	pthread_detach(pthread_self());

	struct CliMsg info = *(struct CliMsg*)arg;
	struct sockaddr_in cin = info.cin;
	int newfd = info.newfd;
	sqlite3* db=info.db;

	char buf[228]="";
	ssize_t res = 0;
	while(1)
	{
		bzero(buf,sizeof(buf));
		res = recv(newfd,buf,sizeof(buf),0);
		if(res < 0)
		{
			ERR_MSG("recv");
			break;
		}
		else if(0 == res)
		{
			printf("[%s:%d] newfd = %d　客户端关闭\n",inet_ntoa(cin.sin_addr),ntohs(cin.sin_port),newfd);
			break;
		}

		mode_selection(buf,db,newfd);
	}
	return 0;
}
