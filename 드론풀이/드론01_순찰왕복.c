/*=====================================================================
 * 드론 1. 순찰 경로 생성 + 왕복 시뮬레이션 - 라이브러리 조립 풀이
 *  요구: 난수 경로를 만들고, 출발->도착->복귀로 순찰. 배터리 소진 시 추락.
 *  사용 라이브러리: drone(createDronePathFile, patrolSimulation), utils
 *  직접 구현 없음 - 라이브러리 함수 호출만으로 완성.
 *=====================================================================*/
#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"
#include "drone.h"

int main(void) {
	initRandom();

	/* (1) 0~9 격자 위에 난수 경로 8개 지점 생성 -> drone_path.txt 저장+화면출력 */
	createDronePathFile("drone_path.txt", 8, 9, 9);

	/* (2) 배터리 50으로 순찰: 전진(출발->도착) 후 왔던 길로 복귀.
	       비행 기록은 patrol_log.txt에도 저장. 반환값=남은 배터리(-1=추락) */
	FILE* log = fopen("patrol_log.txt", "w");
	int remain = patrolSimulation("drone_path.txt", 50, log);
	if (log) fclose(log);

	if (remain >= 0) printf("\n순찰 성공! 남은 배터리 = %d\n", remain);
	else             printf("\n배터리 부족으로 추락!\n");
	return 0;
}
