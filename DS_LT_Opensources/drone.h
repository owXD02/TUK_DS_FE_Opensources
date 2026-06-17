/*=====================================================================
 * drone.h - 드론 응용 시나리오 모음 (다른 모듈 통합 활용 예시)
 *---------------------------------------------------------------------
 * [무엇이 들어있나]
 *  - Drone 구조체 : id, 좌표(x,y), 배터리
 *  - 경로 파일 생성(난수) / 경로 읽기 / 순찰 왕복 시뮬레이션
 *  - 드론 목록 파일 생성(난수) / 읽기 / 출력 / 정렬 / 탐색
 *
 * [중간고사 기출 패턴과의 대응]
 *  - createDronePathFile  = 난수 경로를 txt로 저장 (기출 createDronePath)
 *  - patrolSimulation     = 경로 따라 전진 후 복귀, 배터리 소모 (기출 patrol)
 *  - 역순 비행이 필요하면 xyStack(stack.h)에 push 후 pop (기출 suicide)
 *
 * [기말 예상 활용]
 *  - "드론 N대의 배터리를 선택 정렬로 내림차순 정렬하라"
 *      -> readDrones + sortDronesBy(a, n, 'b', 0)
 *  - "드론 id를 BST에 넣고 탐색하라"
 *      -> for문으로 bstInsert(root, a[i].id)  (bst.h 참고)
 *  - "임무 좌표를 큐에 넣고 순서대로 처리하라"
 *      -> xyList(xyList.h) 또는 cQueue 사용
 *=====================================================================*/
#pragma once
#include <stdio.h>
#include "utils.h"

typedef struct {
	int id;          /* 드론 고유 번호 */
	int x, y;        /* 현재 위치 좌표 */
	int battery;     /* 배터리 잔량 */
} Drone;

/*------- 경로(좌표) 관련 -------*/
/* 난수 좌표 n개를 "x y" 형식으로 파일에 저장하고 화면에도 출력한다. */
void createDronePathFile(const char* filename, int n, int maxX, int maxY);

/* 경로 파일을 읽어 전진(출발->도착) 후 왔던 길로 복귀하는 순찰 시뮬레이션.
 * 한 지점 이동마다 배터리 1 소모. log가 NULL이 아니면 비행 기록을 파일에도 남긴다.
 * 반환값: 남은 배터리(성공), -1(배터리 부족으로 추락) */
int patrolSimulation(const char* pathFile, int battery, FILE* log);

/*------- 드론 목록 관련 -------*/
/* 드론 n대를 난수로 만들어 "id x y battery" 형식으로 파일에 저장한다.
 * id는 1~n까지 차례로 부여된다. */
void createDroneListFile(const char* filename, int n, int maxX, int maxY, int maxBattery);

/* "id x y battery" 형식의 파일을 읽어 Drone 배열에 담는다.
 * 읽은 드론 수를 반환하고, 파일 열기 실패 시 -1을 반환한다. */
int readDrones(const char* filename, Drone a[], int maxN);

/* Drone 배열을 파일에 "id x y battery" 형식으로 저장한다. 성공 1. */
int writeDrones(const char* filename, const Drone a[], int n);

/* Drone 배열을 표 형태로 출력한다. log가 NULL이 아니면 파일에도 기록. */
void printDrones(const Drone a[], int n, FILE* log);

/* Drone 배열을 선택 정렬로 정렬한다.
 * key : 'i'=id, 'x'=x좌표, 'y'=y좌표, 'b'=배터리
 * ascending : 1=오름차순, 0=내림차순
 * 예) sortDronesBy(a, n, 'b', 0);  // 배터리 많은 순 정렬 */
void sortDronesBy(Drone a[], int n, char key, int ascending);

/* id로 드론을 찾아 배열 인덱스를 반환한다(순차 탐색). 없으면 -1. */
int findDroneById(const Drone a[], int n, int id);

/* id로 드론을 찾아 인덱스를 반환한다(이진 탐색). 없으면 -1.
 * 주의: 먼저 sortDronesBy(a, n, 'i', 1)로 id 오름차순 정렬이 되어 있어야 함! */
int binarySearchDroneId(const Drone a[], int n, int id);
