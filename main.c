#include "chessboard.h"
#include <stdio.h>
#include <stdlib.h>
int main() {
	Chessboard **stu, **temp;
	// ����һ��
	stu = createChessboard(10, 9, 10);
	stu = makeChessboard(stu, 10, 9);
	stu[3][4].tagOrNot = 1;
	/*for (int i = 0; i < 10; i++) {
		for (int t = 0; t < 9; t++) {
			printf("%d\t", stu[i][t].flag);
		}
		printf("\n");
	}
	printf("\n");
	for (int i = 0; i < 10; i++) {
		for (int t = 0; t < 9; t++) {
			printf("%d\t", stu[i][t].nearbyMineNum);
		}
		printf("\n");
	}
	printf("\n");*/
	do
	{
		temp = drawOneChess(stu, 10, 9, 2, 5);
	} while (temp == NULL);
	stu = temp;
	/*for (int i = 0; i < 10; i++) {
		for (int t = 0; t < 9; t++) {
			printf("%d\t", stu[i][t].drawOrNot);
		}
		printf("\n");
	}*/


	//  ����stu��Ϊ�Ѿ����ƺõ����̣��ڴ˴�����Chessprint
	ChessboardPrint(stu, 10, 9);
	free(stu);
	stu = NULL;
	return 0;
}