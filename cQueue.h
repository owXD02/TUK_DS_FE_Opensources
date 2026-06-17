/*=====================================================================
 * cQueue.h - 원형 큐 (배열 기반, int 저장)
 *---------------------------------------------------------------------
 * [특징]
 *  - 배열 기반 원형 큐. front == rear 이면 공백, (rear+1)%크기 == front 이면 포화.
 *  - 한 칸을 비워두는 방식이라 실제로는 CQ_SIZE-1 개까지 저장 가능.
 *  - 수업 교재(ch06_2 cQueueS)와 같은 방식이며, char 대신 int를 저장.
 *
 * [선형 큐로 바꿔야 할 때] (문제에서 "선형 큐"를 콕 집어 요구하면)
 *  - createCQueue에서 front = rear = -1 로 초기화
 *  - enCQueue : 포화 조건 rear == CQ_SIZE-1, 삽입은 Q->data[++Q->rear] = item
 *  - deCQueue : 삭제는 return Q->data[++Q->front]
 *  - 즉 % 연산만 빼면 선형 큐가 된다.
 *
 * [사용 예시]
 *  CQueue* Q = createCQueue();
 *  enCQueue(Q, 10);  enCQueue(Q, 20);
 *  int v = deCQueue(Q);        // v = 10 (먼저 넣은 것이 먼저 나옴)
 *  printCQ(Q, NULL);           // 화면에만 출력 (파일에도 쓰려면 FILE* 전달)
 *  free(Q);
 *=====================================================================*/
#pragma once
#include <stdio.h>

#define CQ_SIZE 100        /* 큐 크기. 문제 조건에 맞게 수정해서 사용 (실제 저장은 CQ_SIZE-1개) */

typedef struct {
	int data[CQ_SIZE];     /* 원소를 저장하는 1차원 배열 */
	int front;             /* 첫 원소 "앞" 인덱스 */
	int rear;              /* 마지막 원소 인덱스 */
} CQueue;

CQueue* createCQueue(void);              /* 공백 원형 큐 생성 (사용 후 free(Q) 필요) */
int  isCQEmpty(CQueue* Q);               /* 공백이면 1, 아니면 0 */
int  isCQFull(CQueue* Q);                /* 포화이면 1, 아니면 0 */
int  enCQueue(CQueue* Q, int item);      /* rear에 삽입. 성공 1, 포화로 실패 0 */
int  deCQueue(CQueue* Q);                /* front에서 삭제 후 반환. 공백이면 -1 */
int  peekCQ(CQueue* Q);                  /* 맨 앞 원소 확인(삭제 안 함). 공백이면 -1 */
int  cqCount(CQueue* Q);                 /* 현재 저장된 원소 개수 */
void printCQ(CQueue* Q, FILE* log);      /* 전체 출력. log가 NULL이 아니면 파일에도 기록 */
