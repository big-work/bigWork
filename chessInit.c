#include "chessboard.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

Chessboard** createChessboard(int x, int y, int MineNum)
{
	//int* num = (int*)malloc(sizeof(int) * 8);
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
	return myCBList;
}

Chessboard** markOneChess(Chessboard** myCBList, int cx, int cy, int x, int y) {
	int winFlag = 1;
	if (myCBList[x][y].tagOrNot = 1) {
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