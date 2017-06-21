#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
  char Sno[32] = "\0";
  char Cno[32] = "\0";
	char Grade[16] = "\0";
	char status = 0;

  status = cgiFormString("Sno",  Sno, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Sno error!\n");
		return 1;
	}

	status = cgiFormString("Cno",  Cno, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Cno error!\n");
		return 1;
	}

	status = cgiFormString("Grade",  Grade, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Grade error!\n");
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



	strcpy(sql, "create table sc( Sno int not null,Cno int not null , Grade int,primary key(Sno,Cno),foreign key(Sno) references    stu(Sno),  foreign key(Cno) references course(Cno))");
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return -1;
		}
	}



	sprintf(sql, "insert into sc values(%d, %d , %d )", atoi(Sno), atoi(Cno), atoi(Grade));
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	fprintf(cgiOut, "add sc ok!\n");
	mysql_close(db);
	return 0;
}
