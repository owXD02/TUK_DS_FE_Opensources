/*=====================================================================
 * arrayBT.c - 순차 자료구조 이진 트리 구현부 (설명은 arrayBT.h 참고)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS   /* VS 보안 경고 끄기 - 반드시 모든 include보다 위에! */
#include <stdlib.h>
#include "arrayBT.h"
#include "utils.h"     /* dualPrintf 사용 */

/* 모든 자리가 빈(ABT_EMPTY) 배열 이진 트리를 생성한다. */
ArrayBT* createArrayBT(void)
{
	ArrayBT* T = (ArrayBT*)malloc(sizeof(ArrayBT));
	int i;
	for (i = 0; i < ABT_SIZE; i++)
		T->data[i] = ABT_EMPTY;
	T->count = 0;
	return T;
}

/*------- 인덱스 관계 -------*/

/* 인덱스 i인 노드의 부모 인덱스를 반환한다. (루트(1)의 부모는 없음 -> 0) */
int abtParentIndex(int i)
{
	return i / 2;
}

/* 인덱스 i인 노드의 왼쪽 자식 인덱스를 반환한다. */
int abtLeftIndex(int i)
{
	return 2 * i;
}

/* 인덱스 i인 노드의 오른쪽 자식 인덱스를 반환한다. */
int abtRightIndex(int i)
{
	return 2 * i + 1;
}

/*------- 저장 / 읽기 -------*/

/* index 위치에 값을 저장한다. (유효 범위: 1 ~ ABT_SIZE-1) */
void abtSet(ArrayBT* T, int index, int value)
{
	if (index < 1 || index >= ABT_SIZE) {
		printf(" [배열 트리] 인덱스 %d는 범위(1~%d)를 벗어남!\n", index, ABT_SIZE - 1);
		return;
	}
	T->data[index] = value;
}

/* index 위치의 값을 읽는다. 빈 자리거나 범위 밖이면 ABT_EMPTY 반환. */
int abtGet(ArrayBT* T, int index)
{
	if (index < 1 || index >= ABT_SIZE) return ABT_EMPTY;
	return T->data[index];
}

/* 완전 이진 트리 모양이 되도록 다음 빈 자리(1, 2, 3, ...)에 차례로 삽입한다. */
void abtInsertCBT(ArrayBT* T, int value)
{
	if (T->count >= ABT_SIZE - 1) {
		printf(" [배열 트리] 가득 차서 %d 삽입 실패!\n", value);
		return;
	}
	T->count++;
	T->data[T->count] = value;     /* 1번부터 차례대로 = 완전 이진 트리 */
}

/*------- 순회 (재귀, 인덱스 버전) -------*/

/* 전위 순회: 자신(D) -> 왼쪽(L) -> 오른쪽(R) */
void abtPreorder(ArrayBT* T, int i, FILE* log)
{
	if (i < ABT_SIZE && T->data[i] != ABT_EMPTY) {
		dualPrintf(log, "%d ", T->data[i]);
		abtPreorder(T, abtLeftIndex(i), log);
		abtPreorder(T, abtRightIndex(i), log);
	}
}

/* 중위 순회: 왼쪽(L) -> 자신(D) -> 오른쪽(R) */
void abtInorder(ArrayBT* T, int i, FILE* log)
{
	if (i < ABT_SIZE && T->data[i] != ABT_EMPTY) {
		abtInorder(T, abtLeftIndex(i), log);
		dualPrintf(log, "%d ", T->data[i]);
		abtInorder(T, abtRightIndex(i), log);
	}
}

/* 후위 순회: 왼쪽(L) -> 오른쪽(R) -> 자신(D) */
void abtPostorder(ArrayBT* T, int i, FILE* log)
{
	if (i < ABT_SIZE && T->data[i] != ABT_EMPTY) {
		abtPostorder(T, abtLeftIndex(i), log);
		abtPostorder(T, abtRightIndex(i), log);
		dualPrintf(log, "%d ", T->data[i]);
	}
}

/* 채워진 인덱스의 값과 부모/자식 인덱스 관계를 표로 출력한다. */
void printArrayBT(ArrayBT* T, FILE* log)
{
	int i;
	dualPrintf(log, " %6s %6s %6s %8s %8s\n", "인덱스", "값", "부모", "왼자식", "오른자식");
	dualPrintf(log, " ------------------------------------------\n");
	for (i = 1; i < ABT_SIZE; i++) {
		if (T->data[i] == ABT_EMPTY) continue;          /* 빈 자리는 건너뜀 */
		dualPrintf(log, " %6d %6d %6d %8d %8d\n",
			i, T->data[i],
			abtParentIndex(i),                          /* 0이면 루트(부모 없음) */
			abtLeftIndex(i), abtRightIndex(i));
	}
}
