#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
// 定义棋格
typedef struct
{
	int  flag;
	int  nearbyMineNum;
	int  tagOrNot;
	int  drawOrNot;
	int  cursorOrNot;
}Chessboard;

// 定义棋盘
typedef struct
{
	Chessboard** CBList;
	int           line;
	int           column;
	int           mineNum;
	int           position_x;
	int           position_y;
}CBResult;

// 定义交互行为
typedef struct behavior
{
	int               drawOrMark;
	int               x;
	int               y;
	struct behavior* next;
	struct behavior* bef;
}behavior;

typedef struct CBChainTable
{
	CBResult              myCB;
	struct CBChainTable* next;
	struct CBChainTable* bef;

}CBChainTable;

// 定义用于存储的棋盘格式
typedef struct
{
	int    line;
	int    column;
	char* chessboard;
}CBstring;

typedef struct
{
	int    ID;
	char* name;
	int    lines;
	int    columns;
	char* chessboard;
	int    mines;
	int    bestScore;
	char* bester;
}CBFromMysql;

// 定义静态变量
static CBResult WINCB = { NULL, 1, 1, 1, 0, 0 };
static CBResult LOSTCB = { NULL, -1, -1, -1, 0, 0 };
static CBResult ERRORCB = { NULL, 0, 0, 0, 0, 0 };
static CBstring ERRORCS = { 0, 0, NULL };
static CBFromMysql ERRORMS = { 0, NULL, 0, 0, NULL, 0, 0, NULL };

// create_chessboard 返回一个埋好雷的二维数组（可以先不计算nearbyMineNum，默认为0）
CBResult create_chessboard(int x, int y, int MineNum);

// CB_copy 拷贝一份棋盘
CBResult CB_copy(CBResult myCB);

// make_chessboard 返回一个埋好雷并算好周边雷数的二维数组(计算每个格子的nearbyMineNum)
CBResult make_chessboard(CBResult myCB);

// draw_one_chess 翻开指定坐标的格子，并自动翻开根据规则同时翻开的格子，如果该格子埋有雷，直接返回NULL，如果指定的格子已被翻开，则返回原棋盘。
CBResult draw_one_chess(CBResult myCB, int x, int y);

// mark_one_chess 标记指定坐标的格子为红旗，如果此时所有雷都已被标记且标记的格子内全部含有雷，直接返回NULL，如果指定的格子已被标记，则取消标记。
CBResult mark_one_chess(CBResult myCB, int x, int y);

// chessboard_print 打印游戏中的棋盘
void chessboard_print(CBResult myCB);

// result_print 打印棋盘埋雷结果
void result_print(CBResult myCB);

// scan_chessboard 输入棋盘交互
CBResult scan_chessboard();

// get_order 翻开/标记交互
CBResult get_order(CBResult myCB);

// reister_user 用户注册
void register_user();

// login_user 用户登录
void login_user();

// make_one_CBResult dly一份棋盘
CBResult make_one_CBResult();

// ChessTrans_StrToRes 将棋盘从CBString格式转化为CBResult
CBResult ChessTrans_StrToRes(CBstring CBstr);

// ChessTrans_ResToStf 将棋盘从CBResult格式转化为CBString
CBstring ChessTrans_ResToStr(CBResult myCB);

// saveCB 在本地存储棋盘
void saveCB(CBstring CBStr);

// readCB 从本地读取棋盘
CBstring readCB();

// read_from_mysql 从mysql数据库读取棋盘
CBFromMysql read_from_mysql();

// upload_mysql 上传棋盘到mysql数据库
void upload_mysql(CBstring CBStr, int score, int mineNum);

// make_rand_game 生成随机棋盘并开始游戏
void make_rand_game();

// make_appointed_game 读取指定棋盘并开始游戏
void make_appointed_game();

// make_one_chessboard 自定义棋盘以上传至mysql数据库或本地
void make_one_chessboard();

// score 获取得分
int score(double consuming, behavior* head, CBResult temp);

// update_scoer 在mysql数据库更新最高分
void update_score(int ID, int myCB_score);

// log_off 退出登录
void log_off();

// get_simplified_token 获取简易token
void get_simplified_token();

// write_token 保存token
void write_token();

// delete_token 删除token
void delete_token();

// refresh_login_time 刷新登录时间
void refresh_login_time();

// gotoxy 辅助函数，刷新光标位置
void gotoxy(int x, int y);

// create_chessboard_service 创建棋盘服务
CBResult create_chessboard_service();

// get_order 获取用户指令
CBResult get_order(CBResult myCB);

// replay 复盘服务
void replay(CBResult myCB, behavior* head);

// win 赢麻了服务
int win(clock_t start, behavior* head, CBResult temp);

// check_token 检查token是否伪造
int check_token(char* username, int time_login);