/*=====================================================================
 * 문제 7. 이진 트리 순회 3종 (전위/중위/후위) - 라이브러리 조립 풀이
 *  사용 라이브러리: bst(makeTreeNode로 트리 구성, bstFree로 해제)
 *  직접 구현: 순회 3종을 '문자(%c)'로 출력하기 위해 직접 작성.
 *    (라이브러리 bstPreorder/Inorder/Postorder는 BST_KEY_FMT="%d "로 숫자
 *     출력하므로 문자 수식 트리에는 부적합. 로직은 라이브러리와 100% 동일)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "bst.h"

/* 전위: 자신(D) → 왼쪽(L) → 오른쪽(R) */
static void pre(BSTNode* r) { if (r) { printf("%c ", (char)r->key); pre(r->left); pre(r->right); } }
/* 중위: 왼쪽(L) → 자신(D) → 오른쪽(R) */
static void in(BSTNode* r) { if (r) { in(r->left); printf("%c ", (char)r->key); in(r->right); } }
/* 후위: 왼쪽(L) → 오른쪽(R) → 자신(D) */
static void post(BSTNode* r) { if (r) { post(r->left); post(r->right); printf("%c ", (char)r->key); } }

int main(void) {
	/* (A + B) * (C - D) 수식 트리를 makeTreeNode(라이브러리)로 구성
	            *
	          /   \
	         +     -
	        / \   / \
	       A   B C   D                                        */
	BSTNode* A = makeTreeNode('A', NULL, NULL);
	BSTNode* B = makeTreeNode('B', NULL, NULL);
	BSTNode* C = makeTreeNode('C', NULL, NULL);
	BSTNode* D = makeTreeNode('D', NULL, NULL);
	BSTNode* plus = makeTreeNode('+', A, B);
	BSTNode* minus = makeTreeNode('-', C, D);
	BSTNode* root = makeTreeNode('*', plus, minus);

	printf("전위(preorder) : "); pre(root);  printf("\n");   /* * + A B - C D */
	printf("중위(inorder)  : "); in(root);   printf("\n");   /* A + B * C - D (원식 형태) */
	printf("후위(postorder): "); post(root); printf("\n");   /* A B + C D - * */

	bstFree(root);   /* 해제는 라이브러리 재사용 (구조가 같으므로 그대로 동작) */
	return 0;
}
