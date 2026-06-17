/*=====================================================================
 * xyList.h - 좌표(x,y) 이중 연결 리스트 (덱/큐 겸용)
 *---------------------------------------------------------------------
 * [특징]
 *  - 중간고사 드론 경로(doubleLinkedList)의 개선판.
 *  - 양쪽 끝 삽입/삭제가 모두 가능 -> 덱(Deque)으로도, 큐로도 사용 가능.
 *  - 앞으로/뒤로 순회 가능 -> 드론 "순찰 후 왔던 길로 복귀" 문제에 최적.
 *  - 파일에서 경로를 바로 읽어오거나 저장하는 함수 포함.
 *
 * [사용 예시 - 드론 경로 왕복]
 *  XYList* path = createXYList();
 *  xyLoadFromFile("drone_path.txt", path);   // 파일에서 경로 읽기
 *  xyPrintForward(path, NULL);               // 출발 -> 도착 (전진)
 *  xyPrintBackward(path, NULL);              // 도착 -> 출발 (복귀)
 *  freeXYList(path);
 *
 * [사용 예시 - 큐처럼 사용]
 *  xyAddRear(L, 1, 2);                       // enqueue
 *  Point pt;
 *  xyRemoveFront(L, &pt);                    // dequeue
 *=====================================================================*/
#pragma once
#include <stdio.h>
#include "utils.h"          /* Point 구조체 사용 */

typedef struct XYNode {     /* 이중 연결 리스트의 노드 */
	Point pt;               /* 좌표 (x, y) */
	struct XYNode* prev;    /* 이전 노드 (왼쪽 링크) */
	struct XYNode* next;    /* 다음 노드 (오른쪽 링크) */
} XYNode;

typedef struct {            /* 머리/꼬리 포인터와 개수를 묶은 구조체 */
	XYNode* head;           /* 첫 노드 */
	XYNode* tail;           /* 마지막 노드 */
	int count;              /* 현재 노드 개수 */
} XYList;

XYList* createXYList(void);                  /* 공백 리스트 생성 */
int  isXYListEmpty(XYList* L);               /* 공백이면 1 */
void xyAddRear(XYList* L, int x, int y);     /* 맨 뒤에 삽입 (큐의 enqueue) */
void xyAddFront(XYList* L, int x, int y);    /* 맨 앞에 삽입 */
int  xyRemoveFront(XYList* L, Point* out);   /* 맨 앞 삭제, *out에 좌표. 성공 1, 공백 0 (큐의 dequeue) */
int  xyRemoveRear(XYList* L, Point* out);    /* 맨 뒤 삭제, *out에 좌표. 성공 1, 공백 0 */
void xyPrintForward(XYList* L, FILE* log);   /* head -> tail 순서로 전체 출력 */
void xyPrintBackward(XYList* L, FILE* log);  /* tail -> head 순서로 전체 출력 */
int  xyLoadFromFile(const char* filename, XYList* L); /* "x y" 형식 파일을 읽어 뒤에 추가. 읽은 개수 반환(실패 -1) */
int  xySaveToFile(const char* filename, XYList* L);   /* 리스트 전체를 "x y" 형식으로 저장. 성공 1 */
void freeXYList(XYList* L);                  /* 리스트 전체(노드 포함) 메모리 해제 */
