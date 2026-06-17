/*=====================================================================
 * cQueue.c - 원형 큐 구현부 (설명은 cQueue.h 참고)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS   /* VS 보안 경고 끄기 - 반드시 모든 include보다 위에! */
#include <stdlib.h>
#include "cQueue.h"
#include "utils.h"     /* dualPrintf 사용 */

/* 공백 상태의 원형 큐를 생성하여 주소를 반환한다. */
CQueue* createCQueue(void)
{
	CQueue* Q = (CQueue*)malloc(sizeof(CQueue));
	Q->front = 0;          /* front, rear가 같으면 공백 상태 */
	Q->rear = 0;
	return Q;
}

/* 큐가 공백 상태인지 검사한다. 공백이면 1, 아니면 0. */
int isCQEmpty(CQueue* Q)
{
	return (Q->front == Q->rear);
}

/* 큐가 포화 상태인지 검사한다. 포화이면 1, 아니면 0. */
int isCQFull(CQueue* Q)
{
	return (((Q->rear + 1) % CQ_SIZE) == Q->front);
}

/* 큐의 rear에 원소를 삽입한다. 성공 시 1, 포화 상태면 0 반환. */
int enCQueue(CQueue* Q, int item)
{
	if (isCQFull(Q)) {
		printf(" [원형 큐 포화] %d 삽입 실패!\n", item);
		return 0;
	}
	Q->rear = (Q->rear + 1) % CQ_SIZE;   /* rear를 한 칸 옮기고 (원형이므로 % 사용) */
	Q->data[Q->rear] = item;             /* 그 자리에 저장 */
	return 1;
}

/* 큐의 front에서 원소를 삭제하고 그 값을 반환한다. 공백이면 -1 반환. */
int deCQueue(CQueue* Q)
{
	if (isCQEmpty(Q)) {
		printf(" [원형 큐 공백] 삭제 실패!\n");
		return -1;
	}
	Q->front = (Q->front + 1) % CQ_SIZE; /* front를 한 칸 옮기면 */
	return Q->data[Q->front];            /* 그 자리가 삭제되는 원소 */
}

/* 맨 앞 원소를 삭제하지 않고 확인만 한다. 공백이면 -1 반환. */
int peekCQ(CQueue* Q)
{
	if (isCQEmpty(Q)) {
		printf(" [원형 큐 공백] peek 실패!\n");
		return -1;
	}
	return Q->data[(Q->front + 1) % CQ_SIZE];
}

/* 현재 큐에 들어있는 원소의 개수를 반환한다. */
int cqCount(CQueue* Q)
{
	return (Q->rear - Q->front + CQ_SIZE) % CQ_SIZE;
}

/* 큐의 모든 원소를 front부터 rear 순서로 출력한다.
 * log가 NULL이 아니면 같은 내용을 파일에도 기록한다. */
void printCQ(CQueue* Q, FILE* log)
{
	int i = (Q->front + 1) % CQ_SIZE;          /* 첫 원소 위치 */
	int last = (Q->rear + 1) % CQ_SIZE;        /* 마지막 원소 다음 위치 */

	dualPrintf(log, " 원형 큐 : [");
	while (i != last) {
		dualPrintf(log, "%4d", Q->data[i]);
		i = (i + 1) % CQ_SIZE;
	}
	dualPrintf(log, " ]\n");
}
