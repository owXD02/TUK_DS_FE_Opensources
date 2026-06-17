/*=====================================================================
 * 문제 5. 수식 괄호 검사 (스택) - 라이브러리 조립 풀이
 *  사용 라이브러리: stack(IntStack에 여는 괄호 문자를 int로 저장)
 *  직접 구현: 여는/닫는 괄호 짝 판정 로직 (아래 주석)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "stack.h"

/* 닫는 괄호 c에 대응하는 여는 괄호를 반환 (직접 구현: 단순 매핑 표) */
static char opener(char c) {
	if (c == ')') return '(';
	if (c == '}') return '{';
	if (c == ']') return '[';
	return 0;
}

/* 괄호 균형 검사: 균형이면 1, 아니면 0
   ── 직접 구현 ──
   여는 괄호는 스택에 push, 닫는 괄호를 만나면 pop해서 짝이 맞는지 비교.
   ① 닫는데 스택이 비어 있으면 → 불균형
   ② pop한 여는 괄호가 짝이 아니면 → 불균형
   ③ 문자열이 끝났는데 스택에 여는 괄호가 남아 있으면 → 불균형 */
static int isBalanced(const char* s) {
	IntStack* st = createIntStack();
	int ok = 1;
	for (int i = 0; s[i]; i++) {
		char c = s[i];
		if (c == '(' || c == '{' || c == '[')
			pushInt(st, c);                         /* 여는 괄호 push (char→int) */
		else if (c == ')' || c == '}' || c == ']') {
			if (isIntStackEmpty(st)) { ok = 0; break; }      /* ① */
			char top = (char)popInt(st);
			if (top != opener(c)) { ok = 0; break; }         /* ② */
		}
	}
	if (!isIntStackEmpty(st)) ok = 0;               /* ③ */
	free(st);
	return ok;
}

int main(void) {
	const char* tests[] = { "(a+{b-[c]})", "(a+[b)]", "{[()()]}", "(((" };
	for (int i = 0; i < 4; i++)
		printf("\"%s\" -> %s\n", tests[i], isBalanced(tests[i]) ? "균형" : "불균형");
	return 0;
}
