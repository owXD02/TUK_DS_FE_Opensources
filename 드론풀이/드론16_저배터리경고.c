/*=====================================================================
 * 드론 16. 저배터리 경고 필터 + 파일 기록 - 조립 풀이
 *  요구: 배터리가 임계값 이하인 드론을 찾아 화면과 파일에 경고.
 *  사용 라이브러리: drone(생성/읽기), utils(dualPrintf=화면+파일 동시)
 *  직접 구현: 임계값 비교 필터 (작은 루프)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "drone.h"

int main(void) {
	initRandom();
	createDroneListFile("drone_list.txt", 12, 99, 99, 100);
	Drone fleet[20];
	int n = readDrones("drone_list.txt", fleet, 20);

	int threshold = 30;
	FILE* warn = fopen("low_battery.txt", "w");

	/* ── 직접 구현: 임계값 이하 필터 ──
	   배터리 <= threshold 인 드론을 화면과 low_battery.txt에 동시에 경고 */
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (fleet[i].battery <= threshold) {
			dualPrintf(warn, "경고! 드론%d 배터리 %d (임계 %d 이하)\n",
				fleet[i].id, fleet[i].battery, threshold);
			cnt++;
		}
	}
	if (cnt == 0) dualPrintf(warn, "저배터리 드론 없음\n");
	if (warn) fclose(warn);

	printf("\n저배터리 드론 %d대 (기록: low_battery.txt)\n", cnt);
	return 0;
}
