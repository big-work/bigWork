#pragma once
struct Chessboard
{
    int  flag;
    int  nearbyMineNum;
    int  tagOrNot;
};

struct Chessboard** createChessboard(int x, int y, int MineNum);