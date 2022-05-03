#include "chessboard.h"
#include <stdio.h>
#include <stdlib.h>
int main() {
	Chessboard** stu;
	// 测试一下
	stu = createChessboard(10, 9, 10);
	stu = makeChessboard(stu, 10, 9);
	stu[3][4].tagOrNot = 1;
	/*for (int i = 0; i < 10; i++) {
		for (int t = 0; t < 9; t++) {
			printf("%d\t", stu[i][t].flag);
		}
		printf("\n");
	}
	printf("\n");*/
	/*for (int i = 0; i < 10; i++) {
		for (int t = 0; t < 9; t++) {
			printf("%d\t", stu[i][t].nearbyMineNum);
		}
		printf("\n");
	}*/
	/*printf("\n");*/
	do
	{
		stu = drawOneChess(stu, 10, 9, 2, 5);
	} while (stu == NULL);
	/*for (int i = 0; i < 10; i++) {
		for (int t = 0; t < 9; t++) {
			printf("%d\t", stu[i][t].drawOrNot);
		}
		printf("\n");
	}*/


	//  以上stu即为已经绘制好的棋盘，在此处调试Chessprint
	ChessboardPrint(stu, 9, 10);
	free(stu);
	stu = NULL;
	return 0;
}