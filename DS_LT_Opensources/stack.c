/*=====================================================================
 * stack.c - 스택 구현부 (설명은 stack.h 참고)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS   /* VS 보안 경고 끄기 - 반드시 모든 include보다 위에! */
#include <stdlib.h>
#include "stack.h"

/*---------------- 1) 정수 배열 스택 ----------------*/

/* 공백 상태의 정수 스택을 생성하여 주소를 반환한다. */
IntStack* createIntStack(void)
{
	IntStack* S = (IntStack*)malloc(sizeof(IntStack));
	S->top = -1;               /* top이 -1이면 공백 상태 */
	return S;
}

/* 스택이 공백 상태인지 검사한다. */
int isIntStackEmpty(IntStack* S)
{
	return (S->top == -1);
}

/* 스택이 포화 상태인지 검사한다. */
int isIntStackFull(IntStack* S)
{
	return (S->top == STACK_SIZE - 1);
}

/* 스택의 top에 원소를 삽입한다. 성공 시 1, 포화 상태면 0 반환. */
int pushInt(IntStack* S, int item)
{
	if (isIntStackFull(S)) {
		printf(" [스택 포화] %d 삽입 실패!\n", item);
		return 0;
	}
	S->data[++(S->top)] = item;   /* top을 한 칸 올리고 저장 */
	return 1;
}

/* 스택의 top에서 원소를 삭제하고 그 값을 반환한다. 공백이면 -1 반환. */
int popInt(IntStack* S)
{
	if (isIntStackEmpty(S)) {
		printf(" [스택 공백] 삭제 실패!\n");
		return -1;
	}
	return S->data[(S->top)--];   /* top 원소를 반환하고 top을 한 칸 내림 */
}

/* top 원소를 삭제하지 않고 확인만 한다. 공백이면 -1 반환. */
int peekInt(IntStack* S)
{
	if (isIntStackEmpty(S)) {
		printf(" [스택 공백] peek 실패!\n");
		return -1;
	}
	return S->data[S->top];
}

/* 스택을 바닥부터 top까지 출력한다. log가 NULL이 아니면 파일에도 기록. */
void printIntStack(IntStack* S, FILE* log)
{
	int i;
	dualPrintf(log, " 스택(바닥->top) : [");
	for (i = 0; i <= S->top; i++)
		dualPrintf(log, "%4d", S->data[i]);
	dualPrintf(log, " ]\n");
}

/*---------------- 2) 좌표 연결 스택 ----------------*/

/* 공백 상태의 좌표 스택을 생성하여 주소를 반환한다. */
XYStack* createXYStack(void)
{
	XYStack* S = (XYStack*)malloc(sizeof(XYStack));
	S->top = NULL;
	return S;
}

/* 좌표 스택이 공백 상태인지 검사한다. */
int isXYStackEmpty(XYStack* S)
{
	return (S->top == NULL);
}

/* 좌표 (x, y)를 스택의 top에 삽입한다. */
void pushXY(XYStack* S, int x, int y)
{
	XYSNode* newNode = (XYSNode*)malloc(sizeof(XYSNode));
	newNode->pt.x = x;
	newNode->pt.y = y;
	newNode->link = S->top;    /* 새 노드가 기존 top을 가리키게 하고 */
	S->top = newNode;          /* top을 새 노드로 변경 */
}

/* top의 좌표를 *out에 담고 노드를 삭제한다. 성공 시 1, 공백이면 0 반환.
 * 사용법: Point pt;  while (popXY(S, &pt)) { printf("%d %d\n", pt.x, pt.y); } */
int popXY(XYStack* S, Point* out)
{
	XYSNode* old = S->top;
	if (isXYStackEmpty(S)) {
		printf(" [좌표 스택 공백] 삭제 실패!\n");
		return 0;
	}
	*out = old->pt;            /* 좌표를 복사해 주고 */
	S->top = old->link;        /* top을 아래 노드로 이동 */
	free(old);                 /* 노드 메모리 해제 */
	return 1;
}

/* top의 좌표를 *out에 담기만 한다(삭제 안 함). 성공 시 1, 공백이면 0. */
int peekXY(XYStack* S, Point* out)
{
	if (isXYStackEmpty(S)) {
		printf(" [좌표 스택 공백] peek 실패!\n");
		return 0;
	}
	*out = S->top->pt;
	return 1;
}

/* 스택을 top부터 바닥까지 출력한다. log가 NULL이 아니면 파일에도 기록. */
void printXYStack(XYStack* S, FILE* log)
{
	XYSNode* temp = S->top;
	dualPrintf(log, " 좌표 스택(top->바닥) :\n");
	while (temp != NULL) {
		dualPrintf(log, "  (%d, %d)\n", temp->pt.x, temp->pt.y);
		temp = temp->link;
	}
}

/* 스택에 남아 있는 모든 노드와 스택 자체의 메모리를 해제한다. */
void freeXYStack(XYStack* S)
{
	XYSNode* p = S->top;
	XYSNode* next;
	while (p != NULL) {
		next = p->link;
		free(p);
		p = next;
	}
	free(S);
}
