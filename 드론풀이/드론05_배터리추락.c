/*=====================================================================
 * 드론 5. 배터리 소모 시뮬레이션 + 추락 지점 찾기 - 조립 풀이
 *  요구: 경로를 따라 한 지점 이동마다 배터리 1 소모. 0이 되면 그 지점에서 추락.
 *  사용 라이브러리: utils(난수/파일), xyList(경로 큐)
 *  직접 구현: 배터리 소모 루프와 추락 판정 (아래 주석)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "xyList.h"

int main(void) {
	initRandom();

	/* 경로 20지점 생성 (배터리보다 길게 만들어 추락을 유도) */
	Point path[20];
	int n = 20;
	for (int i = 0; i < n; i++) { path[i].x = randInt(0, 9); path[i].y = randInt(0, 9); }
	writePointsToFile("drone_path.txt", path, n);

	XYList* L = createXYList();
	xyLoadFromFile("drone_path.txt", L);

	/* ── 직접 구현: 비행 시뮬레이션 ──
	   배터리 12로 출발. 매 지점 도착 시 배터리가 0이면 그 지점에서 추락,
	   아니면 배터리 1 소모하고 다음 지점으로. 끝까지 가면 완주. */
	int battery = 12;
	int step = 0, crashed = 0;
	Point p;
	while (!isXYListEmpty(L)) {
		xyRemoveFront(L, &p);
		if (battery <= 0) {
			printf("배터리 소진! %d번째 지점 (%d,%d)에서 추락\n", step + 1, p.x, p.y);
			crashed = 1;
			break;
		}
		printf(" 이동 %2d: (%d,%d) [남은 배터리 %d]\n", step + 1, p.x, p.y, battery);
		battery--;
		step++;
	}
	if (!crashed) printf("완주! 남은 배터리 = %d\n", battery);

	freeXYList(L);
	return 0;
}
