#include "chessboard.h"

// ChessboardPrint 打印游戏中的棋盘
void ChessboardPrint(CBResult myCB)
{
	for (int i = 0; i < myCB.line; i++)
	{
<<<<<<< HEAD
		for (int j = 0; j < y; j++)
		{
			if (myCBList[i][j].drawOrNot == 1)
			{
				if (myCBList[i][j].flag == 1)
					{
						printf('*');
					}
				else
					{
						printf("%d", myCBList[i][j].nearbyMineNum);
					}
			
			}
=======
		for (int j = 0; j < myCB.column; j++)
			if (myCB.CBList[i][j].drawOrNot == 1)
				printf("%d ", myCB.CBList[i][j].nearbyMineNum);
>>>>>>> 43716c3e88ee8b9fed5d108f47fad1410f411a50
			else
				if (myCB.CBList[i][j].tagOrNot == 1)
					printf("# ");
				else
					printf("□");
		printf("\n");
	}
}

// ResultPrint 打印棋盘埋雷结果
void ResultPrint(CBResult myCB)
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