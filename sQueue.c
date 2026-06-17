/*=====================================================================
 * sQueue.c - 순차 큐(선형 큐) 구현부 (설명은 sQueue.h 참고)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS   /* VS 보안 경고 끄기 - 반드시 모든 include보다 위에! */
#include <stdlib.h>
#include "sQueue.h"
#include "utils.h"     /* dualPrintf 사용 */

/* 공백 상태의 순차 큐를 생성하여 주소를 반환한다. */
SQueue* createSQueue(void)
{
	SQueue* Q = (SQueue*)malloc(sizeof(SQueue));
	Q->front = -1;         /* front, rear가 -1이면 공백 상태 */
	Q->rear = -1;
	return Q;
}

/* 큐가 공백 상태인지 검사한다. 공백이면 1, 아니면 0. */
int isSQEmpty(SQueue* Q)
{
	return (Q->front == Q->rear);
}

/* 큐가 포화 상태인지 검사한다. 포화이면 1, 아니면 0.
 * (순차 큐는 rear가 배열의 끝에 도달하면 앞이 비어 있어도 포화!) */
int isSQFull(SQueue* Q)
{
	return (Q->rear == SQ_SIZE - 1);
}

/* 큐의 rear에 원소를 삽입한다. 성공 시 1, 포화 상태면 0 반환. */
int enSQueue(SQueue* Q, int item)
{
	if (isSQFull(Q)) {
		printf(" [순차 큐 포화] %d 삽입 실패!\n", item);
		return 0;
	}
	Q->data[++(Q->rear)] = item;   /* rear를 한 칸 옮기고 저장 */
	return 1;
}

/* 큐의 front에서 원소를 삭제하고 그 값을 반환한다. 공백이면 -1 반환. */
int deSQueue(SQueue* Q)
{
	if (isSQEmpty(Q)) {
		printf(" [순차 큐 공백] 삭제 실패!\n");
		return -1;
	}
	return Q->data[++(Q->front)];  /* front를 한 칸 옮기면 그 자리가 삭제 원소 */
}

/* 맨 앞 원소를 삭제하지 않고 확인만 한다. 공백이면 -1 반환. */
int peekSQ(SQueue* Q)
{
	if (isSQEmpty(Q)) {
		printf(" [순차 큐 공백] peek 실패!\n");
		return -1;
	}
	return Q->data[Q->front + 1];
}

/* 현재 큐에 들어있는 원소의 개수를 반환한다. */
int sqCount(SQueue* Q)
{
	return Q->rear - Q->front;
}

/* 큐의 모든 원소를 front부터 rear 순서로 출력한다.
 * log가 NULL이 아니면 같은 내용을 파일에도 기록한다. */
void printSQ(SQueue* Q, FILE* log)
{
	int i;
	dualPrintf(log, " 순차 큐 : [");
	for (i = Q->front + 1; i <= Q->rear; i++)
		dualPrintf(log, "%4d", Q->data[i]);
	dualPrintf(log, " ]\n");
}
