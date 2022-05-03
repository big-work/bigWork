#include "chessboard.h"
#include <stdio.h>
#include <stdlib.h>
main() {
	Chessboard** stu;
	// ²âÊÔÒ»ÏÂ
	stu = createChessboard(10, 9, 70);
	stu = makeChessboard(stu, 9, 10);
	stu[2][3].drawOrNot = 1;
	stu[3][4].tagOrNot = 1;
	ChessboardPrint(stu, 9, 10);
	free(stu);
	stu = NULL;
	return 0;
}