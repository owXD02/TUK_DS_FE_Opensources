/*=====================================================================
 * 문제 12. 응급실 우선순위 진료 (힙) - 라이브러리 조립 풀이
 *  사용 라이브러리: utils(난수), heap(최소 힙 + tag로 환자번호 저장)
 *  직접 구현: '같은 위급도면 먼저 온 환자 먼저(FIFO)'를 위한 복합 키 설계
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "heap.h"

int main(void) {
	initRandom();
	int n = randInt(8, 12);                  /* 환자 수 8~12명 */
	Heap* h = createHeap(1);                 /* 최소 힙: 키가 작을수록 먼저 진료 */

	/* ── 직접 구현: 복합 키 설계 ──────────────────────────────────
	   위급도(1~5)가 1순위(작을수록 위급), 같은 위급도면 도착 순서가 빠른 사람 우선.
	     key = 위급도 * 1000 + 도착순서
	   이렇게 하면
	     - 위급도가 작을수록 key가 작아 먼저 나오고(최소 힙),
	     - 같은 위급도면 도착순서(0,1,2...)가 작은 사람이 key가 작아 먼저 나온다(FIFO).
	   (도착순서 < 1000 가정. tag에는 환자번호를 저장해 나중에 식별) */
	printf("=== 도착 환자 ===\n");
	for (int arrival = 0; arrival < n; arrival++) {
		int pid = randInt(1000, 9999);       /* 환자번호 */
		int level = randInt(1, 5);           /* 위급도 1~5 */
		int key = level * 1000 + arrival;
		heapInsertTag(h, key, pid);
		printf(" 환자%d (위급도 %d, 도착 %d번째)\n", pid, level, arrival + 1);
	}

	printf("\n=== 진료 순서 ===\n");
	while (!isHeapEmpty(h)) {
		int pid;
		int key = heapDeleteTag(h, &pid);    /* key=복합키, pid=환자번호 */
		int level = key / 1000;              /* 복합 키에서 위급도 복원 */
		printf(" 환자%d (위급도 %d)\n", pid, level);
	}
	free(h);
	return 0;
}
