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
void ChessboardPrint(Chessboard** myCBList, int x, int y);
Chessboard** drawOneChess(Chessboard** myCBList, int cx, int cy, int x, int y);
Chessboard** markOneChess(Chessboard** myCBList, int cx, int cy, int x, int y);