/*=====================================================================
 * arrayDeque.h - 순차 데크 (배열 기반, 원형 방식, int 저장)
 *---------------------------------------------------------------------
 * [특징]
 *  - 배열로 구현한 덱(Deque): 양쪽 끝(front, rear)에서 삽입/삭제 모두 가능.
 *  - 원형(circular) 방식: front/rear를 % 크기로 양방향 이동시켜, 한쪽이
 *    막히지 않고 배열 공간을 재사용한다. (원형 큐를 양끝 연산까지 확장한 것)
 *  - '연결 데크'(deque.h, 노드 방식)와 짝을 이루는 '순차 데크' 구현.
 *  - 한 칸을 비워 두는 방식이라 실제 저장은 ADQ_SIZE-1 개까지.
 *
 * [인덱스 규칙]
 *  - 공백: front == rear
 *  - 포화: (rear + 1) % ADQ_SIZE == front
 *  - 앞 삽입: front를 왼쪽으로 한 칸((front-1+크기)%크기) 옮겨 저장
 *  - 뒤 삽입: rear를 오른쪽으로 한 칸((rear+1)%크기) 옮겨 저장
 *
 * [사용 예시]
 *  ADeque* DQ = createADeque();
 *  aqInsertRear(DQ, 10);     // 뒤 삽입   [10]
 *  aqInsertFront(DQ, 20);    // 앞 삽입   [20 10]
 *  int a = aqDeleteFront(DQ);// a=20      [10]
 *  int b = aqDeleteRear(DQ); // b=10      []
 *  printADeque(DQ, NULL);
 *  free(DQ);
 *=====================================================================*/
#pragma once
#include <stdio.h>

#define ADQ_SIZE 100       /* 배열 크기. 실제 저장은 ADQ_SIZE-1개 (한 칸 비움) */

typedef struct {
	int data[ADQ_SIZE];    /* 원소를 저장하는 1차원 배열 */
	int front;             /* 첫 원소 "앞" 인덱스 */
	int rear;              /* 마지막 원소 인덱스 */
} ADeque;

ADeque* createADeque(void);                /* 공백 순차 데크 생성 (사용 후 free) */
int  isADQEmpty(ADeque* DQ);               /* 공백이면 1 */
int  isADQFull(ADeque* DQ);                /* 포화이면 1 */
int  aqInsertFront(ADeque* DQ, int item);  /* 앞에 삽입. 성공 1, 포화 0 */
int  aqInsertRear(ADeque* DQ, int item);   /* 뒤에 삽입. 성공 1, 포화 0 */
int  aqDeleteFront(ADeque* DQ);            /* 앞 삭제 후 반환. 공백이면 -1 */
int  aqDeleteRear(ADeque* DQ);             /* 뒤 삭제 후 반환. 공백이면 -1 */
int  aqPeekFront(ADeque* DQ);              /* 앞 원소 확인(삭제 안 함). 공백이면 -1 */
int  aqPeekRear(ADeque* DQ);               /* 뒤 원소 확인(삭제 안 함). 공백이면 -1 */
int  aqCount(ADeque* DQ);                  /* 현재 저장된 원소 개수 */
void printADeque(ADeque* DQ, FILE* log);   /* front -> rear 순서로 전체 출력 */
