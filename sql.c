#include <mysql.h>
#include "chessboard.h"

// username: root
// password: Luye!!@@JWH888456


CBResult readFromMySql() 
{
	MYSQL mysql;  //mysql����
	MYSQL_RES* res; //һ��������ṹ��   
	MYSQL_ROW row; //char** ��ά���飬���һ������¼  

	mysql_init(&mysql);   //����mysql�����ݿ�
	if (!(mysql_real_connect(&mysql, "124.70.51.253", "root", "@Luye!!@@JWH888456", "bigWork", 3306, NULL, 0)))
	{
		printf("Error connecting to database:%s\n", mysql_error(&mysql));
		return ERRORCB;
	}
	return ERRORCB;
}