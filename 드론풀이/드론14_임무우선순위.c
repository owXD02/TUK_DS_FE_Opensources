/*=====================================================================
 * 드론 14. 임무 우선순위 스케줄링 (최대 힙) - 조립 풀이
 *  요구: 여러 임무를 우선순위가 높은 것부터 수행한다.
 *  사용 라이브러리: utils(난수), heap(최대 힙 + tag로 임무번호)
 *  직접 구현 없음 - heapInsertTag/heapDeleteTag 조립.
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "heap.h"

int main(void) {
	initRandom();
	int n = 8;
	Heap* h = createHeap(0);           /* 최대 힙: 우선순위 큰 임무 먼저 */

	printf("=== 임무 등록 ===\n");
	for (int i = 0; i < n; i++) {
		int missionId = i + 1;
		int prio = randInt(1, 9);      /* 우선순위 1~9 (클수록 급함) */
		heapInsertTag(h, prio, missionId);   /* key=우선순위, tag=임무번호 */
		printf(" 임무%d (우선순위 %d)\n", missionId, prio);
	}

	printf("=== 수행 순서 ===\n");
	while (!isHeapEmpty(h)) {
		int mid;
		int prio = heapDeleteTag(h, &mid);
		printf(" 임무%d 수행 (우선순위 %d)\n", mid, prio);
	}
	free(h);
	return 0;
}
