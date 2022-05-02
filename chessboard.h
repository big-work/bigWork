#pragma once
typedef struct
{
	int  flag;
	int  nearbyMineNum;
	int  tagOrNot;
	int  drawOrNot;
}Chessboard;

Chessboard** createChessboard(int x, int y, int MineNum);
Chessboard** makeChessboard(Chessboard** myCBList, int cx, int cy);