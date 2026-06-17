/*=====================================================================
 * 문제 20. 작업 스케줄러 (힙 + 큐 + 파일) - 조립 풀이
 *  작업 = (작업ID, 우선순위, 소요시간) 3값 → 병렬 배열로 보관
 *  사용 라이브러리: utils(난수), heap(최대 힙 + tag로 작업 인덱스 저장)
 *  직접 구현: 3값 파일 입출력, 같은 우선순위 FIFO용 복합 키, 완료 시각 누적
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "heap.h"

#define M 8

int main(void) {
	initRandom();

	/* (1) tasks.txt에서 (작업ID 우선순위 소요시간) 읽기. 없으면 생성.
	   값이 3개라 라이브러리 파일함수(1~2값)로는 안 맞아 직접 fscanf 사용. */
	int id[M], prio[M], dur[M];
	int n = 0;
	FILE* fp = fopen("tasks.txt", "r");
	if (fp) {
		while (n < M && fscanf(fp, "%d %d %d", &id[n], &prio[n], &dur[n]) == 3) n++;
		fclose(fp);
	}
	if (n == 0) {                              /* 파일 없으면 난수 생성 후 저장 */
		n = M;
		fp = fopen("tasks.txt", "w");
		for (int i = 0; i < n; i++) {
			id[i] = i + 1;
			prio[i] = randInt(1, 5);           /* 우선순위 1~5 (클수록 먼저) */
			dur[i] = randInt(1, 9);            /* 소요시간 1~9 */
			fprintf(fp, "%d %d %d\n", id[i], prio[i], dur[i]);
		}
		fclose(fp);
	}

	/* (2)(3) ── 직접 구현: 복합 키 설계 ──────────────────────────
	   우선순위 높은 작업 먼저(최대 힙). 같은 우선순위면 먼저 도착(인덱스 작은) 순.
	     key = 우선순위 * 1000 - 도착인덱스
	   이렇게 하면
	     - 우선순위가 클수록 key가 커서 먼저 나오고(최대 힙),
	     - 같은 우선순위면 인덱스가 작을수록 key가 커서 먼저 나온다(FIFO).
	   tag에는 배열 인덱스를 저장해 원래 작업 정보(id/소요시간)를 되찾는다. */
	Heap* h = createHeap(0);                   /* 최대 힙 */
	for (int i = 0; i < n; i++)
		heapInsertTag(h, prio[i] * 1000 - i, i);

	/* (4) 처리: 꺼낸 순서대로 완료 시각을 누적해 schedule.txt에 기록 */
	FILE* out = fopen("schedule.txt", "w");
	int clock = 0;
	dualPrintf(out, "처리 순서 (작업ID, 우선순위, 소요) -> 완료시각\n");
	while (!isHeapEmpty(h)) {
		int idx;
		heapDeleteTag(h, &idx);                /* idx = 원래 배열 위치 */
		clock += dur[idx];                     /* 이 작업이 끝나는 시각 */
		dualPrintf(out, " 작업%d (우선순위 %d, 소요 %d) -> 완료 %d\n",
			id[idx], prio[idx], dur[idx], clock);
	}
	if (out) fclose(out);
	free(h);
	return 0;
}
