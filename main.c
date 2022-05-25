#include "chessboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mysql.h>
#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

behavior* pre;
behavior* bef;
char user_token[100] = "";

// ���޼��������������ɨ��
int main()
{
	RegisterUser();
	LoginUser();
	printf("%s\n", user_token);
	// ������ʼ����
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

	CBResult temp = CBCopy(myCB);
	MessageBoxA(NULL, "���`���_ʼ!", "ɨ��", MB_OK);
	clock_t start = clock();

	// ��Ϸ����
	do
	{
		printf("This is your chessboard.\n");
		ChessboardPrint(temp);
		temp = getOrder(temp);
	} while (temp.CBList != NULL);

	// �ж�ʤ����ʧ������
	clock_t end = clock();
	double consuming = ((double)end - (double)start) / CLOCKS_PER_SEC;
	printf("\n%.2f seconds have been spent.\n", consuming);
	if (temp.mineNum == 1)
		printf("You win!\n");
	else
		printf("You lost!\n");

	// �������
	ResultPrint(myCB);

	// ����
	int order;
	printf("Do you want to Re-plate? (Input 1 to accept.)");
	if (scanf("%d", &order) == 0) order = 0;
	setbuf(stdin, NULL);
	printf("\n");
	if (order == 1)
	{
		temp = CBCopy(myCB);
		while (head->next != NULL)
		{
			printf("drawOrMark: %d\tx: %d\ty: %d\n", head->next->drawOrMark, head->next->x, head->next->y);
			if (head->next->drawOrMark == 0)
				temp = drawOneChess(temp, head->next->x, head->next->y);
			else
				temp = markOneChess(temp, head->next->x, head->next->y);
			if (temp.CBList != NULL) ChessboardPrint(temp); else { printf("End.\n"); ResultPrint(myCB); };
			getchar();
			printf("\n\n");
			head = head->next;
		}
	}

	// �ͷ��ڴ�
	for (int i = 0; i < myCB.line; i++) {
		free(myCB.CBList[i]);
		myCB.CBList[i] = NULL;
	}
	free(myCB.CBList);
	myCB.CBList = NULL;

	return 0;
}