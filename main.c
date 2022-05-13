#include "chessboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#pragma warning(disable : 4996)

// 毫无技术含量和新意的扫雷
int main()
{
	// 声明初始变量
	CBResult myCB, temp;
	myCB = scanChessboard();
	temp = myCB;
	printf("\n\nゲーム開始!\n\n\n");

	// 游戏主体
	do
	{
		printf("This is your chessboard.\n");
		ChessboardPrint(temp);
		temp = getOrder(temp);
	} while (temp.CBList != NULL);

	// 判定胜利或失败条件
	if (temp.mineNum == 1)
		printf("You win!\n");
	else
		printf("You lost!\n");

	// 输出棋盘并释放内存
	ResultPrint(myCB);
	free(myCB.CBList);
	free(temp.CBList);
	system("pause");
	return 0;
}