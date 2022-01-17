#include "sqlite.h"

sqlite3* sqlite_operation()
{
	char * errmsg =NULL;
	static sqlite3 * db;
	if(sqlite3_open("./data.db",&db) != SQLITE_OK)
	{
		fprintf(stderr,"sqlite3_open:%s\n",sqlite3_errmsg(db));
		return NULL;
	}
	//创建一张表格
	char sql[200]="create table if not exists data(id char primary key,\
		               name char,age char,phone char,position char,\
					   salary char,addr char);";
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("sqlite3_exec:%s__%d__\n",errmsg,__LINE__);
		return NULL;
	}


	return db;
}




