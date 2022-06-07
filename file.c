#include "chessboard.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <io.h>
#pragma warning (disable : 4996)
#pragma warning (disable : 6031)

// saveCB �ڱ��ش洢����
void saveCB(CBstring CBStr)
{
    // �����ʼ����
    int column = CBStr.column;
    int line = CBStr.line;
    char name[200] = "";
    char temp_name;
    char* str = (char*)malloc(sizeof(char) * 20005);
    if (str == NULL)
    {
        printf("fail to malloc()!\n");
        return;
    }
    str[0] = '\0';

    // ��"%d-%d-%s"�ĸ�ʽ��Ʊ��ص����̸�ʽ
    sprintf(str, "%d-%d-%s", line, column, CBStr.chessboard);
    char file_str[200];

    // �û�����
    do
    {
        printf("��������Ҫ��������̵����֣�\n");
        setbuf(stdin, NULL);
        for (int i = 0; i < 16; i++)
        {
            if (temp_name = getchar(), temp_name == '\n')
            {
                name[i] = '\0';
                setbuf(stdin, NULL);
                break;
            }
            name[i] = temp_name;
        }
        sprintf(file_str, "./output/%s.txt", name);
        if (strlen(name) > 16 || strlen(name) < 3)
        {
            printf("���ֳ��Ȳ��������ƣ�С�ڵ���16���ַ����ȣ����ڴ���3���ַ����ȣ���\n");
            setbuf(stdin, NULL);
            continue;
        }
        else if (access(file_str, 0) != -1)
        {
            printf("�����outputĿ¼�´��������ļ���������������\n");
            setbuf(stdin, NULL);
            continue;
        }
        break;
    } while (1);

    // ʹ��fputs��������
    FILE* file = fopen(file_str, "w");
    fputs(str, file);
    fclose(file);
    printf("�����ѳɹ����棬ǰ��outputĿ¼�鿴��ϸ��\n");
    free(str);
    return;
}

// readCB �ӱ��ض�ȡ����
CBstring readCB()
{
    // �����ʼ����
    char name[200] = "";
    char file_str[200];
    char temp_name;
    CBstring CBStr;

    char* chessboard = (char*)malloc(sizeof(char) * 20001);
    if (chessboard == NULL)
    {
        printf("fail to malloc()!\n");
        return ERRORCS;
    }

    chessboard[0] = '\0';

    // �û�����
    do
    {
        printf("����outputĿ¼�µ�������������0�Է��أ�:\n");
        setbuf(stdin, NULL);

        for (int i = 0; i < 16; i++)
        {
            if (temp_name = getchar(), temp_name == '\n')
            {
                name[i] = '\0';
                setbuf(stdin, NULL);
                break;
            };
            name[i] = temp_name;
        }

        if (strcmp(name, "0") == 0)
        {
            return ERRORCS;
        }
        else if (strlen(name) > 16 || strlen(name) < 3)
        {
            printf("���ֳ��Ȳ��������ƣ�С�ڵ���16���ַ����ȣ����ڴ���3���ַ����ȣ���\n");
            setbuf(stdin, NULL);
            continue;
        }

        sprintf(file_str, "./output/%s.txt", name);

        if (access(file_str, 0) == -1)
        {
            printf("�����outputĿ¼�����ڸ��ļ���\n");
            setbuf(stdin, NULL);
            continue;
        }

        break;
    } while (1);

    // ��"%d-%d-%s"�ĸ�ʽ�ڱ��ض�ȡ����
    int line, column;
    FILE* file = fopen(file_str, "r");

    if (file == NULL)
    {
        printf("error!\n");
        setbuf(stdin, NULL);
        return ERRORCS;
    }

    fscanf(file, "%d-%d-%s", &line, &column, chessboard);
    fclose(file);

    CBStr.line = line;
    CBStr.column = column;
    CBStr.chessboard = chessboard;

    return CBStr;
}

// get_simplified_token ��ȡ����token
void get_simplified_token()
{
    // �����ʼ����
    extern char user_token[100];
    char username[100] = "";
    char simplified_token[100] = "";
    char* file_str = "./simplified_token/token.txt";
    FILE* file = fopen(file_str, "r");
    time_t now = time(NULL);
    int time_login;
    if (file == NULL)
    {
        return;
    }

    // ��ȡԮ��token, ���token�����򲻷���user_token, ���δ������ˢ��token
    fscanf(file, "%d-%s", &time_login, &username);

    int flag = check_token(username, time_login);

    if (((double)now - (double)time_login) > 3600 || flag == 0)
    {
        // strcpy(user_token, username);
        fclose(file);
        strcpy(user_token, "");
        // log_off();
        return;
    }
    
    sprintf(simplified_token, "%.0f-%s", (double)now, username);
    strcpy(user_token, username);
    fclose(file);

    refresh_login_time();

    if (strcmp(user_token, "") != 0)
    {
        file = fopen(file_str, "w");
        fprintf(file, "%s", simplified_token);
        fclose(file);
    }

    return;
}

// write_token ����token
void write_token()
{
    // �����ʼ����
    extern char user_token[100];
    char simplified_token[100] = "";
    char* file_str = "./simplified_token/token.txt";
    FILE* file = fopen(file_str, "w");
    if (file == NULL)
    {
        printf("error\n");
        return;
    }
    time_t now = time(NULL);

    // ��"%.0f-%s"�ĸ�ʽ���token
    sprintf(simplified_token, "%.0f-%s", (double)now, user_token);
    fprintf(file, "%s", simplified_token);
    fclose(file);

    return;
}

// delete_token ɾ��token
void delete_token()
{
    char* file_str = "./simplified_token/token.txt";
    remove(file_str);
    return;
}