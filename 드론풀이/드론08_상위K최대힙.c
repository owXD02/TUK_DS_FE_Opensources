/*=====================================================================
 * 드론 8. 배터리 상위 K대 선발 (최대 힙) - 조립 풀이
 *  요구: 배터리가 가장 많은 K대를 골라 출격시킨다.
 *  사용 라이브러리: drone(생성/읽기), heap(최대 힙 + tag로 id)
 *  직접 구현: K번만 꺼내기 (작은 루프)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "drone.h"
#include "heap.h"

int main(void) {
	initRandom();
	createDroneListFile("drone_list.txt", 10, 99, 99, 100);
	Drone fleet[20];
	int n = readDrones("drone_list.txt", fleet, 20);

	/* 최대 힙: 키(배터리)가 클수록 먼저 나옴 */
	Heap* h = createHeap(0);
	for (int i = 0; i < n; i++)
		heapInsertTag(h, fleet[i].battery, fleet[i].id);

	int K = 3;
	printf("배터리 상위 %d대 출격:\n", K);
	for (int i = 0; i < K && !isHeapEmpty(h); i++) {   /* 최댓값부터 K번 추출 */
		int id;
		int bat = heapDeleteTag(h, &id);
		printf(" %d위: 드론%d (배터리 %d)\n", i + 1, id, bat);
	}
	free(h);
	return 0;
}
