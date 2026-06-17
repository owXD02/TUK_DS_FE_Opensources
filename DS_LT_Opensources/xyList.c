/*=====================================================================
 * xyList.c - 좌표 이중 연결 리스트 구현부 (설명은 xyList.h 참고)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS   /* VS 보안 경고 끄기 - 반드시 모든 include보다 위에! */
#include <stdlib.h>
#include "xyList.h"

/* 공백 상태의 좌표 리스트를 생성하여 주소를 반환한다. */
XYList* createXYList(void)
{
	XYList* L = (XYList*)malloc(sizeof(XYList));
	L->head = NULL;
	L->tail = NULL;
	L->count = 0;
	return L;
}

/* 리스트가 공백 상태인지 검사한다. */
int isXYListEmpty(XYList* L)
{
	return (L->head == NULL);
}

/* 좌표 (x, y)를 리스트 맨 뒤에 삽입한다. (큐의 enqueue에 해당) */
void xyAddRear(XYList* L, int x, int y)
{
	XYNode* newNode = (XYNode*)malloc(sizeof(XYNode));
	newNode->pt.x = x;
	newNode->pt.y = y;
	newNode->next = NULL;
	newNode->prev = L->tail;

	if (L->tail == NULL)        /* 리스트가 비어 있으면 head도 새 노드 */
		L->head = newNode;
	else                        /* 비어있지 않으면 기존 tail 뒤에 연결 */
		L->tail->next = newNode;
	L->tail = newNode;
	L->count++;
}

/* 좌표 (x, y)를 리스트 맨 앞에 삽입한다. */
void xyAddFront(XYList* L, int x, int y)
{
	XYNode* newNode = (XYNode*)malloc(sizeof(XYNode));
	newNode->pt.x = x;
	newNode->pt.y = y;
	newNode->prev = NULL;
	newNode->next = L->head;

	if (L->head == NULL)        /* 리스트가 비어 있으면 tail도 새 노드 */
		L->tail = newNode;
	else
		L->head->prev = newNode;
	L->head = newNode;
	L->count++;
}

/* 맨 앞 노드를 삭제하고 좌표를 *out에 담는다. 성공 1, 공백 0 반환. */
int xyRemoveFront(XYList* L, Point* out)
{
	XYNode* old = L->head;
	if (old == NULL) {
		printf(" [좌표 리스트 공백] 삭제 실패!\n");
		return 0;
	}
	*out = old->pt;
	L->head = old->next;
	if (L->head == NULL)        /* 마지막 노드였다면 tail도 NULL */
		L->tail = NULL;
	else
		L->head->prev = NULL;
	free(old);
	L->count--;
	return 1;
}

/* 맨 뒤 노드를 삭제하고 좌표를 *out에 담는다. 성공 1, 공백 0 반환. */
int xyRemoveRear(XYList* L, Point* out)
{
	XYNode* old = L->tail;
	if (old == NULL) {
		printf(" [좌표 리스트 공백] 삭제 실패!\n");
		return 0;
	}
	*out = old->pt;
	L->tail = old->prev;
	if (L->tail == NULL)        /* 마지막 노드였다면 head도 NULL */
		L->head = NULL;
	else
		L->tail->next = NULL;
	free(old);
	L->count--;
	return 1;
}

/* head부터 tail까지 순서대로 좌표를 출력한다. (드론 전진 경로) */
void xyPrintForward(XYList* L, FILE* log)
{
	XYNode* temp = L->head;
	while (temp != NULL) {
		dualPrintf(log, " (%3d, %3d)\n", temp->pt.x, temp->pt.y);
		temp = temp->next;
	}
}

/* tail부터 head까지 역순으로 좌표를 출력한다. (드론 복귀 경로) */
void xyPrintBackward(XYList* L, FILE* log)
{
	XYNode* temp = L->tail;
	while (temp != NULL) {
		dualPrintf(log, " (%3d, %3d)\n", temp->pt.x, temp->pt.y);
		temp = temp->prev;
	}
}

/* "x y" 형식의 파일을 읽어 리스트 맨 뒤에 차례대로 추가한다.
 * 읽은 좌표 개수를 반환하고, 파일 열기 실패 시 -1을 반환한다. */
int xyLoadFromFile(const char* filename, XYList* L)
{
	int x, y, count = 0;
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("[오류] %s 파일을 열 수 없습니다.\n", filename);
		return -1;
	}
	while (fscanf(fp, "%d %d", &x, &y) == 2) {
		xyAddRear(L, x, y);
		count++;
	}
	fclose(fp);
	return count;
}

/* 리스트 전체를 "x y" 형식으로 파일에 저장한다. 성공 1, 실패 0 반환. */
int xySaveToFile(const char* filename, XYList* L)
{
	XYNode* temp = L->head;
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("[오류] %s 파일을 열 수 없습니다.\n", filename);
		return 0;
	}
	while (temp != NULL) {
		fprintf(fp, "%d %d\n", temp->pt.x, temp->pt.y);
		temp = temp->next;
	}
	fclose(fp);
	return 1;
}

/* 리스트의 모든 노드와 리스트 자체의 메모리를 해제한다. */
void freeXYList(XYList* L)
{
	XYNode* p = L->head;
	XYNode* next;
	while (p != NULL) {
		next = p->next;
		free(p);
		p = next;
	}
	free(L);
}
