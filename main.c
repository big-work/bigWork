#include "chessboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mysql.h>

#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

behavior* bef;
char user_token[100];

int main()
{
    // 定义全局变量user_token，用于记录登录状态
    user_token[0] = '\0';
    int order;


    // 窗口最大化
    HWND hwnd = GetConsoleWindow();
    if (hwnd != NULL) ShowWindow(hwnd, SW_SHOWMAXIMIZED);

    // 隐藏光标
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);
    CursorInfo.bVisible = 0;
    SetConsoleCursorInfo(handle, &CursorInfo);

    // 读取本地token
    printf("正在读取登录状态......\n");
    // get_simplified_token();


    while (1)
    {
        get_simplified_token();

        system("cls");
        if (user_token[0] == '\0')
            printf("你还没有登录，部分功能受限。\n");
        else
            printf("欢迎回来，%s！\n", user_token);

        printf("\n欢迎使用红星牌扫雷系统：\n\n");



        if (user_token[0] == '\0')
            printf("1. 登录\n2. 注册\n3. 随机棋盘游玩\n4. 读取棋盘游玩\n5. 自定义棋盘\n6. 退出游戏\n");
        else
            printf("1. 取消登录\n2. 注册\n3. 随机棋盘游玩\n4. 读取棋盘游玩\n5. 自定义棋盘\n6. 退出游戏\n");

        printf("输入标号以选择行动：\n");

        if (scanf("%d", &order) == 0)
        {
            printf("请输入有效的数字！\n");
            setbuf(stdin, NULL);
            system("pause");
            continue;
        }

        switch (order)
        {
            // 登录 or 退出登录
        case 1:
        {
            if (user_token[0] == '\0')
            {
                login_user();
            }
            else
            {
                log_off();
                strcpy(user_token, "");
            }
            break;
        }
        // 注册
        case 2:
        {
            register_user();
            break;
        }
        // 随机棋盘游玩
        case 3:
        {
            make_rand_game();
            break;
        }
        // 读取棋盘游玩
        case 4:
        {
            make_appointed_game();
            break;
        }
        // 自定义棋盘
        case 5:
        {
            make_one_chessboard();
            break;
        }
        // 退出游戏
        case 6:
            return 0;
        default:
        {
            printf("请输入有效的数字！\n");
            system("pause");
            break;
        }
        }
    }
}