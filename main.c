#include "chessboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mysql.h>
#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

behavior* bef;
char user_token[100];

// 毫无技术含量和新意的扫雷
int main()
{
	user_token[0] = '\0';
	int order;
	printf("欢迎使用红星牌扫雷系统：\n");
	while (1) {
		printf("1. 登录\n2. 注册\n3. 随机棋盘游玩\n4. 读取棋盘游玩\n");
		printf("输入标号以选择行动：\n");
		if (scanf("%d", &order) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		switch (order)
		{
		case 1: 
		{
			login_user();
			break; 
		}
		case 2:
		{
			register_user();
			break;
		}
		case 3:
		{
			make_rand_game();
			break;
		}
		case 4:
			make_appointed_game();
			break;
		default:
			printf("请输入有效的数字！\n");
			break;
		}
	}
}