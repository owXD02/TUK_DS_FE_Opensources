/*=====================================================================
 * 드론 11. x좌표 / y좌표 기준 정렬 - 조립 풀이
 *  요구: 드론들을 x좌표 기준, 그리고 y좌표 기준으로 각각 정렬.
 *  사용 라이브러리: drone(생성/읽기/정렬/출력)
 *  직접 구현 없음 - sortDronesBy의 key 인자만 바꿔 조립.
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "drone.h"

int main(void) {
	initRandom();
	createDroneListFile("drone_list.txt", 8, 99, 99, 100);
	Drone fleet[20];
	int n = readDrones("drone_list.txt", fleet, 20);

	sortDronesBy(fleet, n, 'x', 1);   /* x좌표 오름차순 */
	printf("=== x좌표 오름차순 ===\n");
	printDrones(fleet, n, NULL);

	sortDronesBy(fleet, n, 'y', 1);   /* y좌표 오름차순 */
	printf("\n=== y좌표 오름차순 ===\n");
	printDrones(fleet, n, NULL);
	return 0;
}
