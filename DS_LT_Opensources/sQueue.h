/*=====================================================================
 * sQueue.h - 순차 큐 (선형 큐, 배열 기반, int 저장)
 *---------------------------------------------------------------------
 * [특징]
 *  - 가장 기본적인 배열 큐. front, rear를 -1로 시작해 뒤로만 이동.
 *  - 수업 교재(ch06_1 queueS)와 같은 방식이며, char 대신 int를 저장.
 *  - 단점: 삭제를 해도 앞 공간을 재사용하지 못해서, rear가 배열 끝에
 *    도달하면 앞이 비어 있어도 포화 상태가 된다. (이 단점을 해결한
 *    것이 원형 큐 -> cQueue.h)
 *
 * [사용 예시]
 *  SQueue* Q = createSQueue();
 *  enSQueue(Q, 10);  enSQueue(Q, 20);
 *  int v = deSQueue(Q);        // v = 10 (먼저 넣은 것이 먼저 나옴)
 *  printSQ(Q, NULL);           // 화면 출력 (파일에도 쓰려면 FILE* 전달)
 *  free(Q);
 *=====================================================================*/
#pragma once
#include <stdio.h>

#define SQ_SIZE 100        /* 순차 큐 크기. 문제 조건에 맞게 수정해서 사용 */

typedef struct {
	int data[SQ_SIZE];     /* 원소를 저장하는 1차원 배열 */
	int front;             /* 첫 원소 "앞" 인덱스 (초기값 -1) */
	int rear;              /* 마지막 원소 인덱스 (초기값 -1) */
} SQueue;

SQueue* createSQueue(void);              /* 공백 순차 큐 생성 (사용 후 free(Q) 필요) */
int  isSQEmpty(SQueue* Q);               /* 공백이면 1, 아니면 0 */
int  isSQFull(SQueue* Q);                /* 포화이면 1, 아니면 0 (rear가 끝에 닿으면 포화) */
int  enSQueue(SQueue* Q, int item);      /* rear에 삽입. 성공 1, 포화로 실패 0 */
int  deSQueue(SQueue* Q);                /* front에서 삭제 후 반환. 공백이면 -1 */
int  peekSQ(SQueue* Q);                  /* 맨 앞 원소 확인(삭제 안 함). 공백이면 -1 */
int  sqCount(SQueue* Q);                 /* 현재 저장된 원소 개수 */
void printSQ(SQueue* Q, FILE* log);      /* 전체 출력. log가 NULL이 아니면 파일에도 기록 */
