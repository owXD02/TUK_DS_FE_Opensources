/*=====================================================================
 * 문제 15. 대용량 난수 정렬 후 파일 저장 (퀵/병합) - 조립 풀이
 *  사용 라이브러리: utils(난수/파일/검증), sort(quickSort)
 *  직접 구현: 중앙값 출력 (정렬 후 가운데 원소, 한 줄)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "sort.h"

int main(void) {
	initRandom();
	static int a[1000];                         /* static: 큰 배열을 스택이 아닌 곳에 */
	genRandomArray(a, 1000, 0, 99999);          /* (1) 난수 1000개 */
	writeArrayToFile("raw.txt", a, 1000);       /*     원본 저장 */

	int n = readArrayFromFile("raw.txt", a, 1000);  /* (2) 읽기 */
	quickSort(a, n, 1);                         /*     퀵 정렬(오름차순) - mergeSort(a,n,1)도 동일 */
	writeArrayToFile("sorted.txt", a, n);       /* (3) 결과 저장 */

	/* (4) 검증 + 중앙값(median): 정렬됐으므로 가운데 원소가 곧 중앙값 */
	printf("정렬 검증: %s\n", isSortedArray(a, n, 1) ? "성공" : "실패");
	printf("중앙값(median) = %d\n", a[n / 2]);
	return 0;
}
