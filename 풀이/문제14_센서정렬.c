/*=====================================================================
 * 문제 14. 센서 측정값 정렬 - 단계별 출력 (선택/삽입/버블) - 조립 풀이
 *  사용 라이브러리: utils(난수/복사/검증), sort(선택/삽입/버블, 단계출력 옵션)
 *  직접 구현 없음 - 라이브러리 정렬 함수의 showSteps 옵션만으로 단계 출력.
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "sort.h"

int main(void) {
	initRandom();
	int origin[10], work[10];
	genRandomArray(origin, 10, -20, 50);        /* -20~50 난수 10개 (원본 보존) */
	printf("원본: "); printArray(origin, 10);

	/* selectionSort/insertionSort/bubbleSort(a, n, 오름차순?, 단계출력?, 로그) */
	printf("\n<선택 정렬 (오름차순)>\n");
	copyArray(origin, work, 10); selectionSort(work, 10, 1, 1, NULL);  /* 단계출력=1 */
	printf("\n<삽입 정렬 (오름차순)>\n");
	copyArray(origin, work, 10); insertionSort(work, 10, 1, 1, NULL);
	printf("\n<버블 정렬 (내림차순)>\n");
	copyArray(origin, work, 10); bubbleSort(work, 10, 0, 1, NULL);

	/* 검증: 세 결과가 방향에 맞게 정렬됐는지 (선택/삽입=오름, 버블=내림) */
	int s1[10], s2[10], s3[10];
	copyArray(origin, s1, 10); selectionSort(s1, 10, 1, 0, NULL);
	copyArray(origin, s2, 10); insertionSort(s2, 10, 1, 0, NULL);
	copyArray(origin, s3, 10); bubbleSort(s3, 10, 0, 0, NULL);
	printf("\n검증: 선택%s 삽입%s 버블%s\n",
		isSortedArray(s1, 10, 1) ? "OK" : "X",
		isSortedArray(s2, 10, 1) ? "OK" : "X",
		isSortedArray(s3, 10, 0) ? "OK" : "X");
	return 0;
}
