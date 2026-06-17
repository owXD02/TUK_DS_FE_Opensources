/*=====================================================================
 * linkedList.c - 범용 단일 연결 리스트 구현부 (설명은 linkedList.h 참고)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include "linkedList.h"
#include "utils.h"     /* dualPrintf 사용 */

/* 공백 리스트 생성 */
LinkedList* createList(void)
{
	LinkedList* L = (LinkedList*)malloc(sizeof(LinkedList));
	L->head = NULL;
	L->count = 0;
	return L;
}

/* 공백 검사 */
int isListEmpty(LinkedList* L)
{
	return (L->head == NULL);
}

/* 맨 앞에 삽입: 새 노드가 기존 head를 가리키고, head를 새 노드로 */
void insertFirst(LinkedList* L, int item)
{
	LLNode* newNode = (LLNode*)malloc(sizeof(LLNode));
	newNode->data = item;
	newNode->next = L->head;
	L->head = newNode;
	L->count++;
}

/* 맨 뒤에 삽입: 마지막 노드까지 가서 연결 */
void insertLast(LinkedList* L, int item)
{
	LLNode* newNode = (LLNode*)malloc(sizeof(LLNode));
	newNode->data = item;
	newNode->next = NULL;
	if (L->head == NULL) {                 /* 비어 있으면 head가 곧 새 노드 */
		L->head = newNode;
	}
	else {
		LLNode* p = L->head;
		while (p->next != NULL) p = p->next;   /* 마지막 노드 찾기 */
		p->next = newNode;
	}
	L->count++;
}

/* pos(0-based) 위치에 삽입.
 *  - pos<=0 이면 맨 앞, pos>=길이 이면 맨 뒤.
 *  - 그 외엔 pos-1 번째 노드 뒤에 끼워 넣는다. */
int insertAt(LinkedList* L, int pos, int item)
{
	if (pos <= 0) { insertFirst(L, item); return 1; }
	if (pos >= L->count) { insertLast(L, item); return 1; }

	LLNode* prev = L->head;
	for (int i = 0; i < pos - 1; i++) prev = prev->next;  /* 삽입 위치 직전 노드 */
	LLNode* newNode = (LLNode*)malloc(sizeof(LLNode));
	newNode->data = item;
	newNode->next = prev->next;             /* 새 노드가 다음 노드를 가리키고 */
	prev->next = newNode;                   /* 직전 노드가 새 노드를 가리킨다 */
	L->count++;
	return 1;
}

/* 값이 item인 첫 번째 노드 삭제. 성공 1, 없으면 0.
 * prev(직전 노드)를 추적하며 찾고, 링크를 건너뛰게 연결한 뒤 free. */
int deleteValue(LinkedList* L, int item)
{
	LLNode* cur = L->head;
	LLNode* prev = NULL;
	while (cur != NULL) {
		if (cur->data == item) {
			if (prev == NULL) L->head = cur->next;   /* 머리 노드 삭제 */
			else prev->next = cur->next;             /* 중간/끝 노드 삭제 */
			free(cur);
			L->count--;
			return 1;
		}
		prev = cur;
		cur = cur->next;
	}
	return 0;                               /* 못 찾음 */
}

/* 값 item의 인덱스(0-based) 반환. 없으면 -1. */
int searchList(LinkedList* L, int item)
{
	int i = 0;
	for (LLNode* c = L->head; c != NULL; c = c->next, i++)
		if (c->data == item) return i;
	return -1;
}

/* 리스트를 역순으로 뒤집기 (포인터 방향을 하나씩 거꾸로) */
void reverseList(LinkedList* L)
{
	LLNode* prev = NULL;
	LLNode* cur = L->head;
	while (cur != NULL) {
		LLNode* next = cur->next;   /* 다음 노드 백업 */
		cur->next = prev;           /* 방향 뒤집기 */
		prev = cur;                 /* 한 칸 전진 */
		cur = next;
	}
	L->head = prev;                 /* 마지막 노드가 새 머리 */
}

/* 현재 길이 반환 */
int listLength(LinkedList* L)
{
	return L->count;
}

/* 전체 출력. log가 NULL이 아니면 파일에도 기록. */
void printList(LinkedList* L, FILE* log)
{
	dualPrintf(log, " List: [");
	for (LLNode* c = L->head; c != NULL; c = c->next)
		dualPrintf(log, "%d ", c->data);
	dualPrintf(log, "]\n");
}

/* 리스트의 모든 노드와 리스트 자체를 해제 */
void freeList(LinkedList* L)
{
	LLNode* p = L->head;
	while (p != NULL) {
		LLNode* next = p->next;
		free(p);
		p = next;
	}
	free(L);
}
