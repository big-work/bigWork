#include "chessboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mysql.h>
#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

behavior* bef;
char user_token[100];

// ���޼��������������ɨ��
int main()
{
	user_token[0] = '\0';
	int order;
	printf("��ӭʹ�ú�����ɨ��ϵͳ��\n");
	while (1) {
		printf("1. ��¼\n2. ע��\n3. �����������\n4. ��ȡ��������\n");
		printf("��������ѡ���ж���\n");
		if (scanf("%d", &order) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		switch (order)
		{
		case 1: 
		{
			login_user();
			break; 
		}
		case 2:
		{
			register_user();
			break;
		}
		case 3:
		{
			make_rand_game();
			break;
		}
		case 4:
			make_appointed_game();
			break;
		default:
			printf("��������Ч�����֣�\n");
			break;
		}
	}
}