/*=====================================================================
 * sort.h - 정렬 모음 (선택 / 삽입 / 버블 + 퀵 / 병합 / 셸 / 기수 / 좌표 정렬)
 *---------------------------------------------------------------------
 * [핵심 3종: 선택, 삽입, 버블] - 시험 출제 예상 1순위
 *  공통 사용법: 정렬이름(배열, 개수, 오름차순여부, 단계출력여부, 로그파일)
 *
 *   selectionSort(a, n, 1, 1, NULL);  // 오름차순 + 단계 화면 출력
 *   bubbleSort(a, n, 0, 1, log);      // 내림차순 + 단계를 화면과 파일에 출력
 *   insertionSort(a, n, 1, 0, NULL);  // 오름차순, 출력 없이 조용히 정렬만
 *
 *  - ascending : 1 = 오름차순(작은 것부터), 0 = 내림차순(큰 것부터)
 *  - showSteps : 1 = 각 단계마다 배열 상태 출력, 0 = 출력 안 함
 *  - log       : 단계 출력을 기록할 파일 포인터. 필요 없으면 NULL
 *
 * [보너스 정렬] - 혹시 다른 정렬이 나올 때 대비
 *   quickSort(a, n, 1);     mergeSort(a, n, 1);
 *   shellSort(a, n, 1);     radixSort(a, n, 1);   // radix는 0 이상 정수만!
 *   (힙 정렬은 heap.h의 heapSortArray, 트리 정렬은 bst.h의 treeSortArray 참고)
 *
 * [좌표 정렬] - 드론 위치를 x 또는 y 기준으로 정렬할 때
 *   sortPointsBy(pts, n, 'x', 1);   // x좌표 기준 오름차순
 *=====================================================================*/
#pragma once
#include <stdio.h>
#include "utils.h"          /* Point, swapInt, dualPrintf 사용 */

/*------- 핵심 3종 (단계 출력/파일 기록 지원) -------*/
void selectionSort(int a[], int n, int ascending, int showSteps, FILE* log); /* 선택 정렬 */
void insertionSort(int a[], int n, int ascending, int showSteps, FILE* log); /* 삽입 정렬 */
void bubbleSort(int a[], int n, int ascending, int showSteps, FILE* log);    /* 버블 정렬(교환 없으면 조기 종료) */

/*------- 보너스 정렬 (조용히 정렬만 수행) -------*/
void quickSort(int a[], int n, int ascending);   /* 퀵 정렬 */
void mergeSort(int a[], int n, int ascending);   /* 병합 정렬 */
void shellSort(int a[], int n, int ascending);   /* 셸 정렬 */
void radixSort(int a[], int n, int ascending);   /* 기수 정렬 (0 이상의 정수 전용) */

/*------- 좌표 배열 정렬 -------*/
/* key: 'x' = x좌표 기준, 'y' = y좌표 기준 (내부적으로 선택 정렬 사용) */
void sortPointsBy(Point p[], int n, char key, int ascending);
