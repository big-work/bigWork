#include <stdlib.h>
#include <windows.h>
#include "chessboard.h"

// gotoxy 辅助函数，刷新光标位置
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    return;
}

// chessboard_print 打印游戏中的棋盘
void chessboard_print(CBResult myCB)
{
    gotoxy(1, 2);
    for (int i = 0; i < myCB.line; i++)
    {
        for (int j = 0; j < myCB.column; j++)
            if (myCB.CBList[i][j].cursorOrNot == 1)
                printf("△");
            else if (myCB.CBList[i][j].drawOrNot == 1)
                printf("%d ", myCB.CBList[i][j].nearbyMineNum);
            else if (myCB.CBList[i][j].tagOrNot == 1)
                printf("# ");
            else
                printf("□");
        printf("\n");
    }
}

// result_print 打印棋盘埋雷结果
void result_print(CBResult myCB)
{
    gotoxy(1, 2);
    for (int i = 0; i < myCB.line; i++)
    {
        for (int j = 0; j < myCB.column; j++)
            if (i == myCB.position_x && j == myCB.position_y)
                printf("△");
            else if (myCB.CBList[i][j].flag == 1)
                printf("* ");
            else
                printf("□");
        printf("\n");
    }
}