#include "chessboard.h"
#include <stdlib.h>
#include <time.h>

struct Chessboard** createChessboard(int x, int y, int MineNum)
{
	struct Chessboard myCB;
	struct Chessboard** myCBList;
	myCB.flag = 0;
	myCB.nearbyMineNum = 0;
	myCB.tagOrNot = 0;
	myCBList = (struct Chessboard**)malloc(sizeof(struct Chessboard*)*x);
	for (int i = 0; i < x; i++)
	{
		myCBList[i] = (struct Chessboard*)malloc(sizeof(struct Chessboard) * y);
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
		if (myCBList[randNumx][randNumy].flag == 1){
			i--;
			continue;
		}
		myCBList[randNumx][randNumy].flag = 1;
	}
	return myCBList;
}