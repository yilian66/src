#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

  char Sno[32] = "\0";
	char Sname[16] = "\0";
	char Snation[20] = "\0";
	char Ssex[16] = "\0";
	char Sage[16] = "\0";
	char Sdept[20] = "\0";
	int status = 0;

	status = cgiFormString("Sno",  Sno, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Sno error!\n");
		return 1;
	}

	status = cgiFormString("Sname",  Sname, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Sname error!\n");
		return 1;
	}
	status = cgiFormString("Snation",  Snation, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Snation error!\n");
		return 1;
	}
	status = cgiFormString("Ssex",  Ssex, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Ssex error!\n");
		return 1;
	}

	status = cgiFormString("Sage",  Sage, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Sage error!\n");
		return 1;
	}
	status = cgiFormString("Sdept",  Sdept, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Sdept error!\n");
		return 1;
	}


	//fprintf(cgiOut, "name = %s, age = %s, stuId = %s\n", name, age, stuId);

	int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}



	strcpy(sql, "create table stu(Sno int not null primary key, Sname char(20) not null, Snation char(20) not null,Ssex char(16) not null,Sage int not null,Sdept char(20) not null)");
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return -1;
		}
	}



	sprintf(sql, "insert into stu values(%d, '%s', '%s', '%s', %d , '%s')", atoi(Sno), Sname, Snation, Ssex, atoi(Sage), Sdept);
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	fprintf(cgiOut, "add student ok!\n");
	mysql_close(db);
	return 0;
}
