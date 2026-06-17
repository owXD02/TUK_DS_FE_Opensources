/*=====================================================================
 * 드론 12. 특정 사각 영역 안의 드론 개수 세기 - 조립 풀이
 *  요구: 좌표 (x1,y1)~(x2,y2) 사각형 안에 있는 드론을 찾아 개수 출력.
 *  사용 라이브러리: drone(생성/읽기)
 *  직접 구현: 영역 포함 판정 루프 (아래 주석)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "drone.h"

int main(void) {
	initRandom();
	createDroneListFile("drone_list.txt", 12, 99, 99, 100);
	Drone fleet[20];
	int n = readDrones("drone_list.txt", fleet, 20);

	/* ── 직접 구현: 사각 영역 필터 ──
	   드론의 x가 [x1,x2], y가 [y1,y2] 범위에 모두 들면 영역 안에 있는 것. */
	int x1 = 20, y1 = 20, x2 = 80, y2 = 80, cnt = 0;
	printf("영역 [%d,%d] ~ [%d,%d] 내 드론:\n", x1, y1, x2, y2);
	for (int i = 0; i < n; i++) {
		if (fleet[i].x >= x1 && fleet[i].x <= x2 &&
			fleet[i].y >= y1 && fleet[i].y <= y2) {
			printf(" 드론%d (%d,%d)\n", fleet[i].id, fleet[i].x, fleet[i].y);
			cnt++;
		}
	}
	printf("총 %d대\n", cnt);
	return 0;
}
