#include "chessboard.h"

void ChessboardPrint(CBResult myCB)
{
	for (int i = 0; i < myCB.line; i++)
	{
		for (int j = 0; j < myCB.column; j++)
			if (myCB.CBList[i][j].drawOrNot == 1)
				printf("%d ", myCB.CBList[i][j].nearbyMineNum);
			else
				if (myCB.CBList[i][j].tagOrNot == 1)//是否插旗
					printf("# ");
				else
					printf("□");
		printf("\n");
	}
}

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