/*=====================================================================
 * sort.c - 정렬 구현부 (설명과 사용법은 sort.h 참고)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS   /* VS 보안 경고 끄기 - 반드시 모든 include보다 위에! */
#include <stdlib.h>
#include "sort.h"

/*---------------------------------------------------------------
 * 내부 도우미 (이 파일 안에서만 사용)
 *---------------------------------------------------------------*/

/* x가 y보다 "앞에 와야 하면" 1을 반환한다.
 * 오름차순이면 작은 값이 앞, 내림차순이면 큰 값이 앞. */
static int comesBefore(int x, int y, int ascending)
{
	return ascending ? (x < y) : (x > y);
}

/* 단계 출력용: "n단계 : 배열내용" 형식으로 화면(과 파일)에 출력 */
static void printStep(FILE* log, int step, const int a[], int n)
{
	int t;
	dualPrintf(log, " %2d단계 :", step);
	for (t = 0; t < n; t++)
		dualPrintf(log, "%4d", a[t]);
	dualPrintf(log, "\n");
}

/*---------------------------------------------------------------
 * 1. 선택 정렬 (Selection Sort)  -  O(n^2)
 *  : 남은 구간에서 가장 작은(큰) 값을 찾아 맨 앞과 교환을 반복
 *---------------------------------------------------------------*/
void selectionSort(int a[], int n, int ascending, int showSteps, FILE* log)
{
	int i, j, target;

	for (i = 0; i < n - 1; i++) {
		target = i;                          /* 일단 i번째를 최솟값(최댓값) 후보로 */
		for (j = i + 1; j < n; j++) {        /* 나머지 구간을 훑으며 */
			if (comesBefore(a[j], a[target], ascending))
				target = j;                  /* 더 앞에 와야 할 값을 발견하면 갱신 */
		}
		swapInt(&a[i], &a[target]);          /* 찾은 값을 i번째 자리로 교환 */
		if (showSteps) printStep(log, i + 1, a, n);
	}
}

/*---------------------------------------------------------------
 * 2. 삽입 정렬 (Insertion Sort)  -  O(n^2), 거의 정렬된 자료에 강함
 *  : i번째 원소를 앞쪽의 "정렬된 구간" 속 알맞은 위치에 끼워 넣기
 *---------------------------------------------------------------*/
void insertionSort(int a[], int n, int ascending, int showSteps, FILE* log)
{
	int i, j, temp;

	for (i = 1; i < n; i++) {
		temp = a[i];                         /* 끼워 넣을 값을 따로 보관 */
		j = i;
		/* temp가 들어갈 자리를 찾을 때까지 앞의 원소들을 한 칸씩 뒤로 민다 */
		while (j > 0 && comesBefore(temp, a[j - 1], ascending)) {
			a[j] = a[j - 1];
			j--;
		}
		a[j] = temp;                         /* 빈 자리에 temp 삽입 */
		if (showSteps) printStep(log, i, a, n);
	}
}

/*---------------------------------------------------------------
 * 3. 버블 정렬 (Bubble Sort)  -  O(n^2)
 *  : 이웃끼리 비교/교환을 반복. 한 바퀴마다 가장 큰(작은) 값이
 *    맨 뒤로 "거품처럼" 떠오른다. 교환이 없으면 조기 종료(개선판).
 *---------------------------------------------------------------*/
void bubbleSort(int a[], int n, int ascending, int showSteps, FILE* log)
{
	int i, j, swapped;

	for (i = n - 1; i > 0; i--) {            /* i = 아직 정렬 안 된 구간의 끝 */
		swapped = 0;
		for (j = 0; j < i; j++) {
			/* 뒤의 원소가 앞에 와야 하면 두 원소를 교환 */
			if (comesBefore(a[j + 1], a[j], ascending)) {
				swapInt(&a[j], &a[j + 1]);
				swapped = 1;
			}
		}
		if (showSteps) printStep(log, n - i, a, n);
		if (!swapped) break;                 /* 한 번도 교환이 없으면 이미 정렬 완료 */
	}
}

/*---------------------------------------------------------------
 * 4. 퀵 정렬 (Quick Sort)  -  평균 O(n log n)
 *  : 피벗을 기준으로 작은 쪽/큰 쪽을 나누고 각각 재귀 정렬
 *---------------------------------------------------------------*/
static void quickSortRange(int a[], int begin, int end, int ascending)
{
	int L = begin, R = end;
	int pivot = a[(begin + end) / 2];        /* 가운데 원소를 피벗으로 선택 */

	while (L <= R) {
		while (comesBefore(a[L], pivot, ascending)) L++;  /* 피벗보다 앞에 올 값은 통과 */
		while (comesBefore(pivot, a[R], ascending)) R--;  /* 피벗보다 뒤에 올 값은 통과 */
		if (L <= R) {                        /* 잘못된 쪽에 있는 두 값을 교환 */
			swapInt(&a[L], &a[R]);
			L++; R--;
		}
	}
	if (begin < R) quickSortRange(a, begin, R, ascending);  /* 왼쪽 부분 재귀 */
	if (L < end)   quickSortRange(a, L, end, ascending);    /* 오른쪽 부분 재귀 */
}

void quickSort(int a[], int n, int ascending)
{
	if (n > 1) quickSortRange(a, 0, n - 1, ascending);
}

/*---------------------------------------------------------------
 * 5. 병합 정렬 (Merge Sort)  -  O(n log n), 안정 정렬
 *  : 반으로 나눠 각각 정렬한 뒤 두 정렬된 부분을 합병
 *---------------------------------------------------------------*/
static void mergeRange(int a[], int tmp[], int m, int middle, int n, int ascending)
{
	int i = m;               /* 왼쪽 부분의 시작 */
	int j = middle + 1;      /* 오른쪽 부분의 시작 */
	int k = m;               /* tmp에 채워 넣을 위치 */
	int t;

	while (i <= middle && j <= n) {          /* 두 부분에서 앞에 올 값을 골라 담기 */
		if (comesBefore(a[j], a[i], ascending))
			tmp[k++] = a[j++];
		else
			tmp[k++] = a[i++];
	}
	while (i <= middle) tmp[k++] = a[i++];   /* 왼쪽에 남은 원소 모두 복사 */
	while (j <= n)      tmp[k++] = a[j++];   /* 오른쪽에 남은 원소 모두 복사 */

	for (t = m; t <= n; t++)                 /* 합병 결과를 원래 배열로 복사 */
		a[t] = tmp[t];
}

static void mergeSortRange(int a[], int tmp[], int m, int n, int ascending)
{
	int middle;
	if (m < n) {
		middle = (m + n) / 2;
		mergeSortRange(a, tmp, m, middle, ascending);      /* 앞쪽 절반 */
		mergeSortRange(a, tmp, middle + 1, n, ascending);  /* 뒤쪽 절반 */
		mergeRange(a, tmp, m, middle, n, ascending);       /* 두 부분 합병 */
	}
}

void mergeSort(int a[], int n, int ascending)
{
	int* tmp;
	if (n <= 1) return;
	tmp = (int*)malloc(sizeof(int) * n);     /* 합병용 임시 배열 */
	if (tmp == NULL) return;
	mergeSortRange(a, tmp, 0, n - 1, ascending);
	free(tmp);
}

/*---------------------------------------------------------------
 * 6. 셸 정렬 (Shell Sort)
 *  : 간격(interval)을 두고 부분집합별 삽입 정렬, 간격을 절반씩 축소
 *---------------------------------------------------------------*/
static void intervalSort(int a[], int begin, int end, int interval, int ascending)
{
	int i, j, item;
	for (i = begin + interval; i <= end; i += interval) {
		item = a[i];
		for (j = i - interval;
			j >= begin && comesBefore(item, a[j], ascending);
			j -= interval) {
			a[j + interval] = a[j];
		}
		a[j + interval] = item;
	}
}

void shellSort(int a[], int n, int ascending)
{
	int i, interval = n / 2;
	while (interval >= 1) {
		for (i = 0; i < interval; i++)
			intervalSort(a, i, n - 1, interval, ascending);
		interval /= 2;
	}
}

/*---------------------------------------------------------------
 * 7. 기수 정렬 (Radix Sort)  -  O(d*n), 0 이상의 정수 전용!
 *  : 1의 자리 -> 10의 자리 -> ... 순서로 자릿수별 분배/수집
 *---------------------------------------------------------------*/
void radixSort(int a[], int n, int ascending)
{
	int i, d, maxVal, factor = 1;
	int bucketCount[10];                     /* 자릿수 숫자(0~9)별 개수 */
	int* out;

	if (n <= 1) return;
	out = (int*)malloc(sizeof(int) * n);
	if (out == NULL) return;

	maxVal = a[0];                           /* 최대값의 자릿수만큼만 반복하기 위해 */
	for (i = 1; i < n; i++)
		if (a[i] > maxVal) maxVal = a[i];

	while (maxVal / factor > 0) {            /* 1, 10, 100, ... 자리 순서로 */
		for (d = 0; d < 10; d++) bucketCount[d] = 0;
		for (i = 0; i < n; i++)              /* 1) 현재 자릿수의 숫자별 개수 세기 */
			bucketCount[(a[i] / factor) % 10]++;
		for (d = 1; d < 10; d++)             /* 2) 누적 개수로 변환 (저장 위치 계산) */
			bucketCount[d] += bucketCount[d - 1];
		for (i = n - 1; i >= 0; i--)         /* 3) 뒤에서부터 안정적으로 분배 */
			out[--bucketCount[(a[i] / factor) % 10]] = a[i];
		for (i = 0; i < n; i++)              /* 4) 결과를 원래 배열로 복사 */
			a[i] = out[i];
		factor *= 10;
	}

	if (!ascending) {                        /* 내림차순이면 전체를 뒤집는다 */
		for (i = 0; i < n / 2; i++)
			swapInt(&a[i], &a[n - 1 - i]);
	}
	free(out);
}

/*---------------------------------------------------------------
 * 8. 좌표 배열 정렬 (선택 정렬 기반)
 *  : key가 'x'면 x좌표, 'y'면 y좌표 기준으로 정렬
 *---------------------------------------------------------------*/
static int pointKey(const Point* p, char key)
{
	return (key == 'y') ? p->y : p->x;       /* 'y'가 아니면 x 기준 */
}

void sortPointsBy(Point p[], int n, char key, int ascending)
{
	int i, j, target;
	Point temp;

	for (i = 0; i < n - 1; i++) {
		target = i;
		for (j = i + 1; j < n; j++) {
			if (comesBefore(pointKey(&p[j], key), pointKey(&p[target], key), ascending))
				target = j;
		}
		temp = p[i];                         /* 구조체는 통째로 대입하면 교환된다 */
		p[i] = p[target];
		p[target] = temp;
	}
}
