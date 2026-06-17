/*=====================================================================
 * heap.c - 힙 구현부 (설명과 사용법은 heap.h 참고)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS   /* VS 보안 경고 끄기 - 반드시 모든 include보다 위에! */
#include <stdlib.h>
#include "heap.h"
#include "utils.h"     /* dualPrintf 사용 */

/* x가 y보다 우선순위가 높으면 1을 반환한다.
 * 최대 힙이면 큰 값이 우선, 최소 힙이면 작은 값이 우선. */
static int hasHigherPriority(Heap* h, int x, int y)
{
	return h->isMin ? (x < y) : (x > y);
}

/* 공백 힙을 생성한다. isMin: 0 = 최대 힙, 1 = 최소 힙 */
Heap* createHeap(int isMin)
{
	Heap* h = (Heap*)malloc(sizeof(Heap));
	h->size = 0;
	h->isMin = isMin;
	return h;
}

/* 힙이 공백 상태인지 검사한다. */
int isHeapEmpty(Heap* h)
{
	return (h->size == 0);
}

/* 힙이 포화 상태인지 검사한다. */
int isHeapFull(Heap* h)
{
	return (h->size == MAX_HEAP - 1);
}

/* 키 + 보조정보(레코드 번호 등)를 함께 삽입한다.
 * 마지막 자리에서 시작해 부모와 비교하며 올라간다. */
void heapInsertTag(Heap* h, int item, int tag)
{
	int i;
	if (isHeapFull(h)) {
		printf(" [힙 포화] %d 삽입 실패!\n", item);
		return;
	}
	i = ++(h->size);                        /* 새 원소가 들어갈 마지막 자리 */

	/* 부모(i/2)보다 우선순위가 높으면 부모를 끌어내리며 자리를 올린다 */
	while (i != 1 && hasHigherPriority(h, item, h->data[i / 2])) {
		h->data[i] = h->data[i / 2];        /* 키와 보조정보를 같이 옮긴다 */
		h->tag[i] = h->tag[i / 2];
		i /= 2;
	}
	h->data[i] = item;                      /* 최종 자리에 저장 */
	h->tag[i] = tag;
}

/* 힙에 원소를 삽입한다. (보조정보가 필요 없을 때) */
void heapInsert(Heap* h, int item)
{
	heapInsertTag(h, item, 0);
}

/* 루트(최대 힙이면 최댓값, 최소 힙이면 최솟값)를 삭제하고 키를 반환한다.
 * 루트의 보조정보는 *outTag에 담아준다 (필요 없으면 NULL 전달).
 * 마지막 원소를 루트로 올린 뒤 자식과 비교하며 내려보낸다. 공백이면 -1. */
int heapDeleteTag(Heap* h, int* outTag)
{
	int parent, child;
	int item, temp, tempTag;

	if (isHeapEmpty(h)) {
		printf(" [힙 공백] 삭제 실패!\n");
		return -1;
	}
	item = h->data[1];                      /* 반환할 루트 원소 */
	if (outTag != NULL) *outTag = h->tag[1];/* 루트의 보조정보도 같이 전달 */
	temp = h->data[h->size];                /* 마지막 원소를 빼서 */
	tempTag = h->tag[h->size];
	h->size--;
	parent = 1;                             /* 루트 자리부터 내려보낼 위치를 찾는다 */
	child = 2;

	while (child <= h->size) {
		/* 두 자식 중 우선순위가 더 높은 쪽을 고른다 */
		if (child < h->size && hasHigherPriority(h, h->data[child + 1], h->data[child]))
			child++;
		/* temp가 자식보다 우선순위가 높으면 그 자리에 정착 */
		if (!hasHigherPriority(h, h->data[child], temp)) break;
		h->data[parent] = h->data[child];   /* 자식을 끌어올리고 한 층 내려간다 */
		h->tag[parent] = h->tag[child];
		parent = child;
		child *= 2;
	}
	h->data[parent] = temp;
	h->tag[parent] = tempTag;
	return item;
}

/* 루트를 삭제하고 반환한다. (보조정보가 필요 없을 때) */
int heapDelete(Heap* h)
{
	return heapDeleteTag(h, NULL);
}

/* 루트 원소를 삭제하지 않고 확인만 한다. 공백이면 -1 반환. */
int heapPeek(Heap* h)
{
	if (isHeapEmpty(h)) {
		printf(" [힙 공백] peek 실패!\n");
		return -1;
	}
	return h->data[1];
}

/* 힙 배열의 내용을 인덱스 1번부터 순서대로 출력한다. */
void printHeap(Heap* h, FILE* log)
{
	int i;
	dualPrintf(log, " %s 힙 : ", h->isMin ? "최소" : "최대");
	for (i = 1; i <= h->size; i++)
		dualPrintf(log, "[%d] ", h->data[i]);
	dualPrintf(log, "\n");
}

/* 힙 정렬: 배열 원소를 모두 힙에 넣고 차례로 꺼내 정렬한다. O(n log n)
 * ascending=1 이면 최소 힙 사용(작은 것부터 나옴) -> 오름차순
 * ascending=0 이면 최대 힙 사용(큰 것부터 나옴)   -> 내림차순 */
void heapSortArray(int a[], int n, int ascending)
{
	Heap* h = createHeap(ascending);        /* 오름차순 = 최소 힙 */
	int i;

	if (n > MAX_HEAP - 1) {
		printf(" [힙 정렬] 원소가 너무 많습니다. MAX_HEAP을 늘려주세요!\n");
		free(h);
		return;
	}
	for (i = 0; i < n; i++)                 /* 1) 전부 힙에 삽입 */
		heapInsert(h, a[i]);
	for (i = 0; i < n; i++)                 /* 2) 우선순위 순서로 꺼내 담기 */
		a[i] = heapDelete(h);
	free(h);
}
