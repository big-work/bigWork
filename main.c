#include "chessboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#pragma warning(disable : 4996)

// ���޼��������������ɨ��
int main()
{
	// ������ʼ����
	CBResult myCB, temp;
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

	// ������̲��ͷ��ڴ�
	ResultPrint(myCB);
	free(myCB.CBList);
	free(temp.CBList);
	system("pause");
	return 0;
}