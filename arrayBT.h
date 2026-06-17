/*=====================================================================
 * arrayBT.h - 순차 자료구조 이진 트리 (1차원 배열 표현)
 *---------------------------------------------------------------------
 * [개념 요약]
 *  - 이진 트리를 포인터 없이 1차원 배열로 표현한다. (힙과 같은 방식)
 *  - 루트는 인덱스 1에 저장하고, 인덱스 i인 노드에 대해:
 *      부모        = i / 2
 *      왼쪽 자식   = 2 * i
 *      오른쪽 자식 = 2 * i + 1
 *  - 빈 자리는 ABT_EMPTY(-1)로 표시한다. (편향 트리면 배열 낭비 발생
 *    -> 이 단점을 해결한 것이 연결 자료구조 이진 트리 = bst.h)
 *
 * [사용 예시 1 - 완전 이진 트리를 차례대로 만들기]
 *  ArrayBT* T = createArrayBT();
 *  abtInsertCBT(T, 10);  abtInsertCBT(T, 20);  abtInsertCBT(T, 30);
 *  // 1번=10(루트), 2번=20(왼쪽), 3번=30(오른쪽) 순서로 채워짐
 *
 * [사용 예시 2 - 원하는 위치에 직접 저장하기]
 *  abtSet(T, 1, 'A');                      // 루트
 *  abtSet(T, abtLeftIndex(1), 'B');        // 루트의 왼쪽(인덱스 2)
 *  abtSet(T, abtRightIndex(1), 'C');       // 루트의 오른쪽(인덱스 3)
 *
 *  abtInorder(T, 1, NULL);                 // 인덱스 1(루트)부터 중위 순회
 *  printArrayBT(T, NULL);                  // 배열 상태 그대로 출력
 *  free(T);
 *=====================================================================*/
#pragma once
#include <stdio.h>

#define ABT_SIZE 128       /* 배열 크기. 인덱스 1~127 사용 = 높이 7까지 저장 가능 */
#define ABT_EMPTY -1       /* 빈 자리 표시값 (데이터로 -1을 써야 하면 다른 값으로 변경) */

typedef struct {
	int data[ABT_SIZE];    /* 노드 값 저장 배열 (인덱스 0은 사용 안 함) */
	int count;             /* abtInsertCBT로 채운 노드 개수 */
} ArrayBT;

ArrayBT* createArrayBT(void);            /* 모든 자리가 빈 트리 생성 (사용 후 free(T)) */

/*------- 인덱스 관계 (시험 단골!) -------*/
int abtParentIndex(int i);               /* 부모 인덱스 = i / 2 */
int abtLeftIndex(int i);                 /* 왼쪽 자식 인덱스 = 2 * i */
int abtRightIndex(int i);                /* 오른쪽 자식 인덱스 = 2 * i + 1 */

/*------- 저장 / 읽기 -------*/
void abtSet(ArrayBT* T, int index, int value);  /* index 위치에 값 저장 (1~ABT_SIZE-1) */
int  abtGet(ArrayBT* T, int index);             /* index 위치 값 읽기. 빈 자리/범위 밖이면 ABT_EMPTY */
void abtInsertCBT(ArrayBT* T, int value);       /* 완전 이진 트리 모양으로 다음 자리에 삽입 */

/*------- 순회 (인덱스 i를 루트로 하는 서브 트리, 보통 i=1) -------*/
void abtPreorder(ArrayBT* T, int i, FILE* log);   /* 전위: D L R */
void abtInorder(ArrayBT* T, int i, FILE* log);    /* 중위: L D R */
void abtPostorder(ArrayBT* T, int i, FILE* log);  /* 후위: L R D */

void printArrayBT(ArrayBT* T, FILE* log);  /* 채워진 인덱스와 값, 부모/자식 관계 출력 */
