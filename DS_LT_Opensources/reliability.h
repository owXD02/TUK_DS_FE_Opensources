/*=====================================================================
 * reliability.h - 신뢰성 / 가용성 계산 (MTBF, MTTR, Availability)
 *---------------------------------------------------------------------
 * [개념 요약]
 *  - MTBF (Mean Time Between Failures, 평균 고장 간격)
 *      = 총 가동 시간 / 고장 횟수  = 가동시간들의 평균
 *  - MTTR (Mean Time To Repair, 평균 수리 시간)
 *      = 총 수리 시간 / 수리 횟수  = 수리시간들의 평균
 *  - Availability (가용성) = MTBF / (MTBF + MTTR)   (0~1, ×100 하면 %)
 *  - 고장률 λ = 1 / MTBF,  수리율 μ = 1 / MTTR
 *
 * [입력 형태]
 *  보통 장비가 "가동 → 고장 → 수리 → 다시 가동 …"을 반복하므로,
 *   - uptimes[]  : 각 가동 구간의 길이(시간) 배열
 *   - repairs[]  : 각 수리 구간의 길이(시간) 배열
 *  로 주어진다. (큐잉 시뮬레이션 jobQueue와 함께 쓰면 운용 분석 문제에 활용)
 *
 * [사용 예시]
 *  int up[]  = { 100, 120, 90, 110 };   // 고장 사이 가동 시간
 *  int rep[] = { 5, 8, 4 };             // 각 수리 시간
 *  double mtbf = calcMTBF(up, 4);       // 105.0
 *  double mttr = calcMTTR(rep, 3);      // 5.67
 *  double a    = calcAvailability(mtbf, mttr);   // 0.9488...
 *  printReliability(up, 4, rep, 3, NULL);        // 한 번에 보고서 출력
 *=====================================================================*/
#pragma once
#include <stdio.h>

double calcMTBF(const int uptimes[], int n);        /* 평균 고장 간격 = 가동시간 합 / n */
double calcMTTR(const int repairs[], int n);        /* 평균 수리 시간 = 수리시간 합 / n */
double calcAvailability(double mtbf, double mttr);  /* MTBF / (MTBF + MTTR) */
double calcFailureRate(double mtbf);                /* 고장률 λ = 1 / MTBF */
double calcRepairRate(double mttr);                 /* 수리율 μ = 1 / MTTR */

/* 총 가동 시간과 총 정지(수리) 시간만 알 때의 가용성 = 가동 / (가동 + 정지) */
double availabilityFromTotals(int totalUptime, int totalDowntime);

/* MTBF/MTTR/가용성/고장률/수리율을 한 번에 계산해 출력.
 * log가 NULL이 아니면 같은 내용을 파일에도 기록한다. */
void printReliability(const int uptimes[], int upN, const int repairs[], int repN, FILE* log);
