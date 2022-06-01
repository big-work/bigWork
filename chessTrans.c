#include "chessboard.h"

// ChessTrans_ResToStr 将棋盘从CBResult格式转化为CBString
CBstring ChessTrans_ResToStr(CBResult myCB)
{
	int a = 0, b = 0, c = 0;
	char* str = (char*)malloc(sizeof(char) * 20001);
	CBstring CBstr = { 0, 0, str };

	for (int i = 0; i < myCB.line; i++)
		for (int j = 0; j < myCB.column; j++)//存一次有两个字符
		{
			a = myCB.CBList[i][j].flag;
			b = myCB.CBList[i][j].nearbyMineNum;
			CBstr.chessboard[(i * myCB.line + j) * 2] = (char)(a + 48);//第一个
			CBstr.chessboard[(i * myCB.line + j) * 2 + 1] = (char)(b + 48);//第二个数（字符）
		}

	CBstr.chessboard[myCB.line * myCB.column * 2] = 0;
	CBstr.line = myCB.line;
	CBstr.column = myCB.column;

	return CBstr;
}

// ChessTrans_StrToRes 将棋盘从CBString格式转化为CBResult
CBResult ChessTrans_StrToRes(CBstring CBStr)
{
	char a, b;
	CBResult myCB = create_chessboard(CBStr.line, CBStr.column, 0);

	for (int i = 0; i < CBStr.line; i++)
		for (int j = 0; j < CBStr.column; j++)//存一次有两个字符
		{
			a = CBStr.chessboard[(i * myCB.line + j) * 2];//第一个
			b = CBStr.chessboard[(i * myCB.line + j) * 2 + 1];//第二个数（字符）
			myCB.CBList[i][j].flag = (int)a - 48;
			myCB.CBList[i][j].nearbyMineNum = (int)b - 48;
			if (myCB.CBList[i][j].flag == 1) myCB.mineNum++;
		}

	return myCB;
}

