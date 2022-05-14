#include "chessboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#pragma warning(disable : 4996)

behavior* pre;
behavior* bef;

// 毫无技术含量和新意的扫雷
int main()
{
	// 声明初始变量
	CBResult myCB, temp;
	behavior* head = (behavior*)malloc(sizeof(behavior));
	if (head == NULL)
	{
		printf("fail to malloc()!\n");
		return 0;
	}
	bef = head;
	pre = head;
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

	// 暂时测试用
	while (head->next != NULL) {
		printf("%d %d %d\n", head->next->drawOrMark, head->next->x, head->next->y);
		head = head->next;
	}

	// 输出棋盘并释放内存
	ResultPrint(myCB);
	for (int i = 0; i < myCB.line; i++) {
		free(myCB.CBList[i]);
		myCB.CBList[i] = NULL;
	}
	free(myCB.CBList);
	myCB.CBList = NULL;
	system("pause");
	return 0;
}