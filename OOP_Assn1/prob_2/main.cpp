# -*- coding: utf-8 -*-
#include "prob_2.h"


int arr[100000] = { 0 }; //주어진 나무막대를 저장할 배열
int narr[100000] = { 0 }; //최대로 보이게 하는 나무막대의 순서를 저장할 배열

/*Honor Code : 나는 이 프로그래밍 과제를 다른 사람의 부적절한 도움 없이 완수하였습니다.*/

int main()
{
	int n, k = 0; //k는 narr에서 배열이 차있는 마지막 자리를 나타낸다.
	scanf("%d", &n); //나무막대의 개수를 입력받는다.

	for (int i = 0; i < n; i++) //주어진 나무막대의 길이를 차례대로 입력받는다.
		scanf("%d", &arr[i]);

	narr[0] = arr[0]; 
	for (int i = 1; i < n; i++)
	{
		if (narr[k] < arr[i]) //주어진 나무막대의 길이가 narr의 마지막 길이보다 크다면 narr 다음칸에 추가한다.
			narr[++k] = arr[i];
		else //주어진 나무막대의 길이가 narr의 마지막 길이보다 작거나 같다면 narr에서 binary search를 이용하여 길이순으로 들어갈 자리를 찾는다.
		{
			int j = found(k, arr[i], narr); //found함수가 binarysearch를 통하여 들어갈 자리를 찾아준다.
			narr[j] = arr[i]; //찾은 자리에 arr[i]를 집어넣는다.
		}
	}
	printf("%d", k + 1);
	return 0;
}
