#include "chessboard.h"
#include <stdio.h>
#include <stdlib.h>
main() {
	Chessboard** stu;
	stu = createChessboard(10, 9, 90);
	for (int i = 0; i < 8; i++) {
		for (int t = 0; t < 9; t++) {
			printf("%d\t", stu[i][t].flag);
		}
		printf("\n");
	}
	free(stu);
	stu = NULL;
	return 0;
}