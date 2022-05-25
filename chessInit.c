#include "chessboard.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// createChessboard ����һ������׵Ķ�ά���飨�����Ȳ�����nearbyMineNum��Ĭ��Ϊ0��
CBResult createChessboard(int x, int y, int mineNum)
{
	// ��ʼ�����
	Chessboard myChess = { 0, 0, 0, 0 };

	if (x == 0 || y == 0) return ERRORCB;

	// �����ڴ��Դ����������
	Chessboard** myCBList = (Chessboard**)malloc(sizeof(Chessboard*) * x);
	if (myCBList == NULL)
	{
		printf("fail to malloc()!\n");
		return ERRORCB;
	}
	for (int i = 0; i < x; i++)
	{
		myCBList[i] = (Chessboard*)malloc(sizeof(Chessboard) * y);
		if (myCBList[i] == NULL)
		{
			printf("fail to malloc()!\n");
			return ERRORCB;
		}
	}

	for (int i = 0; i < x; i++)
		for (int t = 0; t < y; t++)
			myCBList[i][t] = myChess;

	// ����ʱ�����Ϊ�����������
	srand((unsigned)time(NULL));
	int randNumx, randNumy;
	for (int i = 0; i < mineNum; i++)
	{
		randNumx = rand() % x;
		randNumy = rand() % y;
		if (myCBList[randNumx][randNumy].flag == 1) {
			i--;
			continue;
		}
		myCBList[randNumx][randNumy].flag = 1;
	}

	CBResult myCB = { myCBList, x, y, mineNum };
	return myCB;
}

// CBResult ����һ������
CBResult CBCopy(CBResult myCB)
{
	CBResult temp = createChessboard(myCB.line, myCB.column, 0);
	for (int i = 0; i < myCB.line; i++)
		for (int t = 0; t < myCB.column; t++)
			temp.CBList[i][t] = myCB.CBList[i][t];
	temp.line = myCB.line; temp.column = myCB.column;
	return temp;
}

// markOneChess ���ָ������ĸ���Ϊ���죬�����ʱ�����׶��ѱ�����ұ�ǵĸ�����ȫ�������ף�ֱ�ӷ���NULL�����ָ���ĸ����ѱ���ǣ���ȡ����ǡ�
CBResult markOneChess(CBResult myCB, int x, int y)
{
	int winFlag = 1;
	if (myCB.CBList[x][y].drawOrNot == 1) return myCB;
	if (myCB.CBList[x][y].tagOrNot == 1) {
		myCB.CBList[x][y].tagOrNot = 0;
		return myCB;
	}

	myCB.CBList[x][y].tagOrNot = 1;
	for (int i = 0; i < myCB.line; i++)
		for (int t = 0; t < myCB.column; t++) {
			Chessboard p = myCB.CBList[i][t];
			if (p.tagOrNot == 1 && p.flag == 0 || p.tagOrNot == 0 && p.flag == 1) {
				winFlag = 0;
				break;
			}
		}

	if (winFlag) {
		for (int i = 0; i < myCB.line; i++) {
			free(myCB.CBList[i]);
			myCB.CBList[i] = NULL;
		}
		free(myCB.CBList);
		myCB.CBList = NULL;
		return WINCB;
	};
	return myCB;
}

// makeChessboard ����һ������ײ�����ܱ������Ķ�ά����(����ÿ�����ӵ�nearbyMineNum)
CBResult makeChessboard(CBResult myCB)
{
	// ���������Լ���
	for (int x = 0; x < myCB.line; x++)
		for (int y = 0; y < myCB.column; y++)
			for (int i = -1; i < 2; i++)
				for (int t = -1; t < 2; t++)
					if (x + i >= 0 && y + t >= 0 && x + i < myCB.line && y + t < myCB.column && (i != 0 || t != 0))
						if (myCB.CBList[x + i][y + t].flag == 1)
							myCB.CBList[x][y].nearbyMineNum++;
	return myCB;
}

// drawOneChess ����ָ������ĸ��ӣ����Զ��������ݹ���ͬʱ�����ĸ��ӣ�����ø��������ף�ֱ�ӷ���NULL�����ָ���ĸ����ѱ��������򷵻�ԭ���̡�
CBResult drawOneChess(CBResult myCB, int x, int y)
{
	if (myCB.CBList[x][y].flag)
	{
		for (int i = 0; i < myCB.line; i++) {
			free(myCB.CBList[i]);
			myCB.CBList[i] = NULL;
		}
		free(myCB.CBList);
		myCB.CBList = NULL;
		return LOSTCB;
	};
	if (myCB.CBList[x][y].drawOrNot == 1) return myCB;

	myCB.CBList[x][y].drawOrNot = 1;

	// ʹ�õݹ鷴����������
	if (myCB.CBList[x][y].nearbyMineNum == 0)
		for (int i = -1; i < 2; i++)
			for (int t = -1; t < 2; t++)
				if ((i != 0 || t != 0) && x + i < myCB.line && x + i > -1 && y + t < myCB.column && y + t > -1)
					drawOneChess(myCB, x + i, y + t);

	return myCB;
}