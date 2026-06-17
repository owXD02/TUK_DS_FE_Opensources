/*=====================================================================
 * 문제 10. 스레드 이진 트리 (스택 없는 중위 순회) - 라이브러리 조립 풀이
 *  사용 라이브러리: threadBT(스레드 트리), bst(검증용 일반 중위 순회)
 *  직접 구현 없음 - 전부 라이브러리 함수 조립.
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "threadBT.h"
#include "bst.h"

int main(void) {
	int a[] = { 50, 30, 70, 20, 40, 60, 80, 10 };
	int n = (int)(sizeof(a) / sizeof(a[0]));

	/* (1)(2) BST 생성 + 빈 오른쪽 링크를 중위 후속자로 자동 스레딩 (라이브러리 한 줄) */
	ThreadNode* t = buildThreadedBST(a, n);

	/* (3) 스택/재귀 없이 스레드를 따라 중위 순회 */
	printf("스레드 중위 순회 : "); threadInorder(t, NULL);   /* 함수가 끝에 줄바꿈 출력 */

	/* (4) 검증: 일반 BST의 재귀 중위 순회 결과와 같아야 함 */
	BSTNode* b = bstFromArray(a, n);
	printf("일반 중위 순회   : "); bstInorder(b, NULL); printf("\n");

	freeThreadBT(t);
	bstFree(b);
	return 0;
}
