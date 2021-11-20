#include "prob_3.h"

extern int arr[1000][1000];
extern int went[1000][1000];

/*���� �� ���α׷��� ������ �ٸ� ����� �������� ���� ���� �ϼ��Ͽ����ϴ�*/

int BFS(QUEUE* q, int h, int w)
{
	int wd, he, num = 0; //���� ���ΰ�, ���ΰ�, ���� ������ ��Ÿ��
	int newr, newc; //���ο� ��ġ�� �˻��� ���� ���ΰ��� ���ΰ��� ��Ÿ��
	int moveh[4] = { 0, -1, 0, 1 }; //BFS�Լ� �ȿ��� ���صǴ� �ڸ��κ��� �˻��� ��ġ������ ���η��� �������� ��Ÿ��.
	int movew[4] = { -1, 0, 1, 0 }; //BFS�Լ� �ȿ��� ���صǴ� �ڸ��κ��� �˻��� ��ġ������ ���η��� �������� ��Ÿ��.

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			wd = j, he = i;
			enqueue(q, arr[i][j], i, j); //ó���� queue�ȿ� ����ִ´�.
			if (q->front->data == 0 || went[he][wd] == 1) //���� �������� �ʰų� �̹� �湮�� ���̸� queue���� ������ ���� for���� �����Ѵ�.
			{
				dequeue(q);
				continue;
			}
			went[he][wd] = 1; //�湮�� ������ ��Ÿ����.
			while (q->count != 0)
			{
				wd = q->front->ps.x, he = q->front->ps.y; //while�� �ȿ��� ���ΰ��� ���ΰ��� �ʱ�ȭ �����ش�.
				dequeue(q); //���� ���� ���� ���� ������.
				for (int k = 0; k < 4; k++)
				{
					went[he][wd] = 1; //�湮�� ������ ��Ÿ����.
					newr = he + moveh[k]; //���Ӱ� �˻��� ���� �����ϱ� ���� �����̴�.
					newc = wd + movew[k];
					if (newr < 0 || newr >= h || newc < 0 || newc >= w) //������ ����� ��� ���� for���� �����Ѵ�.
						continue;
					if (arr[newr][newc] != 0 && went[newr][newc] == 0) //������ ���� ���� �湮���� �ʰ� data���� 0�� �ƴ� ��� �湮�Ѵ�.
					{
						went[newr][newc] = 1;
						enqueue(q, arr[newr][newc], newr, newc);
					}
				}
			}
			num++;
		}
	}

	return num; //���� �� ������ return�Ѵ�.
}