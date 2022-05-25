#pragma once
#include <stdlib.h>
#include <stdio.h>
// 定义棋格
typedef struct
{
	int  flag;
	int  nearbyMineNum;
	int  tagOrNot;
	int  drawOrNot;
}Chessboard;

// 定义棋盘
typedef struct
{
	Chessboard** CBList;
	int line;
	int column;
	int mineNum;
}CBResult;

// 定义交互行为
typedef struct behavior
{
	int drawOrMark;
	int x;
	int y;
	struct behavior *next;
}behavior;

// 定义用于存储的棋盘格式
typedef struct
{
	int line;
	int column;
	char* chessboard;
}CBstring;

// 定义静态变量
static CBResult WINCB = { NULL, 1, 1, 1 };
static CBResult LOSTCB = { NULL, -1, -1, -1 };
static CBResult ERRORCB = { NULL, 0, 0, 0 };

// createChessboard 返回一个埋好雷的二维数组（可以先不计算nearbyMineNum，默认为0）
CBResult createChessboard(int x, int y, int MineNum);

// CBResult 拷贝一份棋盘
CBResult CBCopy(CBResult myCB);

// makeChessboard 返回一个埋好雷并算好周边雷数的二维数组(计算每个格子的nearbyMineNum)
CBResult makeChessboard(CBResult myCB);

// drawOneChess 翻开指定坐标的格子，并自动翻开根据规则同时翻开的格子，如果该格子埋有雷，直接返回NULL，如果指定的格子已被翻开，则返回原棋盘。
CBResult drawOneChess(CBResult myCB, int x, int y);

// markOneChess 标记指定坐标的格子为红旗，如果此时所有雷都已被标记且标记的格子内全部含有雷，直接返回NULL，如果指定的格子已被标记，则取消标记。
CBResult markOneChess(CBResult myCB, int x, int y);

// ChessboardPrint 打印游戏中的棋盘
void ChessboardPrint(CBResult myCB);

// ResultPrint 打印棋盘埋雷结果
void ResultPrint(CBResult myCB);

// scanChessboard 输入棋盘交互
CBResult scanChessboard();

// getOrder 翻开/标记交互
CBResult getOrder(CBResult myCB);

// ReisterUser 用户注册
void RegisterUser();

// LoginUser 用户登录
void LoginUser();

// makeOneCBResult dly一份棋盘
CBResult makeOneCBResult();
