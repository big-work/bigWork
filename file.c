#include "chessboard.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <io.h>
#pragma warning (disable : 4996)
#pragma warning (disable : 6031)

// saveCB 在本地存储棋盘
void saveCB(CBstring CBStr) {
	// 定义初始变量
	int column = CBStr.column;
	int line = CBStr.line;
	char name[200] = "";
	char* str = (char*)malloc(sizeof(char) * 20005);
	if (str == NULL) { printf("fail to malloc()!\n"); return; }
	str[0] = '\0';

	// 以"%d-%d-%s"的格式设计本地的棋盘格式
	sprintf(str, "%d-%d-%s", line, column, CBStr.chessboard);
	char file_str[200];

	// 用户交互
	do {
		printf("输入你想要保存的棋盘的名字：\n");
		if (scanf("%s", name) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		sprintf(file_str, "./output/%s.txt", name);
		if (strlen(name) > 16) {
			printf("名字长度超过了限制（小于等于16个字符长度）！\n");
			setbuf(stdin, NULL); continue;
		}
		else if (access(file_str, 0) != -1) {
			printf("在你的output目录下存在重名文件，请重新命名！\n");
			setbuf(stdin, NULL); continue;
		}
		break;
	} while (1);

	// 使用fputs保存棋盘
	FILE* file = fopen(file_str, "w");
	fputs(str, file);
	fclose(file);
	printf("棋盘已成功保存，前往output目录查看详细。\n");
	free(str);
	return;
}

// readCB 从本地读取棋盘
CBstring readCB() {
	// 定义初始变量
	char name[200] = "";
	char file_str[200];
	CBstring CBStr;
	char* chessboard = (char*)malloc(sizeof(char) * 20001);
	if (chessboard == NULL) { printf("fail to malloc()!\n"); return ERRORCS; }
	chessboard[0] = '\0';

	// 用户交互
	do {
		printf("输入output目录下的棋盘名（输入0以返回）:\n");
		scanf("%s", name);
		if (strcmp(name, "0") == 0) { return ERRORCS; }
		else if (strlen(name) > 16) {
			printf("名字长度超过了限制（小于等于16个字符长度）！\n");
			setbuf(stdin, NULL); continue;
		}
		sprintf(file_str, "./output/%s.txt", name);
		if (access(file_str, 0) == -1) {
			printf("在你的output目录不存在该文件！\n");
			setbuf(stdin, NULL); continue;
		}
		break;
	} while (1);

	// 以"%d-%d-%s"的格式在本地读取棋盘
	int line, column;
	FILE* file = fopen(file_str, "r");
	if (file == NULL) { printf("error!\n"); setbuf(stdin, NULL); return ERRORCS; };
	fscanf(file, "%d-%d-%s", &line, &column, chessboard);
	fclose(file);

	CBStr.line = line;
	CBStr.column = column;
	CBStr.chessboard = chessboard;

	return CBStr;
}

// get_simplified_token 获取简易token
void get_simplified_token() {
	// 定义初始变量
	extern char user_token[100];
	char username[100] = "";
	char simplified_token[100] = "";
	char* file_str = "./simplified_token/token.txt";
	FILE* file = fopen(file_str, "r");
	time_t now = time(NULL);
	int time_login;
	if (file == NULL) { return; };

	// 获取援用token, 如果token过期则不返回user_token, 如果未过期则刷新token
	fscanf(file, "%d-%s", &time_login, &username);
	if (((double)now - (double)time_login) / CLOCKS_PER_SEC > 3600) {
		strcpy(user_token, username);
		log_off();
		fclose(file);
		return;
	};

	sprintf(simplified_token, "%d-%s", time_login, username);
	strcpy(user_token, username);
	fclose(file);

	file = fopen(file_str, "w");
	fprintf(file, "%s", simplified_token);
	fclose(file);

	return;
}

// write_token 保存token
void write_token() {
	// 定义初始变量
	extern char user_token[100];
	char simplified_token[100] = "";
	char* file_str = "./simplified_token/token.txt";
	FILE* file = fopen(file_str, "w");
	if (file == NULL) { printf("error\n"); return; };
	time_t now = time(NULL);

	// 以"%.0f-%s"的格式设计token
	sprintf(simplified_token, "%.0f-%s", (double)now, user_token);
	fprintf(file, "%s", simplified_token);
	fclose(file);

	return;
}

// delete_token 删除token
void delete_token() {
	char* file_str = "./simplified_token/token.txt";
	remove(file_str);
	return;
}