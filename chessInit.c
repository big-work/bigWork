#include "chessboard.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

//函数功能为返回一个埋好雷的二维数组（可以先不计算nearbyMineNum，默认为0）
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
		for (int t = 0; t < y; t++) {
			myCBList[i][t] = myCB;
		}
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
	//printf("%d", myCBList);
	return myCBList;
}

Chessboard** markOneChess(Chessboard** myCBList, int cx, int cy, int x, int y) {
	int winFlag = 1;
	if (myCBList[x][y].tagOrNot == 1) {
		printf("%s", "指定的格子已被标记!");
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
	if (winFlag)
		return NULL;
	return myCBList;
}

Chessboard** makeChessboard(Chessboard** myCBList, int cx, int cy) {
	for (int x = 0; x < cx; x++)
	{
		for (int y = 0; y < cy; y++)
		{
			for (int i = -1; i < 2; i++)
			{
				for (int t = -1; t < 2; t++)
				{
					if (x + i >= 0 && y + t >= 0 && x + i <= cx && y + t <= cy && (i != 0 || t != 0)) {
						if (myCBList[x + i][y + t].flag == 1)
							myCBList[x][y].nearbyMineNum++;
					}
				}
			}
		}
	}
	return myCBList;
}