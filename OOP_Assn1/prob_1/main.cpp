# -*- coding: utf-8 -*-
#include "prob_1.h"

int h[1000000] = { 0 }; //나무막대 배열

/*Honor Code : 나는 이 프로그래밍 과제를 다른 사람의 부적절한 도움 없이 완수하였습니다.*/

int main()
{
	int n, sum;
	scanf("%d", &n); //나무막대의 총 개수를 입력받는다.
	for (int i = 0; i < n; i++) //나무막대 배열에 나무막대의 길이를 scan 받는다.
		scanf("%d", &h[i]);

	sum = compare(n); //compare 함수를 호출하여 sum값을 return 받는다.
	printf("%d", sum);
	return 0;
}
