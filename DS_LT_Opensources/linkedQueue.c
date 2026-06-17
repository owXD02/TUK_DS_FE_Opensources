/*=====================================================================
 * linkedQueue.c - 연결 큐 구현부 (설명은 linkedQueue.h 참고)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS   /* VS 보안 경고 끄기 - 반드시 모든 include보다 위에! */
#include <stdlib.h>
#include "linkedQueue.h"
#include "utils.h"     /* dualPrintf 사용 */

/* 공백 상태의 연결 큐를 생성하여 주소를 반환한다. */
LQueue* createLQueue(void)
{
	LQueue* LQ = (LQueue*)malloc(sizeof(LQueue));
	LQ->front = NULL;
	LQ->rear = NULL;
	return LQ;
}

/* 큐가 공백 상태인지 검사한다. 공백이면 1, 아니면 0. */
int isLQEmpty(LQueue* LQ)
{
	return (LQ->front == NULL);
}

/* 큐의 rear에 원소를 삽입한다. (동적 할당이므로 포화 없음) */
void enLQueue(LQueue* LQ, int item)
{
	LQNode* newNode = (LQNode*)malloc(sizeof(LQNode));
	newNode->data = item;
	newNode->link = NULL;

	if (LQ->front == NULL) {       /* 큐가 비어 있으면 front, rear 모두 새 노드 */
		LQ->front = newNode;
		LQ->rear = newNode;
	}
	else {                         /* 비어있지 않으면 rear 뒤에 연결 */
		LQ->rear->link = newNode;
		LQ->rear = newNode;
	}
}

/* 큐의 front에서 원소를 삭제하고 그 값을 반환한다. 공백이면 -1 반환. */
int deLQueue(LQueue* LQ)
{
	LQNode* old = LQ->front;
	int item;

	if (isLQEmpty(LQ)) {
		printf(" [연결 큐 공백] 삭제 실패!\n");
		return -1;
	}
	item = old->data;
	LQ->front = LQ->front->link;   /* front를 다음 노드로 이동 */
	if (LQ->front == NULL)         /* 마지막 노드였다면 rear도 NULL로 */
		LQ->rear = NULL;
	free(old);                     /* 삭제한 노드의 메모리 해제 */
	return item;
}

/* 맨 앞 원소를 삭제하지 않고 확인만 한다. 공백이면 -1 반환. */
int peekLQ(LQueue* LQ)
{
	if (isLQEmpty(LQ)) {
		printf(" [연결 큐 공백] peek 실패!\n");
		return -1;
	}
	return LQ->front->data;
}

/* 현재 큐에 들어있는 원소의 개수를 반환한다. */
int lqCount(LQueue* LQ)
{
	int count = 0;
	LQNode* temp = LQ->front;
	while (temp != NULL) {
		count++;
		temp = temp->link;
	}
	return count;
}

/* 큐의 모든 원소를 front부터 rear 순서로 출력한다.
 * log가 NULL이 아니면 같은 내용을 파일에도 기록한다. */
void printLQ(LQueue* LQ, FILE* log)
{
	LQNode* temp = LQ->front;
	dualPrintf(log, " 연결 큐 : [");
	while (temp != NULL) {
		dualPrintf(log, "%4d", temp->data);
		temp = temp->link;
	}
	dualPrintf(log, " ]\n");
}

/* 큐에 남아 있는 모든 노드와 큐 자체의 메모리를 해제한다. */
void freeLQueue(LQueue* LQ)
{
	LQNode* p = LQ->front;
	LQNode* next;
	while (p != NULL) {
		next = p->link;
		free(p);
		p = next;
	}
	free(LQ);
}
