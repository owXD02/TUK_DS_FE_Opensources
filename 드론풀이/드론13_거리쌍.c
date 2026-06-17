/*=====================================================================
 * 드론 13. 두 드론의 최단/최장 거리 쌍 찾기 - 조립 풀이
 *  요구: 모든 드론 쌍 중 가장 가까운 쌍과 가장 먼 쌍을 찾는다.
 *  사용 라이브러리: drone(생성/읽기)
 *  직접 구현: 모든 쌍의 거리 비교 (이중 루프, 거리 계산은 아래 주석)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "drone.h"

int main(void) {
	initRandom();
	createDroneListFile("drone_list.txt", 8, 99, 99, 100);
	Drone fleet[20];
	int n = readDrones("drone_list.txt", fleet, 20);

	/* ── 직접 구현: 최단/최장 쌍 탐색 ──
	   거리 비교만 할 거라 굳이 루트를 쓰지 않고 '거리의 제곱'으로 비교한다.
	   (제곱이 작으면 실제 거리도 작으므로 대소 비교에 문제없음, 정수 연산이라 정확) */
	long minD = 2000000000L, maxD = -1;
	int mi = 0, mj = 1, xi = 0, xj = 1;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++) {
			long dx = fleet[i].x - fleet[j].x;
			long dy = fleet[i].y - fleet[j].y;
			long d = dx * dx + dy * dy;        /* 거리의 제곱 */
			if (d < minD) { minD = d; mi = i; mj = j; }
			if (d > maxD) { maxD = d; xi = i; xj = j; }
		}

	printf("가장 가까운 쌍: 드론%d - 드론%d (거리제곱 %ld)\n", fleet[mi].id, fleet[mj].id, minD);
	printf("가장 먼 쌍   : 드론%d - 드론%d (거리제곱 %ld)\n", fleet[xi].id, fleet[xj].id, maxD);
	return 0;
}
