/*=====================================================================
 * search.c - 탐색 구현부 (설명과 사용법은 search.h 참고)
 *  - 모든 함수는 cmp가 NULL이어도 안전하게 동작한다.
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "search.h"

/* 순차 탐색: 정렬 안 된 배열도 OK. 앞에서부터 하나씩 비교. */
int sequentialSearch(const int a[], int n, int key, int* cmp)
{
	int c = 0;
	for (int i = 0; i < n; i++) {
		c++;                               /* 비교 1회 */
		if (a[i] == key) { if (cmp) *cmp = c; return i; }
	}
	if (cmp) *cmp = c;
	return -1;
}

/* 정렬 순차 탐색: 오름차순 배열에서, 원소가 key보다 커지면 더 볼 필요 없어 조기 종료. */
int sequentialSearchSorted(const int a[], int n, int key, int* cmp)
{
	int c = 0;
	for (int i = 0; i < n; i++) {
		c++;
		if (a[i] == key) { if (cmp) *cmp = c; return i; }
		if (a[i] > key) break;             /* 이 뒤는 전부 key보다 크므로 중단 */
	}
	if (cmp) *cmp = c;
	return -1;
}

/* 이진 탐색(반복식): 정렬된 배열에서 가운데와 비교하며 절반씩 줄인다. */
int binarySearch(const int a[], int n, int key, int* cmp)
{
	int lo = 0, hi = n - 1, c = 0;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		c++;                               /* 비교 1회 */
		if (a[mid] == key) { if (cmp) *cmp = c; return mid; }
		else if (a[mid] < key) lo = mid + 1;   /* 오른쪽 절반 */
		else hi = mid - 1;                      /* 왼쪽 절반 */
	}
	if (cmp) *cmp = c;
	return -1;
}

/* 이진 탐색(재귀식): begin~end 구간을 재귀로 좁힌다.
 * 주의: 호출하기 전에 반드시 *cmp = 0 으로 초기화할 것! (재귀라 내부에서 못 함) */
int binarySearchRecursive(const int a[], int begin, int end, int key, int* cmp)
{
	if (begin > end) return -1;            /* 구간이 사라지면 없음 */
	int mid = (begin + end) / 2;
	if (cmp) (*cmp)++;                      /* 이번 단계의 비교 1회 누적 */
	if (a[mid] == key) return mid;
	else if (a[mid] < key) return binarySearchRecursive(a, mid + 1, end, key, cmp);
	else return binarySearchRecursive(a, begin, mid - 1, key, cmp);
}

/* 색인(점프) 탐색: 정렬된 배열을 blockSize 간격으로 나눠
 *  1) 각 블록의 첫 원소(색인)를 보며 key가 들어 있을 블록을 찾고
 *  2) 그 블록 안에서만 순차 탐색한다.
 * 큰 정렬 데이터에서 순차보다 빠르고 이진보다 단순한 절충안. */
int indexSearch(const int a[], int n, int key, int blockSize, int* cmp)
{
	int c = 0, start = 0;
	if (blockSize < 1) blockSize = 1;

	/* 1) key가 속한 블록의 시작 위치(start) 찾기 */
	for (int b = 0; b < n; b += blockSize) {
		c++;                               /* 색인값 비교 */
		if (a[b] == key) { if (cmp) *cmp = c; return b; }
		if (a[b] > key) break;             /* 직전 블록 안에 있음 */
		start = b;                         /* 후보 블록 시작 갱신 */
	}

	/* 2) start부터 블록 끝까지 순차 탐색 */
	int end = start + blockSize;
	if (end > n) end = n;
	for (int i = start; i < end; i++) {
		c++;
		if (a[i] == key) { if (cmp) *cmp = c; return i; }
	}
	if (cmp) *cmp = c;
	return -1;
}
