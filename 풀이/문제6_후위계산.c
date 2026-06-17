/*=====================================================================
 * 문제 6. 후위 표기식 계산 (스택) - 라이브러리 조립 풀이
 *  사용 라이브러리: utils(readLinesFromFile), stack(IntStack에 피연산자 저장)
 *  입력: postfix.txt (한 줄에 후위식 하나, 피연산자는 한 자리 정수, 연산자 + - * /)
 *  출력: result.txt
 *  직접 구현: 후위 표기 평가 알고리즘 (아래 자세히 주석)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "stack.h"

/* 후위식 한 줄을 계산해 결과 반환
   ── 직접 구현: 후위 표기 평가 ──
   왼쪽부터 한 글자씩 보며
    - 숫자면 정수로 바꿔 스택에 push
    - 연산자면 위에서 두 개 pop. 주의: 먼저 pop한 값이 '오른쪽' 피연산자(b),
      그 다음 pop한 값이 '왼쪽' 피연산자(a). a (op) b 를 계산해 다시 push
   문자열이 끝나면 스택에 남은 하나가 최종 결과 */
static int evalPostfix(const char* expr) {
	IntStack* st = createIntStack();
	for (int i = 0; expr[i]; i++) {
		char c = expr[i];
		if (c >= '0' && c <= '9')
			pushInt(st, c - '0');           /* 문자 숫자 → 정수 */
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			int b = popInt(st);             /* 나중에 들어온 것 = 오른쪽 */
			int a = popInt(st);             /* 그 다음 = 왼쪽 */
			int r = 0;
			if (c == '+') r = a + b;
			else if (c == '-') r = a - b;
			else if (c == '*') r = a * b;
			else r = (b != 0) ? a / b : 0;  /* 0으로 나누기 방어 */
			pushInt(st, r);
		}
	}
	int result = popInt(st);                /* 마지막에 남은 값 = 결과 */
	free(st);
	return result;
}

int main(void) {
	char lines[50][LINE_LEN];
	int n = readLinesFromFile("postfix.txt", lines, 50);   /* 조립: 줄 단위 읽기 */
	if (n <= 0) {
		printf("postfix.txt가 없습니다. 예시 한 줄: 52+8*\n");
		return 1;
	}

	FILE* out = fopen("result.txt", "w");
	for (int i = 0; i < n; i++) {
		int r = evalPostfix(lines[i]);
		dualPrintf(out, "%s = %d\n", lines[i], r);   /* 화면+파일 동시 */
	}
	if (out) fclose(out);
	return 0;
}
