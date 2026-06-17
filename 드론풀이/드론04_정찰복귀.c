/*=====================================================================
 * 드론 4. 정찰 후 복귀: 경로 양방향 순회 - 조립 풀이
 *  요구: 경로를 출발->도착(전진) 출력 후, 도착->출발(복귀) 출력.
 *  사용 라이브러리: utils(난수/파일), xyList(이중 연결 → 양방향 순회)
 *  직접 구현 없음 - xyPrintForward / xyPrintBackward 조립.
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "xyList.h"

int main(void) {
	initRandom();

	/* 경로 8지점 생성 후 파일 저장 */
	Point path[8];
	for (int i = 0; i < 8; i++) { path[i].x = randInt(0, 9); path[i].y = randInt(0, 9); }
	writePointsToFile("drone_path.txt", path, 8);

	/* 파일 -> 좌표 리스트로 적재 */
	XYList* L = createXYList();
	xyLoadFromFile("drone_path.txt", L);

	printf("정찰 전진 (출발 -> 도착):\n");
	xyPrintForward(L, NULL);          /* head -> tail */
	printf("복귀 (도착 -> 출발):\n");
	xyPrintBackward(L, NULL);         /* tail -> head */

	freeXYList(L);
	return 0;
}
