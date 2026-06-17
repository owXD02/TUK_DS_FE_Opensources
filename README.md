# DS 기말고사 오픈소스 (DS_LT_Opensources)

큐 / 트리 / 정렬(선택·삽입·버블) + 드론 응용 + 난수·파일 입출력을 모두 담은 시험용 오픈소스.
**모든 파일을 한 Visual Studio 프로젝트에 통째로 넣어도 충돌 없이 컴파일·실행된다** (VS2019에서 경고 0개로 검증 완료).

---

## 1. 시험장에서 시작하는 법 (3단계)

1. Visual Studio에서 **빈 프로젝트(C++)** 생성
2. 이 폴더의 **모든 .c / .h 파일을 프로젝트에 추가**
   (소스 파일 우클릭 → 추가 → 기존 항목. 다 넣어도 됨, 안 쓰는 모듈은 그냥 무시됨)
3. `main.c`를 열고 문제에 맞게 수정
   - 각 `demoXxx()` 함수가 곧 문제 유형별 모범 답안 뼈대다. 필요한 것만 남기고 고치자.
   - **main 함수는 프로젝트에 딱 하나만!** (다른 main이 있는 파일을 추가했다면 제외할 것)

> 일부 모듈만 쓰고 싶으면: 해당 모듈 .h/.c + **utils.h/utils.c**(거의 모든 모듈이 사용)만 넣으면 된다.

---

## 2. 파일 구성

| 파일 | 내용 | 이런 문제에 사용 |
|---|---|---|
| `utils.h/.c` | **난수 생성, txt 파일 입출력**, 배열 도우미, 화면+파일 동시 출력(`dualPrintf`) | 거의 모든 문제의 기본 재료 |
| `sort.h/.c` | **선택/삽입/버블**(오름·내림차순, 단계출력, 파일기록) + 퀵/병합/셸/기수 + 좌표 정렬 | "난수를 정렬하고 과정을 출력하라" |
| `sQueue.h/.c` | **순차 큐(선형 큐)** (배열, int) | "선형 큐를 구현하라" |
| `cQueue.h/.c` | **원형 큐** (배열, int) | "큐에 넣고 순서대로 처리하라" |
| `linkedQueue.h/.c` | **연결 큐** (크기 무제한, int) | 큐 문제, 기수 정렬 버킷 |
| `deque.h/.c` | **덱(Deque)** (이중 연결, int, 양쪽 삽입/삭제) | "덱을 구현하라" |
| `jobQueue.h/.c` | **작업 큐 + 큐잉 이론 시뮬레이션** (난수 도착, 평균 대기 시간) | "작업 스케줄링/평균 대기 시간" |
| `reliability.h/.c` | **신뢰성/가용성 계산** (MTBF, MTTR, Availability, 고장률/수리율) | "장비 가용성/MTBF 계산" |
| `stack.h/.c` | 정수 배열 스택 + 좌표(x,y) 연결 스택 | "역순으로 출력/이동하라" |
| `xyList.h/.c` | 좌표 이중 연결 리스트 (좌표용 덱, 양방향 순회, 파일 연동) | 드론 경로 왕복 |
| `arrayBT.h/.c` | **순차 자료구조 이진 트리** (배열 표현, 부모 i/2·자식 2i,2i+1) | "배열로 트리를 표현하라" |
| `bst.h/.c` | **연결 자료구조 이진 트리 / BST**: 삽입/탐색/삭제 + **전위/중위/후위/레벨 순회** + 트리정렬 | 트리 문제 전반 |
| `threadBT.h/.c` | **스레드 이진 트리**(우 스레드): 빈 링크에 중위 후속자 연결, **스택 없는 중위 순회** | "스레드 트리로 순회하라" |
| `avl.h/.c` | **AVL 트리(균형 BST)** + **LL/RR/LR/RL 회전**, BF 계산 | "균형을 유지하며 삽입하라" |
| `heap.h/.c` | **최대/최소 힙** (생성 시 선택), 힙 삽입/삭제 + 힙 정렬 | 우선순위 문제 ("배터리 적은 드론부터") |
| `drone.h/.c` | 드론 구조체, 경로 생성/순찰 시뮬, 목록 정렬/탐색 | **드론 응용 문제 전반** |
| `main.c` | 메뉴식 데모(11종) = 유형별 답안 뼈대 모음 | 시험 때 이 파일을 고쳐 쓰기 |

---

## 2.5 시험 범위 커버리지 (어떤 주제가 어느 파일에 있나)

| 시험 주제 | 위치 |
|---|---|
| 순차 큐 (선형 큐) | `sQueue` |
| 원형 큐 | `cQueue` |
| 연결 큐 | `linkedQueue` |
| 덱 (Deque) | `deque` (정수), `xyList` (좌표) |
| 작업 큐 | `jobQueue` (Job 구조체 + 큐) |
| 큐잉 이론 | `jobQueue`의 `runQueueSim` (난수 도착 시뮬레이션, 평균 대기 시간) |
| 이진 트리 | `bst`의 `makeTreeNode`로 임의 모양 구성 |
| 순차 자료구조 이진 트리 (배열) | `arrayBT` (부모 i/2, 자식 2i·2i+1) |
| 연결 자료구조 이진 트리 | `bst` (BSTNode: key + left/right 포인터) |
| 이진 트리 순회 (전위/중위/후위) | `bst` (bstPreorder/bstInorder/bstPostorder), 배열판은 `arrayBT` |
| 레벨 순회 (큐 활용) | `bst`의 `bstLevelOrder` |
| 스레드 이진 트리 (스택 없는 중위 순회) | `threadBT` (buildThreadedBST + threadInorder) |
| 이진 탐색 트리 | `bst` |
| BST 노드 탐색 | `bst`의 `bstSearch` |
| BST 노드 삽입 | `bst`의 `bstInsert` |
| BST 노드 삭제 (자식 0/1/2개) | `bst`의 `bstDelete` |
| 균형 이진 탐색 트리 / AVL 트리 | `avl` (BF 계산 + 자동 재균형 삽입) |
| AVL 회전 연산 (LL/RR/LR/RL) | `avl`의 `avlLL/avlRR/avlLR/avlRL` |
| 힙 / 힙 삽입 / 힙 삭제 | `heap` (heapInsert/heapDelete) |
| 최대 힙 / 최소 힙 | `heap`: `createHeap(0)`=최대, `createHeap(1)`=최소 |
| 정렬 (선택/삽입/버블 외) | `sort` |
| 난수 생성 / txt 파일 입출력 | `utils` |
| 드론 응용 | `drone` |

---

## 3. 모듈별 핵심 함수 요약

### utils — 난수 & 파일 (가장 자주 씀!)
```c
initRandom();                              // main 맨 앞에서 딱 1번! (안 하면 매번 같은 난수)
int v = randInt(0, 99);                    // 0~99 난수 1개
genRandomArray(a, n, 0, 99);               // 난수 n개 (중복 허용)
genRandomArrayUnique(a, n, 1, 99);         // 난수 n개 (중복 없음, BST용)
genRandomPoints(pts, n, 9, 9);             // 난수 좌표 n개

writeArrayToFile("data.txt", a, n);        // 배열 -> 파일 (한 줄에 하나)
int n = readArrayFromFile("data.txt", a, 100);   // 파일 -> 배열, 읽은 개수 반환
writePointsToFile / readPointsFromFile     // "x y" 형식 좌표 버전

char words[500][WORD_LEN];                 // 가사/단어 txt 읽기 (중간고사 tdm 유형)
int w = readWordsFromFile("song1.txt", words, 500);   // 공백 단위 단어
char lines[100][LINE_LEN];
int m = readLinesFromFile("memo.txt", lines, 100);    // 한 줄씩 (\n 제거됨)

printArray(a, n);                          // 배열 한 줄 출력
copyArray(src, dst, n);                    // 원본 보존하고 정렬할 때
isSortedArray(a, n, 1);                    // 정렬 검증 (1=오름차순 기준)

FILE* log = fopen("result.txt", "w");
dualPrintf(log, "값: %d\n", x);            // 화면+파일 동시 출력. log가 NULL이면 화면만
fclose(log);
```

### sort — 정렬 (시험 1순위)
```c
//          배열, 개수, 오름차순(1)/내림차순(0), 단계출력(1/0), 로그파일(없으면 NULL)
selectionSort(a, n, 1, 1, NULL);    // 선택 정렬, 오름차순, 단계 화면 출력
insertionSort(a, n, 1, 1, NULL);    // 삽입 정렬
bubbleSort(a, n, 0, 1, log);        // 버블 정렬, 내림차순, 단계를 화면+파일에 출력

quickSort(a, n, 1);   mergeSort(a, n, 1);   shellSort(a, n, 1);
radixSort(a, n, 1);                 // 기수 정렬: 0 이상 정수만!
heapSortArray(a, n, 1);             // 힙 정렬 (heap.h)
treeSortArray(a, n);                // 트리 정렬 (bst.h, 중복 값 없을 때만)

sortPointsBy(pts, n, 'x', 1);       // 좌표 배열을 x기준 오름차순 ('y'도 가능)
```

### sQueue / cQueue / linkedQueue / deque — 큐 4종
```c
SQueue* SQ = createSQueue();        // 순차 큐(선형 큐): front=rear=-1, 뒤로만 이동
enSQueue(SQ, 10);  deSQueue(SQ);  peekSQ(SQ);  sqCount(SQ);
printSQ(SQ, NULL);  free(SQ);       // 단점: 앞 공간 재사용 불가 -> 원형 큐로 해결

CQueue* Q = createCQueue();         // 원형 큐 (크기 CQ_SIZE=100, 변경 가능)
enCQueue(Q, 10);                    // 삽입
int v = deCQueue(Q);                // 삭제(공백이면 -1)
peekCQ(Q);  cqCount(Q);  isCQEmpty(Q);  isCQFull(Q);
printCQ(Q, NULL);  free(Q);

LQueue* LQ = createLQueue();        // 연결 큐 (크기 무제한)
enLQueue(LQ, 10);  deLQueue(LQ);  peekLQ(LQ);  lqCount(LQ);
printLQ(LQ, NULL);  freeLQueue(LQ);

Deque* DQ = createDeque();          // 덱: 양쪽 끝에서 삽입/삭제
dqInsertFront(DQ, 1);  dqInsertRear(DQ, 2);
dqDeleteFront(DQ);  dqDeleteRear(DQ);  dqPeekFront(DQ);  dqPeekRear(DQ);
printDeque(DQ, NULL);  freeDeque(DQ);
```

### jobQueue — 작업 큐 + 큐잉 이론
```c
initRandom();
runQueueSim(20, 50, 3, NULL);       // 20시간, 매 시각 50% 확률 작업 도착,
                                    // 처리 시간 1~3 난수. 과정 + 평균 대기 시간 출력
// 작업 큐를 직접 다루려면: createJobQueue / enJobQueue / deJobQueue / printJobQueue
// Job 구조체 = { id, arrival(도착 시각), service(처리 시간) }
```

### reliability — 신뢰성/가용성 (MTBF/MTTR/Availability)
```c
int up[]  = { 100, 120, 90, 110 };       // 고장 사이 가동 시간들
int rep[] = { 5, 8, 4 };                 // 각 수리 시간들
double mtbf = calcMTBF(up, 4);           // 평균 고장 간격 = 가동시간 평균
double mttr = calcMTTR(rep, 3);          // 평균 수리 시간
double a    = calcAvailability(mtbf, mttr);   // MTBF/(MTBF+MTTR), ×100 하면 %
calcFailureRate(mtbf);                    // 고장률 λ=1/MTBF   calcRepairRate(mttr)=수리율
availabilityFromTotals(420, 17);         // 총가동/총정지만 알 때
printReliability(up, 4, rep, 3, NULL);   // 위 지표를 한 번에 보고서 출력
```
> 공식: MTBF=총가동/고장횟수, MTTR=총수리/수리횟수, 가용성=MTBF/(MTBF+MTTR).

### stack — 스택
```c
IntStack* S = createIntStack();     // 정수 스택
pushInt(S, 10);  int v = popInt(S);  peekInt(S);
printIntStack(S, NULL);  free(S);

XYStack* XS = createXYStack();      // 좌표 스택 (역순 이동 문제!)
pushXY(XS, 3, 5);
Point pt;
while (!isXYStackEmpty(XS)) { popXY(XS, &pt);  printf("(%d,%d)\n", pt.x, pt.y); }
freeXYStack(XS);
```

### xyList — 좌표 리스트 (덱/드론 경로)
```c
XYList* L = createXYList();
xyAddRear(L, x, y);                 // 뒤 삽입 (enqueue)   xyAddFront: 앞 삽입
xyRemoveFront(L, &pt);              // 앞 삭제 (dequeue)   xyRemoveRear: 뒤 삭제
xyPrintForward(L, NULL);            // 출발->도착 출력
xyPrintBackward(L, NULL);           // 도착->출발 출력 (복귀!)
xyLoadFromFile("path.txt", L);      // 파일 -> 리스트 (읽은 개수 반환)
xySaveToFile("path.txt", L);        // 리스트 -> 파일
freeXYList(L);                      // L->count : 현재 개수
```

### bst — 이진 탐색 트리
```c
BSTNode* root = NULL;
root = bstInsert(root, 50);         // !! 반드시 root = 로 받기 !!
root = bstDelete(root, 50);         // !! 삭제도 root = 로 받기 !!
BSTNode* p = bstSearch(root, 30);   // 없으면 NULL

bstInorder(root, NULL);             // 중위 = 오름차순  (전위 bstPreorder, 후위 bstPostorder)
bstLevelOrder(root, NULL);          // 레벨 순회 (내부적으로 큐 사용 - 큐+트리 복합 문제!)
bstCount(root);  bstHeight(root);  bstMin(root)->key;  bstMax(root)->key;
root = bstFromArray(a, n);          // 배열로 한 번에 만들기
bstFree(root);
```
> 문자 트리 문제면: key에 'A'를 그대로 넣고, bst.h의 `BST_KEY_FMT`를 `"%c "`로 바꾸면 끝.
> 수식 트리처럼 모양을 직접 만들 때: `makeTreeNode(데이터, 왼쪽, 오른쪽)` 사용.

### avl — AVL 트리 (균형 이진 탐색 트리)
```c
BSTNode* root = NULL;               // 노드는 BST와 같은 BSTNode를 사용!
root = avlInsert(root, 10);         // !! 반드시 root = 로 받기 !!
root = avlInsert(root, 20);
root = avlInsert(root, 30);         // 불균형 발생 -> RR 회전 자동 수행

avlGetBF(root);                     // 균형 인수 = 왼쪽 높이 - 오른쪽 높이
avlLL(p); avlRR(p); avlLR(p); avlRL(p);   // 회전 4종 (개별 호출도 가능)
// 순회/탐색/높이/해제는 bst.h 함수 그대로: bstInorder, bstSearch, bstHeight, bstFree
```
> 삽입만 `avlInsert`로 바꾸면 BST가 AVL이 된다. 나머지는 전부 bst.h 재사용.

### threadBT — 스레드 이진 트리 (스택 없는 중위 순회)
```c
int a[] = { 50, 30, 70, 20, 40, 60, 80 };
ThreadNode* root = buildThreadedBST(a, 7);  // BST 생성 -> 자동 스레딩까지 한 번에
threadInorder(root, NULL);                  // 스택/재귀 없이 중위 순회 (오름차순)
freeThreadBT(root);                         // 스레드는 안 따라가며 안전하게 해제

// 직접 구성(수식 트리 등): makeThreadNode(데이터, 왼쪽, 오른쪽, isThreadRight)
//  - isThreadRight=1 이면 right가 자식이 아니라 '중위 후속자' 스레드
//  - findSuccessor(p)로 후속자만 따로 구할 수도 있음
// 문자 트리면 threadBT.h의 TH_DATA_FMT를 "%c "로 변경
```
> 핵심 개념: 단말 노드의 빈 오른쪽 링크에 '중위 후속자'를 넣어두면 스택 없이 순회된다.

### arrayBT — 순차 자료구조(배열) 이진 트리
```c
ArrayBT* T = createArrayBT();       // 루트는 인덱스 1
abtInsertCBT(T, 10);                // 완전 이진 트리 모양으로 차례 삽입
abtSet(T, 2, 20);                   // 원하는 인덱스에 직접 저장도 가능
abtParentIndex(i);                  // 부모 = i/2  (왼쪽 2i, 오른쪽 2i+1)
abtPreorder(T, 1, NULL);            // 전위/중위/후위: abtInorder, abtPostorder
printArrayBT(T, NULL);              // 인덱스-부모-자식 관계 표 출력
free(T);
```

### heap — 힙 (우선순위 큐)
```c
Heap* h = createHeap(0);            // 0=최대 힙(큰 값 먼저), 1=최소 힙(작은 값 먼저)
heapInsert(h, 45);
int top = heapDelete(h);            // 루트 꺼내기 (공백이면 -1)
heapPeek(h);  printHeap(h, NULL);  free(h);
```

### drone — 드론 응용 (통합 예시)
```c
typedef struct { int id; int x, y; int battery; } Drone;

createDronePathFile("drone_path.txt", 10, 9, 9);   // 난수 경로 10개 생성+저장
int remain = patrolSimulation("drone_path.txt", 100, log);  // 왕복 순찰, 남은 배터리(-1=추락)

createDroneListFile("drone_list.txt", 8, 99, 99, 100);  // 드론 8대 (id x y battery)
Drone fleet[20];
int n = readDrones("drone_list.txt", fleet, 20);
printDrones(fleet, n, NULL);                       // 표로 출력
sortDronesBy(fleet, n, 'b', 0);                    // 'i'=id 'x' 'y' 'b'=배터리 / 0=내림차순
writeDrones("result.txt", fleet, n);
findDroneById(fleet, n, 3);                        // 순차 탐색 (인덱스 반환, 없으면 -1)
binarySearchDroneId(fleet, n, 3);                  // 이진 탐색 (id 오름차순 정렬 필수!)
```

---

## 4. 시험 유형별 레시피 (복붙용)

### 레시피 A. "난수 N개 생성 → 파일 저장 → 읽어서 정렬 → 결과 파일 출력"
```c
#define N 20
int a[N];
initRandom();
genRandomArray(a, N, 0, 99);                 // 1. 난수 생성
writeArrayToFile("data.txt", a, N);          // 2. 파일 저장
int n = readArrayFromFile("data.txt", a, N); // 3. 파일에서 읽기
FILE* log = fopen("result.txt", "w");
selectionSort(a, n, 1, 1, log);              // 4. 정렬 (과정을 화면+파일에)
fclose(log);
writeArrayToFile("sorted.txt", a, n);        // 5. 결과 저장
```

### 레시피 B. "임무/명령을 큐에 넣고 순서대로 처리"
```c
CQueue* Q = createCQueue();
for (int i = 0; i < n; i++) enCQueue(Q, a[i]);   // 파일에서 읽은 값 적재
while (!isCQEmpty(Q)) {
    int job = deCQueue(Q);
    printf("처리: %d\n", job);                    // 문제의 처리 로직으로 교체
}
free(Q);
```

### 레시피 C. "드론이 경로를 순찰하고 왔던 길로 복귀" (배터리 소모)
```c
initRandom();
createDronePathFile("drone_path.txt", 10, 9, 9);
FILE* log = fopen("drone_log.txt", "w");
int remain = patrolSimulation("drone_path.txt", 50, log);   // 배터리 50으로 출발
fclose(log);
if (remain < 0) printf("추락!\n"); else printf("남은 배터리 %d\n", remain);
```
> 복귀를 "스택으로 구현하라"고 하면: 전진하며 `pushXY(XS, x, y)` → 복귀는 `popXY` 반복.

### 레시피 D. "구조체 배열을 특정 필드 기준으로 정렬" (드론 배터리 등)
```c
Drone fleet[20];
int n = readDrones("drone_list.txt", fleet, 20);
sortDronesBy(fleet, n, 'b', 0);              // 배터리 내림차순
printDrones(fleet, n, NULL);
```
> 다른 구조체가 나오면 `sortDronesBy`(drone.c)를 복사해서 필드 이름만 바꾸면 된다.
> 핵심: 구조체는 `temp = a[i]; a[i] = a[j]; a[j] = temp;` 로 통째로 교환.

### 레시피 E. "값들을 BST에 넣고 탐색/삭제/순회"
```c
int a[N];
initRandom();
genRandomArrayUnique(a, N, 1, 99);           // BST는 중복 금지 -> unique 사용!
BSTNode* root = bstFromArray(a, N);
printf("중위: ");  bstInorder(root, NULL);   printf("\n");
printf("레벨: ");  bstLevelOrder(root, NULL); printf("\n");
if (bstSearch(root, 50)) printf("50 발견!\n");
root = bstDelete(root, a[0]);
bstFree(root);
```

### 레시피 F. "우선순위가 높은 것부터 처리" (힙)
```c
Heap* h = createHeap(1);                     // 최소 힙: 작은 값(배터리 적은 드론)부터
for (int i = 0; i < n; i++) heapInsert(h, fleet[i].battery);
while (!isHeapEmpty(h)) printf("%d ", heapDelete(h));
free(h);
```

### 자주 쓰는 커스터마이징
| 바꾸고 싶은 것 | 방법 |
|---|---|
| 내림차순 정렬 | 정렬 함수의 `ascending` 인자에 0 |
| 단계 출력 끄기 | `showSteps` 인자에 0 |
| 큐/스택/힙 크기 | `CQ_SIZE`, `STACK_SIZE`, `MAX_HEAP` 매크로 수정 |
| 난수 범위 | `genRandomArray(a, n, min, max)`의 min/max |
| 파일 저장 형식 | utils.c의 `fprintf(fp, "%d\n", ...)` 부분 수정 |
| 트리를 문자로 출력 | bst.h의 `BST_KEY_FMT`를 `"%c "`로 |

---

## 5. 꼭 기억할 주의사항 5가지

1. **`initRandom()`은 main 맨 앞에서 딱 1번** — 안 부르면 실행할 때마다 같은 난수, 여러 번 부르면 난수가 꼬일 수 있다.
2. **BST는 `root = bstInsert(root, k);` `root = bstDelete(root, k);`** — 반환값을 안 받으면 트리가 망가진다.
3. **파일을 열면(fopen) 반드시 NULL 검사 후, 다 쓰면 fclose** — fclose를 안 하면 파일 내용이 비어 있을 수 있다.
4. **main은 하나만** — 데모 main.c를 쓰지 않으면 프로젝트에서 제외하기.
5. **막히면 main.c의 데모 함수부터 보기** — 모든 모듈의 정상 동작 예시가 거기 있다.

문제가 생기면 → **TROUBLESHOOTING.md** 를 펼칠 것!
