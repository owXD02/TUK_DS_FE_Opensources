/*=====================================================================
 * 드론 17. 드론 x좌표를 선택/삽입/버블 정렬로 단계 출력 - 조립 풀이
 *  요구: 드론들의 x좌표를 세 가지 기본 정렬로 정렬하며 단계마다 출력.
 *  사용 라이브러리: drone(생성/읽기), sort(선택/삽입/버블 단계출력), utils
 *  직접 구현: x좌표만 배열로 추출 (작은 루프)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "drone.h"
#include "sort.h"

int main(void) {
	initRandom();
	createDroneListFile("drone_list.txt", 8, 99, 99, 100);
	Drone fleet[20];
	int n = readDrones("drone_list.txt", fleet, 20);

	/* 드론 x좌표만 추출해 정렬 대상 배열로 (원본 보존용 work 별도) */
	int xs[20], work[20];
	for (int i = 0; i < n; i++) xs[i] = fleet[i].x;
	printf("드론 x좌표: "); printArray(xs, n);

	printf("\n<선택 정렬(오름차순)>\n");
	copyArray(xs, work, n); selectionSort(work, n, 1, 1, NULL);   /* 단계출력=1 */
	printf("\n<삽입 정렬(오름차순)>\n");
	copyArray(xs, work, n); insertionSort(work, n, 1, 1, NULL);
	printf("\n<버블 정렬(오름차순)>\n");
	copyArray(xs, work, n); bubbleSort(work, n, 1, 1, NULL);
	return 0;
}
