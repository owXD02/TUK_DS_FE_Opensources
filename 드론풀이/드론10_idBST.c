/*=====================================================================
 * 드론 10. 드론 id를 BST에 등록하고 검색 - 조립 풀이
 *  요구: 드론 id들을 이진 탐색 트리에 등록하고, 특정 id를 검색.
 *  사용 라이브러리: drone(생성/읽기), bst(BST 구성/중위순회/검색)
 *  직접 구현: id만 뽑아 배열에 담기 (작은 루프)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "drone.h"
#include "bst.h"

int main(void) {
	initRandom();
	createDroneListFile("drone_list.txt", 10, 99, 99, 100);
	Drone fleet[20];
	int n = readDrones("drone_list.txt", fleet, 20);

	/* 드론 id만 추출해 BST 구성 (조립) */
	int ids[20];
	for (int i = 0; i < n; i++) ids[i] = fleet[i].id;
	BSTNode* root = bstFromArray(ids, n);

	printf("등록된 드론 id (중위순회=오름차순): ");
	bstInorder(root, NULL);
	printf("\n");

	int target = fleet[0].id;
	printf("id %d 검색: %s\n", target, bstSearch(root, target) ? "등록됨" : "없음");
	printf("등록 대수=%d, 트리 높이=%d\n", bstCount(root), bstHeight(root));

	bstFree(root);
	return 0;
}
