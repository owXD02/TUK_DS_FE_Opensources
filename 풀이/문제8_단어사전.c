/*=====================================================================
 * 문제 8. 영어 단어 사전 (이진 탐색 트리) - 풀이
 *  ※ 라이브러리 bst는 'int 키' 전용이라 문자열(단어) 키를 지원하지 못한다.
 *     그래서 '문자열 BST'를 직접 구현한다. 구조와 알고리즘은 라이브러리 bst와
 *     완전히 동일하고, 키 비교만 strcmp로 바꾼 것이다.
 *  사용 라이브러리(조립): utils(readWordsFromFile)로 단어 읽기
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include <string.h>

/* 단어를 담는 BST 노드 (bst.h의 BSTNode와 같되 key가 문자열) */
typedef struct WNode {
	char word[WORD_LEN];
	struct WNode* left, * right;
} WNode;

/* 삽입: strcmp<0이면 왼쪽, >0이면 오른쪽 (BST 규칙의 문자열판)
   같은 단어(==0)는 중복이므로 무시 */
static WNode* insert(WNode* root, const char* w) {
	if (root == NULL) {
		WNode* n = (WNode*)malloc(sizeof(WNode));
		strcpy(n->word, w);
		n->left = n->right = NULL;
		return n;
	}
	int cmp = strcmp(w, root->word);
	if (cmp < 0)      root->left = insert(root->left, w);
	else if (cmp > 0) root->right = insert(root->right, w);
	return root;
}

/* 중위 순회 = 사전(알파벳) 순 출력 (왼쪽 → 자신 → 오른쪽) */
static void inorder(WNode* r) {
	if (r) { inorder(r->left); printf("%s ", r->word); inorder(r->right); }
}

/* 검색: 있으면 1, 없으면 0 (라이브러리 bstSearch의 문자열판) */
static int search(WNode* r, const char* w) {
	while (r) {
		int c = strcmp(w, r->word);
		if (c == 0) return 1;
		r = (c < 0) ? r->left : r->right;
	}
	return 0;
}

static int countNodes(WNode* r) { return r ? 1 + countNodes(r->left) + countNodes(r->right) : 0; }
static int height(WNode* r) {
	if (!r) return 0;
	int l = height(r->left), rr = height(r->right);
	return 1 + (l > rr ? l : rr);
}

/* 삭제: 라이브러리 bstDelete와 동일한 3경우 처리(단말/자식1개/자식2개).
   자식 2개일 때는 오른쪽 서브트리의 최솟값(후계자)을 끌어올린다. */
static WNode* findMin(WNode* r) { while (r && r->left) r = r->left; return r; }
static WNode* deleteWord(WNode* r, const char* w) {
	if (!r) return NULL;
	int c = strcmp(w, r->word);
	if (c < 0)      r->left = deleteWord(r->left, w);
	else if (c > 0) r->right = deleteWord(r->right, w);
	else {                                       /* 찾음 */
		if (!r->left) { WNode* t = r->right; free(r); return t; }   /* 자식 0/오른쪽만 */
		if (!r->right) { WNode* t = r->left;  free(r); return t; }  /* 왼쪽만 */
		WNode* s = findMin(r->right);            /* 자식 2개: 후계자 복사 후 그 노드 삭제 */
		strcpy(r->word, s->word);
		r->right = deleteWord(r->right, s->word);
	}
	return r;
}
static void freeAll(WNode* r) { if (r) { freeAll(r->left); freeAll(r->right); free(r); } }

int main(void) {
	char words[200][WORD_LEN];
	int n = readWordsFromFile("words.txt", words, 200);   /* 조립: 단어 읽기 */
	if (n <= 0) { printf("words.txt가 없습니다. (단어들을 공백/줄로 구분해 저장)\n"); return 1; }

	WNode* root = NULL;
	for (int i = 0; i < n; i++) root = insert(root, words[i]);

	printf("사전(중위) 순 : "); inorder(root); printf("\n");
	printf("노드 수=%d, 높이=%d\n", countNodes(root), height(root));

	const char* key = "apple";
	printf("\"%s\" 검색 : %s\n", key, search(root, key) ? "등재됨" : "미등재");

	printf("\"%s\" 삭제 후 : ", words[0]);
	root = deleteWord(root, words[0]);          /* 첫 단어 삭제 */
	inorder(root); printf("\n");

	freeAll(root);
	return 0;
}
