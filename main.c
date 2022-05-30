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
	get_simplified_token();
	if (user_token[0] == '\0') { printf("你还没有登录，部分功能受限。\n"); }
	else { printf("欢迎回来，%s！\n", user_token); }
	while (1) {
		printf("\n欢迎使用红星牌扫雷系统：\n\n");
		get_simplified_token();
		if (user_token[0] == '\0') { printf("1. 登录\n2. 注册\n3. 随机棋盘游玩\n4. 读取棋盘游玩\n5. 自定义棋盘\n6. 退出游戏\n"); }
		else { printf("1. 取消登录\n2. 注册\n3. 随机棋盘游玩\n4. 读取棋盘游玩\n5. 自定义棋盘\n6. 退出游戏\n"); }
		printf("输入标号以选择行动：\n");
		if (scanf("%d", &order) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		switch (order)
		{
		case 1: 
		{
			if (user_token[0] == '\0') {
				login_user();
				write_token();
			}
			else {
				log_off();
				strcpy(user_token, "");
			}
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
		case 5:
			make_one_chessboard();
			break;
		case 6:
			return 0;
		default:
			printf("请输入有效的数字！\n");
			break;
		}
	}
}