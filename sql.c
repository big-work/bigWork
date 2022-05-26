#include <winsock.h>
#include <mysql.h>
#include <string.h>
#include "chessboard.h"
#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#pragma warning(disable : 6054)

const char* HOST = "124.70.51.253";
// username: root
// password: Luye!!@@JWH888456


MYSQL open_db() {
	MYSQL mysql;

	mysql_init(&mysql);
	if (!(mysql_real_connect(&mysql, HOST, "root", "Luye!!@@JWH888456", "bigWork", 3306, NULL, 0)))
	{
		printf("Error connecting to database:%s\n", mysql_error(&mysql));
		mysql_close(&mysql);
		mysql_library_end();
		return mysql;
	}

	mysql_library_init(0, NULL, NULL);
	printf("Connected successfully!\n");
	mysql_set_character_set(&mysql, "utf8");

	return mysql;
}

void RegisterUser() {
	MYSQL mysql = open_db();
	MYSQL_RES* res;
	//MYSQL_ROW row;
	if (&mysql == NULL) return;
	char username[100];
	char password[100];
	char temp[100];
	char sqlStr[1000] = "";
	while (1) {
		printf("Input your username(Input 0 to exit):\n");
		scanf("%s", username);
		setbuf(stdin, NULL);
		if (strlen(username) > 17) {
			printf("Your length of username is too large.\n");
		}
		else if (strcmp(username, "0") == 0) {
			printf("You cancel registering.\n");
			mysql_close(&mysql);
			mysql_library_end();
			return;
		}

		sprintf(sqlStr, "select username from User where username = '%s'", username);
		mysql_query(&mysql, sqlStr);
		res = mysql_store_result(&mysql);
		long long lengths = mysql_num_rows(res);
		mysql_free_result(res);
		if (lengths) {
			printf("Your username has been registered!\n");
			continue;
		}

		printf("Input your password(Input 0 to exit):\n");
		scanf("%s", password);
		setbuf(stdin, NULL);
		if (strlen(password) > 17) {
			printf("Your length of password is too large.\n");
		}
		else if (strcmp(password, "0") == 0) {
			printf("You cancel registering.\n");
			mysql_close(&mysql);
			mysql_library_end();
			return;
		}

		printf("Input the password again:\n");
		scanf("%s", temp);
		setbuf(stdin, NULL);
		if (strcmp(temp, password) != 0) {
			printf("Your password is not coincident!\n");
			continue;
		}
		break;
	}

	sprintf(sqlStr, "insert into User (username, password) values ('%s','%s')", username, password);
	if (mysql_query(&mysql, sqlStr) == 0) {
		printf("Register successfully!\n");
	}
	else {
		printf("Error connecting to database:%s\n", mysql_error(&mysql));
	};

	mysql_close(&mysql);
	mysql_library_end();

	return;
}

void LoginUser() {
	MYSQL mysql = open_db();
	MYSQL_RES* res;
	MYSQL_ROW row;
	extern char user_token[100];
	char username[100];
	char password[100] = "";
	char temp[100];
	char sqlStr[1000] = "";
	while (1) {
		printf("Input your username:(Input 0 to exit):\n");
		scanf("%s", username);
		setbuf(stdin, NULL);
		if (strlen(username) > 17) {
			printf("Your length of username is too large.\n");
		}
		else if (strcmp(username, "0") == 0) {
			printf("You cancel logining.\n");
			break;
		}

		sprintf(sqlStr, "select username, password from User where username = '%s'", username);
		mysql_query(&mysql, sqlStr);
		res = mysql_store_result(&mysql);
		long long lengths = mysql_num_rows(res);
		mysql_free_result(res);
		if (lengths == 0) {
			printf("Your username has not been registered!\n");
			break;
		}
		else {
			row = mysql_fetch_row(res);
			strcpy(password, row[1]);
		}

		printf("Input your password:(Input 0 to exit):\n");
		scanf("%s", temp);
		setbuf(stdin, NULL);
		if (strlen(temp) > 17) {
			printf("Your length of password is too large.\n");
		}
		else if (strcmp(password, "0") == 0) {
			printf("You cancel logining.\n");
			break;
		}

		if (strcmp(temp, password) != 0) {
			printf("Your password is wrong!\n");
			continue;
		}

		strcpy(user_token, username);
		printf("Login successfully!\n");

		break;
	}

	mysql_close(&mysql);
	mysql_library_end();
	return;
}

CBFromMysql readFromMysql() {

}

void uploadMysql(CBstring CBStr, int score, int mineNum) {
	if (strcmp(user_token, "") == 0) {
		printf("Please login at first!\n");
	}
}