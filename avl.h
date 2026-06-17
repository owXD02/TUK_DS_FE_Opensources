/*=====================================================================
 * avl.h - AVL 트리 (균형 이진 탐색 트리) + 회전 연산(LL, RR, LR, RL)
 *---------------------------------------------------------------------
 * [개념 요약]
 *  - AVL 트리 = 모든 노드에서 |왼쪽 높이 - 오른쪽 높이| <= 1 인 BST.
 *  - 균형 인수 BF = (왼쪽 서브트리 높이) - (오른쪽 서브트리 높이)
 *  - 삽입 후 BF가 +2/-2가 되면 회전으로 균형을 회복한다:
 *      BF > +1 이고 왼쪽 자식 BF > 0   -> LL 회전 (오른쪽으로 한 번)
 *      BF > +1 이고 왼쪽 자식 BF < 0   -> LR 회전 (왼쪽-오른쪽 두 번)
 *      BF < -1 이고 오른쪽 자식 BF < 0 -> RR 회전 (왼쪽으로 한 번)
 *      BF < -1 이고 오른쪽 자식 BF > 0 -> RL 회전 (오른쪽-왼쪽 두 번)
 *
 * [중요] AVL 트리도 BST이므로 노드 구조체(BSTNode)를 그대로 사용한다.
 *  -> bst.h의 모든 함수(bstSearch, bstInorder, bstLevelOrder,
 *     bstHeight, bstCount, bstFree ...)를 AVL 트리에 그대로 쓸 수 있다!
 *  -> 삽입만 avlInsert를 쓰면 된다 (bstInsert는 균형을 안 잡음).
 *
 * [사용 예시]
 *  BSTNode* root = NULL;
 *  root = avlInsert(root, 10);     // !! 반드시 root = 로 받기 !!
 *  root = avlInsert(root, 20);
 *  root = avlInsert(root, 30);     // 여기서 RR 회전 발생 -> 20이 루트가 됨
 *  bstInorder(root, NULL);         // 순회는 bst.h 함수 사용
 *  printf("높이: %d\n", bstHeight(root));
 *  bstFree(root);
 *=====================================================================*/
#pragma once
#include "bst.h"       /* BSTNode, makeTreeNode, bstHeight 등 재사용 */

int avlGetBF(BSTNode* p);              /* 균형 인수 BF = 왼쪽 높이 - 오른쪽 높이 */

BSTNode* avlLL(BSTNode* parent);       /* LL 회전: 왼쪽-왼쪽으로 길어졌을 때 */
BSTNode* avlRR(BSTNode* parent);       /* RR 회전: 오른쪽-오른쪽으로 길어졌을 때 */
BSTNode* avlLR(BSTNode* parent);       /* LR 회전: 왼쪽-오른쪽으로 길어졌을 때 (RR 후 LL) */
BSTNode* avlRL(BSTNode* parent);       /* RL 회전: 오른쪽-왼쪽으로 길어졌을 때 (LL 후 RR) */

BSTNode* avlRebalance(BSTNode* root);  /* BF를 검사해 필요한 회전을 수행하고 새 루트 반환 */
BSTNode* avlInsert(BSTNode* root, int key); /* 균형을 유지하며 삽입. root = avlInsert(root, k); */
