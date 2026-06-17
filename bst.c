/*=====================================================================
 * bst.c - 이진 (탐색) 트리 구현부 (설명과 사용법은 bst.h 참고)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS   /* VS 보안 경고 끄기 - 반드시 모든 include보다 위에! */
#include <stdlib.h>
#include "bst.h"
#include "utils.h"     /* dualPrintf 사용 */

/*---------------- 트리 만들기 ----------------*/

/* key를 데이터로 하고 좌/우 서브 트리를 연결한 노드를 생성한다.
 * BST가 아닌 임의의 이진 트리(수식 트리 등)를 직접 만들 때 사용.
 * 예) makeTreeNode('-', makeTreeNode('A',NULL,NULL), makeTreeNode('B',NULL,NULL)) */
BSTNode* makeTreeNode(int key, BSTNode* left, BSTNode* right)
{
	BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
	node->key = key;
	node->left = left;
	node->right = right;
	return node;
}

/* BST 규칙(왼쪽 < 자신 < 오른쪽)에 따라 key를 삽입하고 루트를 반환한다.
 * 반드시 root = bstInsert(root, key); 형태로 호출할 것! (빈 트리도 처리됨)
 * 중복 키는 무시한다. */
BSTNode* bstInsert(BSTNode* root, int key)
{
	if (root == NULL)                       /* 빈 자리를 찾았으면 새 노드 생성 */
		return makeTreeNode(key, NULL, NULL);

	if (key < root->key)
		root->left = bstInsert(root->left, key);    /* 작으면 왼쪽으로 */
	else if (key > root->key)
		root->right = bstInsert(root->right, key);  /* 크면 오른쪽으로 */
	else
		printf(" [BST] 이미 같은 키 %d가 있습니다!\n", key);

	return root;
}

/* 배열 a의 원소 n개를 순서대로 삽입하여 만든 BST의 루트를 반환한다. */
BSTNode* bstFromArray(const int a[], int n)
{
	BSTNode* root = NULL;
	int i;
	for (i = 0; i < n; i++)
		root = bstInsert(root, a[i]);
	return root;
}

/*---------------- 탐색 / 삭제 ----------------*/

/* key를 가진 노드를 탐색한다. 찾으면 노드 주소, 없으면 NULL 반환.
 * (탐색 성공/실패 메시지는 호출하는 쪽에서 출력하면 된다.) */
BSTNode* bstSearch(BSTNode* root, int key)
{
	BSTNode* p = root;
	while (p != NULL) {
		if (key < p->key)       p = p->left;
		else if (key > p->key)  p = p->right;
		else                    return p;   /* 발견! */
	}
	return NULL;                            /* 못 찾음 */
}

/* 최솟값 노드(가장 왼쪽 노드)를 반환한다. 공백 트리면 NULL. */
BSTNode* bstMin(BSTNode* root)
{
	if (root == NULL) return NULL;
	while (root->left != NULL) root = root->left;
	return root;
}

/* 최댓값 노드(가장 오른쪽 노드)를 반환한다. 공백 트리면 NULL. */
BSTNode* bstMax(BSTNode* root)
{
	if (root == NULL) return NULL;
	while (root->right != NULL) root = root->right;
	return root;
}

/* key를 가진 노드를 삭제하고 (새로운) 루트를 반환한다.
 * 반드시 root = bstDelete(root, key); 형태로 호출할 것!
 * 자식이 0개/1개/2개인 모든 경우를 처리한다. */
BSTNode* bstDelete(BSTNode* root, int key)
{
	BSTNode* child;
	BSTNode* succ;

	if (root == NULL) {
		printf(" [BST] 삭제할 키 %d가 트리에 없습니다!\n", key);
		return NULL;
	}

	if (key < root->key)                    /* 삭제할 노드를 찾아 내려간다 */
		root->left = bstDelete(root->left, key);
	else if (key > root->key)
		root->right = bstDelete(root->right, key);
	else {                                  /* 삭제할 노드를 찾았다 */
		if (root->left == NULL && root->right == NULL) {   /* 1) 단말 노드 */
			free(root);
			return NULL;
		}
		else if (root->left == NULL || root->right == NULL) { /* 2) 자식 1개 */
			child = (root->left != NULL) ? root->left : root->right;
			free(root);
			return child;                   /* 자식이 삭제된 자리를 이어받음 */
		}
		else {                              /* 3) 자식 2개 */
			succ = bstMin(root->right);     /* 오른쪽 서브 트리의 최솟값 = 후계자 */
			root->key = succ->key;          /* 후계자의 키를 복사하고 */
			root->right = bstDelete(root->right, succ->key); /* 후계자를 삭제 */
		}
	}
	return root;
}

/*---------------- 순회 ----------------*/

/* 전위 순회: 자신(D) -> 왼쪽(L) -> 오른쪽(R) */
void bstPreorder(BSTNode* root, FILE* log)
{
	if (root != NULL) {
		dualPrintf(log, BST_KEY_FMT, root->key);
		bstPreorder(root->left, log);
		bstPreorder(root->right, log);
	}
}

/* 중위 순회: 왼쪽(L) -> 자신(D) -> 오른쪽(R). BST면 오름차순 출력! */
void bstInorder(BSTNode* root, FILE* log)
{
	if (root != NULL) {
		bstInorder(root->left, log);
		dualPrintf(log, BST_KEY_FMT, root->key);
		bstInorder(root->right, log);
	}
}

/* 후위 순회: 왼쪽(L) -> 오른쪽(R) -> 자신(D) */
void bstPostorder(BSTNode* root, FILE* log)
{
	if (root != NULL) {
		bstPostorder(root->left, log);
		bstPostorder(root->right, log);
		dualPrintf(log, BST_KEY_FMT, root->key);
	}
}

/* 레벨 순회: 루트부터 한 층씩 왼쪽->오른쪽 순서로 방문 (큐 이용)
 * "큐와 트리를 함께 사용하라"는 복합 문제에 그대로 활용 가능. */
#define BST_LEVELQ_SIZE 1000
void bstLevelOrder(BSTNode* root, FILE* log)
{
	BSTNode* queue[BST_LEVELQ_SIZE];        /* 노드 포인터를 담는 간단한 배열 큐 */
	int front = 0, rear = 0;
	BSTNode* p;

	if (root == NULL) return;
	queue[rear++] = root;                   /* 루트를 큐에 넣고 시작 */

	while (front < rear) {                  /* 큐가 빌 때까지 반복 */
		p = queue[front++];                 /* 큐에서 하나 꺼내 방문하고 */
		dualPrintf(log, BST_KEY_FMT, p->key);
		if (p->left != NULL)  queue[rear++] = p->left;   /* 자식들을 큐에 추가 */
		if (p->right != NULL) queue[rear++] = p->right;
	}
}

/*---------------- 정보 / 활용 ----------------*/

/* 트리의 전체 노드 개수를 반환한다. */
int bstCount(BSTNode* root)
{
	if (root == NULL) return 0;
	return 1 + bstCount(root->left) + bstCount(root->right);
}

/* 트리의 높이를 반환한다. (공백 트리 = 0, 루트만 있으면 1) */
int bstHeight(BSTNode* root)
{
	int lh, rh;
	if (root == NULL) return 0;
	lh = bstHeight(root->left);
	rh = bstHeight(root->right);
	return 1 + (lh > rh ? lh : rh);
}

/* 중위 순회 순서(오름차순)로 키를 out 배열에 담는다.
 * 사용법: int idx = 0;  bstToSortedArray(root, out, &idx);  // idx = 담긴 개수 */
void bstToSortedArray(BSTNode* root, int out[], int* idx)
{
	if (root != NULL) {
		bstToSortedArray(root->left, out, idx);
		out[(*idx)++] = root->key;
		bstToSortedArray(root->right, out, idx);
	}
}

/* 트리 정렬: 배열을 BST에 모두 넣었다가 중위 순회로 꺼내 오름차순 정렬한다.
 * 주의: BST는 중복 키를 무시하므로 중복 값이 있는 배열에는 사용하지 말 것! */
void treeSortArray(int a[], int n)
{
	BSTNode* root = bstFromArray(a, n);
	int idx = 0;
	bstToSortedArray(root, a, &idx);
	bstFree(root);
}

/* 트리의 모든 노드 메모리를 해제한다. (후위 순회 순서로 해제) */
void bstFree(BSTNode* root)
{
	if (root != NULL) {
		bstFree(root->left);
		bstFree(root->right);
		free(root);
	}
}
