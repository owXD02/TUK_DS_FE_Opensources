/*=====================================================================
 * 드론 18. 드론 착륙 대기열 (원형 큐) - 조립 풀이
 *  요구: 활주로가 1개라 드론들이 착륙 순서를 기다린다(FIFO).
 *  사용 라이브러리: utils(난수), cQueue(원형 큐)
 *  직접 구현 없음 - 원형 큐 enqueue/dequeue 조립.
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "cQueue.h"

int main(void) {
	initRandom();
	CQueue* runway = createCQueue();

	int n = randInt(5, 10);            /* 착륙 대기 드론 수 */
	printf("착륙 대기 등록: ");
	for (int id = 1; id <= n; id++) {
		enCQueue(runway, id);          /* 드론 id를 대기열에 추가 */
		printf("드론%d ", id);
	}
	printf("\n현재 대기: %d대\n", cqCount(runway));

	printf("착륙 순서(FIFO): ");
	while (!isCQEmpty(runway))          /* 먼저 온 드론부터 착륙 */
		printf("드론%d ", deCQueue(runway));
	printf("\n");

	free(runway);
	return 0;
}
