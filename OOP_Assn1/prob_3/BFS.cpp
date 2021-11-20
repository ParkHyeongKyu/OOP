#include "prob_3.h"

extern int arr[1000][1000];
extern int went[1000][1000];

/*나는 이 프로그래밍 과제를 다른 사람의 부적절한 도움 없이 완수하였습니다*/

int BFS(QUEUE* q, int h, int w)
{
	int wd, he, num = 0; //각각 가로값, 세로값, 섬의 개수를 나타냄
	int newr, newc; //새로운 위치를 검사할 때의 세로값과 가로값을 나타냄
	int moveh[4] = { 0, -1, 0, 1 }; //BFS함수 안에서 기준되는 자리로부터 검사할 위치까지의 세로로의 움직임을 나타냄.
	int movew[4] = { -1, 0, 1, 0 }; //BFS함수 안에서 기준되는 자리로부터 검사할 위치까지의 가로로의 움직임을 나타냄.

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			wd = j, he = i;
			enqueue(q, arr[i][j], i, j); //처음에 queue안에 집어넣는다.
			if (q->front->data == 0 || went[he][wd] == 1) //섬이 존재하지 않거나 이미 방문한 곳이면 queue에서 빼내고 다음 for문을 실행한다.
			{
				dequeue(q);
				continue;
			}
			went[he][wd] = 1; //방문한 곳임을 나타낸다.
			while (q->count != 0)
			{
				wd = q->front->ps.x, he = q->front->ps.y; //while문 안에서 가로값과 세로값을 초기화 시켜준다.
				dequeue(q); //가장 먼저 들어온 것을 빼낸다.
				for (int k = 0; k < 4; k++)
				{
					went[he][wd] = 1; //방문한 곳임을 나타낸다.
					newr = he + moveh[k]; //새롭게 검사할 곳을 지정하기 위한 변수이다.
					newc = wd + movew[k];
					if (newr < 0 || newr >= h || newc < 0 || newc >= w) //범위를 벗어났을 경우 다음 for문을 실행한다.
						continue;
					if (arr[newr][newc] != 0 && went[newr][newc] == 0) //인접한 곳에 아직 방문하지 않고 data값이 0이 아닐 경우 방문한다.
					{
						went[newr][newc] = 1;
						enqueue(q, arr[newr][newc], newr, newc);
					}
				}
			}
			num++;
		}
	}

	return num; //섬의 총 개수를 return한다.
}