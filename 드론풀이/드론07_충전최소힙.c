/*=====================================================================
 * 드론 7. 배터리 가장 적은 드론부터 충전 (최소 힙) - 조립 풀이
 *  요구: 배터리가 적은 드론이 먼저 충전받도록 우선순위 큐(최소 힙) 사용.
 *  사용 라이브러리: drone(생성/읽기), heap(최소 힙 + tag로 드론 id 저장)
 *  직접 구현 없음 - heapInsertTag/heapDeleteTag 조립.
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "drone.h"
#include "heap.h"

int main(void) {
	initRandom();
	createDroneListFile("drone_list.txt", 8, 99, 99, 100);
	Drone fleet[20];
	int n = readDrones("drone_list.txt", fleet, 20);

	/* 최소 힙: 키(배터리)가 작을수록 먼저 나옴. tag에 드론 id 저장 */
	Heap* h = createHeap(1);
	for (int i = 0; i < n; i++)
		heapInsertTag(h, fleet[i].battery, fleet[i].id);

	printf("충전 우선순위 (배터리 적은 순):\n");
	while (!isHeapEmpty(h)) {
		int id;
		int bat = heapDeleteTag(h, &id);   /* bat=배터리(키), id=드론번호(tag) */
		printf(" 드론%d (배터리 %d)\n", id, bat);
	}
	free(h);
	return 0;
}
