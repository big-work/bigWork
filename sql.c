#include <winsock.h>
#include <mysql.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include "chessboard.h"
#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#pragma warning(disable : 6054)

const char* HOST = "124.70.51.253";
// username: root
// password: Luye!!@@JWH888456

// ����mysql���ݿ�
MYSQL open_db()
{
    MYSQL mysql;

    mysql_init(&mysql);
    if (!(mysql_real_connect(&mysql, HOST, "root", "Luye!!@@JWH888456", "bigWork", 3306, NULL, 0)))
    {
        // printf("mysql����ʧ��:%s\n", mysql_error(&mysql));

        mysql_close(&mysql);
        mysql_library_end();
        return mysql;
    }

    mysql_library_init(0, NULL, NULL);
    mysql_set_character_set(&mysql, "utf8");

    return mysql;
}

// reister_user �û�ע��
void register_user()
{
    MYSQL mysql = open_db();

    if (mysql.db == NULL)
    {
        printf("�������ӹ��ϣ��޷�ע�ᣡ\n");
        system("pause");
        return;
    }
    
    MYSQL_RES* res;
    if (&mysql == NULL) return;

    char username[100];
    char password[100];
    char temp[100];
    char sqlStr[1000] = "";

    while (1)
    {
        system("cls");
        printf("2. ע��\n");
        printf("�����û���(����0���˳�ע��):\n");
        scanf("%s", username);
        setbuf(stdin, NULL);

        if (strlen(username) > 17)
        {
            printf("����û���̫���ˣ�\n");
            system("pause");
            continue;
        }
        else if (strcmp(username, "0") == 0)
        {
            printf("�ɹ�ȡ��ע��\n");
            system("pause");
            mysql_close(&mysql);
            mysql_library_end();
            return;
        }
        else if (strlen(username) < 4)
        {
            printf("����û���̫���ˣ�\n");
            system("pause");
            continue;
        }

        sprintf(sqlStr, "select username from User where username = '%s'", username);
        mysql_query(&mysql, sqlStr);
        res = mysql_store_result(&mysql);
        long long lengths = mysql_num_rows(res);
        mysql_free_result(res);

        if (lengths)
        {
            printf("���û����ѱ�ע�ᣡ\n");
            system("pause");
            continue;
        }

        int i;
        printf("��������(����0���˳�ע��):\n");

        for (i = 0; i < 16; i++)
        {
            password[i] = getch();

            if (password[i] == '\b' && i > 0)
            {
                password[i - 1] = '\0';
                i -= 2;
            }
            else if (password[i] == '\b' && i == 0) i = -1;
            else if (password[i] == '\r') break;
        }
        password[i] = '\0';
        setbuf(stdin, NULL);
        if (strlen(password) > 17)
        {
            printf("�������̫���ˣ�\n");
            system("pause");
            continue;
        }
        else if (strcmp(password, "0") == 0)
        {
            printf("�ɹ�ȡ��ע��.\n");
            system("pause");
            mysql_close(&mysql);
            mysql_library_end();
            return;
        }
        else if (strlen(password) < 8)
        {
            printf("�������̫���ˣ�\n");
            system("pause");
            continue;
        }

        printf("���ٴ���������:\n");
        for (i = 0; i < 16; i++)
        {
            temp[i] = getch();

            if (temp[i] == '\b' && i > 0)
            {
                temp[i - 1] = '\0';
                i -= 2;
            }
            else if (temp[i] == '\b' && i == 0) i = -1;
            else if (temp[i] == '\r') break;
        }

        temp[i] = '\0';
        setbuf(stdin, NULL);
        if (strcmp(temp, password) != 0)
        {
            printf("��������������벻һ����\n");
            system("pause");
            continue;
        }
        break;
    }

    sprintf(sqlStr, "insert into User (username, password) values ('%s','%s')", username, password);
    if (mysql_query(&mysql, sqlStr) == 0)
    {
        printf("ע��ɹ���\n");
        system("pause");
    }
    else
    {
        printf("mysql����:%s\n", mysql_error(&mysql));
        system("pause");
    }

    mysql_close(&mysql);
    mysql_library_end();

    return;
}

// login_user �û���¼
void login_user()
{
    MYSQL mysql = open_db();

    if (mysql.db == NULL)
    {
        printf("�������ӹ��ϣ��޷���¼��\n");
        system("pause");
        return;
    }

    MYSQL_RES* res;
    MYSQL_ROW row;

    extern char user_token[100];
    char username[100];
    char password[100] = "";
    char temp[100];
    char sqlStr[1000] = "";

    while (1)
    {
        system("cls");
        printf("1. ��¼\n");
        printf("�����û���:(����0���˳���¼):\n");
        scanf("%s", username);

        if (strlen(username) > 17)
        {
            printf("����û���̫���ˣ�\n");
            system("pause");
            continue;
        }
        else if (strcmp(username, "0") == 0)
        {
            printf("�ɹ�ȡ����¼.\n");
            system("pause");
            break;
        }

        sprintf(sqlStr, "select username, password, loginOrNot, logintime from User where username = '%s'", username);
        mysql_query(&mysql, sqlStr);
        res = mysql_store_result(&mysql);
        long long lengths = mysql_num_rows(res);
        mysql_free_result(res);

        if (lengths == 0)
        {
            printf("���û���δ��ע�ᣡ\n");
            system("pause");
            continue;
        }
        else
        {
            row = mysql_fetch_row(res);
            time_t now = time(NULL);

            if (atoi(row[2]) == 1 && ((double)now - (double)atoi(row[3])) <= 3600)
            {
                printf("���˺��Ѿ��ڱ𴦵�¼��\n");
                system("pause");
                break;
            }
            strcpy(password, row[1]);
        }

        int i;
        printf("��������(���16λ):(����0���˳���¼):\n");
        for (i = 0; i < 16; i++)
        {
            temp[i] = getch();

            if (temp[i] == '\b' && i > 0)
            {
                temp[i - 1] = '\0';
                i -= 2;
            }
            else if (temp[i] == '\b' && i == 0) i = -1;
            else if (temp[i] == '\r') break;
        }
        temp[i] = '\0';

        setbuf(stdin, NULL);
        if (strcmp(temp, "0") == 0)
        {
            printf("�ɹ�ȡ����¼.\n");
            system("pause");
            break;
        }

        if (strcmp(temp, password) != 0)
        {
            printf("�������˴�������룡\n");
            continue;
        }

        strcpy(user_token, username);
        time_t now = time(NULL);
        sprintf(sqlStr, "update User set loginOrNot = 1, logintime = %.0f where username = '%s'", (double)now, username);
        if (mysql_query(&mysql, sqlStr))
        {
            printf("error\n");
            return;
        }

        printf("��¼�ɹ���\n");

        break;
    }

    write_token();

    mysql_close(&mysql);
    mysql_library_end();
    return;
}

// read_from_mysql ��mysql���ݿ��ȡ����
CBFromMysql read_from_mysql()
{
    CBFromMysql mysql_myCB;
    extern char user_token[100];
    if (strcmp(user_token, "") == 0)
    {
        printf("�ù�����Ҫ��¼�������飡\n");
        system("pause");
        return ERRORMS;
    }
    MYSQL mysql = open_db();

    if (mysql.db == NULL)
    {
        printf("�������ӹ��ϣ��޷��������ݿ⣡\n");
        system("pause");
        return ERRORMS;
    }

    MYSQL_RES* res;
    MYSQL_ROW row;
    char* sqlStr = (char*)malloc(sizeof(char) * 20501);

    if (sqlStr == NULL)
    {
        printf("fail to malloc()!\n");
        return ERRORMS;
    }

    char* myCB_row[3];

    sqlStr[0] = '\0';

    for (int i = 0; i < 3; i++)
    {
        myCB_row[i] = (char*)malloc(sizeof(char) * 20001);
        if (myCB_row[i] == NULL)
        {
            printf("fail to malloc()!\n");
            return ERRORMS;
        }
        myCB_row[i][0] = '\0';
    }
    strcpy(sqlStr, "select * from minesweeper");
    mysql_query(&mysql, sqlStr);
    res = mysql_store_result(&mysql);

    long long pageNum = mysql_num_rows(res) / 10 + 1;
    long long pageNow = 1;
    long long temp = 0;
    char order[3];

    while (1)
    {
        printf("| %-10s | %-20s | %-10s | %-10s | %-10s | %-10s | %-20s |\n", "ID", "������", "����", "����", "����", "��߷�", "��¼������");
        while ((row = mysql_fetch_row(res)) != NULL)
        {
            printf("| %-10s | %-20s | %-10s | %-10s | %-10s | %-10s | %-20s |\n", row[0], row[1], row[2], row[3], row[5], row[6], row[7]);
            temp++;
            if (temp % 9 == 0) break;
        }
        printf("�������ڵ�%lldҳ��\tһ����%lldҳ. ����Ҫ��ҳ��(Y/N):\n", pageNow, pageNum);

        scanf("%s", &order);
        setbuf(stdin, NULL);

        if (strcmp(order, "Y") == 0 || strcmp(order, "y") == 0)
        {
            while (1)
            {
                printf("����ҳ��:\n");
                if (scanf("%lld", &pageNow) == 0)
                {
                    printf("error!\n");
                    setbuf(stdin, NULL);
                    continue;
                };
                if (pageNow > 0 && pageNow <= pageNum)
                {
                    mysql_data_seek(res, (pageNow - 1) * 10);
                    temp = 0;
                    // system("cls");
                }
                else
                {
                    printf("�������ҳ�벻�Ϸ���\n");
                    system("pause");
                    continue;
                }
                break;
            }
        }
        else
            break;
    }

    mysql_free_result(res);
    int ID;
    while (1)
    {
        printf("��������򿪵����̵�ID:\n");
        if (scanf("%d", &ID) == 0)
        {
            printf("error!\n");
            setbuf(stdin, NULL);
            continue;
        }
        sprintf(sqlStr, "select * from minesweeper where ID = %d", ID);
        mysql_query(&mysql, sqlStr);
        res = mysql_store_result(&mysql);
        long long length = mysql_num_rows(res);

        if (length == 0)
        {
            printf("���޸�ID��\n");
            mysql_free_result(res);
            continue;
        }

        row = mysql_fetch_row(res);
        strcpy(myCB_row[0], row[1]);
        strcpy(myCB_row[1], row[4]);
        strcpy(myCB_row[2], row[7]);
        mysql_myCB.ID = atoi(row[0]);
        mysql_myCB.name = myCB_row[0];
        mysql_myCB.lines = atoi(row[2]);
        mysql_myCB.columns = atoi(row[3]);
        mysql_myCB.chessboard = myCB_row[1];
        mysql_myCB.mines = atoi(row[5]);
        mysql_myCB.bestScore = atoi(row[6]);
        mysql_myCB.bester = myCB_row[2];
        break;
    }
    mysql_free_result(res);

    mysql_close(&mysql);
    mysql_library_end();
    return mysql_myCB;
}

// upload_mysql �ϴ����̵�mysql���ݿ�
void upload_mysql(CBstring CBStr, int score, int mineNum)
{
    extern char user_token[100];

    if (strcmp(user_token, "") == 0)
    {
        printf("�ù�����Ҫ��¼�������飡\n");
        system("pause");
        return;
    }

    int line = CBStr.line;
    int column = CBStr.column;
    char* chessboard = (char*)malloc(sizeof(char) * 20001);

    if (chessboard == NULL)
    {
        printf("fail to malloc()!\n");
        return;
    }

    chessboard[0] = '\0';
    strcpy(chessboard, CBStr.chessboard);

    MYSQL mysql = open_db();

    if (mysql.db == NULL)
    {
        printf("�������ӹ��ϣ��޷��������ݿ⣡\n");
        system("pause");
        return;
    }

    MYSQL_RES* res;

    char* sqlStr = (char*)malloc(sizeof(char) * 20501);
    if (sqlStr == NULL)
    {
        printf("fail to malloc()!\n");
        return;
    }
    sqlStr[0] = '\0';

    char name[100];

    while (1)
    {
        system("cls");
        char temp_name;
        printf("����������(����0���˳�):\n");
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

        setbuf(stdin, NULL);
        if (strlen(name) > 17)
        {
            printf("������̫���ˣ�\n");
            system("pause");
            continue;
        }
        else if (strcmp(name, "0") == 0)
        {
            printf("�ɹ�ȡ���ϴ�.\n");
            system("pause");
            break;
        }

        sprintf(sqlStr, "select name from minesweeper where name = '%s'", name);
        mysql_query(&mysql, sqlStr);
        res = mysql_store_result(&mysql);
        long long lengths = mysql_num_rows(res);
        mysql_free_result(res);

        if (lengths != 0)
        {
            printf("���������Ѵ��ڣ����������룡\n");
            system("pause");
            continue;
        }
        break;
    }

    sprintf(sqlStr, "insert into minesweeper (name, `lines`, columns, chessboard, mines, best_score, bester) values ('%s',%d,%d,'%s',%d,%d,'%s')",
        name, line, column, chessboard, mineNum, score, user_token);
    if (mysql_query(&mysql, sqlStr) == 0)
    {
        printf("�ɹ��ϴ���\n");
        system("pause");
    }
    else
    {
        printf("mysql����:%s\n", mysql_error(&mysql));
        system("pause");
    }

    mysql_close(&mysql);
    mysql_library_end();
    return;
}

// update_scoer ��mysql���ݿ������߷�
void update_score(int ID, int myCB_score)
{
    extern char user_token[100];
    MYSQL mysql = open_db();

    if (mysql.db == NULL)
    {
        printf("�������ӹ��ϣ��޷��������ݿ⣡\n");
        system("pause");
        return;
    }

    MYSQL_RES* res;
    MYSQL_ROW row;

    char sqlStr[200] = "";

    sprintf(sqlStr, "select best_score from minesweeper where ID =  %d", ID);
    mysql_query(&mysql, sqlStr);
    res = mysql_store_result(&mysql);

    if (mysql_num_rows(res) == 0 || strcmp(user_token, "") == 0)
    {
        printf("error\n");
        return;
    }

    row = mysql_fetch_row(res);
    mysql_free_result(res);

    if (atoi(row[0]) < myCB_score)
    {
        sprintf(sqlStr, "update minesweeper set bester = '%s', best_score = %d where ID = %d", user_token, myCB_score, ID);
        if (mysql_query(&mysql, sqlStr))
        {
            printf("error\n");
            return;
        }
    }

    mysql_close(&mysql);
    mysql_library_end();
    return;
}

// log_off �˳���¼
void log_off()
{
    extern char user_token[100];
    if (user_token[0] == '\0') return;
    MYSQL mysql = open_db();

    if (mysql.db == NULL) 
    { 
        //printf("�������ӹ��ϣ��޷�����¼״̬��\n"); 
        // system("pause");

        strcpy(user_token, "");
        return; 
    }

    char sqlStr[200] = "";

    sprintf(sqlStr, "update User set loginOrNot = 0, logintime = 0 where username = '%s'", user_token);
    mysql_query(&mysql, sqlStr);
    strcpy(user_token, "");
    delete_token();

    mysql_close(&mysql);
    mysql_library_end();
    return;
}

// refresh_login_time ˢ�µ�¼ʱ��
void refresh_login_time()
{
    extern char user_token[100];
    MYSQL mysql = open_db();

    if (mysql.db == NULL)
    {
        //printf("�������ӹ��ϣ��޷�����¼״̬��\n");
        // system("pause");

        strcpy(user_token, "");
        return;
    }

    char sqlStr[1000] = "";

    time_t now = time(NULL);
    sprintf(sqlStr, "update User set loginOrNot = 1, logintime = %.0f where username = '%s'", (double)now, user_token);
    if (mysql_query(&mysql, sqlStr))
    {
        printf("error\n");
        return;
    }

    mysql_close(&mysql);
    mysql_library_end();
    return;
}

// check_token ���token�Ƿ�α��
int check_token(char* username, int time_login) {
    MYSQL mysql = open_db();
    MYSQL_RES* res;
    MYSQL_ROW row;

    if (mysql.db == NULL)
    {
        //printf("�������ӹ��ϣ��޷�����¼״̬��\n");
        // system("pause");

        return 0;
    }

    char sqlStr[100] = "";
    sprintf(sqlStr, "select logintime from User where username = '%s'", username);

    mysql_query(&mysql, sqlStr);

    res = mysql_store_result(&mysql);

    long long length = mysql_num_rows(res);

    if (length != 0)
    {
        row = mysql_fetch_row(res);
        if (abs(atoi(row[0]) - time_login) > 5) return 0;
    }
    else 
        return 0;


    mysql_close(&mysql);
    mysql_library_end();
    return 1;
}