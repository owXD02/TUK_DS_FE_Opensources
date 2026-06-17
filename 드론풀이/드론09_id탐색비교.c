/*=====================================================================
 * 드론 9. id로 드론 검색: 순차 탐색 vs 이진 탐색 - 조립 풀이
 *  요구: 특정 id의 드론을 순차/이진 탐색으로 각각 찾는다.
 *  사용 라이브러리: drone(findDroneById=순차, binarySearchDroneId=이진, 정렬)
 *  핵심: 이진 탐색은 'id 오름차순 정렬'이 되어 있어야 한다!
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "drone.h"

int main(void) {
	initRandom();
	createDroneListFile("drone_list.txt", 10, 99, 99, 100);
	Drone fleet[20];
	int n = readDrones("drone_list.txt", fleet, 20);

	int target = fleet[n / 2].id;     /* 존재하는 id 하나를 목표로 */

	/* 순차 탐색: 정렬 불필요. 앞에서부터 하나씩 비교 */
	int seqIdx = findDroneById(fleet, n, target);

	/* 이진 탐색: 반드시 id 오름차순 정렬 후 사용 */
	sortDronesBy(fleet, n, 'i', 1);
	int binIdx = binarySearchDroneId(fleet, n, target);

	printf("id %d 검색\n", target);
	printf(" 순차 탐색: %s\n", seqIdx >= 0 ? "발견" : "없음");
	printf(" 이진 탐색: %s", binIdx >= 0 ? "발견" : "없음");
	if (binIdx >= 0)
		printf(" -> 위치(%d,%d) 배터리 %d", fleet[binIdx].x, fleet[binIdx].y, fleet[binIdx].battery);
	printf("\n");
	return 0;
}
