#include "chessboard.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// 函数功能为返回一个埋好雷的二维数组（可以先不计算nearbyMineNum，默认为0）
CBResult createChessboard(int x, int y, int mineNum)
{
	//test
	Chessboard myChess;
	Chessboard** myCBList;
	myChess.flag = 0;
	myChess.nearbyMineNum = 0;
	myChess.tagOrNot = 0;
	myChess.drawOrNot = 0;
	//printf("%d,%d", sizeof(struct Chessboard*), sizeof(struct Chessboard));
	if (x == 0 || y == 0)
		return ERRORCB;
	myCBList = (Chessboard**)malloc(sizeof(Chessboard*) * x);
	if (myCBList == NULL)
	{
		printf("fail to malloc()!\n");
		return ERRORCB;
	}
	for (int i = 0; i < x; i++)
	{
		myCBList[i] = (Chessboard*)malloc(sizeof(Chessboard) * y);
		if (myCBList[i] == NULL)
		{
			printf("fail to malloc()!\n");
			return ERRORCB;
		}
	}
	for (int i = 0; i < x; i++)
		for (int t = 0; t < y; t++)
			myCBList[i][t] = myChess;
	srand((unsigned)time(NULL));
	int randNumx, randNumy;
	for (int i = 0; i < mineNum; i++)
	{
		randNumx = rand() % x;
		randNumy = rand() % y;
		if (myCBList[randNumx][randNumy].flag == 1) {
			i--;
			continue;
		}
		myCBList[randNumx][randNumy].flag = 1;
	}
	CBResult myCB = { myCBList, x, y, mineNum };
	return myCB;
}

// 函数功能为标记指定坐标的格子为红旗，如果此时所有雷都已被标记且标记的格子内全部含有雷，直接返回NULL，如果指定的格子已被标记，则返回原棋盘并输出错误。
CBResult markOneChess(CBResult myCB, int x, int y) 
{
	int winFlag = 1;
	if (myCB.CBList[x][y].tagOrNot == 1) {
		printf("指定的格子已被标记!");
		return myCB;
	}
	myCB.CBList[x][y].tagOrNot = 1;
	for (int i = 0; i < myCB.line; i++)
		for (int t = 0; t < myCB.column; t++) {
			Chessboard p = myCB.CBList[i][t];
			if (p.tagOrNot == 1 && p.flag == 0 || p.tagOrNot == 0 && p.flag == 1) {
				winFlag = 0;
				break;
			}
		}
	if (winFlag) return WINCB;
	return myCB;
}

// 函数功能为返回一个埋好雷并算好周边雷数的二维数组(计算每个格子的nearbyMineNum)
CBResult makeChessboard(CBResult myCB) 
{
	for (int x = 0; x < myCB.line; x++)
		for (int y = 0; y < myCB.column; y++)
			for (int i = -1; i < 2; i++)
				for (int t = -1; t < 2; t++)
					if (x + i >= 0 && y + t >= 0 && x + i < myCB.line && y + t < myCB.column && (i != 0 || t != 0))
						if (myCB.CBList[x + i][y + t].flag == 1)
							myCB.CBList[x][y].nearbyMineNum++;
	return myCB;
}

// 函数功能为翻开指定坐标的格子，并自动翻开根据规则同时翻开的格子，如果该格子埋有雷，直接返回NULL，如果指定的格子已被翻开，则返回原棋盘并输出错误。
CBResult drawOneChess(CBResult myCB, int x, int y) 
{
	int t;
	if (myCB.CBList[x][y].flag) return LOSTCB;
	if (myCB.CBList[x][y].drawOrNot == 1) return myCB;
	myCB.CBList[x][y].drawOrNot = 1;
	if (myCB.CBList[x][y].nearbyMineNum == 0)
		for (int i = -1; i < 2; i++)
			if (i == 1 || i == -1) {
				t = 0;
				if (x + i >= 0 && y + t >= 0 && x + i < myCB.line && y + t < myCB.column)
					myCB = drawOneChess(myCB, x + i, y + t);
			}
			else
				for (t = -1; t < 2; t += 2)
					if (x + i >= 0 && y + t >= 0 && x + i < myCB.line && y + t < myCB.column)
						myCB = drawOneChess(myCB, x + i, y + t);
	return myCB;
}