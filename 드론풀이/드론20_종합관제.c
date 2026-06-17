/*=====================================================================
 * 드론 20. 종합 관제 시스템 (메뉴 통합) - 조립 풀이
 *  요구: 생성/정렬/검색/충전우선순위/순찰을 메뉴로 통합 운용.
 *  사용 라이브러리: drone(생성/읽기/정렬/검색/순찰), heap(충전 우선순위), utils
 *  직접 구현: 메뉴 루프 (각 기능은 라이브러리 호출로 조립)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "drone.h"
#include "heap.h"

int main(void) {
	initRandom();
	Drone fleet[30];
	int n = 0;                 /* 현재 보유 드론 수 */
	int menu;

	while (1) {
		printf("\n===== 드론 종합 관제 =====\n");
		printf(" 1. 드론 편대 생성(난수)\n");
		printf(" 2. 배터리 내림차순 정렬\n");
		printf(" 3. id로 드론 검색\n");
		printf(" 4. 충전 우선순위(배터리 적은 순)\n");
		printf(" 5. 순찰 왕복 시뮬레이션\n");
		printf(" 0. 종료\n");
		printf(" 선택 >> ");
		if (scanf("%d", &menu) != 1) { while (getchar() != '\n'); continue; }

		if (menu == 0) { printf("관제 종료\n"); break; }
		else if (menu == 1) {
			createDroneListFile("drone_list.txt", 8, 99, 99, 100);
			n = readDrones("drone_list.txt", fleet, 30);
			printf("드론 %d대 생성\n", n);
			printDrones(fleet, n, NULL);
		}
		else if (menu == 2) {
			sortDronesBy(fleet, n, 'b', 0);     /* 배터리 내림차순 */
			printDrones(fleet, n, NULL);
		}
		else if (menu == 3) {
			int id; printf("검색할 id >> ");
			if (scanf("%d", &id) == 1) {
				int idx = findDroneById(fleet, n, id);   /* 순차 탐색 */
				if (idx >= 0) printf("드론%d: 위치(%d,%d) 배터리 %d\n",
					fleet[idx].id, fleet[idx].x, fleet[idx].y, fleet[idx].battery);
				else printf("id %d 없음\n", id);
			}
		}
		else if (menu == 4) {
			Heap* h = createHeap(1);            /* 최소 힙: 배터리 적은 순 */
			for (int i = 0; i < n; i++) heapInsertTag(h, fleet[i].battery, fleet[i].id);
			printf("충전 우선순위: ");
			while (!isHeapEmpty(h)) { int id; int b = heapDeleteTag(h, &id); printf("드론%d(%d) ", id, b); }
			printf("\n");
			free(h);
		}
		else if (menu == 5) {
			createDronePathFile("drone_path.txt", 6, 9, 9);
			int remain = patrolSimulation("drone_path.txt", 30, NULL);
			printf(remain >= 0 ? "순찰 성공(남은 배터리 %d)\n" : "추락!\n", remain);
		}
		else printf("0~5 중에서 선택하세요\n");
	}
	return 0;
}
