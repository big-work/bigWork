#include "chessboard.h"
void ChessboardPrint(Chessboard** myCBList, int x, int y)
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			printf("��");
		}
	 }
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			if (myCBList[x][y].drawOrNot == 1)
			{
				if (myCBList[x][y].tagOrNot == 1)//�Ƿ����
				{
					printf("#");
				}
				else
				{
					if (myCBList[x][y].flag == 1)
					{
						printf("*");
					}
					else
					{
						printf("%d", myCBList[x][y].nearbyMineNum);
					}
				}
			}
		}
	}
}