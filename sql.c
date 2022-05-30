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
	mysql_set_character_set(&mysql, "utf8");

	return mysql;
}

void register_user() {
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
			continue;
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

void login_user() {
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
			continue;
		}
		else if (strcmp(username, "0") == 0) {
			printf("You cancel logining.\n");
			break;
		}

		sprintf(sqlStr, "select username, password, loginOrNot from User where username = '%s'", username);
		mysql_query(&mysql, sqlStr);
		res = mysql_store_result(&mysql);
		long long lengths = mysql_num_rows(res);
		mysql_free_result(res);
		if (lengths == 0) {
			printf("Your username has not been registered!\n");
			continue;
		}
		else {
			row = mysql_fetch_row(res);
			if (atoi(row[2]) == 1) {
				printf("The account is logining in another computer.\n");
				break;
			}
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
		sprintf(sqlStr, "update User set loginOrNot = 1 where username = '%s'", username);
		if (mysql_query(&mysql, sqlStr)) { printf("error\n"); return; };

		printf("Login successfully!\n");

		break;
	}

	mysql_close(&mysql);
	mysql_library_end();
	return;
}

CBFromMysql read_from_mysql() {
	CBFromMysql mysql_myCB;
	extern char user_token[100];
	if (strcmp(user_token, "") == 0) {
		printf("Please login at first!\n");
		return ERRORMS;
	}
	MYSQL mysql = open_db();
	MYSQL_RES* res;
	MYSQL_ROW row;
	char* sqlStr = (char*)malloc(sizeof(char) * 20501);
	if (sqlStr == NULL)
	{
		printf("fail to malloc()!\n");
		return ERRORMS;
	}
	sqlStr[0] = '\0';
	strcpy(sqlStr, "select * from minesweeper");
	mysql_query(&mysql, sqlStr);
	res = mysql_store_result(&mysql);
	long long pageNum = mysql_num_rows(res) / 10 + 1;
	long long pageNow = 1;
	long long temp = 0;
	char order[3];
	while (1) {
		printf("| %-10s | %-20s | %-10s | %-10s | %-10s | %-10s | %-20s |\n", "ID", "name", "line", "column", "mineNum", "record", "record-holder");
		while ((row = mysql_fetch_row(res)) != NULL) {
			printf("| %-10s | %-20s | %-10s | %-10s | %-10s | %-10s | %-20s |\n", row[0], row[1], row[2], row[3], row[5], row[6], row[7]);
			temp++;
			if (temp % 9 == 0) break;
		};
		printf("Page %lld\t totally %lld pages. Do you want to change page?(Y/N):\n", (temp) / 10 + 1, pageNum);
		scanf("%s", &order);
		setbuf(stdin, NULL);
		if (strcmp(order, "Y") == 0 || strcmp(order, "y") == 0) {
			printf("Input the page you chosed:\n");
			while (1) {
				if (scanf("%lld", &pageNow) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
				if (pageNow > 0 && pageNow <= pageNum) {
					mysql_data_seek(res, (pageNow - 1) * 10);
				}
				else {
					printf("The page is too large/too small.\n");
					continue;
				}
				break;
			}
		}
		else
			break;
	}

	mysql_free_result(res);
	int ID;
	while (1) {
		printf("Input the ID of the chessboard which you want to choose:\n");
		if (scanf("%d", &ID) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		sprintf(sqlStr, "select * from minesweeper where ID = %d", ID);
		mysql_query(&mysql, sqlStr);
		res = mysql_store_result(&mysql);
		long long length = mysql_num_rows(res);

		if (length == 0) {
			printf("There is no this ID!\n");
			mysql_free_result(res);
			continue;
		}

		/*char* temp_str = (char*)malloc(sizeof(char) * 20001);
		temp_str[0] = '\0';
		strcpy(temp_str, row[4]);*/

		row = mysql_fetch_row(res);
		mysql_myCB.ID = atoi(row[0]);
		mysql_myCB.name = row[1];
		mysql_myCB.lines = atoi(row[2]);
		mysql_myCB.columns = atoi(row[3]);
		mysql_myCB.chessboard = row[4];
		mysql_myCB.mines = atoi(row[5]);
		mysql_myCB.bestScore = atoi(row[6]);
		mysql_myCB.bester = row[7];
		break;
	}
	mysql_free_result(res);

	return mysql_myCB;
}

void upload_mysql(CBstring CBStr, int score, int mineNum) {
	extern char user_token[100];
	if (strcmp(user_token, "") == 0) {
		printf("Please login at first!\n");
		return;
	}
	int line = CBStr.line;
	int column = CBStr.column;
	char* chessboard = (char*)malloc(sizeof(char) * 20001);
	if (chessboard == NULL)
	{
		printf("fail to malloc()!\n");
		return;
	}
	chessboard[0] = '\0';
	strcpy(chessboard, CBStr.chessboard);

	MYSQL mysql = open_db();
	MYSQL_RES* res;
	char* sqlStr = (char*)malloc(sizeof(char) * 20501);
	if (sqlStr == NULL)
	{
		printf("fail to malloc()!\n");
		return;
	}
	sqlStr[0] = '\0';
	char name[100];
	while (1) {
		printf("Input the name of your chessboard(Input 0 to exit):\n");
		scanf("%s", name);
		setbuf(stdin, NULL);
		if (strlen(name) > 17) {
			printf("The length of name is too large.\n");
			continue;
		}
		else if (strcmp(name, "0") == 0) {
			printf("You cancel uploading.\n");
			break;
		}

		sprintf(sqlStr, "select name from minesweeper where name = '%s'", name);
		mysql_query(&mysql, sqlStr);
		res = mysql_store_result(&mysql);
		long long lengths = mysql_num_rows(res);
		mysql_free_result(res);
		if (lengths != 0) {
			printf("The name has been registered!\n");
			continue;
		}
		break;
	}

	sprintf(sqlStr, "insert into minesweeper (name, `lines`, columns, chessboard, mines, best_score, bester) values ('%s',%d,%d,'%s',%d,%d,'%s')",
		name, line, column, chessboard, mineNum, score, user_token);
	if (mysql_query(&mysql, sqlStr) == 0) {
		printf("Upload successfully!\n");
	}
	else {
		printf("Error connecting to database:%s\n", mysql_error(&mysql));
	};

	mysql_close(&mysql);
	mysql_library_end();
	return;
}

void update_score(int ID, int myCB_score)
{
	extern char user_token[100];
	MYSQL mysql = open_db();
	MYSQL_RES* res;
	MYSQL_ROW row;
	char sqlStr[200] = "";
	sprintf(sqlStr, "select best_score from minesweeper where ID =  %d", ID);
	mysql_query(&mysql, sqlStr);
	res = mysql_store_result(&mysql);
	if (mysql_num_rows(res) == 0 || strcmp(user_token, "") == 0) { printf("error\n"); return; };
	row = mysql_fetch_row(res);
	mysql_free_result(res);
	if (atoi(row[0]) < myCB_score) {
		sprintf(sqlStr, "update minesweeper set bester = '%s', best_score = %d where ID = %d", user_token, myCB_score, ID);
		if (mysql_query(&mysql, sqlStr)) { printf("error\n"); return; };
	}
	return;
}

void log_off() {
	extern char user_token[100];
	if (user_token[0] == '\0') { return; };
	MYSQL mysql = open_db();
	MYSQL_RES* res;
	MYSQL_ROW row;
	char sqlStr[200] = "";

	sprintf(sqlStr, "update User set loginOrNot = 0 where username = '%s'", user_token);
	mysql_query(&mysql, sqlStr);
	return;
}