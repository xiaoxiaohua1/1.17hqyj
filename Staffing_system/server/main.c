#include <stdio.h>
#include "sqlite.h"
#include "recv.h"

int main(int argc,const char *argv[])
{
	sqlite3 *db=NULL;

	//初始化数据库
    db = sqlite_operation();
	//接收客户端数据
	create_pthread_recv(db);

	return 0;
}
