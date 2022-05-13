#include "chessboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#pragma warning(disable : 4996)

int main() 
{
	CBResult myCB, temp;
	myCB = scanChessboard();
	temp = myCB;
	do
	{
		printf("This is your chessboard.\n");
		ChessboardPrint(temp);
		temp = getOrder(temp);
	} while (temp.CBList != NULL);
	if (temp.mineNum == 1)
		printf("You win!\n");
	else
		printf("You lost!\n");
	ResultPrint(myCB);
	free(myCB.CBList);
	free(temp.CBList);
	system("pause");
	return 0;
}