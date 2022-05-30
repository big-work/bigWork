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
	get_simplified_token();
	if (user_token[0] == '\0') { printf("�㻹û�е�¼�����ֹ������ޡ�\n"); }
	else { printf("��ӭ������%s��\n", user_token); }
	while (1) {
		printf("\n��ӭʹ�ú�����ɨ��ϵͳ��\n\n");
		get_simplified_token();
		if (user_token[0] == '\0') { printf("1. ��¼\n2. ע��\n3. �����������\n4. ��ȡ��������\n5. �Զ�������\n6. �˳���Ϸ\n"); }
		else { printf("1. ȡ����¼\n2. ע��\n3. �����������\n4. ��ȡ��������\n5. �Զ�������\n6. �˳���Ϸ\n"); }
		printf("��������ѡ���ж���\n");
		if (scanf("%d", &order) == 0) { printf("error!\n"); setbuf(stdin, NULL); continue; };
		switch (order)
		{
		case 1: 
		{
			if (user_token[0] == '\0') {
				login_user();
				write_token();
			}
			else {
				log_off();
				strcpy(user_token, "");
			}
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
		case 5:
			make_one_chessboard();
			break;
		case 6:
			return 0;
		default:
			printf("��������Ч�����֣�\n");
			break;
		}
	}
}