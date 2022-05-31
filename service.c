#include "chessboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mysql.h>
#include <conio.h>
#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

// scanChessboard 输入棋盘交互
CBResult scan_chessboard()
{
	int line, column, mineNum;
	CBResult stu = ERRORCB;

	do
	{
		printf("输入棋盘的行数：\n");
		if (scanf("%d", &line) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		fflush(stdin);

		printf("输入棋盘的列数：\n");
		if (scanf("%d", &column) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		fflush(stdin);

		printf("输入棋盘的总雷数：\n");
		if (scanf("%d", &mineNum) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		fflush(stdin);

		if (line < 5 || column < 5 || line > 80 || column > 80)
		{
			printf("你的棋盘大小不符合规则（行数和列数应该大于等于5并小于等于80）\n");
			setbuf(stdin, NULL);
			continue;
		}
		else if (mineNum > (line * column - 10))
		{
			printf("你的棋盘的埋雷数超过了限制（雷数 <= 行数 * 列数 - 10）\n");
			setbuf(stdin, NULL);
			continue;
		}
		else if (mineNum < (line * column / 10))
		{
			printf("你的棋盘的埋雷数过少（埋雷数 >= 行数 * 列数 / 10）\n");
			setbuf(stdin, NULL);
			continue;
		}

		stu = create_chessboard(line, column, mineNum);
		stu = make_chessboard(stu);
	} while (stu.CBList == NULL);
	return stu;
}

// get_order 翻开/标记交互
CBResult get_order(CBResult myCB)
{
	extern behavior* bef;
	behavior* myBH = (behavior*)malloc(sizeof(behavior));
	if (myBH == NULL)
	{
		printf("fail to malloc()!\n");
		return ERRORCB;
	}
	char i = '\0';
	int x = myCB.position_x, y = myCB.position_y;
	printf("输入0以翻开一个格子，输入1以标记一个未翻开的格子。\n请输入：\n");

	while ((i = getch()) != 0) {
		// up
		if (i == 72) {
			myCB.CBList[x][y].cursorOrNot = 0;
			x--;
			if (x < 0) x = 0;
			myCB.CBList[x][y].cursorOrNot = 1;
			myCB.position_x = x;
			myCB.position_y = y;
			break;
		}
		// down
		if (i == 80) {
			myCB.CBList[x][y].cursorOrNot = 0;
			x++;
			if (x == myCB.line) x--;
			myCB.CBList[x][y].cursorOrNot = 1;
			myCB.position_x = x;
			myCB.position_y = y;
			break;
		}
		// left
		if (i == 75) {
			myCB.CBList[x][y].cursorOrNot = 0;
			y--;
			if (y < 0) y = 0;
			myCB.CBList[x][y].cursorOrNot = 1;
			myCB.position_x = x;
			myCB.position_y = y;
			break;
		}
		// right
		if (i == 77) {
			myCB.CBList[x][y].cursorOrNot = 0;
			y++;
			if (y == myCB.column) y--;
			myCB.CBList[x][y].cursorOrNot = 1;
			myCB.position_x = x;
			myCB.position_y = y;
			break;
		}
		if (i == '0') {
			CBResult temp = draw_one_chess(myCB, x, y);
			if (temp.column != 0) {
				myCB = temp;
				myBH->drawOrMark = 0; myBH->x = x; myBH->y = y; myBH->next = NULL; bef->next = myBH; bef = myBH;
			}
			break;
		}
		if (i == '1') {
			CBResult temp = mark_one_chess(myCB, x, y);
			if (temp.column != 0) {
				myCB = temp;
				myBH->drawOrMark = 1; myBH->x = x; myBH->y = y; myBH->next = NULL; bef->next = myBH; bef = myBH;
			}
			break;
		}

	}
	return myCB;
}

CBResult make_one_CBResult() {
	int line, column, mineNum = 0;
	CBResult stu = ERRORCB;

	do
	{
		printf("输入棋盘的行数：\n");
		if (scanf("%d", &line) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		fflush(stdin);

		printf("输入棋盘的列数：\n");
		if (scanf("%d", &column) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		fflush(stdin);

		printf("输入棋盘的总雷数：\n");
		if (scanf("%d", &mineNum) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		fflush(stdin);

		if (line < 5 || column < 5 || line > 80 || column > 80)
		{
			printf("你的棋盘大小不符合规则（行数和列数应该大于等于5并小于等于80）\n");
			setbuf(stdin, NULL);
			continue;
		}
		else if (mineNum > (line * column - 10))
		{
			printf("你的棋盘的埋雷数超过了限制（雷数 <= 行数 * 列数 - 10）\n");
			setbuf(stdin, NULL);
			continue;
		}
		else if (mineNum < (line * column / 10))
		{
			printf("你的棋盘的埋雷数过少（埋雷数 >= 行数 * 列数 / 10）\n");
			setbuf(stdin, NULL);
			continue;
		}

		stu = create_chessboard(line, column, 0);
		stu.mineNum = mineNum;
	} while (stu.CBList == NULL);
	int x = 0, y = 0;
	system("cls");
	printf("这是你的棋盘：\n");

	do
	{
		result_print(stu);
		printf("你还可以埋下 %-4d 颗雷(输入回车以埋雷)。\n", mineNum);
		int i;
		while ((i = getch()) != 0) {
			// up
			if (i == 72) {
				stu.CBList[x][y].cursorOrNot = 0;
				x--;
				if (x < 0) x = 0;
				stu.CBList[x][y].cursorOrNot = 1;
				stu.position_x = x;
				stu.position_y = y;
				break;
			}
			// down
			if (i == 80) {
				stu.CBList[x][y].cursorOrNot = 0;
				x++;
				if (x == stu.line) x--;
				stu.CBList[x][y].cursorOrNot = 1;
				stu.position_x = x;
				stu.position_y = y;
				break;
			}
			// left
			if (i == 75) {
				stu.CBList[x][y].cursorOrNot = 0;
				y--;
				if (y < 0) y = 0;
				stu.CBList[x][y].cursorOrNot = 1;
				stu.position_x = x;
				stu.position_y = y;
				break;
			}
			// right
			if (i == 77) {
				stu.CBList[x][y].cursorOrNot = 0;
				y++;
				if (y == stu.column) y--;
				stu.CBList[x][y].cursorOrNot = 1;
				stu.position_x = x;
				stu.position_y = y;
				break;
			}

			if (i == '\r') {
				if (stu.CBList[x][y].flag == 0) {
					stu.CBList[x][y].flag++;
					mineNum--;
				}
				else {
					stu.CBList[x][y].flag--;
					mineNum++;
				}
				break;
			}
		}
		
	} while (mineNum != 0);
	system("cls");
	printf("这是你的棋盘：\n");
	result_print(stu);
	make_chessboard(stu);
	return stu;
}

void make_rand_game() {
	CBResult myCB;
	extern behavior* bef;
	behavior* head = (behavior*)malloc(sizeof(behavior));
	if (head == NULL)
	{
		printf("fail to malloc()!\n");
		return;
	}
	bef = head;
	myCB = scan_chessboard();
	CBResult temp = CB_copy(myCB);
	MessageBoxA(NULL, "ゲーム開始!", "掃海", MB_OK);
	clock_t start = clock();
	system("cls");
	printf("这是你的棋盘：\n");

	// 游戏主体
	do
	{
		chessboard_print(temp);
		temp = get_order(temp);
	} while (temp.CBList != NULL);

	// 判定胜利或失败条件
	clock_t end = clock();
	double consuming = ((double)end - (double)start) / CLOCKS_PER_SEC;
	char str[50] = "";
	int myCB_score = score(consuming, head, temp);

	if (temp.mineNum == 1) {
		sprintf(str, "お前の勝ちだ！\n\n%.2f秒かかる\nscore : %d", consuming, myCB_score);
		MessageBoxA(NULL, str, "掃海", MB_OK);
	}
	else
	{
		sprintf(str, "君は失敗した！\n\n%.2f秒かかる\nscore : %d", consuming, myCB_score);
		MessageBoxA(NULL, str, "掃海", MB_OK);
	}

	// 输出棋盘
	system("cls");
	myCB.position_x = -1; myCB.position_y = -1;
	result_print(myCB);

	// 复盘
	int order;
	printf("你需要复盘吗？（输入1以复盘）");
	if (scanf("%d", &order) == 0) order = 0;
	setbuf(stdin, NULL);
	printf("\n");
	if (order == 1)
	{
		temp = CB_copy(myCB);
		behavior* temp_bh = head;
		behavior* temp_bh_1;
		temp.CBList[temp.position_x][temp.position_y].cursorOrNot = 0;
		while (temp_bh->next != NULL)
		{
			system("cls");
			printf("drawOrMark: %d\tx: %d\ty: %d\n", temp_bh->next->drawOrMark, temp_bh->next->x, temp_bh->next->y);
			if (temp_bh->next->drawOrMark == 0)
				temp = draw_one_chess(temp, temp_bh->next->x, temp_bh->next->y);
			else
				temp = mark_one_chess(temp, temp_bh->next->x, temp_bh->next->y);
			if (temp.CBList != NULL) chessboard_print(temp); else { myCB.position_x = -1; myCB.position_y = -1; result_print(myCB); free(temp_bh); temp_bh = NULL; getchar(); break; };
			getchar();
			printf("\n\n");
			temp_bh_1 = temp_bh->next;
			free(temp_bh);
			temp_bh = temp_bh_1;
		}
	}

	// 保存棋盘
	CBstring CBStr;
	printf("你需要保存棋盘吗？(1/0)");
	if (scanf("%d", &order) != 0, order == 1) {
		CBStr = ChessTrans_ResToStr(myCB);
		saveCB(CBStr);
		printf("是否将该棋盘上传到互联网？(1/0)");
		if (scanf("%d", &order) != 0, order == 1) {
			upload_mysql(CBStr, myCB_score, myCB.mineNum);
		}
		free(CBStr.chessboard);
		CBStr.chessboard = NULL;
	};

	for (int i = 0; i < myCB.line; i++) {
		free(myCB.CBList[i]);
		myCB.CBList[i] = NULL;
	}

	free(myCB.CBList);
	myCB.CBList = NULL;
	return;
}


void make_appointed_game() {
	int gm_order;
	extern behavior* bef;
	while (1) {
		printf("1. 从本地选择棋盘并游玩\t2. 从互联网下载棋盘并游玩\t3. 返回\n");
		if (scanf("%d", &gm_order) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		switch (gm_order)
		{
		case 1:
		{
			CBstring CBStr = readCB();
			CBResult myCB = ChessTrans_StrToRes(CBStr);
			if (myCB.CBList == NULL) { printf("error\n"); return; };
			behavior* head = (behavior*)malloc(sizeof(behavior));
			if (head == NULL)
			{
				printf("fail to malloc()!\n");
				return;
			}
			bef = head;
			CBResult temp = CB_copy(myCB);
			MessageBoxA(NULL, "ゲーム開始!", "扫雷", MB_OK);
			clock_t start = clock();
			system("cls");
			printf("这是你的棋盘：\n");

			// 游戏主体
			do
			{
				chessboard_print(temp);
				temp = get_order(temp);
			} while (temp.CBList != NULL);

			// 判定胜利或失败条件
			clock_t end = clock();
			double consuming = ((double)end - (double)start) / CLOCKS_PER_SEC;
			char str[50] = "";
			int myCB_score = score(consuming, head, temp);

			if (temp.mineNum == 1) {
				sprintf(str, "お前の勝ちだ！\n\n%.2f秒かかる\nscore : %d", consuming, myCB_score);
				MessageBoxA(NULL, str, "掃海", MB_OK);
			}
			else
			{
				sprintf(str, "君は失敗した！\n\n%.2f秒かかる\nscore : %d", consuming, myCB_score);
				MessageBoxA(NULL, str, "掃海", MB_OK);
			}

			// 输出棋盘
			system("cls");
			myCB.position_x = -1; myCB.position_y = -1;
			result_print(myCB);

			// 复盘
			int order;
			printf("你需要复盘吗？（输入1以复盘）");
			if (scanf("%d", &order) == 0) order = 0;
			setbuf(stdin, NULL);
			printf("\n");
			if (order == 1)
			{
				temp = CB_copy(myCB);
				behavior* temp_bh = head;
				behavior* temp_bh_1;
				temp.CBList[temp.position_x][temp.position_y].cursorOrNot = 0;
				while (temp_bh->next != NULL)
				{
					system("cls");
					printf("drawOrMark: %d\tx: %d\ty: %d\n", temp_bh->next->drawOrMark, temp_bh->next->x, temp_bh->next->y);
					if (temp_bh->next->drawOrMark == 0)
						temp = draw_one_chess(temp, temp_bh->next->x, temp_bh->next->y);
					else
						temp = mark_one_chess(temp, temp_bh->next->x, temp_bh->next->y);
					if (temp.CBList != NULL) chessboard_print(temp); else { myCB.position_x = -1; myCB.position_y = -1; result_print(myCB); free(temp_bh); temp_bh = NULL; getchar(); break; };
					getchar();
					printf("\n\n");
					temp_bh_1 = temp_bh->next;
					free(temp_bh);
					temp_bh = temp_bh_1;
				}
			}

			for (int i = 0; i < myCB.line; i++) {
				free(myCB.CBList[i]);
				myCB.CBList[i] = NULL;
			}

			free(myCB.CBList);
			myCB.CBList = NULL;
			break;
		}
		case 2:
		{
			CBFromMysql mysql_myCB = read_from_mysql();
			if (mysql_myCB.ID == 0) continue;
			CBstring CBStr = { mysql_myCB.lines, mysql_myCB.columns, mysql_myCB.chessboard };
			CBResult myCB = ChessTrans_StrToRes(CBStr);
			if (myCB.CBList == NULL) { printf("error\n"); return; };
			behavior* head = (behavior*)malloc(sizeof(behavior));
			if (head == NULL)
			{
				printf("fail to malloc()!\n");
				return;
			}
			bef = head;
			CBResult temp = CB_copy(myCB);
			MessageBoxA(NULL, "ゲーム開始!", "扫雷", MB_OK);
			clock_t start = clock();
			system("cls");
			printf("这是你的棋盘：\n");

			// 游戏主体
			do
			{
				chessboard_print(temp);
				temp = get_order(temp);
			} while (temp.CBList != NULL);

			// 判定胜利或失败条件
			clock_t end = clock();
			double consuming = ((double)end - (double)start) / CLOCKS_PER_SEC;
			char str[50] = "";
			int myCB_score = score(consuming, head, temp);

			if (temp.mineNum == 1) {
				sprintf(str, "お前の勝ちだ！\n\n%.2f秒かかる\nscore : %d", consuming, myCB_score);
				MessageBoxA(NULL, str, "掃海", MB_OK);
			}
			else
			{
				sprintf(str, "君は失敗した！\n\n%.2f秒かかる\nscore : %d", consuming, myCB_score);
				MessageBoxA(NULL, str, "掃海", MB_OK);
			}

			// 输出棋盘
			system("cls");
			myCB.position_x = -1; myCB.position_y = -1;
			result_print(myCB);

			// 复盘
			int order;
			printf("你需要复盘吗？（输入1以复盘）");
			if (scanf("%d", &order) == 0) order = 0;
			setbuf(stdin, NULL);
			printf("\n");
			if (order == 1)
			{
				temp = CB_copy(myCB);
				behavior* temp_bh = head;
				behavior* temp_bh_1;
				temp.CBList[temp.position_x][temp.position_y].cursorOrNot = 0;
				while (temp_bh->next != NULL)
				{
					system("cls");
					printf("drawOrMark: %d\tx: %d\ty: %d\n", temp_bh->next->drawOrMark, temp_bh->next->x, temp_bh->next->y);
					if (temp_bh->next->drawOrMark == 0)
						temp = draw_one_chess(temp, temp_bh->next->x, temp_bh->next->y);
					else
						temp = mark_one_chess(temp, temp_bh->next->x, temp_bh->next->y);
					if (temp.CBList != NULL) chessboard_print(temp); else { myCB.position_x = -1; myCB.position_y = -1; result_print(myCB); free(temp_bh); temp_bh = NULL; getchar(); break; };
					getchar();
					printf("\n\n");
					temp_bh_1 = temp_bh->next;
					free(temp_bh);
					temp_bh = temp_bh_1;
				}
			}

			update_score(mysql_myCB.ID, myCB_score);

			// 保存棋盘
			printf("你需要保存棋盘吗？(1/0)");
			if (scanf("%d", &order) != 0, order == 1) {
				saveCB(CBStr);
			};

			for (int i = 0; i < myCB.line; i++) {
				free(myCB.CBList[i]);
				myCB.CBList[i] = NULL;
			}

			free(myCB.CBList);
			myCB.CBList = NULL;
			break;
		}
		case 3:
			return;
		default:
			printf("请输入有效的数字！\n");
			break;
		}
		break;
	}
};

void make_one_chessboard() {
	CBResult myCB = make_one_CBResult();
	CBstring CBStr = ChessTrans_ResToStr(myCB);
	saveCB(CBStr);
	int gm_order;
	printf("是否上传到互联网：（输入1以上传）\n");
	if (scanf("%d", &gm_order) == 0) { printf("error!\n"); setbuf(stdin, NULL); return; };
	if (gm_order == 1) {
		upload_mysql(CBStr, 0, myCB.mineNum);
	}
	return;
}