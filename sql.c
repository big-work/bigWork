#include <mysql.h>
#include "chessboard.h"

// username: root
// password: Luye!!@@JWH888456


CBResult readFromMySql() 
{
	MYSQL mysql;  //mysql连接
	MYSQL_RES* res; //一个结果集结构体   
	MYSQL_ROW row; //char** 二维数组，存放一条条记录  

	mysql_init(&mysql);   //连接mysql，数据库
	if (!(mysql_real_connect(&mysql, "124.70.51.253", "root", "@Luye!!@@JWH888456", "bigWork", 3306, NULL, 0)))
	{
		printf("Error connecting to database:%s\n", mysql_error(&mysql));
		return ERRORCB;
	}
	return ERRORCB;
}