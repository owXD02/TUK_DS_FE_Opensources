/*=====================================================================
 * utils.h - 범용 유틸리티 (난수 생성 / 파일 입출력 / 배열 도우미)
 *---------------------------------------------------------------------
 * [무엇이 들어있나]
 *  - Point 구조체      : (x, y) 좌표 한 쌍 (드론 경로 등에서 사용)
 *  - 난수 생성 함수    : initRandom, randInt, genRandomArray, ...
 *  - 파일 입출력 함수  : 정수 배열 / 좌표 배열을 txt로 읽고 쓰기
 *  - 출력 도우미       : printArray, dualPrintf(화면+파일 동시 출력)
 *
 * [사용 순서 예시]
 *  initRandom();                                  // main 시작 시 1회만 호출!
 *  int a[20];
 *  genRandomArray(a, 20, 0, 99);                  // 0~99 난수 20개 생성
 *  writeArrayToFile("data.txt", a, 20);           // 파일로 저장
 *  int b[100];
 *  int n = readArrayFromFile("data.txt", b, 100); // 파일에서 읽기(개수 반환)
 *=====================================================================*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS   /* scanf, fopen 관련 VS 보안 경고 끄기 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

/* (x, y) 좌표 한 쌍을 표현하는 구조체 - 드론 위치, 경로 등에 사용 */
typedef struct {
	int x;
	int y;
} Point;

/*---------------- 난수 생성 ----------------*/
void initRandom(void);                                    /* 난수 시드 설정. main 맨 앞에서 딱 1번 호출 */
int  randInt(int min, int max);                           /* min~max 범위(양 끝 포함)의 난수 1개 반환 */
void genRandomArray(int a[], int n, int min, int max);    /* min~max 난수 n개를 배열에 채움(중복 허용) */
void genRandomArrayUnique(int a[], int n, int min, int max); /* 중복 없는 난수 n개 (범위가 n 이상이어야 함) */
void genRandomPoints(Point p[], int n, int maxX, int maxY); /* 0~maxX, 0~maxY 범위의 난수 좌표 n개 */

/*---------------- 배열 도우미 ----------------*/
void swapInt(int* a, int* b);                             /* 두 정수 값 교환 */
void copyArray(const int src[], int dst[], int n);        /* 배열 복사 (원본 보존하고 정렬할 때 필수) */
void printArray(const int a[], int n);                    /* 배열을 화면에 한 줄로 출력 */
int  isSortedArray(const int a[], int n, int ascending);  /* 정렬됐는지 검사: 맞으면 1, 아니면 0 */

/*---------------- 화면+파일 동시 출력 ----------------*/
/* printf와 똑같이 쓰되, fp가 NULL이 아니면 파일에도 같은 내용을 기록한다.
 * 예) FILE* log = fopen("result.txt", "w");
 *     dualPrintf(log, "결과: %d\n", x);   -> 화면과 result.txt에 모두 출력 */
void dualPrintf(FILE* fp, const char* fmt, ...);

/*---------------- 파일 입출력 (정수) ----------------*/
int writeArrayToFile(const char* filename, const int a[], int n);  /* 정수 n개를 한 줄에 하나씩 저장. 성공 시 1 */
int readArrayFromFile(const char* filename, int a[], int maxN);    /* 정수를 읽어 배열에 저장. 읽은 개수 반환(실패 -1) */

/*---------------- 파일 입출력 (좌표) ----------------*/
int writePointsToFile(const char* filename, const Point p[], int n); /* "x y" 형식으로 한 줄에 한 좌표씩 저장 */
int readPointsFromFile(const char* filename, Point p[], int maxN);   /* "x y" 형식 좌표 읽기. 읽은 개수 반환(실패 -1) */

/*---------------- 파일 입출력 (문자열) ----------------*/
/* 중간고사 tdm.c처럼 가사/단어가 든 txt를 읽는 문제용.
 * 사용 예) char words[500][WORD_LEN];
 *          int n = readWordsFromFile("song1.txt", words, 500);
 *          char lines[100][LINE_LEN];
 *          int m = readLinesFromFile("memo.txt", lines, 100);          */
#define WORD_LEN 50      /* 단어 하나의 최대 길이 */
#define LINE_LEN 200     /* 한 줄의 최대 길이 */
int readWordsFromFile(const char* filename, char words[][WORD_LEN], int maxN); /* 공백/줄바꿈 단위로 단어 읽기. 읽은 개수 반환(실패 -1) */
int readLinesFromFile(const char* filename, char lines[][LINE_LEN], int maxN); /* 한 줄씩 읽기(줄 끝 \n 제거). 읽은 개수 반환(실패 -1) */

/*---------------- 수행시간 측정 (시험 단골: "검색시간/수행시간 출력") ----------------*/
/* 사용 예) startTimer();
 *          ... 측정할 작업 ...
 *          printf("수행시간: %.6f초\n", elapsedSec());                  */
void   startTimer(void);     /* 타이머 시작 (clock 기반) */
double elapsedSec(void);     /* startTimer 이후 경과 시간을 초 단위로 반환 */

/*---------------- 파일 자동 오픈 / 폴더 생성 (시험 단골 요구사항) ----------------*/
void openFileAuto(const char* filename);  /* 결과 txt를 메모장으로 자동 오픈 ("파일 자동 오픈" 요구 대응) */
void makeFolder(const char* name);        /* 폴더 생성. 예) makeFolder("DB"); -> DB 폴더에 파일 저장 가능 */
