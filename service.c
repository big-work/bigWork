#include "chessboard.h"
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

// scanChessboard 输入棋盘交互
CBResult scanChessboard()
{
	int line, column, mineNum;
	CBResult stu = ERRORCB;

	do
	{
		printf("Input the line of the chessboard:\n");
		if (scanf("%d", &line) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		fflush(stdin);

		printf("Input the column of the chessboard:\n");
		if (scanf("%d", &column) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		fflush(stdin);

		printf("Input thr num of mines:\n");
		if (scanf("%d", &mineNum) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		fflush(stdin);

		if (line < 5 || column < 5)
		{
			printf("Your chessboard is too small(line > 5 && column > 5)\n");
			setbuf(stdin, NULL);
			continue;
		}
		else if (mineNum > (line * column - 10))
		{
			printf("Your mines are too many(mineNum <= line * column - 10)\n");
			setbuf(stdin, NULL);
			continue;
		}

		stu = createChessboard(line, column, mineNum);
		stu = makeChessboard(stu);
	} while (stu.CBList == NULL);
	return stu;
}

// getOrder 翻开/标记交互
CBResult getOrder(CBResult myCB)
{
	extern behavior* bef;
	behavior* myBH = (behavior*)malloc(sizeof(behavior));
	if (myBH == NULL)
	{
		printf("fail to malloc()!\n");
		return ERRORCB;
	}
	int order, x, y;
	do
	{
		printf("Input 0 to draw a chequer, 1 to mark a mine.\nInput instruction:\n");
		if (scanf("%d", &order) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };

		if (order == 0) {
			printf("Input two numbers to confirm the position(example: 1 1):");
			if (scanf("%d%d", &x, &y) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
			if (x < 1 || x > myCB.line || y < 1 || y > myCB.column) { printf("error!\n"); setbuf(stdin, NULL); continue; };
			myCB = drawOneChess(myCB, x - 1, y - 1);
			myBH->drawOrMark = 0; myBH->x = x - 1; myBH->y = y - 1; myBH->next = NULL; bef->next = myBH; bef = myBH;
		}
		else if (order == 1) {
			printf("Input two numbers to confirm the position(example: 1 1):");
			if (scanf("%d%d", &x, &y) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
			if (x < 1 || x > myCB.line || y < 1 || y > myCB.column) { printf("error!\n"); setbuf(stdin, NULL); continue; };
			myCB = markOneChess(myCB, x - 1, y - 1);
			myBH->drawOrMark = 1; myBH->x = x - 1; myBH->y = y - 1; myBH->next = NULL; bef->next = myBH; bef = myBH;
		}
		else { printf("error!\n"); setbuf(stdin, NULL); continue; }

		break;
	} while (1);
	return myCB;
}