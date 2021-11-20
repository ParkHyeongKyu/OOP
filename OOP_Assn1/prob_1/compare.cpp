# -*- coding: utf-8 -*-
#include "prob_1.h"

extern int h[1000000]; //main.cpp에서 선언된 global 배열 사용하기 위해 extern 사용

/*나는 이 프로그래밍 과제를 다른 사람의 부적절한 도움 없이 완수하였습니다*/

int compare(int n)
{
	int sum = 0, left = 1, right = 1; //left는 왼쪽에서 보이는 나무막대의 개수이고 right는 오른쪽에서 보이는 나무 막대의 개수이다.
	int Maxleft = h[0], Maxright = h[n - 1]; //왼쪽에서 봤을때와 오른쪽에서 봤을 때 가장 긴 나무막대의 변수를 정의한다.
	for (int i = 1; i < n; i++) //왼쪽에서 나무막대기 하나씩 비교하며 left와 Maxleft의 값을 변화시킨다.
	{
		if (h[i] > Maxleft)
		{
			left++;
			Maxleft = h[i];
		}
	}
	for (int j = 1; j < n; j++) //오른쪽에서 나무막대기 하나씩 비교하며 left와 Maxleft의 값을 변화시킨다.
	{
		if (h[n - 1 - j] > Maxright)
		{
			right++;
			Maxright = h[n - 1 - j];
		}
	}

	sum = left + right;
	return sum;
}
