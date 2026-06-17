/*=====================================================================
 * 문제 3. 웹 브라우저 방문 기록 (덱) - 라이브러리 조립 풀이
 *  사용 라이브러리: deque(방문 기록), stack(앞으로가기 보관소)
 *  페이지는 정수 ID(1,2,3...)로 표현(실제 URL 대용).
 *  직접 구현: 방문/뒤로/앞으로 명령 처리 규칙 (각 함수 주석 참고)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "deque.h"
#include "stack.h"

/* 현재 페이지 = 덱의 rear(맨 뒤). 덱 상태도 함께 출력한다. */
static void showState(Deque* hist) {
	int cur = dqPeekRear(hist);            /* 맨 뒤 = 현재 보고 있는 페이지 */
	if (cur == -1) printf("   현재 없음 |");
	else           printf("   현재 %d |", cur);
	printDeque(hist, NULL);
}

/* 방문: 새 페이지를 rear에 삽입. 새로 방문하면 '앞으로 기록'은 무효 → 보관소 비움 */
static void visit(Deque* hist, IntStack* fwd, int page) {
	dqInsertRear(hist, page);
	while (!isIntStackEmpty(fwd)) popInt(fwd);   /* 앞으로 기록 폐기 */
	printf(" 방문 %d ->", page); showState(hist);
}

/* 뒤로: rear에서 하나 빼 보관소(fwd)로. 단, 뺐더니 덱이 비면 갈 곳이 없으므로
   되돌려 놓고 "더 이상 뒤로" 메시지. (직접 구현: deque엔 개수 함수가 없어
   '빼본 뒤 비었는지'로 1개 이하를 판정) */
static void back(Deque* hist, IntStack* fwd) {
	if (isDQEmpty(hist)) { printf(" 뒤로 -> 더 이상 뒤로 갈 수 없습니다\n"); return; }
	int x = dqDeleteRear(hist);
	if (isDQEmpty(hist)) {                  /* 이전 페이지가 없었음 → 복구 */
		dqInsertRear(hist, x);
		printf(" 뒤로 -> 더 이상 뒤로 갈 수 없습니다\n");
		return;
	}
	pushInt(fwd, x);                       /* 빠져나온 페이지는 앞으로용으로 보관 */
	printf(" 뒤로 ->"); showState(hist);
}

/* 앞으로: 보관소에서 pop하여 다시 rear로. 보관소가 비면 불가 */
static void forward(Deque* hist, IntStack* fwd) {
	if (isIntStackEmpty(fwd)) { printf(" 앞으로 -> 더 이상 앞으로 갈 수 없습니다\n"); return; }
	int x = popInt(fwd);
	dqInsertRear(hist, x);
	printf(" 앞으로 ->"); showState(hist);
}

int main(void) {
	Deque* hist = createDeque();      /* 방문 기록(뒤로 갈 수 있는 페이지들) */
	IntStack* fwd = createIntStack(); /* 앞으로 갈 페이지 보관소 */

	/* 명령 10개 수행 (요구사항: 8개 이상) */
	visit(hist, fwd, 1);
	visit(hist, fwd, 2);
	visit(hist, fwd, 3);
	back(hist, fwd);        /* 3 -> 2 */
	back(hist, fwd);        /* 2 -> 1 */
	forward(hist, fwd);     /* 1 -> 2 */
	visit(hist, fwd, 4);    /* 새 방문 → 앞으로기록(3) 폐기 */
	back(hist, fwd);        /* 4 -> 2 */
	back(hist, fwd);        /* 2 -> 1 */
	back(hist, fwd);        /* 1뿐 → 더 이상 뒤로 불가 */

	freeDeque(hist);
	free(fwd);
	return 0;
}
