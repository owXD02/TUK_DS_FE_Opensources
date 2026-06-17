/*=====================================================================
 * bst.h - 이진 트리 / 이진 탐색 트리 (int key)
 *---------------------------------------------------------------------
 * [무엇이 들어있나]
 *  - BST 삽입/탐색/삭제 (삭제는 자식 0/1/2개 모든 경우 처리)
 *  - 4가지 순회: 전위(preorder), 중위(inorder), 후위(postorder), 레벨(level)
 *    -> 레벨 순회는 큐를 사용하므로 "큐+트리" 복합 문제에 그대로 사용 가능
 *  - 노드 수 / 높이 / 최솟값 / 최댓값 구하기
 *  - 배열 -> BST 만들기, BST -> 정렬된 배열 (트리 정렬)
 *  - makeTreeNode로 임의 모양의 이진 트리도 직접 만들 수 있음 (수식 트리 등)
 *
 * [사용 예시 - BST 기본]
 *  BSTNode* root = NULL;
 *  root = bstInsert(root, 50);          // 삽입은 반드시 root = ... 로 받기!
 *  root = bstInsert(root, 30);
 *  bstInorder(root, NULL);  printf("\n");   // 중위 순회 = 오름차순 출력
 *  if (bstSearch(root, 30) != NULL) printf("있음\n");
 *  root = bstDelete(root, 50);          // 삭제도 root = ... 로 받기!
 *  bstFree(root);
 *
 * [참고] 문자를 다루는 문제면 key에 'A' 같은 문자를 그대로 넣고
 *        출력 형식만 BST_KEY_FMT를 "%c "로 바꾸면 된다.
 *=====================================================================*/
#pragma once
#include <stdio.h>

#define BST_KEY_FMT "%d "     /* 순회 출력 형식. 문자 트리면 "%c "로 변경 */

typedef struct BSTNode {
	int key;                  /* 데이터(키) 필드 */
	struct BSTNode* left;     /* 왼쪽 서브 트리 링크 */
	struct BSTNode* right;    /* 오른쪽 서브 트리 링크 */
} BSTNode;

/*------- 트리 만들기 -------*/
BSTNode* makeTreeNode(int key, BSTNode* left, BSTNode* right); /* 노드 직접 생성(수식 트리 등 임의 트리용) */
BSTNode* bstInsert(BSTNode* root, int key);   /* BST 규칙대로 삽입. 사용법: root = bstInsert(root, k); */
BSTNode* bstFromArray(const int a[], int n);  /* 배열 원소를 차례로 삽입한 BST 반환 */

/*------- 탐색 / 삭제 -------*/
BSTNode* bstSearch(BSTNode* root, int key);   /* 키 탐색. 찾으면 노드 주소, 없으면 NULL */
BSTNode* bstDelete(BSTNode* root, int key);   /* 키 삭제. 사용법: root = bstDelete(root, k); */
BSTNode* bstMin(BSTNode* root);               /* 최솟값 노드 (가장 왼쪽) */
BSTNode* bstMax(BSTNode* root);               /* 최댓값 노드 (가장 오른쪽) */

/*------- 순회 (log가 NULL이 아니면 파일에도 기록) -------*/
void bstPreorder(BSTNode* root, FILE* log);   /* 전위: 자신 -> 왼쪽 -> 오른쪽 (D L R) */
void bstInorder(BSTNode* root, FILE* log);    /* 중위: 왼쪽 -> 자신 -> 오른쪽 (L D R) = 오름차순 */
void bstPostorder(BSTNode* root, FILE* log);  /* 후위: 왼쪽 -> 오른쪽 -> 자신 (L R D) */
void bstLevelOrder(BSTNode* root, FILE* log); /* 레벨: 위에서 아래로, 왼쪽에서 오른쪽으로 (큐 사용) */

/*------- 정보 / 활용 -------*/
int  bstCount(BSTNode* root);                 /* 전체 노드 개수 */
int  bstHeight(BSTNode* root);                /* 트리 높이 (공백 트리 = 0) */
void bstToSortedArray(BSTNode* root, int out[], int* idx); /* 중위 순회로 배열에 담기. *idx는 0으로 시작 */
void treeSortArray(int a[], int n);           /* 트리 정렬: BST에 넣었다 빼서 a를 오름차순으로 */
void bstFree(BSTNode* root);                  /* 트리 전체 메모리 해제 */
