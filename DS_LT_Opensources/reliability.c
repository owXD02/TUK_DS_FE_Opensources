/*=====================================================================
 * reliability.c - 신뢰성/가용성 계산 구현부 (설명은 reliability.h 참고)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS   /* VS 보안 경고 끄기 - 반드시 모든 include보다 위에! */
#include "reliability.h"
#include "utils.h"     /* dualPrintf 사용 */

/* 정수 배열의 합을 구하는 내부 도우미 */
static long sumArray(const int a[], int n)
{
	long s = 0;
	for (int i = 0; i < n; i++) s += a[i];
	return s;
}

/* MTBF = 가동시간들의 평균 = 총 가동시간 / 가동 구간 수 (= 고장 횟수)
 * n이 0 이하이면 0을 반환(0으로 나누기 방지). */
double calcMTBF(const int uptimes[], int n)
{
	if (n <= 0) return 0.0;
	return (double)sumArray(uptimes, n) / n;
}

/* MTTR = 수리시간들의 평균 = 총 수리시간 / 수리 횟수 */
double calcMTTR(const int repairs[], int n)
{
	if (n <= 0) return 0.0;
	return (double)sumArray(repairs, n) / n;
}

/* 가용성 Availability = MTBF / (MTBF + MTTR)
 * 분모가 0이면 0을 반환. (1.0이면 100% 가용) */
double calcAvailability(double mtbf, double mttr)
{
	double denom = mtbf + mttr;
	if (denom == 0.0) return 0.0;
	return mtbf / denom;
}

/* 고장률 λ = 1 / MTBF (단위 시간당 평균 고장 횟수). MTBF가 0이면 0 반환. */
double calcFailureRate(double mtbf)
{
	if (mtbf == 0.0) return 0.0;
	return 1.0 / mtbf;
}

/* 수리율 μ = 1 / MTTR (단위 시간당 평균 수리 완료 횟수). MTTR이 0이면 0 반환. */
double calcRepairRate(double mttr)
{
	if (mttr == 0.0) return 0.0;
	return 1.0 / mttr;
}

/* 총 가동 시간/총 정지 시간만 알 때의 가용성 = 가동 / (가동 + 정지) */
double availabilityFromTotals(int totalUptime, int totalDowntime)
{
	int total = totalUptime + totalDowntime;
	if (total == 0) return 0.0;
	return (double)totalUptime / total;
}

/* MTBF/MTTR/가용성/고장률/수리율을 한 번에 계산해 보고서 형태로 출력한다.
 * log가 NULL이 아니면 같은 내용을 파일에도 기록한다. */
void printReliability(const int uptimes[], int upN, const int repairs[], int repN, FILE* log)
{
	double mtbf = calcMTBF(uptimes, upN);
	double mttr = calcMTTR(repairs, repN);
	double avail = calcAvailability(mtbf, mttr);

	dualPrintf(log, " ===== 신뢰성/가용성 분석 =====\n");
	dualPrintf(log, " 가동 구간 %d개 (합 %ld시간), 수리 %d회 (합 %ld시간)\n",
		upN, sumArray(uptimes, upN), repN, sumArray(repairs, repN));
	dualPrintf(log, " MTBF (평균 고장 간격) = %.2f 시간\n", mtbf);
	dualPrintf(log, " MTTR (평균 수리 시간) = %.2f 시간\n", mttr);
	dualPrintf(log, " 고장률 λ = %.5f /시간\n", calcFailureRate(mtbf));
	dualPrintf(log, " 수리율 μ = %.5f /시간\n", calcRepairRate(mttr));
	dualPrintf(log, " 가용성 Availability = %.4f (%.2f%%)\n", avail, avail * 100.0);
}
