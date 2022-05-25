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
        for (int j = 0; j < 2 * myCB.column; j+=2)//��һ���������ַ�
        {
            a = myCB.CBList[i][j].flag;
            b = myCB.CBList[i][j].nearbyMineNum;
            CBstr.chessboard[(i * myCB.line + j)] = (char)a;//��һ��
            CBstr.chessboard[(i * myCB.line + j + 1)] = (char)b;//�ڶ��������ַ���
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
        for (int j = 0; j < 2 * CBstr.column; j += 2)//��һ���������ַ�
        {
            a = CBstr.chessboard[(i * myCB_1.line + j)];//��һ��
            b = CBstr.chessboard[(i * myCB_1.line + j + 1)];//�ڶ��������ַ���

        }
    }
    return myCB_1;
}
