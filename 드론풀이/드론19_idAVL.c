/*=====================================================================
 * 드론 19. 드론 id 순차 등록 시 AVL로 균형 유지 - 조립 풀이
 *  요구: id가 1,2,3,... 순서로 등록되면 일반 BST는 한쪽으로 쏠린다.
 *        AVL 트리로 등록하면 회전(LL/RR/LR/RL)으로 균형이 유지됨을 보인다.
 *  사용 라이브러리: avl(균형 삽입), bst(비교용 일반 BST, 높이, 레벨순회)
 *  직접 구현 없음 - avlInsert / bstInsert 조립.
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "avl.h"
#include "bst.h"

int main(void) {
	int n = 10;
	BSTNode* avl = NULL;     /* AVL 트리 */
	BSTNode* bst = NULL;     /* 비교용 일반 BST */

	/* 드론 id를 1~n 순서로 등록 (정렬된 순서 입력 = BST 최악의 경우) */
	for (int id = 1; id <= n; id++) {
		avl = avlInsert(avl, id);   /* 균형 유지 (필요 시 회전 자동) */
		bst = bstInsert(bst, id);   /* 균형 없음 → 오른쪽으로 쏠림 */
	}

	printf("드론 %d대 순차 등록(id 1~%d)\n", n, n);
	printf("일반 BST 높이 = %d  (한쪽 쏠림)\n", bstHeight(bst));
	printf("AVL 트리 높이 = %d  (회전으로 균형)\n", bstHeight(avl));
	printf("AVL 레벨 순회 : "); bstLevelOrder(avl, NULL); printf("\n");

	bstFree(avl);
	bstFree(bst);
	return 0;
}
