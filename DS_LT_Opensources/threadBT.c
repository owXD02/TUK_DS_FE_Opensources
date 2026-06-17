/*=====================================================================
 * threadBT.c - 스레드 이진 트리 구현부 (개념/사용법은 threadBT.h 참고)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS   /* VS 보안 경고 끄기 - 반드시 모든 include보다 위에! */
#include <stdlib.h>
#include "threadBT.h"
#include "utils.h"     /* dualPrintf 사용 */

/*---------------- 직접 구성 ----------------*/

/* data를 값으로, 좌/우 링크를 연결한 노드를 생성한다.
 * isThreadRight: 1이면 right가 스레드(후속자), 0이면 실제 오른쪽 자식.
 * (수식 트리 등 모양을 직접 만들 때 사용) */
ThreadNode* makeThreadNode(int data, ThreadNode* left, ThreadNode* right, int isThreadRight)
{
	ThreadNode* node = (ThreadNode*)malloc(sizeof(ThreadNode));
	node->data = data;
	node->left = left;
	node->right = right;
	node->isThreadRight = isThreadRight;
	return node;
}

/*---------------- 중위 후속자 / 순회 ----------------*/

/* p의 중위 후속자(inorder successor) 노드를 반환한다.
 *  - p->right가 스레드면 그 스레드가 곧 후속자 (NULL이면 마지막 노드).
 *  - p->right가 실제 자식이면, 그 오른쪽 서브 트리의 가장 왼쪽 노드가 후속자. */
ThreadNode* findSuccessor(ThreadNode* p)
{
	ThreadNode* q = p->right;
	if (q == NULL || p->isThreadRight)   /* 스레드(또는 끝)면 바로 반환 */
		return q;
	while (q->left != NULL)               /* 실제 자식이면 오른쪽 서브트리의 최좌단 */
		q = q->left;
	return q;
}

/* 스레드를 이용해 스택/재귀 없이 중위 순회한다.
 * log가 NULL이 아니면 같은 내용을 파일에도 기록한다. */
void threadInorder(ThreadNode* root, FILE* log)
{
	ThreadNode* q = root;
	if (q == NULL) return;

	while (q->left != NULL)               /* 1) 가장 왼쪽(첫 중위 노드)으로 이동 */
		q = q->left;

	while (q != NULL) {                   /* 2) 후속자를 따라가며 출력 */
		dualPrintf(log, TH_DATA_FMT, q->data);
		q = findSuccessor(q);
	}
	dualPrintf(log, "\n");
}

/*---------------- BST로 자동 구성 ----------------*/

/* 일반 이진 탐색 트리 규칙(왼쪽<자신<오른쪽)으로 key를 삽입한다.
 * 스레딩은 makeThreads에서 별도로 한다. root = threadInsert(root, key); 형태로 호출. */
ThreadNode* threadInsert(ThreadNode* root, int key)
{
	if (root == NULL)
		return makeThreadNode(key, NULL, NULL, 0);

	if (key < root->data)
		root->left = threadInsert(root->left, key);
	else if (key > root->data)
		root->right = threadInsert(root->right, key);
	else
		printf(" [스레드BT] 이미 같은 키 %d가 있습니다!\n", key);
	return root;
}

/* 보통의 BST를 (재귀로) 중위 순서대로 모아 order[]에 담는다.
 * 아직 스레딩 전이므로 일반 재귀 중위 순회로 안전하게 수집 가능. */
static void collectInorder(ThreadNode* root, ThreadNode* order[], int* n)
{
	if (root == NULL) return;
	collectInorder(root->left, order, n);
	if (*n < TH_MAX) order[(*n)++] = root;
	collectInorder(root->right, order, n);
}

/* 완성된 BST의 빈 오른쪽 링크를 '중위 후속자' 스레드로 채운다.
 *  - 오른쪽 링크가 NULL인 노드만 다음 중위 노드로 연결하고 isThreadRight=1 설정.
 *  - 가장 마지막 중위 노드는 후속자가 없으므로 NULL로 둔다(순회가 거기서 끝남). */
void makeThreads(ThreadNode* root)
{
	ThreadNode* order[TH_MAX];
	int n = 0, i;

	collectInorder(root, order, &n);      /* 중위 순서로 노드 수집 */
	for (i = 0; i < n; i++) {
		if (order[i]->right == NULL && i + 1 < n) {
			order[i]->right = order[i + 1];   /* 빈 오른쪽 -> 후속자 스레드 */
			order[i]->isThreadRight = 1;
		}
	}
}

/* 배열 원소 n개를 BST로 삽입한 뒤 자동으로 스레딩까지 마쳐 반환한다. */
ThreadNode* buildThreadedBST(const int keys[], int n)
{
	ThreadNode* root = NULL;
	int i;
	for (i = 0; i < n; i++)
		root = threadInsert(root, keys[i]);
	makeThreads(root);                    /* 삽입이 끝난 뒤 한 번에 스레딩 */
	return root;
}

/*---------------- 해제 ----------------*/

/* 트리 전체를 해제한다. 오른쪽이 '스레드'면 따라가지 않으므로
 * 같은 노드를 두 번 free하는 일이 없다. (왼쪽은 항상 실제 자식) */
void freeThreadBT(ThreadNode* root)
{
	if (root == NULL) return;
	freeThreadBT(root->left);
	if (!root->isThreadRight)             /* 실제 오른쪽 자식만 재귀 해제 */
		freeThreadBT(root->right);
	free(root);
}
