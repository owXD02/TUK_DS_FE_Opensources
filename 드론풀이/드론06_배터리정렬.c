/*=====================================================================
 * 드론 6. 편대 명단 생성 -> 배터리 내림차순 정렬 - 조립 풀이
 *  요구: 드론 N대(id,x,y,battery)를 만들어 파일로 저장하고, 배터리 많은
 *        순으로 정렬해 출력/저장.
 *  사용 라이브러리: drone(생성/읽기/정렬/출력/저장)
 *  직접 구현 없음 - 전부 라이브러리 조립.
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "drone.h"

int main(void) {
	initRandom();

	/* 드론 10대 생성 (좌표 0~99, 배터리 0~100) -> 파일 저장 */
	createDroneListFile("drone_list.txt", 10, 99, 99, 100);

	/* 파일 읽기 */
	Drone fleet[20];
	int n = readDrones("drone_list.txt", fleet, 20);
	printf("=== 원본 명단 ===\n");
	printDrones(fleet, n, NULL);

	/* 배터리(b) 기준 내림차순(0) 정렬 */
	sortDronesBy(fleet, n, 'b', 0);
	printf("\n=== 배터리 내림차순 ===\n");
	printDrones(fleet, n, NULL);

	/* 정렬 결과 저장 */
	writeDrones("drone_sorted.txt", fleet, n);
	return 0;
}
