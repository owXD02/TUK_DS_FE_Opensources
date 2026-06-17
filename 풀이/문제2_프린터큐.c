/*=====================================================================
 * 문제 2. 프린터 작업 대기열 (연결 큐) - 풀이 (라이브러리 조립 버전)
 *---------------------------------------------------------------------
 * 작업 = (작업번호, 페이지수) 두 값이므로, 두 값을 담는 연결 구조인
 * xyList를 '연결 큐'로 사용한다. (xyAddRear=enqueue, xyRemoveFront=dequeue)
 *  - x = 작업번호, y = 페이지수
 *  - 사용 라이브러리: utils(난수/파일), xyList(연결 큐)
 *  - 직접 짠 부분은 '대기 시간 누적'이라는 문제 고유 로직뿐.
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "xyList.h"

int main(void) {
	initRandom();                               /* 난수 시드 - 맨 앞 1번 */

	/* (1) 난수로 작업 5~10개 생성 -> jobs.txt에 "작업번호 페이지수"로 저장 */
	int n = randInt(5, 10);                     /* 작업 개수 5~10 */
	Point jobs[10];
	for (int i = 0; i < n; i++) {
		jobs[i].x = i + 1;                      /* 작업번호: 1..n */
		jobs[i].y = randInt(1, 30);            /* 페이지수: 1~30 */
	}
	writePointsToFile("jobs.txt", jobs, n);     /* "x y" = "작업번호 페이지수" 저장 */
	printf("작업 %d개 생성 -> jobs.txt 저장\n", n);

	/* (2) jobs.txt를 읽어 연결 큐(xyList)에 적재 */
	XYList* q = createXYList();
	xyLoadFromFile("jobs.txt", q);              /* "x y"를 읽어 rear에 추가 = enqueue */

	/* (2)+(3) 먼저 들어온 순서(FIFO)로 인쇄하며 대기 시간 누적 */
	printf("\n=== 인쇄 시작 (먼저 들어온 순서) ===\n");
	Point job;
	int currentTime = 0;                        /* 지금까지 흐른 시간(초) */
	int totalWait = 0;                          /* 대기 시간 합계 */
	int count = 0;

	while (!isXYListEmpty(q)) {
		xyRemoveFront(q, &job);                 /* dequeue: job.x=번호, job.y=페이지 */
		int wait = currentTime;                 /* 대기 시간 = 앞 작업들 인쇄 시간 합 */
		printf(" 작업 %2d 인쇄 (%2d페이지) - 대기 %3d초\n", job.x, job.y, wait);
		totalWait += wait;
		currentTime += job.y;                   /* 한 페이지=1초, 페이지수만큼 소요 */
		count++;
	}
	freeXYList(q);

	/* (3) 평균 대기 시간 */
	printf("\n총 작업 %d개, 전체 인쇄 시간 %d초\n", count, currentTime);
	printf("평균 대기 시간 = %.2f초\n", (double)totalWait / count);
	return 0;
}
