#pragma once
#include <stdlib.h>
#include <stdio.h>
// �������
typedef struct
{
	int  flag;
	int  nearbyMineNum;
	int  tagOrNot;
	int  drawOrNot;
}Chessboard;

// ��������
typedef struct
{
	Chessboard** CBList;
	int line;
	int column;
	int mineNum;
}CBResult;

// ���彻����Ϊ
typedef struct behavior
{
	int drawOrMark;
	int x;
	int y;
	struct behavior *next;
}behavior;

// �������ڴ洢�����̸�ʽ
typedef struct
{
	int line;
	int column;
	char* chessboard;
}CBstring;

// ���徲̬����
static CBResult WINCB = { NULL, 1, 1, 1 };
static CBResult LOSTCB = { NULL, -1, -1, -1 };
static CBResult ERRORCB = { NULL, 0, 0, 0 };

// createChessboard ����һ������׵Ķ�ά���飨�����Ȳ�����nearbyMineNum��Ĭ��Ϊ0��
CBResult createChessboard(int x, int y, int MineNum);

// CBResult ����һ������
CBResult CBCopy(CBResult myCB);

// makeChessboard ����һ������ײ�����ܱ������Ķ�ά����(����ÿ�����ӵ�nearbyMineNum)
CBResult makeChessboard(CBResult myCB);

// drawOneChess ����ָ������ĸ��ӣ����Զ��������ݹ���ͬʱ�����ĸ��ӣ�����ø��������ף�ֱ�ӷ���NULL�����ָ���ĸ����ѱ��������򷵻�ԭ���̡�
CBResult drawOneChess(CBResult myCB, int x, int y);

// markOneChess ���ָ������ĸ���Ϊ���죬�����ʱ�����׶��ѱ�����ұ�ǵĸ�����ȫ�������ף�ֱ�ӷ���NULL�����ָ���ĸ����ѱ���ǣ���ȡ����ǡ�
CBResult markOneChess(CBResult myCB, int x, int y);

// ChessboardPrint ��ӡ��Ϸ�е�����
void ChessboardPrint(CBResult myCB);

// ResultPrint ��ӡ�������׽��
void ResultPrint(CBResult myCB);

// scanChessboard �������̽���
CBResult scanChessboard();

// getOrder ����/��ǽ���
CBResult getOrder(CBResult myCB);

// ReisterUser �û�ע��
void RegisterUser();

// LoginUser �û���¼
void LoginUser();

// makeOneCBResult dlyһ������
CBResult makeOneCBResult();
