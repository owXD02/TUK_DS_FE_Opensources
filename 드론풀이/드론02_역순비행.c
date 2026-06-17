/*=====================================================================
 * 드론 2. 자폭 임무: 경로를 역순으로 비행 (좌표 스택) - 조립 풀이
 *  요구: 정해진 경로를 거꾸로(도착->출발) 비행.
 *  사용 라이브러리: utils(난수/파일), stack(XYStack: 좌표 스택)
 *  원리: 경로를 순서대로 push하면, pop은 LIFO라 자동으로 역순이 된다.
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "stack.h"

int main(void) {
	initRandom();

	/* 경로 8지점 난수 생성 후 파일 저장 */
	Point path[8];
	int n = 8;
	for (int i = 0; i < n; i++) { path[i].x = randInt(0, 9); path[i].y = randInt(0, 9); }
	writePointsToFile("drone_path.txt", path, n);

	printf("원래 경로(출발->도착):\n");
	for (int i = 0; i < n; i++) printf(" (%d,%d)", path[i].x, path[i].y);
	printf("\n");

	/* 좌표 스택에 순서대로 push -> pop하면 역순 */
	XYStack* s = createXYStack();
	for (int i = 0; i < n; i++) pushXY(s, path[i].x, path[i].y);

	printf("자폭(역순) 비행 경로:\n");
	Point p;
	while (!isXYStackEmpty(s)) {      /* 빌 때까지 pop = 도착 지점부터 거꾸로 */
		popXY(s, &p);
		printf(" (%d,%d)", p.x, p.y);
	}
	printf("\n");
	freeXYStack(s);
	return 0;
}
