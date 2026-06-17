/*=====================================================================
 * deque.h - 덱 (Deque, 이중 연결 리스트 기반, int 저장)
 *---------------------------------------------------------------------
 * [특징]
 *  - 양쪽 끝(front, rear)에서 모두 삽입/삭제가 가능한 큐.
 *  - 수업 교재(ch06_4 deQue)와 같은 방식이며, char 대신 int를 저장.
 *  - 덱 하나로 큐(뒤 삽입+앞 삭제)도, 스택(뒤 삽입+뒤 삭제)도 흉내 가능.
 *  - 좌표(x,y)를 담는 덱이 필요하면 xyList.h를 사용할 것.
 *
 * [사용 예시]
 *  Deque* DQ = createDeque();
 *  dqInsertRear(DQ, 10);       // 뒤에 삽입   [10]
 *  dqInsertFront(DQ, 20);      // 앞에 삽입   [20 10]
 *  int a = dqDeleteFront(DQ);  // a = 20      [10]
 *  int b = dqDeleteRear(DQ);   // b = 10      []
 *  printDeque(DQ, NULL);
 *  freeDeque(DQ);
 *=====================================================================*/
#pragma once
#include <stdio.h>

typedef struct DQNode {        /* 덱의 노드 (양방향 링크) */
	int data;                  /* 저장할 값 */
	struct DQNode* llink;      /* 왼쪽(앞) 노드 링크 */
	struct DQNode* rlink;      /* 오른쪽(뒤) 노드 링크 */
} DQNode;

typedef struct {               /* front, rear 포인터를 묶은 구조체 */
	DQNode* front;             /* 맨 앞 노드 */
	DQNode* rear;              /* 맨 뒤 노드 */
} Deque;

Deque* createDeque(void);                /* 공백 덱 생성 */
int  isDQEmpty(Deque* DQ);               /* 공백이면 1, 아니면 0 */
void dqInsertFront(Deque* DQ, int item); /* 맨 앞에 삽입 */
void dqInsertRear(Deque* DQ, int item);  /* 맨 뒤에 삽입 */
int  dqDeleteFront(Deque* DQ);           /* 맨 앞 삭제 후 반환. 공백이면 -1 */
int  dqDeleteRear(Deque* DQ);            /* 맨 뒤 삭제 후 반환. 공백이면 -1 */
int  dqPeekFront(Deque* DQ);             /* 맨 앞 확인(삭제 안 함). 공백이면 -1 */
int  dqPeekRear(Deque* DQ);              /* 맨 뒤 확인(삭제 안 함). 공백이면 -1 */
void printDeque(Deque* DQ, FILE* log);   /* front -> rear 순서로 전체 출력 */
void freeDeque(Deque* DQ);               /* 덱 전체(노드 포함) 메모리 해제 */
