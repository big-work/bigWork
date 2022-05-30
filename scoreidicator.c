#include "chessboard.h"

int score(double consuming, behavior* head, CBResult temp)
{
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
