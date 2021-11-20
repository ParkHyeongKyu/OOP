# -*- coding: utf-8 -*-
#include "prob_2.h"

extern int arr[100000]; //main.cpp에서 선언된 global 배열 사용하기 위해 extern 사용
extern int narr[100000];

/*나는 이 프로그래밍 과제를 다른 사람의 부적절한 도움 없이 완수하였습니다*/

int found(int k, int target, int* narr) //binary search를 수행하는 함수이다.
{
	int first = 0, last = k, mid; //narr 배열에서 처음, 중간, 끝의 변수를 각각 정의한다.
	while (first <= last)
	{
		mid = (first + last) / 2; //중간 변수를 처음과 끝의 절반으로 정의한다.
		if (target <= narr[mid]) //target이 narr[mid]보다 작거나 같을 경우 mid를 return한다.
			return mid;
		else //target이 narr[mid]보다 클 경우 배열에서 first와 last사이의 간격을 좁혀나간다.
			first = mid + 1;
	}
	return mid;
}
