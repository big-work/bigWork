#include "chessboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mysql.h>
#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

// scanChessboard �������̽���
CBResult scan_chessboard()
{
	int line, column, mineNum;
	CBResult stu = ERRORCB;

	do
	{
		printf("�������̵�������\n");
		if (scanf("%d", &line) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		fflush(stdin);

		printf("�������̵�������\n");
		if (scanf("%d", &column) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		fflush(stdin);

		printf("�������̵���������\n");
		if (scanf("%d", &mineNum) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		fflush(stdin);

		if (line < 5 || column < 5 || line > 80 || column > 80)
		{
			printf("������̴�С�����Ϲ�������������Ӧ�ô��ڵ���5��С�ڵ���80��\n");
			setbuf(stdin, NULL);
			continue;
		}
		else if (mineNum > (line * column - 10))
		{
			printf("������̵����������������ƣ����� <= ���� * ���� - 10��\n");
			setbuf(stdin, NULL);
			continue;
		}
		else if (mineNum < (line * column / 10))
		{
			printf("������̵����������٣������� >= ���� * ���� / 10��\n");
			setbuf(stdin, NULL);
			continue;
		}

		stu = create_chessboard(line, column, mineNum);
		stu = make_chessboard(stu);
	} while (stu.CBList == NULL);
	return stu;
}

// get_order ����/��ǽ���
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
		printf("����0�Է���һ�����ӣ�����1�Ա��һ��δ�����ĸ��ӡ�\n�����룺\n");
		if (scanf("%d", &order) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };

		if (order == 0) {
			printf("�����������ִ���λ�ã�example: 1 1��:");
			if (scanf("%d%d", &x, &y) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
			if (x < 1 || x > myCB.line || y < 1 || y > myCB.column) { printf("error!\n"); setbuf(stdin, NULL); continue; };
			CBResult temp = draw_one_chess(myCB, x - 1, y - 1);
			if (temp.column != 0) {
				myCB = temp;
				myBH->drawOrMark = 0; myBH->x = x - 1; myBH->y = y - 1; myBH->next = NULL; bef->next = myBH; bef = myBH;
			}
		}
		else if (order == 1) {
			printf("�����������ִ���λ�ã�example: 1 1��:");
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
		printf("�������̵�������\n");
		if (scanf("%d", &line) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		fflush(stdin);

		printf("�������̵�������\n");
		if (scanf("%d", &column) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		fflush(stdin);

		printf("�������̵���������\n");
		if (scanf("%d", &mineNum) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		fflush(stdin);

		if (line < 5 || column < 5 || line > 80 || column > 80)
		{
			printf("������̴�С�����Ϲ�������������Ӧ�ô��ڵ���5��С�ڵ���80��\n");
			setbuf(stdin, NULL);
			continue;
		}
		else if (mineNum > (line * column - 10))
		{
			printf("������̵����������������ƣ����� <= ���� * ���� - 10��\n");
			setbuf(stdin, NULL);
			continue;
		}
		else if (mineNum < (line * column / 10))
		{
			printf("������̵����������٣������� >= ���� * ���� / 10��\n");
			setbuf(stdin, NULL);
			continue;
		}

		stu = create_chessboard(line, column, 0);
		stu.mineNum = mineNum;
	} while (stu.CBList == NULL);
	int x, y;
	do
	{
		printf("����������̣�\n");
		result_print(stu);
		printf("�㻹�������� %d ���ס�\n", mineNum);
		printf("�����������ִ���λ�ã�example: 1 1�����������λ�������ף�����ջظø��ӵ��ף�");
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
	printf("����������̣�\n");
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
	MessageBoxA(NULL, "���`���_ʼ!", "�ߺ�", MB_OK);
	clock_t start = clock();

	// ��Ϸ����
	do
	{
		printf("����������̣�\n");
		chessboard_print(temp);
		temp = get_order(temp);
	} while (temp.CBList != NULL);

	// �ж�ʤ����ʧ������
	clock_t end = clock();
	double consuming = ((double)end - (double)start) / CLOCKS_PER_SEC;
	char str[50] = "";
	int myCB_score = score(consuming, head, temp);
	
	if (temp.mineNum == 1){
		sprintf(str, "��ǰ�΄٤�����\n\n%.2f�뤫����\nscore : %d", consuming, myCB_score);
		MessageBoxA(NULL, str, "�ߺ�", MB_OK);
	}
	else
	{
		sprintf(str, "����ʧ��������\n\n%.2f�뤫����\nscore : %d", consuming, myCB_score);
		MessageBoxA(NULL, str, "�ߺ�", MB_OK);
	}

	// �������
	result_print(myCB);
	
	// ����
	int order;
	printf("����Ҫ�����𣿣�����1�Ը��̣�");
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

	// ��������
	CBstring CBStr;
	printf("����Ҫ����������(1/0)");
	if (scanf("%d", &order) != 0, order == 1) {
		CBStr = ChessTrans_ResToStr(myCB);
		saveCB(CBStr);
		printf("�Ƿ񽫸������ϴ�����������(1/0)");
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
		printf("1. �ӱ���ѡ�����̲�����\t2. �ӻ������������̲�����\t3. ����\n");
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
			MessageBoxA(NULL, "���`���_ʼ!", "ɨ��", MB_OK);
			clock_t start = clock();

			// ��Ϸ����
			do
			{
				printf("����������̣�\n");
				chessboard_print(temp);
				temp = get_order(temp);
			} while (temp.CBList != NULL);

			// �ж�ʤ����ʧ������
			clock_t end = clock();
			double consuming = ((double)end - (double)start) / CLOCKS_PER_SEC;
			char str[50] = "";
			int myCB_score = score(consuming, head, temp);

			if (temp.mineNum == 1) {
				sprintf(str, "��ǰ�΄٤�����\n\n%.2f�뤫����\nscore : %d", consuming, myCB_score);
				MessageBoxA(NULL, str, "�ߺ�", MB_OK);
			}
			else
			{
				sprintf(str, "����ʧ��������\n\n%.2f�뤫����\nscore : %d", consuming, myCB_score);
				MessageBoxA(NULL, str, "�ߺ�", MB_OK);
			}

			// �������
			result_print(myCB);

			// ����
			int order;
			printf("����Ҫ�����𣿣�����1�Ը��̣�");
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
			MessageBoxA(NULL, "���`���_ʼ!", "ɨ��", MB_OK);
			clock_t start = clock();

			// ��Ϸ����
			do
			{
				printf("����������̣�\n");
				chessboard_print(temp);
				temp = get_order(temp);
			} while (temp.CBList != NULL);

			// �ж�ʤ����ʧ������
			clock_t end = clock();
			double consuming = ((double)end - (double)start) / CLOCKS_PER_SEC;
			char str[50] = "";
			int myCB_score = score(consuming, head, temp);

			if (temp.mineNum == 1) {
				sprintf(str, "��ǰ�΄٤�����\n\n%.2f�뤫����\nscore : %d", consuming, myCB_score);
				MessageBoxA(NULL, str, "�ߺ�", MB_OK);
			}
			else
			{
				sprintf(str, "����ʧ��������\n\n%.2f�뤫����\nscore : %d", consuming, myCB_score);
				MessageBoxA(NULL, str, "�ߺ�", MB_OK);
			}

			// �������
			result_print(myCB);

			// ����
			int order;
			printf("����Ҫ�����𣿣�����1�Ը��̣�");
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

			update_score(mysql_myCB.ID, myCB_score);

			// ��������
			printf("����Ҫ����������(1/0)");
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
			printf("��������Ч�����֣�\n");
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
	printf("�Ƿ��ϴ�����������������1���ϴ���\n");
	if (scanf("%d", &gm_order) == 0) { printf("error!\n"); setbuf(stdin, NULL); return; };
	if (gm_order == 1) {
		upload_mysql(CBStr, 0, myCB.mineNum);
	}
	return;
}