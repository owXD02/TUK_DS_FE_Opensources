/*=====================================================================
 * 문제 17. 정렬 + 이진 탐색 (검색 비교 횟수) - 조립 풀이
 *  사용 라이브러리: utils(난수/검증/출력), sort(quickSort)
 *  직접 구현: 비교 횟수를 세는 이진/순차 탐색
 *    (라이브러리 탐색에는 '비교 횟수 카운트' 기능이 없어 직접 작성)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "sort.h"

/* 이진 탐색 + 비교 횟수
   ── 직접 구현 ──
   정렬된 배열에서 가운데 원소와 비교하며 절반씩 줄인다.
   비교할 때마다 *cmp를 1 증가. 찾으면 인덱스, 없으면 -1 반환. */
static int binarySearchCount(int a[], int n, int key, int* cmp) {
	int lo = 0, hi = n - 1;
	*cmp = 0;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		(*cmp)++;                       /* 비교 1회 */
		if (a[mid] == key) return mid;
		else if (a[mid] < key) lo = mid + 1;   /* 오른쪽 절반 */
		else hi = mid - 1;                      /* 왼쪽 절반 */
	}
	return -1;
}

/* 순차 탐색 + 비교 횟수 (앞에서부터 하나씩 비교) */
static int seqSearchCount(int a[], int n, int key, int* cmp) {
	*cmp = 0;
	for (int i = 0; i < n; i++) {
		(*cmp)++;
		if (a[i] == key) return i;
	}
	return -1;
}

int main(void) {
	initRandom();
	int a[30];
	genRandomArray(a, 30, 0, 99);
	quickSort(a, 30, 1);                 /* 이진 탐색 전 반드시 정렬 (조립) */
	printf("정렬됨: "); printArray(a, 30);

	int key = a[randInt(0, 29)];         /* 존재하는 값 하나를 목표로 */
	int bc, sc;
	int bi = binarySearchCount(a, 30, key, &bc);
	int si = seqSearchCount(a, 30, key, &sc);

	printf("탐색 키 %d\n", key);
	printf("이진 탐색: %s (비교 %d회)\n", bi >= 0 ? "발견" : "없음", bc);
	printf("순차 탐색: %s (비교 %d회)\n", si >= 0 ? "발견" : "없음", sc);
	return 0;
}
