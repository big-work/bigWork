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
	struct behavior* next;
}behavior;

// �������ڴ洢�����̸�ʽ
typedef struct
{
	int line;
	int column;
	char* chessboard;
}CBstring;

typedef struct
{
	int ID;
	char* name;
	int lines;
	int columns;
	char* chessboard;
	int mines;
	int bestScore;
	char* bester;
}CBFromMysql;

// ���徲̬����
static CBResult WINCB = { NULL, 1, 1, 1 };
static CBResult LOSTCB = { NULL, -1, -1, -1 };
static CBResult ERRORCB = { NULL, 0, 0, 0 };
static CBstring ERRORCS = { 0, 0, NULL };
static CBFromMysql ERRORMS = { 0, NULL, 0, 0, NULL, 0, 0, NULL };

// create_chessboard ����һ������׵Ķ�ά���飨�����Ȳ�����nearbyMineNum��Ĭ��Ϊ0��
CBResult create_chessboard(int x, int y, int MineNum);

// CB_copy ����һ������
CBResult CB_copy(CBResult myCB);

// make_chessboard ����һ������ײ�����ܱ������Ķ�ά����(����ÿ�����ӵ�nearbyMineNum)
CBResult make_chessboard(CBResult myCB);

// draw_one_chess ����ָ������ĸ��ӣ����Զ��������ݹ���ͬʱ�����ĸ��ӣ�����ø��������ף�ֱ�ӷ���NULL�����ָ���ĸ����ѱ��������򷵻�ԭ���̡�
CBResult draw_one_chess(CBResult myCB, int x, int y);

// mark_one_chess ���ָ������ĸ���Ϊ���죬�����ʱ�����׶��ѱ�����ұ�ǵĸ�����ȫ�������ף�ֱ�ӷ���NULL�����ָ���ĸ����ѱ���ǣ���ȡ����ǡ�
CBResult mark_one_chess(CBResult myCB, int x, int y);

// chessboard_print ��ӡ��Ϸ�е�����
void chessboard_print(CBResult myCB);

// result_print ��ӡ�������׽��
void result_print(CBResult myCB);

// scan_chessboard �������̽���
CBResult scan_chessboard();

// get_order ����/��ǽ���
CBResult get_order(CBResult myCB);

// reister_user �û�ע��
void register_user();

// login_user �û���¼
void login_user();

// make_one_CBResult dlyһ������
CBResult make_one_CBResult();

// ChessTrans_StrToRes �����̴�CBString��ʽת��ΪCBResult
CBResult ChessTrans_StrToRes(CBstring CBstr);

// ChessTrans_ResToStf �����̴�CBResult��ʽת��ΪCBString
CBstring ChessTrans_ResToStr(CBResult myCB);

// saveCB �ڱ��ش洢����
void saveCB(CBstring CBStr);

// readCB �ӱ��ض�ȡ����
CBstring readCB();

// read_from_mysql ��mysql���ݿ��ȡ����
CBFromMysql read_from_mysql();

// upload_mysql �ϴ����̵�mysql���ݿ�
void upload_mysql(CBstring CBStr, int score, int mineNum);

// make_rand_game ����������̲���ʼ��Ϸ
void make_rand_game();

// make_appointed_game ��ȡָ�����̲���ʼ��Ϸ
void make_appointed_game();

// make_one_chessboard �Զ����������ϴ���mysql���ݿ�򱾵�
void make_one_chessboard();

int score(double consuming, behavior* head, CBResult temp);

void update_score(int ID, int myCB_score);

void log_off();

void get_simplified_token();

void write_token();

void delete_token();