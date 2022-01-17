#include "operation.h"


//模式选择
int mode_selection(char str[],sqlite3 *db,int newfd)
{
	char choose;
	char buf[228];
	strcpy(buf,&str[1]);
	choose = str[0];

	switch(choose)
	{
		//管理员注册信息插入 
	case 'L':
		admin_login_inform_insert(buf,db,newfd);
		break;
 		//登入信息验证 
	case 'E':
		enter_inform_verify(buf,db,newfd);
		break;
    //管理员插入员工信息
	case 'A':
		admin_insert_staff_inform(buf,db,newfd);
		break;
    //管理员删除员工信息
	case 'D':
		admin_delete_staff_inform(buf,db,newfd);
		break;
   //修改员工信息和修改个人信息
	case 'M':
		admin_mod_staff_inform(buf,db,newfd);
		break;
   //查看员工信息和查看个人信息
	case 'C':
		admin_check_staff_inform(buf,db,newfd);
		break;
   //管理员查看所有员工的信息
	case 'F':
		admin_check_all_staff_inform(db,newfd);
		break;
	default:
		break;
	}

	return 0;

}
//管理员注册信息插入
int admin_login_inform_insert(char buf[],sqlite3* db,int newfd)
{
	char sql[228]="",str[228]="";
	char *errmsg = NULL;
	char id[20]="",name[20]="",age[20]="",phone[20]="",\
				 position[20]="",pay[20]="",addr[20]="";

	sscanf(buf,"%s%s%s%s%s%s%s",id,name,age,phone,position,pay,addr);
	sprintf(sql,"insert into data values (\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\")",id,name,age,phone,position,pay,addr);

	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("sqlite3_exec: %s   __%d__\n",errmsg,__LINE__);
		return -1;
	}

	sprintf(str,"注册成功！");
	if(send(newfd,str,sizeof(str),0) < 0)
	{
		perror("send");
		return -1;
	}
	return 0;
}
//登入信息验证
int enter_inform_verify(char buf[],sqlite3* db,int newfd)
{
	int row,column;
	char **presult = NULL;
	char sql[228]="",str[228]="";
	char *errmsg = NULL;
	char id[20]="",name[20]="";
	char admin[5]="";

	//printf("buf=%s",buf);
	sscanf(buf,"%s%s%s",admin,id,name);
	sprintf(sql,"select position from data where id=\"%s\" and name =\"%s\"",id,name);
	if(sqlite3_get_table(db,sql,&presult,&row,&column,&errmsg) != SQLITE_OK)
	{
		printf("sqlite3_exec: %s   __%d__\n",errmsg,__LINE__);
		return -1;
	}

	if(row == 0)
	{
		sprintf(str,"查询无结果！");
		if(send(newfd,str,sizeof(str),0) < 0)
		{
			perror("send");
			return -1;
		}
		bzero(str,sizeof(str));
		return -1;
	}
	//管理员信息验证
	if(admin[0] == 'S' && strncasecmp(presult[column],"ceo",3)==0) //'S'管理员识别码，"ceo"管理员职位
	{
		sprintf(str,"验证成功!");
		if(send(newfd,str,sizeof(str),0) < 0)
		{
			perror("send");
			return -1;
		}
		bzero(str,sizeof(str));
	}else if(admin[0]== 'S' && strncasecmp(presult[column],"ceo",3) !=0){
		sprintf(str,"权限不够!");
		if(send(newfd,str,sizeof(str),0) < 0)
		{
			perror("send");
			return -1;
		}
		bzero(str,sizeof(str));
	}
	//员工信息验证
	if(admin[0] == '*' && row > 0)//'*':普通员工识别码
	{
		sprintf(str,"验证成功!");
		if(send(newfd,str,sizeof(str),0) < 0)
		{
			perror("send");
			return -1;
		}
		bzero(str,sizeof(str));
	}


	sqlite3_free_table(presult);
	return 0;

}
//管理员插入员工信息
int admin_insert_staff_inform(char buf[],sqlite3* db,int newfd) 
{
	char sql[228]="",str[228]="";
	char *errmsg = NULL;
	char id[20]="",name[20]="",age[20]="",phone[20]="",\
				 position[20]="",pay[20]="",addr[20]="";

	sscanf(buf,"%s%s%s%s%s%s%s",id,name,age,phone,position,pay,addr);
	sprintf(sql,"insert into data values (\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\")",id,name,age,phone,position,pay,addr);

	printf("%s\n",sql);

	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("sqlite3_exec: %s   __%d__\n",errmsg,__LINE__);
		return -1;
	}
	sprintf(str,"增加员工信息成功！");
	if(send(newfd,str,sizeof(str),0) < 0)
	{
		perror("send");
		return -1;
	}
	return 0;
}
//管理员删除员工信息
int admin_delete_staff_inform(char buf[],sqlite3* db,int newfd) 
{
	int row,column;
	char **presult = NULL;
	char sql[228]="",str[228]="";
	char *errmsg = NULL;
	char id[20]="",name[20]="";

	sscanf(buf,"%s%s",id,name);
	sprintf(sql,"select id,name from data where id=\"%s\" and name =\"%s\"",id,name);

	if(sqlite3_get_table(db,sql,&presult,&row,&column,&errmsg) != SQLITE_OK)
	{
		printf("sqlite3_exec: %s   __%d__\n",errmsg,__LINE__);
		return -1;
	}


	if(row == 0)
	{
		sprintf(str,"查询无结果！");
		if(send(newfd,str,sizeof(str),0) < 0)
		{
			perror("send");
			return -1;
		}
	}else if(row > 0){
		bzero(sql,sizeof(sql));
		sprintf(sql,"delete from data where id=\"%s\" and name=\"%s\"",id,name);

		if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
		{
			printf("sqlite3_exec: %s   __%d__\n",errmsg,__LINE__);
			return -1;
		}
		sprintf(str,"删除成功！");
		if(send(newfd,str,sizeof(str),0) < 0)
		{
			perror("send");
			return -1;
		}

	}
	sqlite3_free_table(presult);
	return 0;
}
//修改员工信息和修改个人信息
int admin_mod_staff_inform(char buf[],sqlite3* db,int newfd) 
{
	int row,column;
	char **presult = NULL;
	char sql[228]="",str[228]="";
	char *errmsg = NULL;
	char id[20]="",name[20]="";
	char mod[30]="",type[30]="";

	sscanf(buf,"%s%s%s%s",type,id,name,mod);
	sprintf(sql,"select id,name from data where id=\"%s\" and name =\"%s\"",id,name);

	if(sqlite3_get_table(db,sql,&presult,&row,&column,&errmsg) != SQLITE_OK)
	{
		printf("sqlite3_exec: %s   __%d__\n",errmsg,__LINE__);
		return -1;
	}

	if(row == 0)
	{
		sprintf(str,"查询无结果！");
		if(send(newfd,str,sizeof(str),0) < 0)
		{
			perror("send");
			return -1;
		}
	}else if(row > 0){
		bzero(sql,sizeof(sql));
		sprintf(sql,"update data set %s=\"%s\" where id=\"%s\" and name =\"%s\"",type,mod,id,name);
		printf("%s\n",sql);

		if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
		{
			printf("sqlite3_exec: %s   __%d__\n",errmsg,__LINE__);
			return -1;
		}
		sprintf(str,"修改成功！");
		if(send(newfd,str,sizeof(str),0) < 0)
		{
			perror("send");
			return -1;
		}

	}
	sqlite3_free_table(presult);
	return 0;
}
//查看员工信息和查看个人信息
int admin_check_staff_inform(char buf[],sqlite3* db,int newfd) 
{                                                                     
	int row,column,j,i,k=0;
	char **presult = NULL;
	char sql[228]="",str[228]="";
	char *errmsg = NULL;
	char id[20]="",name[20]="";
	char string[128]="";

	sscanf(buf,"%s%s",id,name);
	sprintf(sql,"select * from data where id=\"%s\" and name =\"%s\"",id,name);

	if(sqlite3_get_table(db,sql,&presult,&row,&column,&errmsg) != SQLITE_OK)
	{
		printf("sqlite3_exec: %s   __%d__\n",errmsg,__LINE__);
		return -1;
	}

	//printf("%s\n",sql);

	if(row == 0)
	{
		sprintf(str,"查询无结果！");
		if(send(newfd,str,sizeof(str),0) < 0)
		{
			perror("send");
			return -1;
		}
	}else if(row > 0){

	for(i=0;i<(row+1);i++)
	{
		for(j=0;j<column;j++)
		{
			sprintf(string,"%s",presult[k++]);
			if(send(newfd,string,sizeof(string),0) < 0)
			{
				perror("send");
				return -1;
			}
			bzero(string,sizeof(string));
		}
	}

		bzero(string,sizeof(string));
		sprintf(string,"%c",'O');
		if(send(newfd,string,1,0) < 0)
		{
			perror("send");
			return -1;
		}

	}
	sqlite3_free_table(presult);
	return 0;
}

//管理员查看所有员工的信息
int admin_check_all_staff_inform(sqlite3* db,int newfd) 
{                                                                     
	int row,column,j,i,k=0;
	char **presult = NULL;
	char sql[228]="",str[228]="";
	char *errmsg = NULL;
	char id[20]="",name[20]="";
	char string[128]="";

	//sscanf(buf,"%s%s",id,name);
	sprintf(sql,"select * from data");

	if(sqlite3_get_table(db,sql,&presult,&row,&column,&errmsg) != SQLITE_OK)
	{
		printf("sqlite3_exec: %s   __%d__\n",errmsg,__LINE__);
		return -1;
	}

	//printf("%s\n",sql);

	if(row == 0)
	{
		sprintf(str,"查询无结果！");
		if(send(newfd,str,sizeof(str),0) < 0)
		{
			perror("send");
			return -1;
		}
	}else if(row > 0){

	for(i=0;i<(row+1);i++)
	{
		for(j=0;j<column;j++)
		{
			sprintf(string,"%s",presult[k++]);
			if(send(newfd,string,sizeof(string),0) < 0)
			{
				perror("send");
				return -1;
			}
			bzero(string,sizeof(string));
		}
	}

		bzero(string,sizeof(string));
		sprintf(string,"%c",'O');
		if(send(newfd,string,1,0) < 0)
		{
			perror("send");
			return -1;
		}

	}
	sqlite3_free_table(presult);
	return 0;
}
//员工修改个人信息
/*
int staff_modify_personal_inform(char buf[],sqlite3* db,int newfd)
{
	int row,column;
	char **presult = NULL;
	char sql[228]="",str[228]="";
	char *errmsg = NULL;
	char id[20]="",name[20]="";
	char mod[30]="",type[30]="";

	sscanf(buf,"%s%s%s%s",type,id,name,mod);
	sprintf(sql,"select id,name from data where id=\"%s\" and name =\"%s\"",id,name);

	if(sqlite3_get_table(db,sql,&presult,&row,&column,&errmsg) != SQLITE_OK)
	{
		printf("sqlite3_exec: %s   __%d__\n",errmsg,__LINE__);
		return -1;
	}


	if(row == 0)
	{
		sprintf(str,"查询无结果！");
		if(send(newfd,str,sizeof(str),0) < 0)
		{
			perror("send");
			return -1;
		}
	}else if(row > 0){
		bzero(sql,sizeof(sql));
		sprintf(sql,"update data set %s=\"%s\" where id=\"%s\" and name =\"%s\"",type,mod,id,name);
		printf("%s\n",sql);

		if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
		{
			printf("sqlite3_exec: %s   __%d__\n",errmsg,__LINE__);
			return -1;
		}
		sprintf(str,"修改成功！");
		if(send(newfd,str,sizeof(str),0) < 0)
		{
			perror("send");
			return -1;
		}

	}
	sqlite3_free_table(presult);
	return 0;

}
*/
