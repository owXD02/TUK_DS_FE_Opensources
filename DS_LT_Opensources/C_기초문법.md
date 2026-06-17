# C 언어 기초 문법 (이 오픈소스를 쓰기 위한 최소 지식)

> 오랜만에 C를 보는 사람을 위해, **이 라이브러리를 조립할 때 실제로 필요한 문법만** 골라 정리했습니다.
> 위에서부터 한 번 훑고, 모르는 게 나오면 여기서 찾으세요.

---

## 0. 프로그램의 기본 골격
```c
#define _CRT_SECURE_NO_WARNINGS   // VS 보안 경고 끄기 (항상 맨 위!)
#include <stdio.h>                // 표준 입출력 (printf, scanf, fopen...)
#include "utils.h"               // 우리 라이브러리 (큰따옴표로 포함)

int main(void) {                  // 프로그램은 main에서 시작한다
    printf("Hello\n");
    return 0;                     // 0 = 정상 종료
}
```
- `<stdio.h>` 처럼 **꺾쇠**는 표준 라이브러리, `"utils.h"` 처럼 **큰따옴표**는 내가 만든(같은 폴더) 헤더.
- 모든 문장 끝에는 세미콜론 `;` 을 붙인다.
- `//` 는 한 줄 주석, `/* ... */` 는 여러 줄 주석.

---

## 1. 변수와 자료형
| 자료형 | 의미 | 예시 |
|---|---|---|
| `int` | 정수 | `int n = 10;` |
| `double` | 실수(소수점) | `double avg = 3.14;` |
| `char` | 문자 1개 | `char c = 'A';` (작은따옴표) |
| 배열 | 같은 자료형 여러 개 | `int a[5];` |
| 문자열 | char 배열 | `char s[20] = "hello";` (큰따옴표) |

- 배열 인덱스는 **0부터** 시작: `a[0]`, `a[1]`, ... , `a[4]` (총 5칸)
- `int a[5] = {0};` → 모두 0으로 초기화

---

## 2. printf / scanf 형식 지정자 (가장 자주 헷갈림)
| 지정자 | 자료형 | 비고 |
|---|---|---|
| `%d` | int 정수 | |
| `%f` | 실수 출력 | `%.2f` = 소수 둘째 자리까지 |
| `%lf` | double 입력(scanf) | 출력은 `%f` 써도 됨 |
| `%c` | 문자 | |
| `%s` | 문자열 | |

```c
int n = 5;  double g = 3.82;  char ch = 'Q';
printf("%d %.2f %c\n", n, g, ch);   // 출력: 5 3.82 Q

scanf("%d", &n);     // 입력받을 변수 앞에 & (주소!)
scanf(" %c", &ch);   // %c 앞에 공백 한 칸! (직전 엔터를 무시하려고)
```
- `\n` 줄바꿈, `\t` 탭, `%4d` 4칸 폭으로 우측 정렬, `%-10s` 10칸 폭 좌측 정렬.

---

## 3. 구조체 (struct) ★★★ 이 라이브러리의 핵심
여러 값을 하나로 묶은 것. 드론·좌표·작업 등 전부 구조체다.
```c
typedef struct {
    int id;
    int x, y;
    int battery;
} Drone;          // 이제 'Drone'이 하나의 자료형이 된다

Drone d;                    // 구조체 변수 선언
d.id = 1;                   // 멤버 접근은 점(.)
d.battery = 100;
printf("%d\n", d.battery);  // 100
```
- **구조체 배열**: `Drone fleet[20];  fleet[0].id = 1;  fleet[0].battery = 50;`
- **구조체끼리 통째로 복사/교환** 가능 (정렬할 때 이렇게 교환):
```c
Drone temp = a[i];
a[i] = a[j];
a[j] = temp;        // a[i]와 a[j]를 통째로 맞바꿈
```
- 트리/리스트 노드도 구조체다 (자기 자신을 가리키는 포인터를 멤버로 가짐):
```c
typedef struct BSTNode {
    int key;
    struct BSTNode* left;   // 왼쪽 자식 주소
    struct BSTNode* right;  // 오른쪽 자식 주소
} BSTNode;
```

---

## 4. 포인터 (pointer) ★★★
포인터 = "어떤 변수가 들어 있는 **주소**". 트리·연결 리스트·결과 돌려받기에 꼭 필요.
```c
int x = 10;
int* p = &x;      // &x = x의 주소.  p는 'x를 가리키는 포인터'
printf("%d\n", *p);   // *p = p가 가리키는 값 = 10 (이걸 '역참조'라 함)
*p = 20;              // x가 20으로 바뀐다
```
- **구조체 포인터는 멤버 접근에 화살표 `->`** 를 쓴다:
```c
Drone* dp = &d;
dp->battery = 50;     // (*dp).battery 와 같은 뜻. 화살표가 편하다.
```
- **함수가 원본을 바꾸게 하려면 주소(&)를 넘긴다**:
```c
void setTen(int* p) { *p = 10; }
int a = 0;
setTen(&a);           // a가 10이 된다
```
  우리 라이브러리의 `popXY(S, &pt)`, `binarySearch(a, n, key, &cmp)` 가 이 방식 —
  **결과를 `&변수` 로 받아온다.** (반환값 외에 추가로 값을 돌려주는 흔한 패턴)

---

## 5. 동적 할당 malloc / free ★★
실행 중에 개수가 정해지는 것(트리 노드, 리스트 노드 등)에 사용.
```c
Drone* d = (Drone*)malloc(sizeof(Drone));  // Drone 1개 크기만큼 메모리 확보
d->id = 1;
free(d);                                    // 다 쓰면 반드시 해제!
```
- `sizeof(자료형)` = 그 자료형의 바이트 크기.
- **우리 라이브러리에서는 `createXxx()` 가 malloc을 대신** 해준다.
  그래서 직접 malloc 할 일은 거의 없고, **`createX()` 했으면 `freeX()`(또는 `free()`)** 만 기억하면 된다.
```c
CQueue* Q = createCQueue();   // 생성 (내부에서 malloc)
// ... 사용 ...
free(Q);                      // 해제
```

---

## 6. 배열을 함수에 넘기기
```c
void printAll(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
}
int a[5] = {1,2,3,4,5};
printAll(a, 5);     // 배열 이름만 넘긴다. 크기 n도 함께!
```
- C는 함수가 배열 크기를 모른다 → **항상 개수 `n` 을 같이 넘긴다** (라이브러리 함수 대부분 이 형태).
- 배열 원소 개수 구하기(선언된 그 자리에서만): `int n = sizeof(a) / sizeof(a[0]);`

---

## 7. 함수
```c
int add(int a, int b) {   // 반환형  이름(매개변수들)
    return a + b;
}
```
- 반환형이 `void` 면 돌려주는 값이 없다는 뜻.
- **선언은 헤더(.h)**, **구현은 소스(.c)** 에 나눠 둔다 (8장 참고).

---

## 8. 헤더(.h) / 소스(.c) / 매크로
- `.h` (헤더) = 함수 **선언** + 구조체 정의 (= 설명서/목차)
- `.c` (소스) = 함수 **구현** (= 실제 내용)
- 어떤 모듈을 쓰려면 `#include "그모듈.h"` 한 줄이면 된다.
- `#pragma once` = 헤더가 두 번 포함되는 것을 막음 (헤더 맨 위에 그냥 둔다).
- `#define N 20` = 코드의 `N` 을 전부 `20` 으로 치환. 크기 상수를 바꿀 때 한 곳만 고치면 됨.
```c
#define CQ_SIZE 100   // 이 값을 바꾸면 원형 큐 크기가 전부 바뀐다
```

---

## 9. 반복문 / 조건문 / switch
```c
for (int i = 0; i < n; i++) { /* n번 반복 */ }
while (조건) { /* 조건이 참인 동안 반복 */ }

if (a > b) { ... }
else if (a == b) { ... }
else { ... }

switch (menu) {
    case 1: /* menu가 1일 때 */ break;   // break 빼먹으면 아래로 흘러내림!
    case 2: ... break;
    default: ... break;                  // 아무 case도 아닐 때
}
```

---

## 10. 파일 입출력 ★★★ 시험 단골
```c
FILE* fp = fopen("data.txt", "w");   // 파일 열기. 모드: "r"읽기 "w"새로쓰기 "a"이어쓰기
if (fp == NULL) {                    // 항상 NULL 검사!
    printf("파일 열기 실패\n");
    return 1;
}
fprintf(fp, "%d %d\n", x, y);        // 파일에 쓰기 (printf와 형식 동일)
fscanf(fp, "%d %d", &x, &y);         // 파일에서 읽기 (scanf와 형식 동일, & 필수)
fclose(fp);                          // 반드시 닫기! (안 닫으면 내용이 비거나 잘림)
```
- "한 줄씩" 또는 "단어씩" 읽으려면 → utils의 `readLinesFromFile`, `readWordsFromFile`.
- 숫자 배열/좌표 읽고 쓰기 → utils의 `readArrayFromFile`, `writeArrayToFile`, `readPointsFromFile` 등 (직접 fopen 안 해도 됨).
- `fscanf(...) == 2` 처럼 **읽은 개수로 끝(EOF) 판정**:
```c
while (fscanf(fp, "%d %d", &x, &y) == 2) { /* x, y가 잘 읽혔을 때만 */ }
```

---

## 11. 이 라이브러리에서 반복되는 패턴 3가지 (이것만 알면 조립 끝)
1. **생성 → 사용 → 해제**
   ```c
   CQueue* Q = createCQueue();
   enCQueue(Q, 10);  int v = deCQueue(Q);
   free(Q);
   ```
2. **트리는 `root =` 로 다시 받기** (안 받으면 트리가 망가짐!)
   ```c
   root = bstInsert(root, 50);
   root = bstDelete(root, 50);
   ```
3. **결과를 `&변수` 로 받기**
   ```c
   Point pt;   popXY(S, &pt);            // pt에 좌표가 담김
   int cmp;    binarySearch(a, n, k, &cmp);   // cmp에 비교 횟수가 담김
   ```

---

## 12. 자주 하는 실수 체크리스트
- [ ] 세미콜론 `;` 빠뜨림 → **바로 윗줄**을 확인
- [ ] scanf에 `&` 안 붙임 → `scanf("%d", &n)`
- [ ] `%c` 입력 시 앞 공백 빠뜨림 → `scanf(" %c", &ch)`
- [ ] fopen 후 NULL 검사 / fclose 누락
- [ ] `createX()` 했는데 `free` 안 함 (메모리 누수)
- [ ] 배열 범위 초과 (`int a[5];` 인데 `a[5]` 접근 — 0~4까지만!)
- [ ] 트리 삽입/삭제 후 `root =` 로 안 받음
- [ ] `initRandom()` 을 main 맨 앞에서 안 부름 → 매번 같은 난수

> 실제 에러 메시지(C2065, LNK2019, 0xC0000005 ...) 대처는 **TROUBLESHOOTING.md** 참고.
> 모듈별 함수 사용법과 시험 유형별 조립 레시피는 **README.md** 참고.
