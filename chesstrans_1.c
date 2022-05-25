#include "chessboard.h"

/*CBResult
Chessboard **CBList;
int line;
int column;
int mineNum;*/
typedef struct
{
    int line;
    int column;
    char chessboard[20001];
}Chessboard_1;
CBstring ChessTrans_ResToStr(CBResult myCB)
{
    int a = 0, b = 0, c = 0;
    CBstring CBstr = {0, 0, ""};
    for (int i = 0; i < myCB.line; i++)
    {
        for (int j = 0; j < 2 * myCB.column; j+=2)//存一次有两个字符
        {
            a = myCB.CBList[i][j].flag;
            b = myCB.CBList[i][j].nearbyMineNum;
            CBstr.chessboard[(i * myCB.line + j)] = (char)a;//第一个
            CBstr.chessboard[(i * myCB.line + j + 1)] = (char)b;//第二个数（字符）
        }
    }
    return CBstr;
}

CBResult ChessTrans_StrToRes(CBstring CBstr)
{
    char a , b;
    CBResult myCB_1 = createChessboard(CBstr.line, CBstr.column, 0);
    for (int i = 0; i < CBstr.line; i++)
    {
        for (int j = 0; j < 2 * CBstr.column; j += 2)//存一次有两个字符
        {
            a = CBstr.chessboard[(i * myCB_1.line + j)];//第一个
            b = CBstr.chessboard[(i * myCB_1.line + j + 1)];//第二个数（字符）
            myCB_1.CBList[i][j].flag = (int)a;
            myCB_1.CBList[i][j].nearbyMineNum = (int)b;
        }
    }
    return myCB_1;
}

