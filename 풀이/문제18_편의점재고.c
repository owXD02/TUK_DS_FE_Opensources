/*=====================================================================
 * 문제 18. 편의점 재고 관리 (BST + 정렬 + 파일) - 조립 풀이
 *  상품 = (상품코드, 재고수량) 2값 → Point(x=코드, y=수량)로 표현
 *  사용 라이브러리: utils(난수/파일/동시출력), bst(코드 BST 검색),
 *                   sort(sortPointsBy: 좌표 배열을 특정 키로 정렬)
 *  직접 구현: 합계/평균 합산, 하위 3개 선택 (작은 루프, 주석)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "bst.h"
#include "sort.h"

int main(void) {
	initRandom();

	/* (1) inventory.txt에서 상품 읽기. 없으면 난수로 생성 후 저장 */
	Point inv[10];
	int n = readPointsFromFile("inventory.txt", inv, 10);
	if (n <= 0) {
		n = 10;
		for (int i = 0; i < n; i++) {
			inv[i].x = 101 + i;             /* 상품코드 101~110 */
			inv[i].y = randInt(0, 50);      /* 재고수량 0~50 */
		}
		writePointsToFile("inventory.txt", inv, n);
	}

	/* (2) 상품코드를 키로 하는 BST 구성 + 코드로 검색 (조립) */
	int codes[10];
	for (int i = 0; i < n; i++) codes[i] = inv[i].x;
	BSTNode* root = bstFromArray(codes, n);
	int target = inv[0].x;
	printf("코드 %d 검색: %s\n", target, bstSearch(root, target) ? "있음" : "없음");

	/* (3) 재고수량(y) 기준 오름차순 정렬 → 앞 3개가 '재고 부족 하위 3개' */
	sortPointsBy(inv, n, 'y', 1);          /* 'y'=수량 기준, 1=오름차순 */
	printf("재고 부족 경고(하위 3개):\n");
	for (int i = 0; i < 3 && i < n; i++)
		printf(" 코드 %d : %d개\n", inv[i].x, inv[i].y);

	/* (4) 합계/평균 (직접 구현: 작은 합산 루프) + 화면+파일 동시 출력 */
	int sum = 0;
	for (int i = 0; i < n; i++) sum += inv[i].y;
	FILE* rep = fopen("report.txt", "w");
	dualPrintf(rep, "총 재고 합계 = %d, 평균 = %.2f\n", sum, (double)sum / n);
	if (rep) fclose(rep);

	bstFree(root);
	return 0;
}
