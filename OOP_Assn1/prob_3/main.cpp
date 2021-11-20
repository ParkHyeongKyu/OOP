# -*- coding: utf-8 -*-
#include "prob_3.h"

int arr[1000][1000] = { 0 }; //처음 빙하를 나타낼 2차원 배열
int went[1000][1000] = { 0 }; //빙하의 검사 여부를 나타내는 2차원 배열
/*Honor Code : 나는 이 프로그래밍 과제를 다른 사람의 부적절한 도움 없이 완수하였습니다.*/

int main()
{
	QUEUE* q = new QUEUE; //BFS에서 사용할 q를 할당해준다.
	q->count = 0; //q의 초기값 지정
	q->front = NULL, q->rear = NULL;
	int w, h, year;
	scanf("%d %d %d", &w, &h, &year); //w,h, year를 입력받는다.

	for (int j = 0; j < h; j++) //처음 빙하의 모습을 scan받는다.
	{
		for (int k = 0; k < w; k++)
		{
			scanf("%d", &arr[j][k]);
		}
	}

	for (int l = 0; l < year; l++) //year만큼 지났을 때 빙하의 모습을 보여준다.
	{
		for (int q = 0; q < h; q++)
		{
			for (int p = 0; p < w; p++)
			{
				if (arr[q][p] > 0)
					arr[q][p]--;
			}
		}
	}

	printf("%d", BFS(q, h, w)); //결과값 출력
	delete q;

	return 0;
}
