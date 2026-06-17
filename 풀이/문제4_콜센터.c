/*=====================================================================
 * 문제 4. 콜센터 대기 시뮬레이션 (큐잉 이론) - 조립 + 시뮬 풀이
 *  사용 라이브러리: jobQueue(연결 큐로 전화 대기열), utils(난수)
 *  참고: 라이브러리 runQueueSim()도 있으나, 요구사항 ④ '최대 대기열 길이'를
 *        함께 구하기 위해 동일한 이산시간 시뮬레이션을 직접 작성한다.
 *  직접 구현: 아래 시뮬레이션 루프 (단계별 주석 참고)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "jobQueue.h"

int main(void) {
	initRandom();
	JobQueue* q = createJobQueue();          /* 전화 대기열 (라이브러리 연결 큐) */

	int duration = 30, arrivalPct = 40, maxService = 4;
	int nextId = 1, busy = 0;                /* busy: 상담 남은 시간(0이면 상담원 놀고 있음) */
	int arrived = 0, served = 0, totalWait = 0, maxLen = 0;

	/* ── 직접 구현: 이산시간 시뮬레이션 ──────────────────────────
	   매 시각 t마다
	    1) arrivalPct% 확률로 전화 1통 도착 → 큐에 enqueue (도착시각 기록)
	    2) 상담원이 통화 중이면 남은 시간 1 감소
	    3) 상담원이 놀고 있고 대기 전화가 있으면 dequeue하여 상담 시작
	       (이때 대기시간 = 현재시각 - 도착시각 을 누적)
	    4) 매 시각 큐 길이(q->count)의 최대값을 갱신 */
	for (int t = 0; t < duration; t++) {
		if (randInt(1, 100) <= arrivalPct) {        /* 1) 전화 도착? */
			Job call;
			call.id = nextId++;
			call.arrival = t;
			call.service = randInt(1, maxService);
			enJobQueue(q, call);
			arrived++;
		}
		if (busy > 0) busy--;                       /* 2) 상담 진행 */
		if (busy == 0 && !isJQEmpty(q)) {           /* 3) 다음 전화 상담 시작 */
			Job c;
			deJobQueue(q, &c);
			totalWait += (t - c.arrival);
			busy = c.service;
			served++;
		}
		if (q->count > maxLen) maxLen = q->count;   /* 4) 최대 대기열 길이 */
	}

	printf("① 도착한 전화 수   : %d통\n", arrived);
	printf("② 처리한 전화 수   : %d통\n", served);
	printf("③ 평균 대기 시간   : %.2f\n", served ? (double)totalWait / served : 0.0);
	printf("④ 최대 대기열 길이 : %d\n", maxLen);
	freeJobQueue(q);
	return 0;
}
