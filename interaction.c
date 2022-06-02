#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <conio.h>
#include "chessboard.h"

#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

CBResult make_one_CBResult()
{
    CBResult stu = create_chessboard_service();

    int x = 0, y = 0, mineNum = stu.mineNum;

    stu = create_chessboard(stu.line, stu.column, 0);

    system("cls");
    printf("����������̣�\n");

    do
    {
        result_print(stu);
        printf("�㻹�������� %-4d ����(����س�������)��\n", mineNum);

        int i;
        while ((i = getch()) != 0)
        {
            // up
            if (i == 72)
            {
                stu.CBList[x][y].cursorOrNot = 0;
                x--;
                if (x < 0) x = 0;
                stu.CBList[x][y].cursorOrNot = 1;
                stu.position_x = x;
                stu.position_y = y;
                break;
            }
            // down
            if (i == 80)
            {
                stu.CBList[x][y].cursorOrNot = 0;
                x++;
                if (x == stu.line) x--;
                stu.CBList[x][y].cursorOrNot = 1;
                stu.position_x = x;
                stu.position_y = y;
                break;
            }
            // left
            if (i == 75)
            {
                stu.CBList[x][y].cursorOrNot = 0;
                y--;
                if (y < 0) y = 0;
                stu.CBList[x][y].cursorOrNot = 1;
                stu.position_x = x;
                stu.position_y = y;
                break;
            }
            // right
            if (i == 77)
            {
                stu.CBList[x][y].cursorOrNot = 0;
                y++;
                if (y == stu.column) y--;
                stu.CBList[x][y].cursorOrNot = 1;
                stu.position_x = x;
                stu.position_y = y;
                break;
            }
            // enter
            if (i == '\r')
            {
                if (stu.CBList[x][y].flag == 0)
                {
                    stu.CBList[x][y].flag++;
                    mineNum--;
                }
                else
                {
                    stu.CBList[x][y].flag--;
                    mineNum++;
                }
                break;
            }
        }

    } while (mineNum != 0);
    system("cls");

    stu.position_x = -1;
    stu.position_y = -1;

    printf("����������̣�\n");
    result_print(stu);
    make_chessboard(stu);

    system("pause");
    Sleep(CLOCKS_PER_SEC);
    return stu;
}

void make_rand_game()
{
    CBResult myCB;
    extern behavior* bef;
    behavior* head = (behavior*)malloc(sizeof(behavior));
    if (head == NULL)
    {
        printf("fail to malloc()!\n");
        return;
    }
    bef = head;
    head->x = 0;
    head->y = 0;
    head->drawOrMark = 0;
    head->bef = NULL;

    myCB = scan_chessboard();
    CBResult temp = CB_copy(myCB);
    MessageBoxA(NULL, "���`���_ʼ!", "�ߺ�", MB_OK);
    clock_t start = clock();
    system("cls");
    printf("����������̣�\n");

    // ��Ϸ����
    do
    {
        chessboard_print(temp);
        temp = get_order(temp);
    } while (temp.CBList != NULL);

    // �ж�ʤ����ʧ������
    int myCB_score = win(start, head, temp);

    // �������
    system("cls");
    myCB.position_x = -1;
    myCB.position_y = -1;
    result_print(myCB);

    // ����
    replay(myCB, head);

    int order;

    // ��������
    CBstring CBStr;
    printf("����Ҫ����������(1/0)");
    if (scanf("%d", &order) != 0, order == 1)
    {
        CBStr = ChessTrans_ResToStr(myCB);
        saveCB(CBStr);
        printf("�Ƿ񽫸������ϴ�����������(1/0)");
        if (scanf("%d", &order) != 0, order == 1)
        {
            upload_mysql(CBStr, myCB_score, myCB.mineNum);
        }
        free(CBStr.chessboard);
        CBStr.chessboard = NULL;
    }

    for (int i = 0; i < myCB.line; i++)
    {
        free(myCB.CBList[i]);
        myCB.CBList[i] = NULL;
    }

    free(myCB.CBList);
    myCB.CBList = NULL;
    return;
}


void make_appointed_game()
{
    int gm_order;
    extern behavior* bef;

    while (1)
    {
        system("cls");
        printf("�����룺\n\n1. �ӱ���ѡ�����̲�����\n\n2. �ӻ������������̲�����\n\n3. ����\n");
        if (scanf("%d", &gm_order) == 0)
        {
            printf("error!\n");
            setbuf(stdin, NULL);
            continue;
        }

        switch (gm_order)
        {
        case 1:
        {
            CBstring CBStr = readCB();

            CBResult myCB = ChessTrans_StrToRes(CBStr);
            if (myCB.CBList == NULL)
            {
                printf("error\n");
                return;
            };

            behavior* head = (behavior*)malloc(sizeof(behavior));
            if (head == NULL)
            {
                printf("fail to malloc()!\n");
                return;
            }
            bef = head;
            head->x = 0;
            head->y = 0;
            head->drawOrMark = 0;
            head->bef = NULL;

            CBResult temp = CB_copy(myCB);
            MessageBoxA(NULL, "���`���_ʼ!", "ɨ��", MB_OK);
            clock_t start = clock();
            system("cls");
            printf("����������̣�\n");

            // ��Ϸ����
            do
            {
                chessboard_print(temp);
                temp = get_order(temp);
            } while (temp.CBList != NULL);

            // �ж�ʤ����ʧ������
            int myCB_score = win(start, head, temp);

            // �������
            system("cls");
            myCB.position_x = -1;
            myCB.position_y = -1;
            result_print(myCB);

            // ����
            replay(myCB, head);

            for (int i = 0; i < myCB.line; i++)
            {
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
            if (myCB.CBList == NULL)
            {
                printf("error\n");
                return;
            }

            behavior* head = (behavior*)malloc(sizeof(behavior));
            if (head == NULL)
            {
                printf("fail to malloc()!\n");
                return;
            }
            bef = head;
            head->x = 0;
            head->y = 0;
            head->drawOrMark = 0;
            head->bef = NULL;

            CBResult temp = CB_copy(myCB);
            MessageBoxA(NULL, "���`���_ʼ!", "ɨ��", MB_OK);
            clock_t start = clock();
            system("cls");
            printf("����������̣�\n");

            // ��Ϸ����
            do
            {
                chessboard_print(temp);
                temp = get_order(temp);
            } while (temp.CBList != NULL);

            // �ж�ʤ����ʧ������
            int myCB_score = win(start, head, temp);

            // �������
            system("cls");
            myCB.position_x = -1;
            myCB.position_y = -1;
            result_print(myCB);

            int order;

            // ����
            replay(myCB, head);

            // ˢ�¼�¼
            update_score(mysql_myCB.ID, myCB_score);

            // ��������
            printf("����Ҫ����������(1/0)");
            if (scanf("%d", &order) != 0, order == 1)
            {
                saveCB(CBStr);
            }

            for (int i = 0; i < myCB.line; i++)
            {
                free(myCB.CBList[i]);
                myCB.CBList[i] = NULL;
            }

            free(myCB.CBList);
            free(mysql_myCB.name);
            free(mysql_myCB.chessboard);
            free(mysql_myCB.bester);
            myCB.CBList = NULL;
            break;
        }
        case 3:
            return;
        default:
            printf("��������Ч�����֣�\n");
            system("pause");
            break;
        }
        break;
    }
};

void make_one_chessboard()
{
    CBResult myCB = make_one_CBResult();
    CBstring CBStr = ChessTrans_ResToStr(myCB);

    saveCB(CBStr);

    int gm_order;
    printf("�Ƿ��ϴ�����������������1���ϴ���\n");
    if (scanf("%d", &gm_order) == 0)
    {
        printf("error!\n");
        setbuf(stdin, NULL);
        return;
    }

    if (gm_order == 1) upload_mysql(CBStr, 0, myCB.mineNum);
    return;
}