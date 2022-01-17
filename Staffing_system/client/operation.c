#include "operation.h"


//注册
int admin_login(int sfd)
{

	char id[30],name[30],age[30],phone[30],\
		position[30],pay[30],addr[30];
	char buf[228]="0";

	printf("请输入注册的工号，姓名，年龄，电话:");
	scanf("%s%s%s%s",id,name,age,phone);
	getchar();
	printf("请输入注册的职位，薪资，住址:");
	scanf("%s%s%s",position,pay,addr);

	sprintf(buf,"%c%c%s%c%s%c%s%c%s%c%s%c%s%c%s",'L',' ',id,' ',name,' ',age,' ',phone,\
			' ',position,' ',pay,' ',addr);

	if(send(sfd,buf,sizeof(buf),0) < 0)
	{
		perror("send");
		return -1;
	}
	bzero(buf,sizeof(buf));
	if(recv(sfd,buf,sizeof(buf),0) < 0)
	{
		perror("recv");
		return -1;
	}
	printf("%s\n",buf);

	return 0;

}
//管理员登入
int admin_enter(int sfd,char admin)
{
	char id[30],name[30];
	char buf[228]="0";

	printf("请输入您的工号:");
	scanf("%s",id);
	getchar();
	printf("请输入您的姓名:");
	scanf("%s",name);

	sprintf(buf,"%c%c%c%c%s%c%s",'E',' ',admin,' ',id,' ',name);

	if(send(sfd,buf,sizeof(buf),0) < 0)
	{
		perror("send");
		return -1;
	}
	bzero(buf,sizeof(buf));
	if(recv(sfd,buf,sizeof(buf),0) < 0)
	{
		perror("recv");
		return -1;
	}

	printf("%s\n",buf);
	if(strncmp(buf,"验证成功!",5)==0)
	{
		return 1;
	}
	return 0;
}
//员工登入
int staff_enter(int sfd)
{
	char id[30],name[30];
	char buf[228]="0";

	printf("请输入您的工号:");
	scanf("%s",id);
	getchar();
	printf("请输入您的姓名:");
	scanf("%s",name);

	sprintf(buf,"%c%c%c%c%s%c%s",'E',' ','*',' ',id,' ',name);

	if(send(sfd,buf,sizeof(buf),0) < 0)
	{
		perror("send");
		return -1;
	}
	bzero(buf,sizeof(buf));
	if(recv(sfd,buf,sizeof(buf),0) < 0)
	{
		perror("recv");
		return -1;
	}

	printf("%s\n",buf);
	if(strncmp(buf,"验证成功!",5)==0)
	{
		return 1;
	}
	return 0;
}
//增加员工信息
int add_staff_inform(int sfd)
{
	char id[30],name[30],age[30],phone[30],\
		position[30],pay[30],addr[30];
	char buf[228]="0";

	printf("请输入要增加员工的工号，姓名，年龄，电话:");
	scanf("%s%s%s%s",id,name,age,phone);
	getchar();
	printf("请输入要增加员工的职位，薪资，住址:");
	scanf("%s%s%s",position,pay,addr);

	sprintf(buf,"%c%c%s%c%s%c%s%c%s%c%s%c%s%c%s",'A',' ',id,' ',name,' ',age,' ',phone,\
			' ',position,' ',pay,' ',addr);

	if(send(sfd,buf,sizeof(buf),0) < 0)
	{
		perror("send");
		return -1;
	}
	bzero(buf,sizeof(buf));
	if(recv(sfd,buf,sizeof(buf),0) < 0)
	{
		perror("recv");
		return -1;
	}
	printf("%s\n",buf);

	return 0;
}
//删除员工信息
int delete_staff_inform(int sfd)
{
	char id[30],name[30];
	char buf[228]="0";

	printf("请输入要删除员工的工号:");
	scanf("%s",id);
	getchar();
	printf("请输入要删除员工的姓名:");
	scanf("%s",name);

	sprintf(buf,"%c%c%s%c%s",'D',' ',id,' ',name);

	if(send(sfd,buf,sizeof(buf),0) < 0)
	{
		perror("send");
		return -1;
	}
	bzero(buf,sizeof(buf));
	if(recv(sfd,buf,sizeof(buf),0) < 0)
	{
		perror("recv");
		return -1;
	}
	printf("%s\n",buf);


	return 0;
}

//修改员工信息
int mod_staff_inform(int sfd)
{
	int choose=0,flag=0;
	char ack[10]="";
	char id[30],name[30];
	char buf[228]="0";
	char age[30],position[30],pay[30];

	printf("请输入员工的工号:");
	scanf("%s",id);
	getchar();
	printf("请输入员工的姓名:");
	scanf("%s",name);
	getchar();

	while(1)
	{
		printf("              ******************************************                 \n");
		printf("              ***************  1---职位  ***************                 \n");
		printf("              ***************  2---薪资  ***************                 \n");
		printf("              ***************  3---年龄  ***************                 \n");
		printf("              ***************  4---返回上一级  *********                 \n");
		printf("              ******************************************                 \n");

		printf("请输入你要选择的模式:");
		scanf("%d",&choose);
		getchar();
		switch(choose)
		{
		case 1:
			printf("请输入新职位:");
			scanf("%s",position);
			sprintf(buf,"%c%c%s%c%s%c%s%c%s",'M',' ',"position",' ',id,' ',name,' ',position);
			break;
		case 2:
			printf("请输入薪资:");
			scanf("%s",pay);
			sprintf(buf,"%c%c%s%c%s%c%s%c%s",'M',' ',"pay",' ',id,' ',name,' ',pay);
			break;
		case 3:
			printf("请输入年龄:");
			scanf("%s",age);
			sprintf(buf,"%c%c%s%c%s%c%s%c%s",'M',' ',"age",' ',id,' ',name,' ',age);
			break;
		case 4:
			flag =1;
			break;
		default:
			printf("输入有误,请重新输入.\n");
			break;
		}

		if(flag == 1)
		{
			break;
		}
		if(send(sfd,buf,sizeof(buf),0) < 0)
		{
			perror("send");
			return -1;
		}
		bzero(buf,sizeof(buf));

		if(recv(sfd,buf,sizeof(buf),0) < 0)
		{
			perror("recv");
			return -1;
		}
		printf("%s\n",buf);
		bzero(buf,sizeof(buf));

		printf("是否继续修改信息?(y/n):");
		scanf("%s",ack);
		getchar();
		if(strncasecmp(ack,"yes",3)==0 || ack[0]=='y' || ack[0] == 'Y')
		{
			continue;
		}else{
			break;
		}
	}
	return 0;
}
//查询员工信息
int check_staff_inform(int sfd)
{
	char id[30],name[30];
	char buf[228]="0";
	char str[128]="";

	printf("请输入要查询的员工的工号:");
	scanf("%s",id);
	getchar();
	printf("请输入要查询的员工的姓名:");
	scanf("%s",name);

	sprintf(buf,"%c%c%s%c%s",'C',' ',id,' ',name);

	if(send(sfd,buf,sizeof(buf),0) < 0)
	{
		perror("send");
		return -1;
	}
	while(1)
	{
		bzero(str,sizeof(str));
		if(recv(sfd,str,sizeof(str),0) < 0)
		{
			perror("recv");
			return -1;
		}
		if(str[0]=='O')//接受结束
		{
			printf("\n");
			break;
		}
		printf("%s  ",str);
	}
	return 0;
}
//查看个人信息
int check_personal_inform(int sfd)
{
	char id[30],name[30];
	char buf[128]="0";

	printf("请输入您的工号:");
	scanf("%s",id);
	getchar();
	printf("请输入您的姓名:");
	scanf("%s",name);

	sprintf(buf,"%c%c%s%c%s",'C',' ',id,' ',name);

	if(send(sfd,buf,sizeof(buf),0) < 0)
	{
		perror("send");
		return -1;
	}
	while(1)
	{
		bzero(buf,sizeof(buf));
		if(recv(sfd,buf,sizeof(buf),0) < 0)
		{
			perror("recv");
			return -1;
		}
		if(buf[0]=='O')//接受结束
		{
			printf("\n");
			break;
		}
		printf("%s  ",buf);
	}
	return 0;
}

//修改个人信息
int mod_personal_inform(int sfd)
{
	int choose=0,flag=0;
	char ack[10]="";
	char id[30],name[30];
	char buf[228]="0",phone[30]="",addr[30]="";

	printf("请输入您的工号:");
	scanf("%s",id);
	getchar();
	printf("请输入您的姓名:");
	scanf("%s",name);
	getchar();

	while(1)
	{
		printf("              **********************************************                 \n");
		printf("              *****************  1---电话  *****************                 \n");
		printf("              *****************  2---住址  *****************                 \n");
		printf("              *****************  3---返回上一级  ***********                 \n");
		printf("              **********************************************                 \n");

		printf("请输入你要选择的模式:");
		scanf("%d",&choose);
		getchar();
		switch(choose)
		{
		case 1:
			printf("请输入新电话:");
			scanf("%s",phone);
			sprintf(buf,"%c%c%s%c%s%c%s%c%s",'M',' ',"phone",' ',id,' ',name,' ',phone);
			break;
		case 2:
			printf("请输入新住址:");
			scanf("%s",addr);
			sprintf(buf,"%c%c%s%c%s%c%s%c%s",'M',' ',"addr",' ',id,' ',name,' ',addr);
			break;
		case 3:
			flag=1;
			break;
		default:
			printf("输入有误,请重新输入.\n");
			break;
		}

		if(flag == 1)
		{
			break;
		}
		if(send(sfd,buf,sizeof(buf),0) < 0)
		{
			perror("send");
			return -1;
		}
		bzero(buf,sizeof(buf));

		if(recv(sfd,buf,sizeof(buf),0) < 0)
		{
			perror("recv");
			return -1;
		}
		printf("%s\n",buf);

		printf("是否继续修改信息?(y/n):");
		scanf("%s",ack);
		getchar();
		if(strncasecmp(ack,"yes",3)==0 || ack[0]=='y' || ack[0] == 'Y')
		{
			continue;
		}else{
			break;
		}
	}
	return 0;
}

