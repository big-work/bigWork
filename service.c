#include "chessboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mysql.h>
#include <conio.h>

#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

// win Ӯ���˷���
int win(clock_t start, behavior* head, CBResult temp)
{
    clock_t end = clock();
    double consuming = ((double)end - (double)start) / CLOCKS_PER_SEC;
    char str[50] = "";
    int myCB_score = score(consuming, head, temp);

    if (temp.mineNum == 1)
    {
        sprintf(str, "��ǰ�΄٤�����\n\n%.2f�뤫����\nscore : %d", consuming, myCB_score);
        MessageBoxA(NULL, str, "�ߺ�", MB_OK);
    }
    else
    {
        sprintf(str, "����ʧ��������\n\n%.2f�뤫����\nscore : %d", consuming, myCB_score);
        MessageBoxA(NULL, str, "�ߺ�", MB_OK);
    }

    return myCB_score;
}

// replay ���̷���
void replay(CBResult myCB, behavior* head)
{
    int order;

    if (head == NULL || myCB.CBList == NULL)
    {
        printf("error!\n");
        return;
    }

    printf("����Ҫ�����𣿣�����1�Ը��̣�\n");
    if (scanf("%d", &order) == 0) order = 0;
    if (order == 1)
    {
        CBResult temp = CB_copy(myCB);
        behavior* temp_bh = head;

        temp.CBList[temp.position_x][temp.position_y].cursorOrNot = 0;
        char i;
        CBChainTable* headCT = (CBChainTable*)malloc(sizeof(CBChainTable));
        if (headCT == NULL)
        {
            printf("fail to malloc()!\n");
            return;
        }
        CBChainTable* bef_ct = headCT;
        CBChainTable* temp_ct;
        myCB.CBList[0][0].cursorOrNot = 0;
        headCT->myCB = myCB;
        headCT->bef = NULL;

        while (temp_bh->next != NULL)
        {
            // printf("drawOrMark: %d\tx: %d\ty: %d\n", temp_bh->next->drawOrMark, temp_bh->next->x, temp_bh->next->y);
            if (temp_bh->next->drawOrMark == 0)
                temp = draw_one_chess(temp, temp_bh->next->x, temp_bh->next->y);
            else
                temp = mark_one_chess(temp, temp_bh->next->x, temp_bh->next->y);

            temp_ct = (CBChainTable*)malloc(sizeof(CBChainTable));
            if (temp_ct == NULL)
            {
                printf("fail to malloc()!\n");
                return;
            }

            if (temp.CBList != NULL) temp_ct->myCB = CB_copy(temp);
            else temp_ct->myCB = ERRORCB;
            temp_ct->bef = bef_ct;
            temp_ct->next = NULL;

            bef_ct->next = temp_ct;

            bef_ct = temp_ct;
            temp_bh = temp_bh->next;
        }

        temp_bh = head;
        temp_ct = headCT;

        system("cls");
        printf("����س��˳����̣����뷽����Բٿ����̣�\n");
        chessboard_print(temp_ct->myCB);

        while (1)
        {
            i = getch();
            if (i == 77 && temp_bh->next != NULL)
            {
                system("cls");
                printf("drawOrMark: %d\tx: %d\ty: %d\n", temp_bh->next->drawOrMark, temp_bh->next->x + 1, temp_bh->next->y + 1);
                temp_ct = temp_ct->next;
                temp_bh = temp_bh->next;
                if (temp_bh->next == NULL)
                    result_print(myCB);
                else
                    chessboard_print(temp_ct->myCB);
            }
            else if (i == 75 && temp_bh->bef != NULL)
            {
                system("cls");
                temp_bh = temp_bh->bef;
                printf("drawOrMark: %d\tx: %d\ty: %d\n", temp_bh->drawOrMark, temp_bh->x + 1, temp_bh->y + 1);
                temp_ct = temp_ct->bef;
                if (temp_ct != NULL) chessboard_print(temp_ct->myCB);
                else
                {
                    printf("error!\n");
                    return;
                }
            }
            else if (i == '\r')
            {
                system("cls");
                break;
            }
        }

        temp_bh = head;
        temp_ct = headCT->next;
        behavior* temp_bh_1;
        CBChainTable* temp_ct_1;

        while (temp_bh->next != NULL)
        {
            temp_bh_1 = temp_bh->next;
            free(temp_bh);

            temp_bh = temp_bh_1;

        }

        while (temp_ct->next != NULL)
        {
            temp_ct_1 = temp_ct->next;
            free(temp_ct->myCB.CBList);
            free(temp_ct);

            temp_ct = temp_ct_1;
        }

        free(temp_bh);
        free(temp_ct);
    }

    return;
}

// get_order ��ȡ�û�ָ��
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
    printf("����س��Է���һ�����ӣ�����0�Ա��һ��δ�����ĸ��ӡ�\n�����룺\n");

    while ((i = getch()) != 0)
    {
        // up
        if (i == 72)
        {
            myCB.CBList[x][y].cursorOrNot = 0;
            x--;
            if (x < 0) x = 0;
            myCB.CBList[x][y].cursorOrNot = 1;
            myCB.position_x = x;
            myCB.position_y = y;
            break;
        }
        // down
        if (i == 80)
        {
            myCB.CBList[x][y].cursorOrNot = 0;
            x++;
            if (x == myCB.line) x--;
            myCB.CBList[x][y].cursorOrNot = 1;
            myCB.position_x = x;
            myCB.position_y = y;
            break;
        }
        // left
        if (i == 75)
        {
            myCB.CBList[x][y].cursorOrNot = 0;
            y--;
            if (y < 0) y = 0;
            myCB.CBList[x][y].cursorOrNot = 1;
            myCB.position_x = x;
            myCB.position_y = y;
            break;
        }
        // right
        if (i == 77)
        {
            myCB.CBList[x][y].cursorOrNot = 0;
            y++;
            if (y == myCB.column) y--;
            myCB.CBList[x][y].cursorOrNot = 1;
            myCB.position_x = x;
            myCB.position_y = y;
            break;
        }
        if (i == '\r')
        {
            CBResult temp = draw_one_chess(myCB, x, y);
            if (temp.column != 0)
            {
                myCB = temp;
                myBH->drawOrMark = 0;
                myBH->x = x;
                myBH->y = y;
                myBH->next = NULL;
                myBH->bef = bef;
                bef->next = myBH;
                bef = myBH;
            }
            break;
        }
        if (i == '0')
        {
            CBResult temp = mark_one_chess(myCB, x, y);
            if (temp.column != 0)
            {
                myCB = temp;
                myBH->drawOrMark = 1;
                myBH->x = x;
                myBH->y = y;
                myBH->next = NULL;
                myBH->bef = bef;
                bef->next = myBH;
                bef = myBH;
            }
            break;
        }
    }
    return myCB;
}

// create_chessboard_service �������̷���
CBResult create_chessboard_service()
{
    int line, column, mineNum;
    CBResult stu = ERRORCB;

    do
    {
        system("cls");
        printf("�����������̣�\n");
        printf("�������̵�������\n");
        if (scanf("%d", &line) == 0)
        {
            printf("error!\n");
            setbuf(stdin, NULL);
            continue;
        };
        fflush(stdin);

        printf("�������̵�������\n");
        if (scanf("%d", &column) == 0)
        {
            printf("error!\n");
            setbuf(stdin, NULL);
            continue;
        };
        fflush(stdin);

        printf("�������̵���������\n");
        if (scanf("%d", &mineNum) == 0)
        {
            printf("error!\n");
            setbuf(stdin, NULL);
            continue;
        };
        fflush(stdin);

        if (line < 5 || column < 5 || line > 80 || column > 80)
        {
            printf("������̴�С�����Ϲ�������������Ӧ�ô��ڵ���5��С�ڵ���80��\n");
            setbuf(stdin, NULL);
            system("pause");
            continue;
        }
        else if (mineNum > (line * column - 10))
        {
            printf("������̵����������������ƣ����� <= ���� * ���� - 10��\n");
            setbuf(stdin, NULL);
            system("pause");
            continue;
        }
        else if (mineNum < (line * column / 10))
        {
            printf("������̵����������٣������� >= ���� * ���� / 10��\n");
            setbuf(stdin, NULL);
            system("pause");
            continue;
        }
        break;
    } while (1);

    stu.line = line;
    stu.column = column;
    stu.mineNum = mineNum;
    return stu;

}


// scanChessboard �������̽���
CBResult scan_chessboard()
{
    CBResult stu = create_chessboard_service();

    stu = create_chessboard(stu.line, stu.column, stu.mineNum);

    stu = make_chessboard(stu);

    return stu;
}
