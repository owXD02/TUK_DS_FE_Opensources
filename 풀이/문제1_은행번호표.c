/*=====================================================================
 * 문제 1. 은행 번호표 시스템 (원형 큐) - 라이브러리 조립 풀이
 *  사용 라이브러리: utils(난수), cQueue(원형 큐)
 *  직접 구현: 번호표 발급/호출 흐름, 처리/미처리 집계 (아래 주석 참고)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "cQueue.h"

int main(void) {
	initRandom();                              /* 난수 시드 - 맨 앞 1번 */

	/* (1) 도착 고객 수를 0~50 난수로 정하고 1번부터 번호표 발급(enqueue) */
	int customers = randInt(0, 50);
	CQueue* Q = createCQueue();
	FILE* log = fopen("call_log.txt", "w");    /* (2) 호출 기록 파일 */

	printf("=== 오늘 도착 고객 수: %d명 ===\n", customers);
	for (int t = 1; t <= customers; t++)
		enCQueue(Q, t);            /* 번호표 t번 발급. 큐가 가득 차면 cQueue가 full 메시지 출력 */
	printf("발급 완료, 현재 대기: %d명\n", cqCount(Q));

	/* (2)+(4) 창구에서 한 명씩 호출(dequeue).
	   ── 직접 구현 ──────────────────────────────────────────────
	   '마감 시간'에 미처리 고객이 남는 상황을 만들기 위해, 오늘 실제로
	   처리한 인원(served)을 0~전체 사이 난수로 정한다. 전체보다 적으면
	   큐에 고객이 남아 '미처리'가 된다. (전체를 다 처리하면 미처리=0) */
	int served = (customers > 0) ? randInt(0, customers) : 0;
	int processed = 0;
	for (int i = 0; i < served; i++) {
		int no = deCQueue(Q);      /* 가장 먼저 발급된 번호부터 호출 (FIFO) */
		if (no == -1) break;       /* 큐가 비면 -1 (empty 메시지는 cQueue가 출력) */
		dualPrintf(log, " %d번 고객님 창구로 오세요\n", no);  /* 화면+파일 동시 */
		processed++;
	}
	if (log) fclose(log);

	/* (4) 처리/미처리 집계: 미처리 = 큐에 남은 인원(cqCount) */
	printf("\n=== 마감 ===\n");
	printf("처리한 고객 수      : %d명\n", processed);
	printf("미처리(대기) 고객 수 : %d명\n", cqCount(Q));
	free(Q);
	return 0;
}
