# -*- coding: utf-8 -*-
#include "prob_3.h"

/*나는 이 프로그래밍 과제를 다른 사람의 부적절한 도움 없이 완수하였습니다*/

void enqueue(QUEUE* q, int d, int i, int j) //queue안에 집어넣는 함수이다.
{
	node* n = new node;
	n->data = d; //node 초기화
	n->next = NULL;
	n->ps.x = j;
	n->ps.y = i;

	if (q->count == 0) //queue가 비어 있을 경우
		q->front = n;
	else
		q->rear->next = n;
	(q->count)++;
	q->rear = n;
}

void dequeue(QUEUE* q) //queue에서 빼내는 함수이다.
{
	node* d = q->front;
	if (q->count == 1) //queue에 값이 하나밖에 없을 경우
		q->rear = q->front = NULL;
	else
		q->front = q->front->next;
	(q->count)--;
	delete d;
}
