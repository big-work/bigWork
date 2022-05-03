#include "chessboard.h"
void ChessboardPrint(Chessboard** myCBList, int x, int y)
{
	
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			if (myCBList[i][j].drawOrNot == 1)
			{
				if (myCBList[i][j].flag == 1)
					{
						printf("* ");
					}
				else
					{
						printf("%d ", myCBList[i][j].nearbyMineNum);
					}
			
			}
			else
			{
				if (myCBList[i][j].tagOrNot == 1)//是否插旗
				{
					printf("# ");
				}
				else
				{
					printf("□");
				}
			}
		}
		printf("\n");
	}
}