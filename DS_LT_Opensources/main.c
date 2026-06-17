/*=====================================================================
 * main.c - 전체 모듈 데모 (메뉴 선택형)
 *---------------------------------------------------------------------
 * 이 파일은 모든 모듈의 "사용 예시"이자 동작 확인용이다.
 * 시험장에서는 이 파일의 내용을 문제에 맞게 고쳐 쓰면 된다.
 *  - 각 demo 함수가 곧 시험 답안의 뼈대다. 필요한 함수만 복사해 가자.
 *  - 주의: 한 프로젝트에 main 함수는 반드시 하나만 있어야 한다!
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS   /* VS 보안 경고 끄기 - 반드시 모든 include보다 위에! */
#include "utils.h"
#include "sQueue.h"
#include "cQueue.h"
#include "linkedQueue.h"
#include "deque.h"
#include "arrayDeque.h"
#include "jobQueue.h"
#include "stack.h"
#include "xyList.h"
#include "sort.h"
#include "bst.h"
#include "avl.h"
#include "arrayBT.h"
#include "threadBT.h"
#include "heap.h"
#include "reliability.h"
#include "search.h"
#include "queuing.h"
#include "linkedList.h"
#include "drone.h"

#define DEMO_N 10        /* 데모에서 사용할 데이터 개수 */

/*----------------------------------------------------------------
 * [데모 1] 난수 -> 파일 저장 -> 읽기 -> 선택/삽입/버블 정렬 -> 결과 저장
 *  : "난수 N개를 파일에 쓰고, 읽어서 정렬한 뒤 결과를 파일로 출력하라"
 *    유형의 표준 풀이 흐름
 *----------------------------------------------------------------*/
void demoSort(void)
{
	int original[DEMO_N], work[DEMO_N];
	int n;
	FILE* log;

	/* 1) 난수 생성 후 파일 저장 */
	genRandomArray(original, DEMO_N, 0, 99);
	writeArrayToFile("random_data.txt", original, DEMO_N);
	printf("\n[1] 난수 %d개 생성 -> random_data.txt 저장\n", DEMO_N);

	/* 2) 파일에서 다시 읽기 */
	n = readArrayFromFile("random_data.txt", original, DEMO_N);
	printf("[2] 파일에서 %d개 읽음 : ", n);
	printArray(original, n);

	/* 3) 선택 정렬 (오름차순, 단계 출력) */
	printf("\n<< 선택 정렬 (오름차순) >>\n");
	copyArray(original, work, n);            /* 원본 보존을 위해 복사본 정렬 */
	selectionSort(work, n, 1, 1, NULL);

	/* 4) 삽입 정렬 (오름차순, 단계 출력) */
	printf("\n<< 삽입 정렬 (오름차순) >>\n");
	copyArray(original, work, n);
	insertionSort(work, n, 1, 1, NULL);

	/* 5) 버블 정렬 (내림차순, 단계를 화면+파일 동시 출력) */
	printf("\n<< 버블 정렬 (내림차순, sort_log.txt에도 기록) >>\n");
	copyArray(original, work, n);
	log = fopen("sort_log.txt", "w");
	bubbleSort(work, n, 0, 1, log);
	if (log != NULL) fclose(log);

	/* 6) 정렬 결과를 파일로 저장 */
	writeArrayToFile("sorted_result.txt", work, n);
	printf("\n[6] 정렬 결과 -> sorted_result.txt 저장 (정렬 검증: %s)\n",
		isSortedArray(work, n, 0) ? "성공" : "실패");
}

/*----------------------------------------------------------------
 * [데모 2] 원형 큐 : 삽입/삭제/peek 기본 동작
 *----------------------------------------------------------------*/
void demoCQueue(void)
{
	CQueue* Q = createCQueue();
	int i, v;

	printf("\n<< 원형 큐 데모 >>\n");
	for (i = 1; i <= 5; i++) {               /* 10, 20, ..., 50 삽입 */
		enCQueue(Q, i * 10);
		printf(" 삽입 %d ->", i * 10);
		printCQ(Q, NULL);
	}
	printf(" peek : %d\n", peekCQ(Q));
	for (i = 0; i < 2; i++) {                /* 2개 삭제 */
		v = deCQueue(Q);
		printf(" 삭제 %d ->", v);
		printCQ(Q, NULL);
	}
	printf(" 현재 원소 수 : %d\n", cqCount(Q));
	free(Q);
}

/*----------------------------------------------------------------
 * [데모 3] 연결 큐 : 난수를 넣고 차례로 꺼내기
 *----------------------------------------------------------------*/
void demoLQueue(void)
{
	LQueue* LQ = createLQueue();
	int i;

	printf("\n<< 연결 큐 데모 >>\n");
	for (i = 0; i < 5; i++)
		enLQueue(LQ, randInt(1, 99));        /* 난수 5개 삽입 */
	printLQ(LQ, NULL);
	printf(" 꺼내기 : ");
	while (!isLQEmpty(LQ))                   /* 빌 때까지 dequeue */
		printf("%d ", deLQueue(LQ));
	printf("\n");
	freeLQueue(LQ);
}

/*----------------------------------------------------------------
 * [데모 4] BST : 삽입 -> 4가지 순회 -> 탐색 -> 삭제
 *----------------------------------------------------------------*/
void demoBST(void)
{
	int data[DEMO_N];
	int n = DEMO_N, i;
	BSTNode* root = NULL;
	BSTNode* found;

	printf("\n<< 이진 탐색 트리 데모 >>\n");
	genRandomArrayUnique(data, n, 1, 99);    /* BST는 중복 불가이므로 unique 사용 */
	printf(" 삽입 순서  : ");
	printArray(data, n);

	for (i = 0; i < n; i++)
		root = bstInsert(root, data[i]);     /* 반드시 root = 로 받기! */

	printf(" 중위 순회  : ");  bstInorder(root, NULL);    printf("  <- 오름차순!\n");
	printf(" 전위 순회  : ");  bstPreorder(root, NULL);   printf("\n");
	printf(" 후위 순회  : ");  bstPostorder(root, NULL);  printf("\n");
	printf(" 레벨 순회  : ");  bstLevelOrder(root, NULL); printf("\n");
	printf(" 노드 수 = %d, 높이 = %d, 최소 = %d, 최대 = %d\n",
		bstCount(root), bstHeight(root), bstMin(root)->key, bstMax(root)->key);

	found = bstSearch(root, data[0]);        /* 반드시 있는 키 탐색 */
	printf(" %d 탐색 -> %s\n", data[0], found ? "성공" : "실패");

	root = bstDelete(root, data[0]);         /* 루트 삭제 (자식 2개 경우 포함) */
	printf(" %d 삭제 후 : ", data[0]);
	bstInorder(root, NULL);
	printf("\n");
	bstFree(root);
}

/*----------------------------------------------------------------
 * [데모 5] 힙 : 최대 힙 삽입/삭제 + 힙 정렬
 *----------------------------------------------------------------*/
void demoHeap(void)
{
	Heap* h = createHeap(0);                 /* 0 = 최대 힙 */
	int data[DEMO_N];
	int i;

	printf("\n<< 힙 데모 >>\n");
	genRandomArray(data, DEMO_N, 1, 99);
	printf(" 원본       : ");
	printArray(data, DEMO_N);

	for (i = 0; i < 5; i++)
		heapInsert(h, data[i]);
	printHeap(h, NULL);
	printf(" 삭제(큰 것부터) : ");
	while (!isHeapEmpty(h))
		printf("%d ", heapDelete(h));
	printf("\n");
	free(h);

	heapSortArray(data, DEMO_N, 1);          /* 힙 정렬 (오름차순) */
	printf(" 힙 정렬 후 : ");
	printArray(data, DEMO_N);
}

/*----------------------------------------------------------------
 * [데모 6] 스택 + 좌표 리스트 : 경로 역순 출력 등
 *----------------------------------------------------------------*/
void demoStackList(void)
{
	IntStack* S = createIntStack();
	XYStack* XS = createXYStack();
	XYList* L = createXYList();
	Point pt;
	int i;

	printf("\n<< 스택 데모 >>\n");
	for (i = 1; i <= 4; i++) pushInt(S, i * 11);
	printIntStack(S, NULL);
	printf(" pop : %d\n", popInt(S));         /* 44 (마지막에 넣은 것) */
	printf(" pop : %d\n", popInt(S));         /* 33 */
	free(S);

	printf("\n<< 좌표 스택: 넣은 순서의 역순으로 나옴 >>\n");
	pushXY(XS, 1, 2);  pushXY(XS, 3, 4);  pushXY(XS, 5, 6);
	while (!isXYStackEmpty(XS)) {             /* 빌 때까지 꺼내기 */
		popXY(XS, &pt);
		printf(" pop -> (%d, %d)\n", pt.x, pt.y);
	}
	freeXYStack(XS);

	printf("\n<< 좌표 리스트(덱): 양방향 순회 >>\n");
	for (i = 0; i < 4; i++)
		xyAddRear(L, randInt(0, 9), randInt(0, 9));
	printf(" 전진 :\n");  xyPrintForward(L, NULL);
	printf(" 복귀 :\n");  xyPrintBackward(L, NULL);
	freeXYList(L);
}

/*----------------------------------------------------------------
 * [데모 7] 드론 통합 시나리오
 *  : 경로 생성 -> 순찰 왕복 -> 드론 목록 정렬/탐색 (기말 예상 유형)
 *----------------------------------------------------------------*/
void demoDrone(void)
{
	Drone fleet[20];
	int n, idx, remain;
	FILE* log;

	/* 1) 난수 경로 파일 생성 후 순찰 시뮬레이션 (비행 기록을 파일로) */
	printf("\n<< 드론 순찰 시뮬레이션 >>\n");
	createDronePathFile("drone_path.txt", 5, 9, 9);
	log = fopen("drone_log.txt", "w");
	remain = patrolSimulation("drone_path.txt", 100, log);
	if (log != NULL) fclose(log);
	if (remain >= 0) printf(" => 순찰 성공! (기록: drone_log.txt)\n");
	else             printf(" => 순찰 실패(추락)\n");

	/* 2) 드론 목록 생성 -> 읽기 -> 배터리 내림차순 정렬 -> id 탐색 */
	printf("\n<< 드론 목록 정렬/탐색 >>\n");
	createDroneListFile("drone_list.txt", 8, 99, 99, 100);
	n = readDrones("drone_list.txt", fleet, 20);
	printf(" - 읽은 드론 수 : %d\n", n);
	printDrones(fleet, n, NULL);

	sortDronesBy(fleet, n, 'b', 0);          /* 배터리 많은 순 */
	printf("\n - 배터리 내림차순 정렬 후:\n");
	printDrones(fleet, n, NULL);
	writeDrones("drone_sorted.txt", fleet, n);

	sortDronesBy(fleet, n, 'i', 1);          /* 이진 탐색 전 id 오름차순 정렬 */
	idx = binarySearchDroneId(fleet, n, 3);
	if (idx != -1)
		printf("\n - id 3번 드론 탐색 성공: 위치(%d,%d) 배터리 %d\n",
			fleet[idx].x, fleet[idx].y, fleet[idx].battery);
}

/*----------------------------------------------------------------
 * [데모 8] 순차 큐 + 덱(순차/연결 둘 다)
 *----------------------------------------------------------------*/
void demoSQueueDeque(void)
{
	SQueue* SQ = createSQueue();
	ADeque* ADQ = createADeque();   /* 순차 데크 (배열·원형) */
	Deque* DQ = createDeque();      /* 연결 데크 (노드) */
	int i;

	printf("\n<< 순차 큐(선형 큐) 데모 >>\n");
	for (i = 1; i <= 4; i++) {
		enSQueue(SQ, i * 10);                /* 10, 20, 30, 40 삽입 */
		printf(" 삽입 %d ->", i * 10);
		printSQ(SQ, NULL);
	}
	printf(" 삭제 %d ->", deSQueue(SQ));  printSQ(SQ, NULL);
	printf(" 삭제 %d ->", deSQueue(SQ));  printSQ(SQ, NULL);
	printf(" * 순차 큐는 삭제해도 앞 공간 재사용 불가 (원형 큐가 해결)\n");
	free(SQ);

	printf("\n<< 순차 데크(배열·원형) 데모: 양쪽에서 삽입/삭제 >>\n");
	aqInsertRear(ADQ, 10);   printf(" 뒤 삽입 10 ->");  printADeque(ADQ, NULL);
	aqInsertFront(ADQ, 20);  printf(" 앞 삽입 20 ->");  printADeque(ADQ, NULL);
	aqInsertRear(ADQ, 30);   printf(" 뒤 삽입 30 ->");  printADeque(ADQ, NULL);
	aqInsertFront(ADQ, 40);  printf(" 앞 삽입 40 ->");  printADeque(ADQ, NULL);
	printf(" 앞 삭제 %d ->", aqDeleteFront(ADQ));  printADeque(ADQ, NULL);
	printf(" 뒤 삭제 %d ->", aqDeleteRear(ADQ));   printADeque(ADQ, NULL);
	free(ADQ);

	printf("\n<< 연결 데크(노드) 데모: 양쪽에서 삽입/삭제 >>\n");
	dqInsertRear(DQ, 10);   printf(" 뒤 삽입 10 ->");  printDeque(DQ, NULL);
	dqInsertFront(DQ, 20);  printf(" 앞 삽입 20 ->");  printDeque(DQ, NULL);
	dqInsertRear(DQ, 30);   printf(" 뒤 삽입 30 ->");  printDeque(DQ, NULL);
	dqInsertFront(DQ, 40);  printf(" 앞 삽입 40 ->");  printDeque(DQ, NULL);
	printf(" 앞 삭제 %d ->", dqDeleteFront(DQ));  printDeque(DQ, NULL);
	printf(" 뒤 삭제 %d ->", dqDeleteRear(DQ));   printDeque(DQ, NULL);
	freeDeque(DQ);
}

/*----------------------------------------------------------------
 * [데모 9] AVL 트리 : 회전(LL/RR/LR/RL)으로 균형 유지
 *  : 오름차순으로 삽입하면 일반 BST는 한쪽으로 쏠리지만(높이 = n),
 *    AVL은 회전 덕분에 낮은 높이를 유지한다.
 *----------------------------------------------------------------*/
void demoAVL(void)
{
	BSTNode* bstRoot = NULL;     /* 비교용: 일반 BST */
	BSTNode* avlRoot = NULL;     /* AVL 트리 */
	int i;

	printf("\n<< AVL 트리 데모: 10,20,...,70을 순서대로 삽입 >>\n");
	for (i = 1; i <= 7; i++) {
		bstRoot = bstInsert(bstRoot, i * 10);   /* 일반 BST: 오른쪽으로만 쏠림 */
		avlRoot = avlInsert(avlRoot, i * 10);   /* AVL: RR 회전 등으로 균형 유지 */
	}

	printf(" [일반 BST] 높이 = %d (한쪽으로 쏠림!)\n", bstHeight(bstRoot));
	printf(" [AVL 트리] 높이 = %d (회전으로 균형 유지!)\n", bstHeight(avlRoot));
	printf(" AVL 중위 순회 : ");  bstInorder(avlRoot, NULL);    printf(" <- 정렬 순서 유지\n");
	printf(" AVL 레벨 순회 : ");  bstLevelOrder(avlRoot, NULL); printf(" <- 40이 루트\n");
	printf(" 루트의 BF = %d (절댓값 1 이하면 균형)\n", avlGetBF(avlRoot));

	bstFree(bstRoot);
	bstFree(avlRoot);
}

/*----------------------------------------------------------------
 * [데모 10] 순차 자료구조(배열) 이진 트리
 *  : 부모 i/2, 왼쪽 2i, 오른쪽 2i+1 인덱스 관계
 *----------------------------------------------------------------*/
void demoArrayBT(void)
{
	ArrayBT* T = createArrayBT();
	int i;

	printf("\n<< 배열 이진 트리 데모 >>\n");
	for (i = 1; i <= 7; i++)
		abtInsertCBT(T, i * 11);             /* 11~77을 완전 이진 트리로 삽입 */

	printArrayBT(T, NULL);                   /* 인덱스/부모/자식 관계 표 */
	printf(" 전위 순회 : ");  abtPreorder(T, 1, NULL);   printf("\n");
	printf(" 중위 순회 : ");  abtInorder(T, 1, NULL);    printf("\n");
	printf(" 후위 순회 : ");  abtPostorder(T, 1, NULL);  printf("\n");
	printf(" 인덱스 3의 부모 = %d번, 왼쪽 자식 = %d번, 오른쪽 자식 = %d번\n",
		abtParentIndex(3), abtLeftIndex(3), abtRightIndex(3));
	free(T);
}

/*----------------------------------------------------------------
 * [데모 11] 작업 큐 + 큐잉 이론 시뮬레이션
 *  : 난수 도착/처리 시간으로 평균 대기 시간 구하기
 *----------------------------------------------------------------*/
void demoJobQueue(void)
{
	printf("\n<< 작업 큐 / 큐잉 이론 시뮬레이션 >>\n");
	runQueueSim(15, 50, 3, NULL);    /* 15시간, 도착 확률 50%, 처리 시간 1~3 */
}

/*----------------------------------------------------------------
 * [데모 12] 스레드 이진 트리 : 스택 없는 중위 순회
 *----------------------------------------------------------------*/
void demoThreadBT(void)
{
	int a[] = { 50, 30, 70, 20, 40, 60, 80 };
	int n = (int)(sizeof(a) / sizeof(a[0]));
	ThreadNode* root;

	printf("\n<< 스레드 이진 트리 데모 >>\n");
	root = buildThreadedBST(a, n);           /* 배열 -> BST -> 자동 스레딩 */
	printf(" 스택/재귀 없이 중위 순회 : ");
	threadInorder(root, NULL);               /* 빈 오른쪽 링크의 스레드를 따라 순회 */
	printf(" (오름차순으로 나오면 성공! 일반 BST 중위 순회와 결과가 같다)\n");
	freeThreadBT(root);
}

/*----------------------------------------------------------------
 * [데모 13] 신뢰성/가용성 : MTBF / MTTR / Availability 계산
 *----------------------------------------------------------------*/
void demoReliability(void)
{
	/* 예: 장비가 4번 가동되고 그 사이 3번 수리되었다고 가정 */
	int uptimes[] = { 100, 120, 90, 110 };   /* 고장 사이 가동 시간(시간) */
	int repairs[] = { 5, 8, 4 };             /* 각 수리 시간(시간) */

	printf("\n<< 신뢰성/가용성 데모 >>\n");
	/* MTBF=105, MTTR≈5.67, 가용성≈94.88% 가 나온다 */
	printReliability(uptimes, 4, repairs, 3, NULL);
}

/*----------------------------------------------------------------
 * [데모 14] 탐색 : 순차 / 이진 / 색인 + 비교 횟수
 *----------------------------------------------------------------*/
void demoSearch(void)
{
	int a[15], b[15];
	int c1, c2, c3, key;

	printf("\n<< 탐색 데모 >>\n");
	genRandomArray(a, 15, 0, 99);            /* 정렬 안 된 원본 */
	copyArray(a, b, 15);
	quickSort(b, 15, 1);                      /* 이진/색인 탐색용 정렬본 */
	printf(" 원본    : "); printArray(a, 15);
	printf(" 정렬본  : "); printArray(b, 15);

	key = b[7];                               /* 반드시 존재하는 값으로 탐색 */
	sequentialSearch(a, 15, key, &c1);        /* 정렬 무관 */
	binarySearch(b, 15, key, &c2);            /* 정렬 필수 */
	indexSearch(b, 15, key, 4, &c3);          /* 블록 크기 4 색인 탐색 */
	printf(" %d 탐색 -> 순차 비교 %d회, 이진 비교 %d회, 색인 비교 %d회\n",
		key, c1, c2, c3);
}

/*----------------------------------------------------------------
 * [데모 15] 큐잉 이론 M/M/1 공식 계산
 *----------------------------------------------------------------*/
void demoQueuing(void)
{
	printf("\n<< M/M/1 큐잉 공식 데모 >>\n");
	/* λ=2, μ=3 → ρ≈0.67, L=2, W=1, Lq≈1.33, Wq≈0.67 */
	printMM1(2.0, 3.0, NULL);
}

/*----------------------------------------------------------------
 * [데모 16] 연결 리스트 : 삽입/삭제/탐색/역순
 *----------------------------------------------------------------*/
void demoLinkedList(void)
{
	LinkedList* L = createList();

	printf("\n<< 연결 리스트 데모 >>\n");
	insertLast(L, 10); insertLast(L, 20); insertLast(L, 30);
	insertFirst(L, 5);                       /* [5 10 20 30] */
	insertAt(L, 2, 15);                      /* [5 10 15 20 30] */
	printf(" 구성 후 : "); printList(L, NULL);
	printf(" 15의 위치 = %d\n", searchList(L, 15));
	deleteValue(L, 20);                      /* [5 10 15 30] */
	printf(" 20 삭제 : "); printList(L, NULL);
	reverseList(L);                          /* [30 15 10 5] */
	printf(" 역순    : "); printList(L, NULL);
	printf(" 길이 = %d\n", listLength(L));
	freeList(L);
}

/*----------------------------------------------------------------
 * 메인 : 메뉴를 보여주고 선택된 데모 실행
 *----------------------------------------------------------------*/
int main(void)
{
	int menu;

	initRandom();                            /* 난수 시드 설정 - 맨 앞에서 1번만! */

	while (1) {
		printf("\n========= DS 기말고사 오픈소스 데모 =========\n");
		printf(" 1. 정렬 (난수->파일->선택/삽입/버블->저장)\n");
		printf(" 2. 원형 큐\n");
		printf(" 3. 연결 큐\n");
		printf(" 4. 이진 탐색 트리 (4가지 순회 포함)\n");
		printf(" 5. 힙 + 힙 정렬\n");
		printf(" 6. 스택 + 좌표 리스트\n");
		printf(" 7. 드론 통합 시나리오\n");
		printf(" 8. 순차 큐 + 덱\n");
		printf(" 9. AVL 트리 (LL/RR/LR/RL 회전)\n");
		printf(" 10. 배열 이진 트리 (순차 자료구조)\n");
		printf(" 11. 작업 큐 / 큐잉 시뮬레이션\n");
		printf(" 12. 스레드 이진 트리 (스택 없는 중위 순회)\n");
		printf(" 13. 신뢰성/가용성 (MTBF/MTTR/Availability)\n");
		printf(" 14. 탐색 (순차/이진/색인 + 비교횟수)\n");
		printf(" 15. 큐잉 이론 M/M/1 공식\n");
		printf(" 16. 연결 리스트 (삽입/삭제/탐색/역순)\n");
		printf(" 0. 종료\n");
		printf("=============================================\n");
		printf(" 메뉴 선택 >> ");

		if (scanf("%d", &menu) != 1) {       /* 숫자가 아닌 입력 방어 */
			printf(" 숫자를 입력하세요!\n");
			while (getchar() != '\n');       /* 입력 버퍼 비우기 */
			continue;
		}

		switch (menu) {
		case 1: demoSort();      break;
		case 2: demoCQueue();    break;
		case 3: demoLQueue();    break;
		case 4: demoBST();       break;
		case 5: demoHeap();      break;
		case 6: demoStackList(); break;
		case 7: demoDrone();     break;
		case 8: demoSQueueDeque(); break;
		case 9: demoAVL();       break;
		case 10: demoArrayBT();  break;
		case 11: demoJobQueue(); break;
		case 12: demoThreadBT(); break;
		case 13: demoReliability(); break;
		case 14: demoSearch();   break;
		case 15: demoQueuing();  break;
		case 16: demoLinkedList(); break;
		case 0: printf(" 종료합니다.\n");  return 0;
		default: printf(" 0~16 사이의 번호를 입력하세요!\n");  break;
		}
	}
}
