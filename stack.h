/*=====================================================================
 * stack.h - 스택 2종 (정수 배열 스택 / 좌표 연결 스택)
 *---------------------------------------------------------------------
 * [무엇이 들어있나]
 *  1) IntStack : 배열 기반 정수 스택 (간단한 LIFO 문제용)
 *  2) XYStack  : 연결 리스트 기반 좌표(x,y) 스택
 *     - 중간고사 드론 문제처럼 "경로를 역순으로 출력/이동" 할 때 사용.
 *     - 파일에서 읽은 순서대로 push한 뒤 pop하면 자동으로 역순이 된다.
 *
 * [사용 예시 - IntStack]
 *  IntStack* S = createIntStack();
 *  pushInt(S, 10);  pushInt(S, 20);
 *  int v = popInt(S);          // v = 20 (나중에 넣은 것이 먼저 나옴)
 *  free(S);
 *
 * [사용 예시 - XYStack]
 *  XYStack* S = createXYStack();
 *  pushXY(S, 3, 5);
 *  Point pt;
 *  if (popXY(S, &pt)) printf("%d %d\n", pt.x, pt.y);
 *  freeXYStack(S);
 *=====================================================================*/
#pragma once
#include <stdio.h>
#include "utils.h"          /* Point 구조체 사용 */

#define STACK_SIZE 100      /* IntStack의 최대 크기. 문제 조건에 맞게 수정 */

/*---------------- 1) 정수 배열 스택 ----------------*/
typedef struct {
	int data[STACK_SIZE];
	int top;                /* 마지막으로 저장된 위치. 공백이면 -1 */
} IntStack;

IntStack* createIntStack(void);          /* 공백 스택 생성 (사용 후 free(S)) */
int  isIntStackEmpty(IntStack* S);       /* 공백이면 1 */
int  isIntStackFull(IntStack* S);        /* 포화이면 1 */
int  pushInt(IntStack* S, int item);     /* top에 삽입. 성공 1, 포화 0 */
int  popInt(IntStack* S);                /* top에서 삭제 후 반환. 공백이면 -1 */
int  peekInt(IntStack* S);               /* top 원소 확인(삭제 안 함). 공백이면 -1 */
void printIntStack(IntStack* S, FILE* log); /* 바닥부터 top까지 출력 */

/*---------------- 2) 좌표 연결 스택 ----------------*/
typedef struct XYSNode {
	Point pt;               /* 좌표 (x, y) */
	struct XYSNode* link;   /* 아래(다음) 노드 */
} XYSNode;

typedef struct {
	XYSNode* top;           /* 맨 위 노드 */
} XYStack;

XYStack* createXYStack(void);                /* 공백 좌표 스택 생성 */
int  isXYStackEmpty(XYStack* S);             /* 공백이면 1 */
void pushXY(XYStack* S, int x, int y);       /* 좌표를 top에 삽입 */
int  popXY(XYStack* S, Point* out);          /* top 좌표를 *out에 담고 삭제. 성공 1, 공백 0 */
int  peekXY(XYStack* S, Point* out);         /* top 좌표 확인만. 성공 1, 공백 0 */
void printXYStack(XYStack* S, FILE* log);    /* top부터 바닥까지 출력 */
void freeXYStack(XYStack* S);                /* 스택 전체 메모리 해제 */
