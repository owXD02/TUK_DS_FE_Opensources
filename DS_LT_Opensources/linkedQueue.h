/*=====================================================================
 * linkedQueue.h - 연결 큐 (연결 리스트 기반, int 저장)
 *---------------------------------------------------------------------
 * [특징]
 *  - 노드를 동적 할당하므로 크기 제한이 없다 (포화 상태가 없음).
 *  - 수업 교재(ch06_3 LinkedQueue)와 같은 방식이며, char 대신 int를 저장.
 *  - 기수 정렬(radix sort)의 버킷, 트리 레벨 순회 등에도 활용 가능.
 *
 * [사용 예시]
 *  LQueue* LQ = createLQueue();
 *  enLQueue(LQ, 10);  enLQueue(LQ, 20);
 *  int v = deLQueue(LQ);       // v = 10
 *  printLQ(LQ, NULL);          // 화면 출력 (파일에도 쓰려면 FILE* 전달)
 *  freeLQueue(LQ);             // 사용 후 메모리 해제 (남은 노드까지 정리)
 *=====================================================================*/
#pragma once
#include <stdio.h>

typedef struct LQNode {        /* 연결 큐의 노드 */
	int data;                  /* 저장할 값 */
	struct LQNode* link;       /* 다음 노드를 가리키는 링크 */
} LQNode;

typedef struct {               /* front, rear 포인터를 묶은 구조체 */
	LQNode* front;             /* 첫 번째 노드 (삭제가 일어나는 쪽) */
	LQNode* rear;              /* 마지막 노드 (삽입이 일어나는 쪽) */
} LQueue;

LQueue* createLQueue(void);             /* 공백 연결 큐 생성 */
int  isLQEmpty(LQueue* LQ);             /* 공백이면 1, 아니면 0 */
void enLQueue(LQueue* LQ, int item);    /* rear에 삽입 (크기 제한 없음) */
int  deLQueue(LQueue* LQ);              /* front에서 삭제 후 반환. 공백이면 -1 */
int  peekLQ(LQueue* LQ);                /* 맨 앞 원소 확인(삭제 안 함). 공백이면 -1 */
int  lqCount(LQueue* LQ);               /* 현재 저장된 원소 개수 */
void printLQ(LQueue* LQ, FILE* log);    /* 전체 출력. log가 NULL이 아니면 파일에도 기록 */
void freeLQueue(LQueue* LQ);            /* 큐 전체(노드 포함) 메모리 해제 */
