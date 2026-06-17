/*=====================================================================
 * 문제 16. 우편번호 정렬 (기수 정렬) - 조립 풀이
 *  사용 라이브러리: utils(난수/파일/출력), linkedQueue(0~9 버킷 10개)
 *  참고: 라이브러리 radixSort(a,n,asc)도 있으나 '자리별 중간 상태 출력'을
 *        보여줘야 하므로, 버킷(연결 큐)을 직접 돌리는 기수 정렬을 작성한다.
 *  직접 구현: 자리별 분배/수집 반복(기수 정렬 본체)과 단계 출력 (아래 주석)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "linkedQueue.h"

int main(void) {
	initRandom();
	int a[15];
	int n = 15;
	genRandomArray(a, n, 0, 99999);             /* 5자리 우편번호 15개 */
	printf("원본: "); printArray(a, n);

	/* 버킷 = 0~9 연결 큐 10개 (라이브러리 linkedQueue 조립) */
	LQueue* bucket[10];
	for (int d = 0; d < 10; d++) bucket[d] = createLQueue();

	/* ── 직접 구현: 기수 정렬 본체 ──────────────────────────────
	   factor를 1, 10, 100, 1000, 10000으로 키우며 5자리만큼 5번 반복.
	    1) 각 수의 현재 자릿수 (x/factor)%10 에 해당하는 버킷에 enqueue (분배)
	    2) 0번 버킷부터 9번까지 차례로 dequeue하여 배열에 다시 채움 (수집)
	       → 같은 자릿수는 들어온 순서가 보존되므로 '안정 정렬'이 된다
	    3) 한 자리 끝날 때마다 중간 정렬 상태 출력 */
	int step = 1;
	for (int factor = 1; factor <= 10000; factor *= 10) {
		for (int i = 0; i < n; i++) {
			int digit = (a[i] / factor) % 10;   /* 현재 자릿수 */
			enLQueue(bucket[digit], a[i]);      /* 해당 버킷에 분배 */
		}
		int idx = 0;
		for (int d = 0; d < 10; d++)            /* 0~9 버킷 순서로 수집 */
			while (!isLQEmpty(bucket[d]))
				a[idx++] = deLQueue(bucket[d]);
		printf("%d단계(자리 %5d): ", step++, factor); printArray(a, n);
	}

	writeArrayToFile("zipcode_sorted.txt", a, n);   /* 최종 결과 저장 */
	for (int d = 0; d < 10; d++) freeLQueue(bucket[d]);
	return 0;
}
