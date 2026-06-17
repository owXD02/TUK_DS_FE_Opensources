/*=====================================================================
 * 드론 15. 경로 총 비행 거리 계산 - 조립 풀이
 *  요구: 경로의 인접 지점 사이 거리를 모두 더해 총 비행 거리를 구한다.
 *  사용 라이브러리: utils(난수/파일), xyList(경로 큐)
 *  직접 구현: 맨해튼 거리(|dx|+|dy|) 누적 (격자 이동이라 맨해튼이 자연스러움)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "xyList.h"

int main(void) {
	initRandom();

	/* 경로 10지점 생성(0~20 격자) 후 파일 저장 */
	Point path[10];
	for (int i = 0; i < 10; i++) { path[i].x = randInt(0, 20); path[i].y = randInt(0, 20); }
	writePointsToFile("drone_path.txt", path, 10);

	XYList* L = createXYList();
	xyLoadFromFile("drone_path.txt", L);

	/* ── 직접 구현: 인접 지점 간 맨해튼 거리 합산 ──
	   리스트에서 한 지점씩 꺼내며, 직전 지점과의 |x차| + |y차|를 누적한다.
	   첫 지점은 직전이 없으므로 더하지 않는다. */
	Point prev, cur;
	int total = 0, first = 1;
	while (!isXYListEmpty(L)) {
		xyRemoveFront(L, &cur);
		if (!first) {
			int dx = cur.x - prev.x;
			int dy = cur.y - prev.y;
			if (dx < 0) dx = -dx;
			if (dy < 0) dy = -dy;
			total += dx + dy;
		}
		prev = cur;
		first = 0;
	}
	printf("총 비행 거리(맨해튼) = %d\n", total);

	freeXYList(L);
	return 0;
}
