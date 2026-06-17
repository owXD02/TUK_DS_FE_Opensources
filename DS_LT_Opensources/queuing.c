/*=====================================================================
 * queuing.c - M/M/1 큐잉 공식 구현부 (설명은 queuing.h 참고)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "queuing.h"
#include "utils.h"     /* dualPrintf 사용 */
#include <math.h>      /* pow */

/* 이용률 ρ = λ/μ. μ가 0이면 0 반환. */
double calcRho(double lambda, double mu)
{
	if (mu == 0.0) return 0.0;
	return lambda / mu;
}

/* 평균 손님 수 L = λ/(μ-λ). 불안정(μ<=λ)이면 -1. */
double calcL(double lambda, double mu)
{
	if (mu <= lambda) return -1.0;
	return lambda / (mu - lambda);
}

/* 평균 대기열 길이 Lq = ρ²/(1-ρ). 불안정이면 -1. */
double calcLq(double lambda, double mu)
{
	if (mu <= lambda) return -1.0;
	double rho = lambda / mu;
	return (rho * rho) / (1.0 - rho);
}

/* 평균 체류 시간 W = 1/(μ-λ). 불안정이면 -1. */
double calcW(double lambda, double mu)
{
	if (mu <= lambda) return -1.0;
	return 1.0 / (mu - lambda);
}

/* 평균 대기 시간 Wq = λ/(μ(μ-λ)). 불안정이면 -1. */
double calcWq(double lambda, double mu)
{
	if (mu <= lambda) return -1.0;
	return lambda / (mu * (mu - lambda));
}

/* 시스템이 빌 확률 P0 = 1 - ρ */
double calcP0(double lambda, double mu)
{
	return 1.0 - calcRho(lambda, mu);
}

/* 시스템에 n명 있을 확률 Pn = (1-ρ)ρ^n */
double calcPn(double lambda, double mu, int n)
{
	double rho = calcRho(lambda, mu);
	return (1.0 - rho) * pow(rho, n);
}

/* M/M/1 주요 지표를 한 번에 계산해 보고서로 출력.
 * log가 NULL이 아니면 파일에도 기록. 불안정(μ<=λ)이면 경고만 출력. */
void printMM1(double lambda, double mu, FILE* log)
{
	dualPrintf(log, " ===== M/M/1 큐잉 분석 (λ=%.2f, μ=%.2f) =====\n", lambda, mu);
	if (mu <= lambda) {
		dualPrintf(log, " 불안정! λ >= μ 이면 대기열이 무한정 증가합니다.\n");
		return;
	}
	double rho = calcRho(lambda, mu);
	dualPrintf(log, " 이용률 ρ = %.4f (%.2f%%)\n", rho, rho * 100.0);
	dualPrintf(log, " L  (시스템 내 평균 손님 수) = %.4f\n", calcL(lambda, mu));
	dualPrintf(log, " Lq (평균 대기열 길이)       = %.4f\n", calcLq(lambda, mu));
	dualPrintf(log, " W  (평균 체류 시간)         = %.4f\n", calcW(lambda, mu));
	dualPrintf(log, " Wq (평균 대기 시간)         = %.4f\n", calcWq(lambda, mu));
	dualPrintf(log, " P0 (시스템이 빌 확률)       = %.4f\n", calcP0(lambda, mu));
}
