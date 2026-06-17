/*=====================================================================
 * 문제 11. AVL 트리의 4가지 회전 (균형 트리) - 라이브러리 조립 풀이
 *  사용 라이브러리: avl(균형 삽입 avlInsert / 균형인수 avlGetBF),
 *                   bst(비교용 일반 BST, 높이, 레벨순회)
 *  참고: LL/RR/LR/RL 회전은 avlInsert 내부(avlRebalance)에서 자동 수행된다.
 *        삽입마다 루트/BF/레벨순회를 출력해 균형이 잡히는 과정을 관찰한다.
 *        (회전 종류 자체는 라이브러리가 내부 처리 → 루트 변화로 효과 확인)
 *  직접 구현: 두 입력 시퀀스를 차례로 삽입하며 관찰 출력하는 보조 함수
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "avl.h"
#include "bst.h"

/* 한 시퀀스를 AVL과 일반 BST에 동시에 삽입하며 단계별로 관찰 출력 */
static void insertSeq(const char* title, int* keys, int n) {
	printf("\n[%s]\n", title);
	BSTNode* avl = NULL;
	BSTNode* bst = NULL;
	for (int i = 0; i < n; i++) {
		avl = avlInsert(avl, keys[i]);   /* 균형 유지 삽입 (필요 시 LL/RR/LR/RL 자동) */
		bst = bstInsert(bst, keys[i]);   /* 비교용 일반 BST 삽입 */
		printf(" %2d 삽입 -> AVL 루트=%2d, BF=%d | 레벨순회: ",
			keys[i], avl->key, avlGetBF(avl));
		bstLevelOrder(avl, NULL);
		printf("\n");
	}
	printf(" => 최종 높이: AVL=%d  vs  일반BST=%d\n", bstHeight(avl), bstHeight(bst));
	bstFree(avl);
	bstFree(bst);
}

int main(void) {
	int seq1[] = { 10, 20, 30, 40, 50, 60, 70 };   /* 오름차순 → RR 회전 연쇄 */
	int seq2[] = { 50, 30, 70, 20, 40, 10, 5 };    /* LL / LR 유발 */
	insertSeq("가) 오름차순 삽입 (RR 연쇄)", seq1, 7);
	insertSeq("나) 혼합 삽입 (LL/LR)", seq2, 7);
	return 0;
}
