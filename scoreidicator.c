#include "chessboard.h"

// score 获取得分
int score(double consuming, behavior* head, CBResult temp)
{
    /*
    得分规则：初始分数：1000分
    最高分数：上不封顶（通关者一般在4000分以上，但鲜有5000分以上 ）
    最低分数：0分（不会出现负分，扣分至0分为止，且扣分效应不累积）

    加分：1、每点开一个无雷区加50分；
          2、游戏通关额外加1000分；
    扣分：
          1、游戏期间每消耗1秒钟扣1分。
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
