#include "chessboard.h"

// chessboard_print 打印游戏中的棋盘
void chessboard_print(CBResult myCB)
{
	for (int i = 0; i < myCB.line; i++)
	{
		for (int j = 0; j < myCB.column; j++)
			if (myCB.CBList[i][j].drawOrNot == 1)
				printf("%d ", myCB.CBList[i][j].nearbyMineNum);
			else
				if (myCB.CBList[i][j].tagOrNot == 1)
					printf("# ");
				else
					printf("□");
		printf("\n");
	}
}

// result_print 打印棋盘埋雷结果
void result_print(CBResult myCB)
{
	for (int i = 0; i < myCB.line; i++)
	{
		for (int j = 0; j < myCB.column; j++)
			if (myCB.CBList[i][j].flag == 1)
				printf("* ");
			else
				printf("□");
		printf("\n");
	}
}