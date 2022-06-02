#include "chessboard.h"

// score ��ȡ�÷�
int score(double consuming, behavior* head, CBResult temp)
{
    /*
    �÷ֹ��򣺳�ʼ������1000��
    ��߷������ϲ��ⶥ��ͨ����һ����4000�����ϣ�������5000������ ��
    ��ͷ�����0�֣�������ָ��֣��۷���0��Ϊֹ���ҿ۷�ЧӦ���ۻ���

    �ӷ֣�1��ÿ�㿪һ����������50�֣�
          2����Ϸͨ�ض����1000�֣�
    �۷֣�
          1����Ϸ�ڼ�ÿ����1���ӿ�1�֡�
    */
    int sum = 1000, draw = 0;
    behavior* temp_bh = head;
    while (temp_bh->next != NULL)
    {
        if (temp_bh->next->drawOrMark == 0) draw++;
        temp_bh = temp_bh->next;
    }
    sum = draw * 50 - (int)consuming;
    if (sum < 0) sum = 0;
    if (temp.mineNum == 1) sum += 1000;
    return sum;
}
