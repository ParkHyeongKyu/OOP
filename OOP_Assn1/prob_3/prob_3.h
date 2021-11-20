# -*- coding: utf-8 -*-
/*나는 이 프로그래밍 과제를 다른 사람의 부적절한 도움 없이 완수하였습니다*/

#ifndef _PROB_3_H_
#define _PROB_3_H_

#include <cstdio>
#include <cstdlib>

typedef struct //위치를 나타내는 구조체
{
	int x, y;
}pos;

typedef struct node //queue안에 들어가는 node 구조체
{
	pos ps;
	int data;
	struct node* next;
}node;

typedef struct //queue를 관리하는 구조체
{
	node* front;
	node* rear;
	int count;
}QUEUE;

int BFS(QUEUE* q, int h, int w);
void enqueue(QUEUE* q, int d, int i, int j);
void dequeue(QUEUE* q);

#endif
