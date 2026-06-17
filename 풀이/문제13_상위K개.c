/*=====================================================================
 * 문제 13. 최대 히프트리로 상위 K개 뽑기 - 라이브러리 조립 풀이
 *  사용 라이브러리: utils(난수/파일), heap(최대 힙)
 *  직접 구현: K번 꺼내며 합/평균 계산 (작은 루프, 주석)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "heap.h"

int main(void) {
	initRandom();
	int a[30];
	genRandomArray(a, 30, 0, 10000);          /* 점수 30개 */
	writeArrayToFile("scores.txt", a, 30);
	int n = readArrayFromFile("scores.txt", a, 30);

	Heap* h = createHeap(0);                   /* 최대 힙 */
	for (int i = 0; i < n; i++) heapInsert(h, a[i]);   /* 전부 삽입 */

	int K;
	printf("상위 몇 명? K 입력: ");
	if (scanf("%d", &K) != 1) K = 5;           /* 입력 실패 시 기본 5 */
	if (K > n) K = n;

	/* 최댓값부터 K번 꺼내면 상위 K개 (직접 구현: 합 누적) */
	int sum = 0;
	printf("상위 %d개: ", K);
	for (int i = 0; i < K; i++) {
		int v = heapDelete(h);                 /* 매번 현재 최댓값 */
		printf("%d ", v);
		sum += v;
	}
	printf("\n평균 = %.2f\n", (double)sum / K);
	free(h);
	return 0;
}
