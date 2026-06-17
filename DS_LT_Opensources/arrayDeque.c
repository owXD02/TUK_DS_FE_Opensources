/*=====================================================================
 * arrayDeque.c - 순차 데크(배열·원형) 구현부 (설명은 arrayDeque.h 참고)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "arrayDeque.h"
#include "utils.h"     /* dualPrintf 사용 */

/* 공백 상태의 순차 데크 생성. front == rear == 0 이면 공백. */
ADeque* createADeque(void)
{
	ADeque* DQ = (ADeque*)malloc(sizeof(ADeque));
	DQ->front = 0;
	DQ->rear = 0;
	return DQ;
}

/* 공백 검사: front와 rear가 같으면 공백 */
int isADQEmpty(ADeque* DQ)
{
	return (DQ->front == DQ->rear);
}

/* 포화 검사: rear 다음 칸이 front면 포화 (한 칸을 비워 두는 방식) */
int isADQFull(ADeque* DQ)
{
	return (((DQ->rear + 1) % ADQ_SIZE) == DQ->front);
}

/* 앞(front)에 삽입.
   front를 왼쪽으로 한 칸 옮긴 자리에 저장한다. (원형이라 0에서 왼쪽은 끝칸) */
int aqInsertFront(ADeque* DQ, int item)
{
	if (isADQFull(DQ)) {
		printf(" [순차 데크 포화] %d 앞 삽입 실패!\n", item);
		return 0;
	}
	DQ->data[DQ->front] = item;                       /* 현재 front 자리에 저장 후 */
	DQ->front = (DQ->front - 1 + ADQ_SIZE) % ADQ_SIZE;/* front를 왼쪽으로 한 칸 */
	return 1;
}

/* 뒤(rear)에 삽입.
   rear를 오른쪽으로 한 칸 옮긴 자리에 저장한다. (원형 큐의 enqueue와 동일) */
int aqInsertRear(ADeque* DQ, int item)
{
	if (isADQFull(DQ)) {
		printf(" [순차 데크 포화] %d 뒤 삽입 실패!\n", item);
		return 0;
	}
	DQ->rear = (DQ->rear + 1) % ADQ_SIZE;             /* rear를 오른쪽으로 한 칸 */
	DQ->data[DQ->rear] = item;                        /* 그 자리에 저장 */
	return 1;
}

/* 앞(front)에서 삭제 후 반환. 공백이면 -1.
   front를 오른쪽으로 한 칸 옮기면 그 자리가 첫 원소(삭제 대상)다. */
int aqDeleteFront(ADeque* DQ)
{
	if (isADQEmpty(DQ)) {
		printf(" [순차 데크 공백] 앞 삭제 실패!\n");
		return -1;
	}
	DQ->front = (DQ->front + 1) % ADQ_SIZE;
	return DQ->data[DQ->front];
}

/* 뒤(rear)에서 삭제 후 반환. 공백이면 -1.
   현재 rear 자리가 마지막 원소이므로 그 값을 꺼내고 rear를 왼쪽으로 한 칸. */
int aqDeleteRear(ADeque* DQ)
{
	if (isADQEmpty(DQ)) {
		printf(" [순차 데크 공백] 뒤 삭제 실패!\n");
		return -1;
	}
	int item = DQ->data[DQ->rear];
	DQ->rear = (DQ->rear - 1 + ADQ_SIZE) % ADQ_SIZE;
	return item;
}

/* 앞 원소 확인(삭제 안 함). 공백이면 -1. */
int aqPeekFront(ADeque* DQ)
{
	if (isADQEmpty(DQ)) {
		printf(" [순차 데크 공백] peek 실패!\n");
		return -1;
	}
	return DQ->data[(DQ->front + 1) % ADQ_SIZE];   /* front 다음 칸이 첫 원소 */
}

/* 뒤 원소 확인(삭제 안 함). 공백이면 -1. */
int aqPeekRear(ADeque* DQ)
{
	if (isADQEmpty(DQ)) {
		printf(" [순차 데크 공백] peek 실패!\n");
		return -1;
	}
	return DQ->data[DQ->rear];                     /* rear 자리가 마지막 원소 */
}

/* 현재 저장된 원소 개수 */
int aqCount(ADeque* DQ)
{
	return (DQ->rear - DQ->front + ADQ_SIZE) % ADQ_SIZE;
}

/* front부터 rear까지 순서대로 출력. log가 NULL이 아니면 파일에도 기록. */
void printADeque(ADeque* DQ, FILE* log)
{
	int i = (DQ->front + 1) % ADQ_SIZE;            /* 첫 원소 위치 */
	int last = (DQ->rear + 1) % ADQ_SIZE;          /* 마지막 원소 다음 위치 */

	dualPrintf(log, " 순차 데크 : [");
	while (i != last) {
		dualPrintf(log, "%4d", DQ->data[i]);
		i = (i + 1) % ADQ_SIZE;
	}
	dualPrintf(log, " ]\n");
}
