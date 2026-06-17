/*=====================================================================
 * deque.c - 덱 구현부 (설명은 deque.h 참고)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS   /* VS 보안 경고 끄기 - 반드시 모든 include보다 위에! */
#include <stdlib.h>
#include "deque.h"
#include "utils.h"     /* dualPrintf 사용 */

/* 공백 상태의 덱을 생성하여 주소를 반환한다. */
Deque* createDeque(void)
{
	Deque* DQ = (Deque*)malloc(sizeof(Deque));
	DQ->front = NULL;
	DQ->rear = NULL;
	return DQ;
}

/* 덱이 공백 상태인지 검사한다. 공백이면 1, 아니면 0. */
int isDQEmpty(Deque* DQ)
{
	return (DQ->front == NULL);
}

/* 덱의 맨 앞(front)에 원소를 삽입한다. */
void dqInsertFront(Deque* DQ, int item)
{
	DQNode* newNode = (DQNode*)malloc(sizeof(DQNode));
	newNode->data = item;
	newNode->llink = NULL;

	if (isDQEmpty(DQ)) {           /* 덱이 비어 있으면 front, rear 모두 새 노드 */
		newNode->rlink = NULL;
		DQ->front = newNode;
		DQ->rear = newNode;
	}
	else {                         /* 기존 front 앞에 연결 */
		newNode->rlink = DQ->front;
		DQ->front->llink = newNode;
		DQ->front = newNode;
	}
}

/* 덱의 맨 뒤(rear)에 원소를 삽입한다. */
void dqInsertRear(Deque* DQ, int item)
{
	DQNode* newNode = (DQNode*)malloc(sizeof(DQNode));
	newNode->data = item;
	newNode->rlink = NULL;

	if (isDQEmpty(DQ)) {           /* 덱이 비어 있으면 front, rear 모두 새 노드 */
		newNode->llink = NULL;
		DQ->front = newNode;
		DQ->rear = newNode;
	}
	else {                         /* 기존 rear 뒤에 연결 */
		newNode->llink = DQ->rear;
		DQ->rear->rlink = newNode;
		DQ->rear = newNode;
	}
}

/* 덱의 맨 앞 노드를 삭제하고 그 값을 반환한다. 공백이면 -1 반환. */
int dqDeleteFront(Deque* DQ)
{
	DQNode* old = DQ->front;
	int item;

	if (isDQEmpty(DQ)) {
		printf(" [덱 공백] 삭제 실패!\n");
		return -1;
	}
	item = old->data;
	if (old->rlink == NULL) {      /* 마지막 노드였다면 덱이 공백이 된다 */
		DQ->front = NULL;
		DQ->rear = NULL;
	}
	else {
		DQ->front = old->rlink;
		DQ->front->llink = NULL;
	}
	free(old);
	return item;
}

/* 덱의 맨 뒤 노드를 삭제하고 그 값을 반환한다. 공백이면 -1 반환. */
int dqDeleteRear(Deque* DQ)
{
	DQNode* old = DQ->rear;
	int item;

	if (isDQEmpty(DQ)) {
		printf(" [덱 공백] 삭제 실패!\n");
		return -1;
	}
	item = old->data;
	if (old->llink == NULL) {      /* 마지막 노드였다면 덱이 공백이 된다 */
		DQ->front = NULL;
		DQ->rear = NULL;
	}
	else {
		DQ->rear = old->llink;
		DQ->rear->rlink = NULL;
	}
	free(old);
	return item;
}

/* 맨 앞 원소를 삭제하지 않고 확인만 한다. 공백이면 -1 반환. */
int dqPeekFront(Deque* DQ)
{
	if (isDQEmpty(DQ)) {
		printf(" [덱 공백] peek 실패!\n");
		return -1;
	}
	return DQ->front->data;
}

/* 맨 뒤 원소를 삭제하지 않고 확인만 한다. 공백이면 -1 반환. */
int dqPeekRear(Deque* DQ)
{
	if (isDQEmpty(DQ)) {
		printf(" [덱 공백] peek 실패!\n");
		return -1;
	}
	return DQ->rear->data;
}

/* 덱의 모든 원소를 front부터 rear 순서로 출력한다. */
void printDeque(Deque* DQ, FILE* log)
{
	DQNode* temp = DQ->front;
	dualPrintf(log, " 덱 : [");
	while (temp != NULL) {
		dualPrintf(log, "%4d", temp->data);
		temp = temp->rlink;
	}
	dualPrintf(log, " ]\n");
}

/* 덱에 남아 있는 모든 노드와 덱 자체의 메모리를 해제한다. */
void freeDeque(Deque* DQ)
{
	DQNode* p = DQ->front;
	DQNode* next;
	while (p != NULL) {
		next = p->rlink;
		free(p);
		p = next;
	}
	free(DQ);
}
