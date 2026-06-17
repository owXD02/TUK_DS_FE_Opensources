/*=====================================================================
 * threadBT.h - 스레드(쓰레드) 이진 트리 (우 스레드, 중위 순회용)
 *---------------------------------------------------------------------
 * [개념 요약]
 *  - 일반 이진 트리는 단말 노드의 링크가 NULL로 "낭비"된다.
 *  - 스레드 이진 트리는 그 빈 오른쪽 링크에 "중위 후속자(inorder
 *    successor)"를 연결해 둔다. 그러면 스택/재귀 없이도 중위 순회가 된다.
 *  - isThreadRight == 1 이면 right는 자식이 아니라 '스레드(후속자 링크)'.
 *    isThreadRight == 0 이면 right는 보통의 오른쪽 자식.
 *  - 수업 교재(ch07_3 threadBT)와 같은 우(右) 스레드 방식이며, char 대신
 *    int를 저장하도록 일반화했다. (문자 트리면 TH_DATA_FMT만 "%c "로 변경)
 *
 * [사용법 1 - 가장 쉬움: 배열 -> 스레드 BST 자동 생성]
 *  int a[] = { 50, 30, 70, 20, 40, 60, 80 };
 *  ThreadNode* root = buildThreadedBST(a, 7);  // BST 만들고 자동 스레딩까지
 *  threadInorder(root, NULL);                  // 스택 없이 중위 순회 (오름차순)
 *  freeThreadBT(root);
 *
 * [사용법 2 - 직접 구성: 수식 트리 (A*B-C/D) 등 교재 예제]
 *  ThreadNode* D = makeThreadNode('D', NULL, NULL, 0);
 *  ThreadNode* C = makeThreadNode('C', NULL, NULL, 1);   // 오른쪽이 스레드
 *  ...                                                   // 노드 구성 후
 *  C->right = someSuccessor;                             // 스레드를 직접 연결
 *  threadInorder(root, NULL);   // TH_DATA_FMT를 "%c "로 바꾸면 문자로 출력
 *=====================================================================*/
#pragma once
#include <stdio.h>

#define TH_DATA_FMT "%d "     /* 순회 출력 형식. 수식 트리(문자)면 "%c "로 변경 */
#define TH_MAX 1000           /* 자동 스레딩 시 처리 가능한 최대 노드 수 */

typedef struct ThreadNode {
	int data;                       /* 데이터 필드 */
	struct ThreadNode* left;        /* 왼쪽 자식 (항상 실제 링크) */
	struct ThreadNode* right;       /* 오른쪽: 자식이거나 스레드(후속자) */
	int isThreadRight;              /* 1이면 right가 스레드, 0이면 실제 자식 */
} ThreadNode;

/*------- 직접 구성 (수식 트리 등) -------*/
ThreadNode* makeThreadNode(int data, ThreadNode* left, ThreadNode* right, int isThreadRight);

/*------- 중위 후속자 / 스택 없는 중위 순회 -------*/
ThreadNode* findSuccessor(ThreadNode* p);     /* p의 중위 후속자 노드 반환 (없으면 NULL) */
void threadInorder(ThreadNode* root, FILE* log); /* 스택/재귀 없이 중위 순회. log!=NULL이면 파일에도 기록 */

/*------- BST로 자동 구성 (가장 간단한 조립용) -------*/
ThreadNode* threadInsert(ThreadNode* root, int key);   /* 일반 BST 규칙으로 삽입 (스레딩 전). root = ... 로 받기 */
void makeThreads(ThreadNode* root);                    /* 완성된 BST를 우 스레드 트리로 변환 */
ThreadNode* buildThreadedBST(const int keys[], int n); /* 배열 원소를 삽입+스레딩까지 한 번에 */

/*------- 해제 -------*/
void freeThreadBT(ThreadNode* root);          /* 트리 전체 해제 (스레드는 따라가지 않음) */
