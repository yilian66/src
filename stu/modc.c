#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"
char * headname = "head.html";
char * footname = "footer.html";
int cgiMain()
{
FILE * fd;
	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
  char Cno[32] = "\0";
	char Cname[16] = "\0";
	char Cpno[32] = "\0";
	char Ccredit[16] = "\0";
	int status = 0;
	char ch;

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
	if(!(fd = fopen(headname, "r"))){
		fprintf(cgiOut, "Cannot open file, %s\n", headname);
		return -1;
	}
	ch = fgetc(fd);

	while(ch != EOF){
		fprintf(cgiOut, "%c", ch);
		ch = fgetc(fd);
	}
	fclose(fd);

	status = cgiFormString("Cno",  Cno, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Cno error!\n");
		return 1;
	}
	status = cgiFormString("Cname",  Cname, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Cname error!\n");
		return 1;
	}
	status = cgiFormString("Cpno",  Cpno, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Cpno error!\n");
		return 1;
	}
	status = cgiFormString("Ccredit",  Ccredit, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Ccredit error!\n");
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


	sprintf(sql, "update course set Cname='%s',   Cpno= %d ,    Ccredit= %d   where Cno = %d ", Cname,  atoi(Cpno),atoi(Ccredit),  atoi(Cno));
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}



	fprintf(cgiOut, "update course ok!\n");
	mysql_close(db);
	return 0;
}
