/*=====================================================================
 * 드론 3. 경로를 연결 큐(FIFO)에 넣고 순서대로 비행 - 조립 풀이
 *  요구: 경로 지점들을 큐에 넣고 먼저 들어온 순서대로 비행.
 *  사용 라이브러리: utils(난수), xyList(좌표 연결 큐)
 *  원리: xyAddRear=enqueue, xyRemoveFront=dequeue → FIFO 큐로 사용.
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "xyList.h"

int main(void) {
	initRandom();

	XYList* q = createXYList();
	for (int i = 0; i < 8; i++)
		xyAddRear(q, randInt(0, 9), randInt(0, 9));   /* enqueue: 경로 지점 추가 */
	xySaveToFile("drone_path.txt", q);                /* 경로 파일로 저장 */

	printf("비행 순서(FIFO):\n");
	Point p;
	while (!isXYListEmpty(q)) {       /* dequeue: 먼저 넣은 지점부터 */
		xyRemoveFront(q, &p);
		printf(" 이동 (%d,%d)\n", p.x, p.y);
	}
	freeXYList(q);
	return 0;
}
