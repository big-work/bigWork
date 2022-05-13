#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	int  flag;
	int  nearbyMineNum;
	int  tagOrNot;
	int  drawOrNot;
}Chessboard;

typedef struct
{
	Chessboard** CBList;
	int line;
	int column;
	int mineNum;
}CBResult;

static CBResult WINCB = { NULL, 1, 1, 1 };
static CBResult LOSTCB = { NULL, -1, -1, -1 };
static CBResult ERRORCB = { NULL, 0, 0, 0 };

CBResult createChessboard(int x, int y, int MineNum);
CBResult makeChessboard(CBResult myCB);
CBResult drawOneChess(CBResult myCB, int x, int y);
CBResult markOneChess(CBResult myCB, int x, int y);

void ChessboardPrint(CBResult myCB);
void ResultPrint(CBResult myCB);

CBResult scanChessboard();
CBResult getOrder(CBResult myCB);