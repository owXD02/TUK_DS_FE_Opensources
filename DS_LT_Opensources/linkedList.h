/*=====================================================================
 * linkedList.h - 범용 단일 연결 리스트 (int 저장)
 *---------------------------------------------------------------------
 * [왜 필요한가]
 *  - 큐(linkedQueue)·덱(deque)은 양 끝 삽입/삭제만 한다.
 *  - 이 모듈은 "임의 위치 삽입/삭제, 값 탐색, 역순(reverse)" 같은
 *    일반 연결 리스트 연산을 제공한다. ("연결 리스트로 ~하라" 단독 문제용)
 *
 * [사용 예시]
 *  LinkedList* L = createList();
 *  insertLast(L, 10);  insertLast(L, 20);  insertFirst(L, 5);  // [5 10 20]
 *  insertAt(L, 2, 15);                  // [5 10 15 20]
 *  printf("위치=%d\n", searchList(L, 15));   // 2
 *  deleteValue(L, 10);                  // [5 15 20]
 *  reverseList(L);                      // [20 15 5]
 *  printList(L, NULL);
 *  freeList(L);
 *=====================================================================*/
#pragma once
#include <stdio.h>

typedef struct LLNode {        /* 연결 리스트 노드 */
	int data;
	struct LLNode* next;
} LLNode;

typedef struct {               /* 머리 포인터 + 개수 */
	LLNode* head;
	int count;
} LinkedList;

LinkedList* createList(void);                    /* 공백 리스트 생성 */
int  isListEmpty(LinkedList* L);                 /* 공백이면 1 */
void insertFirst(LinkedList* L, int item);       /* 맨 앞 삽입 */
void insertLast(LinkedList* L, int item);        /* 맨 뒤 삽입 */
int  insertAt(LinkedList* L, int pos, int item); /* pos(0-based) 위치에 삽입. 성공 1 */
int  deleteValue(LinkedList* L, int item);       /* 첫 번째 일치 값 삭제. 성공 1, 없으면 0 */
int  searchList(LinkedList* L, int item);        /* 값의 인덱스 반환. 없으면 -1 */
void reverseList(LinkedList* L);                 /* 리스트를 역순으로 뒤집기 */
int  listLength(LinkedList* L);                  /* 현재 길이 */
void printList(LinkedList* L, FILE* log);        /* 전체 출력. log!=NULL이면 파일에도 */
void freeList(LinkedList* L);                    /* 리스트 전체(노드 포함) 해제 */
