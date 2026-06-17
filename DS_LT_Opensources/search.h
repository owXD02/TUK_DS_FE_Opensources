/*=====================================================================
 * search.h - 탐색 (순차 / 정렬 순차 / 이진 / 색인) + 비교 횟수
 *---------------------------------------------------------------------
 * [무엇이 들어있나]
 *  - 정수 배열에서 key를 찾는 여러 탐색법. 모두 '비교 횟수'를 함께 돌려준다.
 *  - 반환값: 찾으면 인덱스(0-based), 못 찾으면 -1
 *  - cmp 인자: 비교 횟수를 담을 int 포인터. 필요 없으면 NULL 전달 가능.
 *
 * [어떤 걸 언제]
 *  - sequentialSearch       : 정렬 안 된 배열 (앞에서부터 전부 비교)
 *  - sequentialSearchSorted : 오름차순 정렬 배열 (key보다 커지면 조기 종료)
 *  - binarySearch           : 정렬된 배열, 반복(loop)식 - 가장 자주 씀
 *  - binarySearchRecursive  : 정렬된 배열, 재귀식 (호출 전 *cmp=0 으로 초기화)
 *  - indexSearch            : 정렬된 배열을 블록으로 나눠 색인 후 순차 (점프 탐색)
 *
 * [사용 예시]
 *  int a[10]; genRandomArray(a,10,0,99); quickSort(a,10,1);  // 정렬
 *  int cmp;
 *  int idx = binarySearch(a, 10, a[5], &cmp);
 *  printf("위치 %d, 비교 %d회\n", idx, cmp);
 *=====================================================================*/
#pragma once
#include <stdio.h>

int sequentialSearch(const int a[], int n, int key, int* cmp);        /* 정렬 무관, 앞에서부터 */
int sequentialSearchSorted(const int a[], int n, int key, int* cmp);  /* 오름차순 배열, 조기 종료 */
int binarySearch(const int a[], int n, int key, int* cmp);            /* 정렬 필수, 반복식 */
int binarySearchRecursive(const int a[], int begin, int end, int key, int* cmp); /* 재귀식(호출 전 *cmp=0) */
int indexSearch(const int a[], int n, int key, int blockSize, int* cmp); /* 색인(점프) 탐색, 정렬 필수 */
