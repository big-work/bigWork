#include "chessboard.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// createChessboard 返回一个埋好雷的二维数组（可以先不计算nearbyMineNum，默认为0）
CBResult createChessboard(int x, int y, int mineNum)
{
	// 初始化棋格
	Chessboard myChess = { 0, 0, 0, 0 };

	if (x == 0 || y == 0) return ERRORCB;

	// 申请内存以存放棋盘数据
	Chessboard** myCBList = (Chessboard**)malloc(sizeof(Chessboard*) * x);
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

	// 利用时间戳作为种子随机埋雷
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

// CBResult 拷贝一份棋盘
CBResult CBCopy(CBResult myCB)
{
	CBResult temp = createChessboard(myCB.line, myCB.column, 0);
	for (int i = 0; i < myCB.line; i++)
		for (int t = 0; t < myCB.column; t++)
			temp.CBList[i][t] = myCB.CBList[i][t];
	temp.line = myCB.line; temp.column = myCB.column;
	return temp;
}

// markOneChess 标记指定坐标的格子为红旗，如果此时所有雷都已被标记且标记的格子内全部含有雷，直接返回NULL，如果指定的格子已被标记，则取消标记。
CBResult markOneChess(CBResult myCB, int x, int y)
{
	int winFlag = 1;
	if (myCB.CBList[x][y].drawOrNot == 1) return myCB;
	if (myCB.CBList[x][y].tagOrNot == 1) {
		myCB.CBList[x][y].tagOrNot = 0;
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

	if (winFlag) {
		for (int i = 0; i < myCB.line; i++) {
			free(myCB.CBList[i]);
			myCB.CBList[i] = NULL;
		}
		free(myCB.CBList);
		myCB.CBList = NULL;
		return WINCB;
	};
	return myCB;
}

// makeChessboard 返回一个埋好雷并算好周边雷数的二维数组(计算每个格子的nearbyMineNum)
CBResult makeChessboard(CBResult myCB)
{
	// 遍历数组以计算
	for (int x = 0; x < myCB.line; x++)
		for (int y = 0; y < myCB.column; y++)
			for (int i = -1; i < 2; i++)
				for (int t = -1; t < 2; t++)
					if (x + i >= 0 && y + t >= 0 && x + i < myCB.line && y + t < myCB.column && (i != 0 || t != 0))
						if (myCB.CBList[x + i][y + t].flag == 1)
							myCB.CBList[x][y].nearbyMineNum++;
	return myCB;
}

// drawOneChess 翻开指定坐标的格子，并自动翻开根据规则同时翻开的格子，如果该格子埋有雷，直接返回NULL，如果指定的格子已被翻开，则返回原棋盘。
CBResult drawOneChess(CBResult myCB, int x, int y)
{
	if (myCB.CBList[x][y].flag)
	{
		for (int i = 0; i < myCB.line; i++) {
			free(myCB.CBList[i]);
			myCB.CBList[i] = NULL;
		}
		free(myCB.CBList);
		myCB.CBList = NULL;
		return LOSTCB;
	};
	if (myCB.CBList[x][y].drawOrNot == 1) return myCB;

	myCB.CBList[x][y].drawOrNot = 1;

	// 使用递归反馈翻开动作
	if (myCB.CBList[x][y].nearbyMineNum == 0)
		for (int i = -1; i < 2; i++)
			for (int t = -1; t < 2; t++)
				if ((i != 0 || t != 0) && x + i < myCB.line && x + i > -1 && y + t < myCB.column && y + t > -1)
					drawOneChess(myCB, x + i, y + t);

	return myCB;
}