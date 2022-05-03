#include "chessboard.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// 函数功能为返回一个埋好雷的二维数组（可以先不计算nearbyMineNum，默认为0）
Chessboard** createChessboard(int x, int y, int MineNum)
{
	//test
	Chessboard myCB;
	Chessboard** myCBList;
	myCB.flag = 0;
	myCB.nearbyMineNum = 0;
	myCB.tagOrNot = 0;
	myCB.drawOrNot = 0;
	//printf("%d,%d", sizeof(struct Chessboard*), sizeof(struct Chessboard));
	if (x == 0 || y == 0) {
		return NULL;
	}
	myCBList = (Chessboard**)malloc(sizeof(Chessboard*) * x);
	if (myCBList == NULL)
	{
		printf("fail to malloc()!\n");
		return NULL;
	}
	for (int i = 0; i < x; i++)
	{
		myCBList[i] = (Chessboard*)malloc(sizeof(Chessboard) * y);
		if (myCBList[i] == NULL)
		{
			printf("fail to malloc()!\n");
			return NULL;
		}
	}
	for (int i = 0; i < x; i++) {
		for (int t = 0; t < y; t++)
			myCBList[i][t] = myCB;
	}
	srand((unsigned)time(NULL));
	int randNumx, randNumy;
	for (int i = 0; i < MineNum; i++)
	{
		randNumx = rand() % x;
		randNumy = rand() % y;
		if (myCBList[randNumx][randNumy].flag == 1) {
			i--;
			continue;
		}
		myCBList[randNumx][randNumy].flag = 1;
	}
	return myCBList;
}

// 函数功能为标记指定坐标的格子为红旗，如果此时所有雷都已被标记且标记的格子内全部含有雷，直接返回NULL，如果指定的格子已被标记，则返回原棋盘并输出错误。
Chessboard** markOneChess(Chessboard** myCBList, int cx, int cy, int x, int y) {
	int winFlag = 1;
	if (myCBList[x][y].tagOrNot == 1) {
		printf("指定的格子已被标记!");
		return myCBList;
	}
	myCBList[x][y].tagOrNot = 1;
	for (int i = 0; i < cx; i++) {
		for (int t = 0; t < cy; t++) {
			Chessboard p = myCBList[i][t];
			if (p.tagOrNot == 1 && p.flag == 0 || p.tagOrNot == 0 && p.flag == 1) {
				winFlag = 0;
				break;
			}
		}
	}
	if (winFlag) return NULL;
	return myCBList;
}

// 函数功能为返回一个埋好雷并算好周边雷数的二维数组(计算每个格子的nearbyMineNum)
Chessboard** makeChessboard(Chessboard** myCBList, int cx, int cy) {
	for (int x = 0; x < cx; x++)
		for (int y = 0; y < cy; y++)
			for (int i = -1; i < 2; i++)
				for (int t = -1; t < 2; t++)
					if (x + i >= 0 && y + t >= 0 && x + i < cx && y + t < cy && (i != 0 || t != 0))
						if (myCBList[x + i][y + t].flag == 1)
							myCBList[x][y].nearbyMineNum++;
	return myCBList;
}

// 函数功能为翻开指定坐标的格子，并自动翻开根据规则同时翻开的格子，如果该格子埋有雷，直接返回NULL，如果指定的格子已被翻开，则返回原棋盘并输出错误。
Chessboard** drawOneChess(Chessboard** myCBList, int cx, int cy, int x, int y) {
	if (myCBList[x][y].flag) return NULL;
	if (myCBList[x][y].drawOrNot == 1) return myCBList;
	myCBList[x][y].drawOrNot = 1;
	if (myCBList[x][y].nearbyMineNum == 0) {
		for (int i = -1; i < 2; i++) {
			int t;
			if (i == 1 || i == -1) {
				t = 0;
				if (x + i >= 0 && y + t >= 0 && x + i < cx && y + t < cy)
					myCBList = drawOneChess(myCBList, cx, cy, x + i, y + t);
				if (myCBList == NULL) {
					printf("bug1:%d %d   ", x + i, y + t);
					break;
				}
			}
			else {
				for (t = -1; t < 2; t += 2)
					if (x + i >= 0 && y + t >= 0 && x + i < cx && y + t < cy)
						myCBList = drawOneChess(myCBList, cx, cy, x + i, y + t);
				if (myCBList == NULL) {
					printf("bug2:%d %d  cy=%d ", x + i, y + t, cy);
					break;
				}
			}
		}
	}
	return myCBList;
}