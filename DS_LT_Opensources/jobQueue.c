/*=====================================================================
 * jobQueue.c - 작업 큐 + 큐잉 이론 시뮬레이션 구현부 (설명은 jobQueue.h)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS   /* VS 보안 경고 끄기 - 반드시 모든 include보다 위에! */
#include <stdlib.h>
#include "jobQueue.h"
#include "utils.h"     /* randInt, dualPrintf 사용 */

/* 공백 상태의 작업 큐를 생성하여 주소를 반환한다. */
JobQueue* createJobQueue(void)
{
	JobQueue* JQ = (JobQueue*)malloc(sizeof(JobQueue));
	JQ->front = NULL;
	JQ->rear = NULL;
	JQ->count = 0;
	return JQ;
}

/* 작업 큐가 공백 상태인지 검사한다. */
int isJQEmpty(JobQueue* JQ)
{
	return (JQ->front == NULL);
}

/* 작업을 큐의 rear에 삽입한다. (먼저 도착한 작업이 먼저 처리되도록) */
void enJobQueue(JobQueue* JQ, Job job)
{
	JQNode* newNode = (JQNode*)malloc(sizeof(JQNode));
	newNode->job = job;
	newNode->link = NULL;

	if (JQ->front == NULL) {       /* 큐가 비어 있으면 front, rear 모두 새 노드 */
		JQ->front = newNode;
		JQ->rear = newNode;
	}
	else {
		JQ->rear->link = newNode;
		JQ->rear = newNode;
	}
	JQ->count++;
}

/* front의 작업을 *out에 담고 큐에서 삭제한다. 성공 1, 공백이면 0 반환. */
int deJobQueue(JobQueue* JQ, Job* out)
{
	JQNode* old = JQ->front;
	if (isJQEmpty(JQ)) return 0;

	*out = old->job;
	JQ->front = old->link;
	if (JQ->front == NULL)
		JQ->rear = NULL;
	free(old);
	JQ->count--;
	return 1;
}

/* 대기 중인 작업 목록을 출력한다. */
void printJobQueue(JobQueue* JQ, FILE* log)
{
	JQNode* temp = JQ->front;
	dualPrintf(log, " 작업 큐(%d개) : ", JQ->count);
	while (temp != NULL) {
		dualPrintf(log, "[id%d 도착%d 처리%d] ",
			temp->job.id, temp->job.arrival, temp->job.service);
		temp = temp->link;
	}
	dualPrintf(log, "\n");
}

/* 큐에 남아 있는 모든 노드와 큐 자체의 메모리를 해제한다. */
void freeJobQueue(JobQueue* JQ)
{
	JQNode* p = JQ->front;
	JQNode* next;
	while (p != NULL) {
		next = p->link;
		free(p);
		p = next;
	}
	free(JQ);
}

/*---------------------------------------------------------------
 * 큐잉 이론 시뮬레이션 (이산 시간 방식)
 *  매 시각 t마다:
 *   1) arrivalPercent% 확률로 새 작업이 도착해 큐에 들어간다.
 *   2) 처리기(CPU)가 놀고 있고 큐에 작업이 있으면 꺼내 처리를 시작한다.
 *      이때 대기 시간 = 현재 시각 - 도착 시각
 *  마지막에 평균 대기 시간 등 통계를 출력한다.
 *---------------------------------------------------------------*/
void runQueueSim(int duration, int arrivalPercent, int maxService, FILE* log)
{
	JobQueue* JQ = createJobQueue();
	Job job;
	int t;
	int nextId = 1;            /* 다음에 부여할 작업 번호 */
	int busyRemain = 0;        /* 처리기가 현재 작업을 끝내기까지 남은 시간 (0이면 놀고 있음) */
	int started = 0;           /* 처리를 시작한 작업 수 */
	int totalWait = 0;         /* 대기 시간 합계 (평균 계산용) */

	dualPrintf(log, " === 큐잉 시뮬레이션: 총 %d시간, 도착 확률 %d%%, 처리 시간 1~%d ===\n",
		duration, arrivalPercent, maxService);

	for (t = 0; t < duration; t++) {
		dualPrintf(log, " [시각 %2d] ", t);

		/* 1) 새 작업 도착 여부 결정 (난수) */
		if (randInt(1, 100) <= arrivalPercent) {
			job.id = nextId++;
			job.arrival = t;
			job.service = randInt(1, maxService);
			enJobQueue(JQ, job);
			dualPrintf(log, "작업%d 도착(처리시간 %d). ", job.id, job.service);
		}

		/* 2) 처리기가 진행 중이면 남은 시간 1 감소 */
		if (busyRemain > 0) {
			busyRemain--;
			dualPrintf(log, "처리 중(남은 시간 %d). ", busyRemain);
		}

		/* 3) 처리기가 놀고 있으면 큐에서 다음 작업을 꺼내 시작 */
		if (busyRemain == 0 && !isJQEmpty(JQ)) {
			deJobQueue(JQ, &job);
			busyRemain = job.service;
			totalWait += (t - job.arrival);     /* 큐에서 기다린 시간 누적 */
			started++;
			dualPrintf(log, "작업%d 시작(대기 %d시간). ", job.id, t - job.arrival);
		}

		dualPrintf(log, "대기 %d개\n", JQ->count);
	}

	/* === 결과 통계 === */
	dualPrintf(log, " --------------------------------------------\n");
	dualPrintf(log, " 도착한 작업    : %d개\n", nextId - 1);
	dualPrintf(log, " 처리 시작한 작업 : %d개 (남은 대기 %d개)\n", started, JQ->count);
	if (started > 0)
		dualPrintf(log, " 평균 대기 시간  : %.2f\n", (double)totalWait / started);
	freeJobQueue(JQ);
}
