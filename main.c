#include "chessboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mysql.h>

#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

behavior* bef;
char user_token[100];

int main()
{
    // ����ȫ�ֱ���user_token�����ڼ�¼��¼״̬
    user_token[0] = '\0';
    int order;


    // �������
    HWND hwnd = GetConsoleWindow();
    if (hwnd != NULL) ShowWindow(hwnd, SW_SHOWMAXIMIZED);

    // ���ع��
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);
    CursorInfo.bVisible = 0;
    SetConsoleCursorInfo(handle, &CursorInfo);

    // ��ȡ����token
    printf("���ڶ�ȡ��¼״̬......\n");
    // get_simplified_token();


    while (1)
    {
        get_simplified_token();

        system("cls");
        if (user_token[0] == '\0')
            printf("�㻹û�е�¼�����ֹ������ޡ�\n");
        else
            printf("��ӭ������%s��\n", user_token);

        printf("\n��ӭʹ�ú�����ɨ��ϵͳ��\n\n");



        if (user_token[0] == '\0')
            printf("1. ��¼\n2. ע��\n3. �����������\n4. ��ȡ��������\n5. �Զ�������\n6. �˳���Ϸ\n");
        else
            printf("1. ȡ����¼\n2. ע��\n3. �����������\n4. ��ȡ��������\n5. �Զ�������\n6. �˳���Ϸ\n");

        printf("��������ѡ���ж���\n");

        if (scanf("%d", &order) == 0)
        {
            printf("��������Ч�����֣�\n");
            setbuf(stdin, NULL);
            system("pause");
            continue;
        }

        switch (order)
        {
            // ��¼ or �˳���¼
        case 1:
        {
            if (user_token[0] == '\0')
            {
                login_user();
            }
            else
            {
                log_off();
                strcpy(user_token, "");
            }
            break;
        }
        // ע��
        case 2:
        {
            register_user();
            break;
        }
        // �����������
        case 3:
        {
            make_rand_game();
            break;
        }
        // ��ȡ��������
        case 4:
        {
            make_appointed_game();
            break;
        }
        // �Զ�������
        case 5:
        {
            make_one_chessboard();
            break;
        }
        // �˳���Ϸ
        case 6:
            return 0;
        default:
        {
            printf("��������Ч�����֣�\n");
            system("pause");
            break;
        }
        }
    }
}