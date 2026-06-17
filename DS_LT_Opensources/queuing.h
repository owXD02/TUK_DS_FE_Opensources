/*=====================================================================
 * queuing.h - 큐잉 이론 M/M/1 공식 계산 (해석적 방법)
 *---------------------------------------------------------------------
 * [개념] M/M/1 = 포아송 도착(λ), 지수 서비스(μ), 서버 1개
 *  - λ(lambda) : 도착률 (단위 시간당 평균 도착 수)
 *  - μ(mu)     : 서비스율 (단위 시간당 평균 처리 수)
 *  - 안정 조건 : λ < μ  (아니면 대기열이 무한정 길어짐 → 함수가 -1 반환)
 *
 * [공식]
 *  ρ  = λ/μ                 (이용률, 서버가 바쁠 확률)
 *  L  = λ/(μ-λ)             (시스템 내 평균 손님 수)
 *  Lq = ρ²/(1-ρ)            (대기열 평균 길이)
 *  W  = 1/(μ-λ)             (평균 체류 시간 = 대기 + 서비스)
 *  Wq = λ/(μ(μ-λ))          (평균 대기 시간)
 *  P0 = 1-ρ                 (시스템이 빌 확률)
 *  Pn = (1-ρ)ρⁿ             (시스템에 n명 있을 확률)
 *  ※ 리틀의 법칙: L = λW,  Lq = λWq
 *
 * [참고] 난수 시뮬레이션으로 평균 대기 시간을 구하려면 jobQueue의
 *        runQueueSim을 쓰고, 공식으로 바로 구하려면 이 모듈을 쓴다.
 *
 * [사용 예시]
 *  printMM1(2.0, 3.0, NULL);          // λ=2, μ=3 → ρ=0.67, L=2, W=1 ...
 *  double w = calcW(2.0, 3.0);        // 1.0
 *=====================================================================*/
#pragma once
#include <stdio.h>

double calcRho(double lambda, double mu);          /* 이용률 ρ = λ/μ */
double calcL(double lambda, double mu);            /* 평균 손님 수 L (불안정 시 -1) */
double calcLq(double lambda, double mu);           /* 평균 대기열 길이 Lq (불안정 시 -1) */
double calcW(double lambda, double mu);            /* 평균 체류 시간 W (불안정 시 -1) */
double calcWq(double lambda, double mu);           /* 평균 대기 시간 Wq (불안정 시 -1) */
double calcP0(double lambda, double mu);           /* 시스템이 빌 확률 P0 = 1-ρ */
double calcPn(double lambda, double mu, int n);    /* n명 있을 확률 Pn = (1-ρ)ρ^n */
void   printMM1(double lambda, double mu, FILE* log); /* 위 지표를 한 번에 보고서 출력 */
