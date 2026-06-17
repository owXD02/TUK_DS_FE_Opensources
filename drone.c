/*=====================================================================
 * drone.c - 드론 응용 시나리오 구현부 (설명은 drone.h 참고)
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS   /* VS 보안 경고 끄기 - 반드시 모든 include보다 위에! */
#include <stdlib.h>
#include "drone.h"
#include "xyList.h"

/*---------------- 경로(좌표) 관련 ----------------*/

/* 난수 좌표 n개를 "x y" 형식으로 파일에 저장하고 화면에도 출력한다. */
void createDronePathFile(const char* filename, int n, int maxX, int maxY)
{
	int i, x, y;
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("[오류] %s 파일을 열 수 없습니다.\n", filename);
		return;
	}
	printf(" --- 드론 경로 %d개 생성 (%s) ---\n", n, filename);
	for (i = 0; i < n; i++) {
		x = randInt(0, maxX);               /* 0~maxX 범위의 난수 좌표 */
		y = randInt(0, maxY);
		printf(" (%3d, %3d)\n", x, y);      /* 화면에 출력 */
		fprintf(fp, "%d %d\n", x, y);       /* 파일에 저장 */
	}
	fclose(fp);
}

/* 경로 파일을 읽어 전진 -> 복귀 순찰을 시뮬레이션한다.
 * 한 지점 이동마다 배터리 1 소모. 반환: 남은 배터리, 추락 시 -1 */
int patrolSimulation(const char* pathFile, int battery, FILE* log)
{
	XYList* path = createXYList();          /* 좌표 이중 연결 리스트에 경로 적재 */
	XYNode* cur;
	int n = xyLoadFromFile(pathFile, path);

	if (n <= 0) {                           /* 파일이 없거나 비어 있는 경우 */
		freeXYList(path);
		return -1;
	}

	dualPrintf(log, " --- 순찰 시작 (지점 %d개, 배터리 %d) ---\n", n, battery);
	cur = path->head;
	while (cur != NULL) {                   /* 1) 전진: head -> tail */
		if (battery <= 0) {
			dualPrintf(log, " 배터리 부족! 드론 추락!\n");
			freeXYList(path);
			return -1;
		}
		dualPrintf(log, " 이동 (%3d, %3d)\n", cur->pt.x, cur->pt.y);
		battery--;                          /* 이동할 때마다 배터리 1 소모 */
		cur = cur->next;
	}

	dualPrintf(log, " --- 끝 지점 도착, 복귀 시작 ---\n");
	cur = (path->tail != NULL) ? path->tail->prev : NULL; /* 마지막 지점은 이미 있으므로 그 이전부터 */
	while (cur != NULL) {                   /* 2) 복귀: tail 직전 -> head (역방향) */
		if (battery <= 0) {
			dualPrintf(log, " 배터리 부족! 드론 추락!\n");
			freeXYList(path);
			return -1;
		}
		dualPrintf(log, " 복귀 (%3d, %3d)\n", cur->pt.x, cur->pt.y);
		battery--;
		cur = cur->prev;
	}

	dualPrintf(log, " --- 복귀 완료! 남은 배터리: %d ---\n", battery);
	freeXYList(path);                       /* 메모리 누수 방지 */
	return battery;
}

/*---------------- 드론 목록 관련 ----------------*/

/* 드론 n대를 난수로 만들어 "id x y battery" 형식으로 저장한다. id는 1~n. */
void createDroneListFile(const char* filename, int n, int maxX, int maxY, int maxBattery)
{
	int i;
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("[오류] %s 파일을 열 수 없습니다.\n", filename);
		return;
	}
	for (i = 0; i < n; i++) {
		fprintf(fp, "%d %d %d %d\n",
			i + 1,                          /* id : 1번부터 차례로 */
			randInt(0, maxX),               /* x 좌표 */
			randInt(0, maxY),               /* y 좌표 */
			randInt(0, maxBattery));        /* 배터리 잔량 */
	}
	fclose(fp);
	printf(" %s에 드론 %d대 정보 저장 완료\n", filename, n);
}

/* "id x y battery" 형식의 파일을 읽어 배열에 담고 읽은 수를 반환한다. */
int readDrones(const char* filename, Drone a[], int maxN)
{
	int count = 0;
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("[오류] %s 파일을 열 수 없습니다.\n", filename);
		return -1;
	}
	while (count < maxN &&
		fscanf(fp, "%d %d %d %d",
			&a[count].id, &a[count].x, &a[count].y, &a[count].battery) == 4) {
		count++;
	}
	fclose(fp);
	return count;
}

/* Drone 배열을 파일에 저장한다. 성공 1, 실패 0. */
int writeDrones(const char* filename, const Drone a[], int n)
{
	int i;
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("[오류] %s 파일을 열 수 없습니다.\n", filename);
		return 0;
	}
	for (i = 0; i < n; i++)
		fprintf(fp, "%d %d %d %d\n", a[i].id, a[i].x, a[i].y, a[i].battery);
	fclose(fp);
	return 1;
}

/* Drone 배열을 표 형태로 출력한다. log가 NULL이 아니면 파일에도 기록. */
void printDrones(const Drone a[], int n, FILE* log)
{
	int i;
	dualPrintf(log, " %4s %5s %5s %8s\n", "id", "x", "y", "battery");
	dualPrintf(log, " --------------------------\n");
	for (i = 0; i < n; i++)
		dualPrintf(log, " %4d %5d %5d %8d\n", a[i].id, a[i].x, a[i].y, a[i].battery);
}

/* 정렬/탐색에 쓸 키 값을 꺼내는 내부 함수 */
static int droneKey(const Drone* d, char key)
{
	switch (key) {
	case 'x': return d->x;
	case 'y': return d->y;
	case 'b': return d->battery;
	default:  return d->id;                 /* 'i' 또는 그 외 = id 기준 */
	}
}

/* Drone 배열을 선택 정렬로 정렬한다. (구조체 정렬 예시: 통째로 대입해 교환) */
void sortDronesBy(Drone a[], int n, char key, int ascending)
{
	int i, j, target;
	Drone temp;

	for (i = 0; i < n - 1; i++) {
		target = i;
		for (j = i + 1; j < n; j++) {
			int kj = droneKey(&a[j], key);
			int kt = droneKey(&a[target], key);
			if (ascending ? (kj < kt) : (kj > kt))  /* 더 앞에 와야 할 드론 발견 */
				target = j;
		}
		temp = a[i];                        /* 구조체는 통째로 대입하면 교환된다 */
		a[i] = a[target];
		a[target] = temp;
	}
}

/* id로 드론을 순차 탐색한다. 찾으면 인덱스, 없으면 -1. */
int findDroneById(const Drone a[], int n, int id)
{
	int i;
	for (i = 0; i < n; i++)
		if (a[i].id == id) return i;
	return -1;
}

/* id로 드론을 이진 탐색한다. (id 오름차순 정렬 필수!) 찾으면 인덱스, 없으면 -1. */
int binarySearchDroneId(const Drone a[], int n, int id)
{
	int begin = 0, end = n - 1, middle;
	while (begin <= end) {
		middle = (begin + end) / 2;
		if (a[middle].id == id)      return middle;
		else if (a[middle].id < id)  begin = middle + 1;  /* 오른쪽 절반 탐색 */
		else                         end = middle - 1;    /* 왼쪽 절반 탐색 */
	}
	return -1;
}
