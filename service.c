#include "chessboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mysql.h>
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

		if (line < 5 || column < 5)
		{
			printf("你的棋盘太小辣（行数和列数应该大于等于5）\n");
			setbuf(stdin, NULL);
			continue;
		}
		else if (mineNum > (line * column - 10))
		{
			printf("你的棋盘的埋雷数超过了限制（雷数 <= 行数 * 列数 - 10）\n");
			setbuf(stdin, NULL);
			continue;
		}
		else if (mineNum < 5)
		{
			printf("你的棋盘的埋雷数过少（埋雷数 >= 5）\n");
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
	int order, x, y;
	do
	{
		printf("输入0以翻开一个格子，输入1以标记一个未翻开的格子。\n请输入：\n");
		if (scanf("%d", &order) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };

		if (order == 0) {
			printf("输入两个数字代表位置（example: 1 1）:");
			if (scanf("%d%d", &x, &y) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
			if (x < 1 || x > myCB.line || y < 1 || y > myCB.column) { printf("error!\n"); setbuf(stdin, NULL); continue; };
			CBResult temp = draw_one_chess(myCB, x - 1, y - 1);
			if (temp.column != 0) {
				myCB = temp;
				myBH->drawOrMark = 0; myBH->x = x - 1; myBH->y = y - 1; myBH->next = NULL; bef->next = myBH; bef = myBH;
			}
		}
		else if (order == 1) {
			printf("输入两个数字代表位置（example: 1 1）:");
			if (scanf("%d%d", &x, &y) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
			if (x < 1 || x > myCB.line || y < 1 || y > myCB.column) { printf("error!\n"); setbuf(stdin, NULL); continue; };
			CBResult temp = mark_one_chess(myCB, x - 1, y - 1);
			if (temp.column != 0) {
				myCB = temp;
				myBH->drawOrMark = 1; myBH->x = x - 1; myBH->y = y - 1; myBH->next = NULL; bef->next = myBH; bef = myBH;
			}
		}
		else { printf("error!\n"); setbuf(stdin, NULL); continue; }

		break;
	} while (1);
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

		if (line < 5 || column < 5)
		{
			printf("你的棋盘太小辣（行数和列数应该大于等于5）\n");
			setbuf(stdin, NULL);
			continue;
		}
		else if (mineNum > (line * column - 10))
		{
			printf("你的棋盘的埋雷数超过了限制（雷数 <= 行数 * 列数 - 10）\n");
			setbuf(stdin, NULL);
			continue;
		}
		else if (mineNum < 5)
		{
			printf("你的棋盘的埋雷数过少（埋雷数 >= 5）\n");
			setbuf(stdin, NULL);
			continue;
		}

		stu = create_chessboard(line, column, 0);
		stu.mineNum = mineNum;
	} while (stu.CBList == NULL);
	int x, y;
	do
	{
		printf("这是你的棋盘：\n");
		result_print(stu);
		printf("你还可以埋下 %d 颗雷。\n", mineNum);
		printf("输入两个数字代表位置（example: 1 1）：（如果该位置已埋雷，则会收回该格子的雷）");
		if (scanf("%d%d", &x, &y) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		if (x > stu.line || x < 1 || y > stu.column || y < 1) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		if (stu.CBList[x - 1][y - 1].flag == 0) {
			stu.CBList[x - 1][y - 1].flag++;
			mineNum--;
		}
		else {
			stu.CBList[x - 1][y - 1].flag--;
			mineNum++;
		}
	} while (mineNum != 0);
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

	// 游戏主体
	do
	{
		printf("这是你的棋盘：\n");
		chessboard_print(temp);
		temp = get_order(temp);
	} while (temp.CBList != NULL);

	// 判定胜利或失败条件
	clock_t end = clock();
	double consuming = ((double)end - (double)start) / CLOCKS_PER_SEC;
	char str[50] = "";
	
	if (temp.mineNum == 1){
		sprintf(str, "お前の勝ちだ！\n\n%.2f秒かかる\n", consuming);
		MessageBoxA(NULL, str, "掃海", MB_OK);
	}
	else
	{
		sprintf(str, "君は失敗した！\n\n%.2f秒かかる\n", consuming);
		MessageBoxA(NULL, str, "掃海", MB_OK);
	}

	// 输出棋盘
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
		while (temp_bh->next != NULL)
		{
			printf("drawOrMark: %d\tx: %d\ty: %d\n", temp_bh->next->drawOrMark, temp_bh->next->x, temp_bh->next->y);
			if (temp_bh->next->drawOrMark == 0)
				temp = draw_one_chess(temp, temp_bh->next->x, temp_bh->next->y);
			else
				temp = mark_one_chess(temp, temp_bh->next->x, temp_bh->next->y);
			if (temp.CBList != NULL) chessboard_print(temp); else { printf("End.\n"); result_print(myCB); free(temp_bh); temp_bh = NULL; break; };
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
			upload_mysql(CBStr, 0, myCB.mineNum);
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

			// 游戏主体
			do
			{
				printf("这是你的棋盘：\n");
				chessboard_print(temp);
				temp = get_order(temp);
			} while (temp.CBList != NULL);

			// 判定胜利或失败条件
			clock_t end = clock();
			double consuming = ((double)end - (double)start) / CLOCKS_PER_SEC;
			char str[50] = "";

			if (temp.mineNum == 1) {
				sprintf(str, "お前の勝ちだ！\n\n%.2f秒かかる\n", consuming);
				MessageBoxA(NULL, str, "掃海", MB_OK);
			}
			else
			{
				sprintf(str, "君は失敗した！\n\n%.2f秒かかる\n", consuming);
				MessageBoxA(NULL, str, "掃海", MB_OK);
			}

			// 输出棋盘
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
				while (temp_bh->next != NULL)
				{
					printf("drawOrMark: %d\tx: %d\ty: %d\n", temp_bh->next->drawOrMark, temp_bh->next->x, temp_bh->next->y);
					if (temp_bh->next->drawOrMark == 0)
						temp = draw_one_chess(temp, temp_bh->next->x, temp_bh->next->y);
					else
						temp = mark_one_chess(temp, temp_bh->next->x, temp_bh->next->y);
					if (temp.CBList != NULL) chessboard_print(temp); else { printf("End.\n"); result_print(myCB); free(temp_bh); temp_bh = NULL; break; };
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

			// 游戏主体
			do
			{
				printf("这是你的棋盘：\n");
				chessboard_print(temp);
				temp = get_order(temp);
			} while (temp.CBList != NULL);

			// 判定胜利或失败条件
			clock_t end = clock();
			double consuming = ((double)end - (double)start) / CLOCKS_PER_SEC;
			char str[50] = "";

			if (temp.mineNum == 1) {
				sprintf(str, "お前の勝ちだ！\n\n%.2f秒かかる\n", consuming);
				MessageBoxA(NULL, str, "掃海", MB_OK);
			}
			else
			{
				sprintf(str, "君は失敗した！\n\n%.2f秒かかる\n", consuming);
				MessageBoxA(NULL, str, "掃海", MB_OK);
			}

			// 输出棋盘
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
				while (temp_bh->next != NULL)
				{
					printf("drawOrMark: %d\tx: %d\ty: %d\n", temp_bh->next->drawOrMark, temp_bh->next->x, temp_bh->next->y);
					if (temp_bh->next->drawOrMark == 0)
						temp = draw_one_chess(temp, temp_bh->next->x, temp_bh->next->y);
					else
						temp = mark_one_chess(temp, temp_bh->next->x, temp_bh->next->y);
					if (temp.CBList != NULL) chessboard_print(temp); else { printf("End.\n"); result_print(myCB); free(temp_bh); temp_bh = NULL; break; };
					getchar();
					printf("\n\n");
					temp_bh_1 = temp_bh->next;
					free(temp_bh);
					temp_bh = temp_bh_1;
				}
			}

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