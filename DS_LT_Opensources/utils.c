/*=====================================================================
 * utils.c - 범용 유틸리티 구현부 (설명은 utils.h 참고)
 *=====================================================================*/
#include "utils.h"

/*---------------- 난수 생성 ----------------*/

/* 난수 시드를 현재 시간으로 설정한다. main 시작 시 딱 1번만 호출할 것.
 * (여러 번 호출하면 같은 난수가 반복될 수 있음) */
void initRandom(void)
{
	srand((unsigned int)time(NULL));
}

/* min 이상 max 이하의 난수 1개를 반환한다. (양 끝 포함) */
int randInt(int min, int max)
{
	if (min > max) {            /* 인자를 거꾸로 줘도 동작하도록 교환 */
		int t = min; min = max; max = t;
	}
	return min + rand() % (max - min + 1);
}

/* min~max 범위의 난수 n개를 배열 a에 채운다. (중복 허용) */
void genRandomArray(int a[], int n, int min, int max)
{
	int i;
	for (i = 0; i < n; i++)
		a[i] = randInt(min, max);
}

/* 중복 없는 난수 n개를 배열 a에 채운다.
 * 주의: (max - min + 1)이 n보다 크거나 같아야 한다. */
void genRandomArrayUnique(int a[], int n, int min, int max)
{
	int i, j, candidate, duplicated;

	if (max - min + 1 < n) {
		printf("[경고] 범위(%d~%d)가 %d개보다 좁아 중복 없는 생성 불가\n", min, max, n);
		return;
	}
	for (i = 0; i < n; i++) {
		do {                        /* 이미 뽑은 값이면 다시 뽑는다 */
			candidate = randInt(min, max);
			duplicated = 0;
			for (j = 0; j < i; j++) {
				if (a[j] == candidate) { duplicated = 1; break; }
			}
		} while (duplicated);
		a[i] = candidate;
	}
}

/* 0~maxX, 0~maxY 범위의 난수 좌표 n개를 배열 p에 채운다. */
void genRandomPoints(Point p[], int n, int maxX, int maxY)
{
	int i;
	for (i = 0; i < n; i++) {
		p[i].x = randInt(0, maxX);
		p[i].y = randInt(0, maxY);
	}
}

/*---------------- 배열 도우미 ----------------*/

/* 두 정수 변수의 값을 교환한다. 사용법: swapInt(&a[i], &a[j]); */
void swapInt(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/* src 배열 n개를 dst 배열로 복사한다. (정렬 전 원본 보존용) */
void copyArray(const int src[], int dst[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		dst[i] = src[i];
}

/* 배열을 화면에 한 줄로 출력한다. 예) "  5  12  37 ..." */
void printArray(const int a[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%4d", a[i]);
	printf("\n");
}

/* 배열이 정렬되어 있는지 검사한다.
 * ascending=1 : 오름차순 검사 / ascending=0 : 내림차순 검사
 * 정렬되어 있으면 1, 아니면 0 반환 */
int isSortedArray(const int a[], int n, int ascending)
{
	int i;
	for (i = 0; i < n - 1; i++) {
		if (ascending && a[i] > a[i + 1]) return 0;
		if (!ascending && a[i] < a[i + 1]) return 0;
	}
	return 1;
}

/*---------------- 화면+파일 동시 출력 ----------------*/

/* printf처럼 사용하면 화면에 출력되고, fp가 NULL이 아니면 파일에도 기록된다. */
void dualPrintf(FILE* fp, const char* fmt, ...)
{
	va_list args;

	va_start(args, fmt);        /* 1) 화면 출력 */
	vprintf(fmt, args);
	va_end(args);

	if (fp != NULL) {           /* 2) 파일 출력 (fp가 있을 때만) */
		va_start(args, fmt);
		vfprintf(fp, fmt, args);
		va_end(args);
	}
}

/*---------------- 파일 입출력 (정수) ----------------*/

/* 정수 n개를 파일에 한 줄에 하나씩 저장한다. 성공 시 1, 실패 시 0 반환.
 * 공백 구분으로 저장하고 싶으면 "%d\n"을 "%d "로 바꾸면 된다. */
int writeArrayToFile(const char* filename, const int a[], int n)
{
	int i;
	FILE* fp = fopen(filename, "w");      /* "w": 새로 쓰기, "a": 이어 쓰기 */
	if (fp == NULL) {
		printf("[오류] %s 파일을 열 수 없습니다.\n", filename);
		return 0;
	}
	for (i = 0; i < n; i++)
		fprintf(fp, "%d\n", a[i]);
	fclose(fp);
	return 1;
}

/* 파일에서 정수를 읽어 배열에 저장한다. (공백/줄바꿈 구분 모두 OK)
 * 최대 maxN개까지 읽고, 실제 읽은 개수를 반환한다. 파일 열기 실패 시 -1. */
int readArrayFromFile(const char* filename, int a[], int maxN)
{
	int count = 0;
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("[오류] %s 파일을 열 수 없습니다.\n", filename);
		return -1;
	}
	while (count < maxN && fscanf(fp, "%d", &a[count]) == 1)
		count++;
	fclose(fp);
	return count;
}

/*---------------- 파일 입출력 (좌표) ----------------*/

/* 좌표 n개를 "x y" 형식으로 한 줄에 하나씩 저장한다. 성공 시 1, 실패 시 0. */
int writePointsToFile(const char* filename, const Point p[], int n)
{
	int i;
	FILE* fp = fopen(filename, "w");
	if (fp == NULL) {
		printf("[오류] %s 파일을 열 수 없습니다.\n", filename);
		return 0;
	}
	for (i = 0; i < n; i++)
		fprintf(fp, "%d %d\n", p[i].x, p[i].y);
	fclose(fp);
	return 1;
}

/* 파일에서 "x y" 형식의 좌표를 읽어 배열에 저장한다.
 * 최대 maxN개까지 읽고, 실제 읽은 개수를 반환한다. 파일 열기 실패 시 -1. */
int readPointsFromFile(const char* filename, Point p[], int maxN)
{
	int count = 0;
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("[오류] %s 파일을 열 수 없습니다.\n", filename);
		return -1;
	}
	while (count < maxN && fscanf(fp, "%d %d", &p[count].x, &p[count].y) == 2)
		count++;
	fclose(fp);
	return count;
}

/*---------------- 파일 입출력 (문자열) ----------------*/

/* 파일에서 공백/줄바꿈 단위로 단어를 읽어 2차원 char 배열에 저장한다.
 * (중간고사 tdm.c의 단어 읽기와 같은 방식: fscanf %s)
 * 최대 maxN개까지 읽고, 실제 읽은 개수를 반환한다. 파일 열기 실패 시 -1. */
int readWordsFromFile(const char* filename, char words[][WORD_LEN], int maxN)
{
	int count = 0;
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("[오류] %s 파일을 열 수 없습니다.\n", filename);
		return -1;
	}
	/* %49s : WORD_LEN-1 글자까지만 읽어 배열 넘침 방지 */
	while (count < maxN && fscanf(fp, "%49s", words[count]) == 1)
		count++;
	fclose(fp);
	return count;
}

/* 파일에서 한 줄씩 읽어 2차원 char 배열에 저장한다. (줄 끝의 \n은 제거)
 * 최대 maxN줄까지 읽고, 실제 읽은 줄 수를 반환한다. 파일 열기 실패 시 -1. */
int readLinesFromFile(const char* filename, char lines[][LINE_LEN], int maxN)
{
	int count = 0;
	size_t len;
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("[오류] %s 파일을 열 수 없습니다.\n", filename);
		return -1;
	}
	while (count < maxN && fgets(lines[count], LINE_LEN, fp) != NULL) {
		len = strlen(lines[count]);
		if (len > 0 && lines[count][len - 1] == '\n')   /* 줄 끝 개행 문자 제거 */
			lines[count][len - 1] = '\0';
		count++;
	}
	fclose(fp);
	return count;
}

/*---------------- 수행시간 측정 ----------------*/

static clock_t g_timerStart = 0;     /* startTimer가 기록하는 시작 시각 */

/* 타이머를 시작한다. 측정할 작업 직전에 호출. */
void startTimer(void)
{
	g_timerStart = clock();
}

/* startTimer 이후 경과한 시간을 초 단위(double)로 반환한다.
 * 예) printf("검색시간: %.6f초\n", elapsedSec()); */
double elapsedSec(void)
{
	return (double)(clock() - g_timerStart) / CLOCKS_PER_SEC;
}

/*---------------- 파일 자동 오픈 / 폴더 생성 ----------------*/

/* 결과 파일을 메모장으로 자동 오픈한다. ("출력파일 자동 오픈" 요구사항 대응)
 * 반드시 fclose()로 파일을 닫은 뒤에 호출할 것! */
void openFileAuto(const char* filename)
{
	char cmd[300];
	sprintf(cmd, "start notepad %s", filename);   /* start: 프로그램을 멈추지 않고 열기 */
	system(cmd);
}

/* 폴더를 생성한다. 이미 있으면 조용히 넘어간다.
 * 예) makeFolder("DB");  fopen("DB\\log1.txt", "w");  <- 폴더 안에 파일 저장 */
void makeFolder(const char* name)
{
	char cmd[300];
	sprintf(cmd, "mkdir %s 2>nul", name);         /* 2>nul: 이미 있을 때 오류 메시지 숨김 */
	system(cmd);
}
