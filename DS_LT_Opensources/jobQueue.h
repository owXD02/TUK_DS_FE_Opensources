/*=====================================================================
 * jobQueue.h - 작업 큐 + 큐잉 이론 시뮬레이션
 *---------------------------------------------------------------------
 * [개념 요약]
 *  - 작업 큐(Job Queue): 처리할 작업(Job)들을 도착 순서대로 큐에 넣고
 *    먼저 온 작업부터 꺼내 처리하는 구조 (운영체제 작업 스케줄링).
 *  - 큐잉 이론(Queuing Theory): 작업이 "랜덤하게 도착"하고 처리 시간도
 *    제각각일 때, 평균 대기 시간/큐 길이 등을 분석하는 이론.
 *    -> 시험에서는 보통 난수로 도착/처리 시간을 만들어 시뮬레이션하고
 *       평균 대기 시간을 구하는 문제로 나온다. (runQueueSim이 그 표준 코드)
 *
 * [사용 예시 1 - 작업 큐 직접 다루기]
 *  JobQueue* JQ = createJobQueue();
 *  Job j = { 1, 0, 3 };            // id=1, 도착시각 0, 처리시간 3
 *  enJobQueue(JQ, j);
 *  Job out;
 *  if (deJobQueue(JQ, &out)) printf("작업 %d 처리\n", out.id);
 *  freeJobQueue(JQ);
 *
 * [사용 예시 2 - 큐잉 시뮬레이션 한 번에 돌리기]
 *  initRandom();
 *  runQueueSim(20, 50, 3, NULL);
 *  // 20단위 시간 동안, 매 시각 50% 확률로 작업 도착,
 *  // 처리 시간은 1~3 난수. 과정과 평균 대기 시간을 출력.
 *=====================================================================*/
#pragma once
#include <stdio.h>

typedef struct {           /* 작업 하나를 표현하는 구조체 */
	int id;                /* 작업 번호 */
	int arrival;           /* 도착 시각 */
	int service;           /* 처리(서비스)에 걸리는 시간 */
} Job;

typedef struct JQNode {    /* 작업 큐의 노드 */
	Job job;
	struct JQNode* link;
} JQNode;

typedef struct {           /* 연결 큐 방식의 작업 큐 */
	JQNode* front;
	JQNode* rear;
	int count;             /* 현재 대기 중인 작업 수 */
} JobQueue;

JobQueue* createJobQueue(void);              /* 공백 작업 큐 생성 */
int  isJQEmpty(JobQueue* JQ);                /* 공백이면 1 */
void enJobQueue(JobQueue* JQ, Job job);      /* 작업을 rear에 삽입 */
int  deJobQueue(JobQueue* JQ, Job* out);     /* front 작업을 *out에 담고 삭제. 성공 1, 공백 0 */
void printJobQueue(JobQueue* JQ, FILE* log); /* 대기 중인 작업 목록 출력 */
void freeJobQueue(JobQueue* JQ);             /* 큐 전체 메모리 해제 */

/* 큐잉 이론 시뮬레이션 (이산 시간 방식)
 *  duration       : 시뮬레이션할 전체 시간 (예: 20)
 *  arrivalPercent : 매 시각 작업이 도착할 확률 % (예: 50)
 *  maxService     : 작업 처리 시간의 최대값 (처리 시간 = 1~maxService 난수)
 *  log            : 과정을 기록할 파일 (필요 없으면 NULL)
 * 매 시각의 도착/처리 과정을 출력하고, 마지막에 평균 대기 시간을 보고한다.
 * 사용 전 initRandom() 호출 필수! */
void runQueueSim(int duration, int arrivalPercent, int maxService, FILE* log);
