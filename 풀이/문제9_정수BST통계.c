/*=====================================================================
 * 문제 9. 정수 BST의 통계 - 라이브러리 조립 풀이
 *  사용 라이브러리: utils(난수/파일), bst(BST 구성/최소·최대/레벨순회/정렬배열화)
 *  직접 구현: 'X보다 작은 노드 수' 세기 (정렬배열을 훑는 작은 루프, 주석)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "bst.h"

int main(void) {
	initRandom();
	int a[20];
	genRandomArrayUnique(a, 20, 0, 999);            /* (1) 중복 없는 난수 20개 */
	writeArrayToFile("nums.txt", a, 20);            /*     파일 저장 */
	int n = readArrayFromFile("nums.txt", a, 20);   /*     다시 읽기 */

	BSTNode* root = bstFromArray(a, n);             /* 배열 → BST (조립) */

	/* (2) 최소/최대: 전체 탐색이 아니라 트리 구조로 찾는다
	       (가장 왼쪽=최소, 가장 오른쪽=최대) */
	printf("최소=%d, 최대=%d\n", bstMin(root)->key, bstMax(root)->key);

	/* (3) 레벨 순회 (큐 사용 - 라이브러리 내부에서 처리) */
	printf("레벨 순회: "); bstLevelOrder(root, NULL); printf("\n");

	/* (4) X보다 작은 노드 수
	   ── 직접 구현 ──
	   중위 순회로 '정렬된 배열'을 얻은 뒤(라이브러리 bstToSortedArray),
	   앞에서부터 X 미만인 원소 개수를 센다. */
	int sorted[20], idx = 0;
	bstToSortedArray(root, sorted, &idx);           /* idx = 노드 수 */
	int X = 500, cnt = 0;
	for (int i = 0; i < idx; i++)
		if (sorted[i] < X) cnt++;
	printf("%d보다 작은 노드 수 = %d\n", X, cnt);

	bstFree(root);
	return 0;
}
