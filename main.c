#include "chessboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#pragma warning(disable : 4996)

behavior* pre;
behavior* bef;

// ���޼��������������ɨ��
int main()
{
	// ������ʼ����
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

	printf("\n\n���`���_ʼ!\n\n\n");

	// ��Ϸ����
	do
	{
		printf("This is your chessboard.\n");
		ChessboardPrint(temp);
		temp = getOrder(temp);
	} while (temp.CBList != NULL);

	// �ж�ʤ����ʧ������
	if (temp.mineNum == 1)
		printf("You win!\n");
	else
		printf("You lost!\n");

	// ��ʱ������
	while (head->next != NULL) {
		printf("%d %d %d\n", head->next->drawOrMark, head->next->x, head->next->y);
		head = head->next;
	}

	// ������̲��ͷ��ڴ�
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