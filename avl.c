/*=====================================================================
 * avl.c - AVL 트리 구현부 (개념 설명과 사용법은 avl.h 참고)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS   /* VS 보안 경고 끄기 - 반드시 모든 include보다 위에! */
#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

/* 균형 인수 BF를 구한다. BF = 왼쪽 서브트리 높이 - 오른쪽 서브트리 높이
 * (높이 계산은 bst.h의 bstHeight를 재사용) */
int avlGetBF(BSTNode* p)
{
	if (p == NULL) return 0;
	return bstHeight(p->left) - bstHeight(p->right);
}

/*---------------------------------------------------------------
 * 회전 연산 4종
 *  - 회전 후 서브 트리의 "새 루트"를 반환하므로,
 *    반드시 부모 링크(또는 root)에 반환값을 다시 연결해야 한다.
 *---------------------------------------------------------------*/

/* LL 회전: 왼쪽 자식의 왼쪽에 삽입되어 불균형 (오른쪽으로 한 번 회전)
 *      parent              child
 *      /                   /    \
 *    child        ->      new  parent
 *    /
 *  new                                  */
BSTNode* avlLL(BSTNode* parent)
{
	BSTNode* child = parent->left;
	parent->left = child->right;    /* child의 오른쪽 서브트리를 parent가 넘겨받고 */
	child->right = parent;          /* parent가 child의 오른쪽 자식으로 내려간다 */
	return child;                   /* child가 새 루트 */
}

/* RR 회전: 오른쪽 자식의 오른쪽에 삽입되어 불균형 (왼쪽으로 한 번 회전)
 *  parent                  child
 *      \                   /    \
 *      child      ->   parent   new
 *         \
 *         new                            */
BSTNode* avlRR(BSTNode* parent)
{
	BSTNode* child = parent->right;
	parent->right = child->left;    /* child의 왼쪽 서브트리를 parent가 넘겨받고 */
	child->left = parent;           /* parent가 child의 왼쪽 자식으로 내려간다 */
	return child;                   /* child가 새 루트 */
}

/* LR 회전: 왼쪽 자식의 오른쪽에 삽입되어 불균형
 * -> 왼쪽 자식을 먼저 RR 회전한 뒤, 자신을 LL 회전 (두 번 회전) */
BSTNode* avlLR(BSTNode* parent)
{
	parent->left = avlRR(parent->left);
	return avlLL(parent);
}

/* RL 회전: 오른쪽 자식의 왼쪽에 삽입되어 불균형
 * -> 오른쪽 자식을 먼저 LL 회전한 뒤, 자신을 RR 회전 (두 번 회전) */
BSTNode* avlRL(BSTNode* parent)
{
	parent->right = avlLL(parent->right);
	return avlRR(parent);
}

/* BF를 검사하여 불균형이면 알맞은 회전을 수행하고 (새) 루트를 반환한다. */
BSTNode* avlRebalance(BSTNode* root)
{
	int BF = avlGetBF(root);

	if (BF > 1) {                       /* 왼쪽이 더 높다 */
		if (avlGetBF(root->left) > 0)
			root = avlLL(root);         /* 왼쪽-왼쪽 -> LL 회전 */
		else
			root = avlLR(root);         /* 왼쪽-오른쪽 -> LR 회전 */
	}
	else if (BF < -1) {                 /* 오른쪽이 더 높다 */
		if (avlGetBF(root->right) < 0)
			root = avlRR(root);         /* 오른쪽-오른쪽 -> RR 회전 */
		else
			root = avlRL(root);         /* 오른쪽-왼쪽 -> RL 회전 */
	}
	return root;                        /* 균형이면 그대로 반환 */
}

/* 균형을 유지하며 key를 삽입하고 (새) 루트를 반환한다.
 * 반드시 root = avlInsert(root, key); 형태로 호출할 것!
 * (BST 방식으로 삽입한 뒤, 올라오면서 각 노드에서 균형을 검사/회복) */
BSTNode* avlInsert(BSTNode* root, int key)
{
	if (root == NULL)                   /* 빈 자리를 찾았으면 새 노드 생성 */
		return makeTreeNode(key, NULL, NULL);

	if (key < root->key) {
		root->left = avlInsert(root->left, key);
		root = avlRebalance(root);      /* 삽입 후 균형 검사 */
	}
	else if (key > root->key) {
		root->right = avlInsert(root->right, key);
		root = avlRebalance(root);      /* 삽입 후 균형 검사 */
	}
	else {
		printf(" [AVL] 이미 같은 키 %d가 있습니다!\n", key);
	}
	return root;
}
