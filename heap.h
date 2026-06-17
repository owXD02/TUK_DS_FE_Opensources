/*=====================================================================
 * heap.h - 힙 (최대 힙 / 최소 힙 겸용) + 힙 정렬
 *---------------------------------------------------------------------
 * [특징]
 *  - 1차원 배열로 구현한 완전 이진 트리. 인덱스 1부터 사용(교재 방식).
 *    부모 = i/2, 왼쪽 자식 = 2i, 오른쪽 자식 = 2i+1
 *  - createHeap(0) -> 최대 힙: 삭제 시 가장 큰 값부터 나옴
 *    createHeap(1) -> 최소 힙: 삭제 시 가장 작은 값부터 나옴
 *  - 우선순위 큐가 필요한 문제(예: 배터리가 가장 적은 드론부터 충전,
 *    우선순위가 높은 임무부터 처리)에 그대로 사용하면 된다.
 *
 * [사용 예시]
 *  Heap* h = createHeap(0);            // 최대 힙
 *  heapInsert(h, 10);  heapInsert(h, 45);  heapInsert(h, 19);
 *  printHeap(h, NULL);                 // 배열 상태 출력
 *  int top = heapDelete(h);            // top = 45 (최대 힙이므로)
 *  free(h);
 *
 * [힙 정렬]
 *  heapSortArray(a, n, 1);             // 오름차순 정렬
 *  heapSortArray(a, n, 0);             // 내림차순 정렬
 *
 * [레코드 힙: "학점이 가장 높은 레코드 번호를 출력하라" 유형]
 *  키와 함께 보조 정보(레코드 번호 등)를 tag로 같이 넣고 꺼낼 수 있다.
 *  Heap* h = createHeap(0);                  // 학점 기준 최대 힙
 *  heapInsertTag(h, 382, 1);                 // 학점 3.82 -> 정수화 382, 레코드 1번
 *  heapInsertTag(h, 430, 3);                 // 학점 4.30, 레코드 3번
 *  int rec;
 *  int top = heapDeleteTag(h, &rec);         // top=430, rec=3 (최고 학점 레코드!)
 *=====================================================================*/
#pragma once
#include <stdio.h>

#define MAX_HEAP 200          /* 힙의 최대 원소 수. 문제 조건에 맞게 수정 */

typedef struct {
	int data[MAX_HEAP];       /* 키 저장 배열 (인덱스 1부터 사용) */
	int tag[MAX_HEAP];        /* 키에 딸린 보조 정보(레코드 번호 등). 안 쓰면 무시 */
	int size;                 /* 현재 원소 개수 */
	int isMin;                /* 0 = 최대 힙, 1 = 최소 힙 */
} Heap;

Heap* createHeap(int isMin);          /* 공백 힙 생성. isMin: 0=최대힙, 1=최소힙 (사용 후 free(h)) */
int  isHeapEmpty(Heap* h);            /* 공백이면 1 */
int  isHeapFull(Heap* h);             /* 포화이면 1 */
void heapInsert(Heap* h, int item);   /* 원소 삽입 (힙 조건 유지) */
int  heapDelete(Heap* h);             /* 루트(최대 or 최소) 삭제 후 반환. 공백이면 -1 */
void heapInsertTag(Heap* h, int item, int tag);  /* 키 + 보조정보(레코드 번호 등) 함께 삽입 */
int  heapDeleteTag(Heap* h, int* outTag);        /* 루트 삭제 후 키 반환, 보조정보는 *outTag에 (필요 없으면 NULL) */
int  heapPeek(Heap* h);               /* 루트 확인(삭제 안 함). 공백이면 -1 */
void printHeap(Heap* h, FILE* log);   /* 힙 배열 상태 출력 */
void heapSortArray(int a[], int n, int ascending); /* 힙을 이용해 배열 정렬 */
