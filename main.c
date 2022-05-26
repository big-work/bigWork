#include "chessboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mysql.h>
#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

behavior* pre;
behavior* bef;
extern char user_token[100] = "";

// 毫无技术含量和新意的扫雷
int main()
{
	// 声明初始变量
	CBResult myCB;
	behavior* head = (behavior*)malloc(sizeof(behavior));
	if (head == NULL)
	{
		printf("fail to malloc()!\n");
		return 0;
	}
	bef = head;
	pre = head;
	myCB = scanChessboard();
	//myCB = makeOneCBResult();
	CBResult temp = CBCopy(myCB);
	MessageBoxA(NULL, "ゲーム開始!", "扫雷", MB_OK);
	clock_t start = clock();

	// 游戏主体
	do
	{
		printf("This is your chessboard.\n");
		ChessboardPrint(temp);
		temp = getOrder(temp);
	} while (temp.CBList != NULL);

	// 判定胜利或失败条件
	clock_t end = clock();
	double consuming = ((double)end - (double)start) / CLOCKS_PER_SEC;
	printf("\n%.2f seconds have been spent.\n", consuming);
	if (temp.mineNum == 1)
		printf("You win!\n");
	else
		printf("You lost!\n");

	// 输出棋盘
	ResultPrint(myCB);

	// 复盘
	int order;
	printf("Do you want to Re-plate? (Input 1 to accept.)");
	if (scanf("%d", &order) == 0) order = 0;
	setbuf(stdin, NULL);
	printf("\n");
	if (order == 1)
	{
		temp = CBCopy(myCB);
		behavior* temp_bh = head;
		behavior* temp_bh_1;
		while (temp_bh->next != NULL)
		{
			printf("drawOrMark: %d\tx: %d\ty: %d\n", temp_bh->next->drawOrMark, temp_bh->next->x, temp_bh->next->y);
			if (temp_bh->next->drawOrMark == 0)
				temp = drawOneChess(temp, temp_bh->next->x, temp_bh->next->y);
			else
				temp = markOneChess(temp, temp_bh->next->x, temp_bh->next->y);
			if (temp.CBList != NULL) ChessboardPrint(temp); else { printf("End.\n"); ResultPrint(myCB); free(temp_bh); temp_bh = NULL; break; };
			getchar();
			printf("\n\n");
			temp_bh_1 = temp_bh->next;
			free(temp_bh);
			temp_bh = temp_bh_1;
		}
	}

	// 保存棋盘
	CBstring CBStr;
	printf("Do you want to save your chessboard?(1/0)");
	if (scanf("%d", &order) != 0, order == 1) {
		CBStr = ChessTrans_ResToStr(myCB);
		saveCB(CBStr);
	};

	for (int i = 0; i < myCB.line; i++) {
		free(myCB.CBList[i]);
		myCB.CBList[i] = NULL;
	}

	free(myCB.CBList);
	myCB.CBList = NULL;
	free(CBStr.chessboard);
	CBStr.chessboard = NULL;

	return 0;
}