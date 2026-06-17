#include "drone.h"

#define MAX 100			// 경로의 개수
#define MAX_B 1000		// 드론의 베터리의 최대 잔량

int battery = 1000;		// 현재 베터리 용량

void createDronePath()		// 경로를 설정하는 함수
{
	FILE* f;
	f = fopen("drone_path.txt", "w");		// drone_path.txt 에 쓰기모드를 사용하여 드론의 경로 저장
	int x, y;								// x좌표 y좌표

	for (int i = 0; i < MAX; i++)
	{
		x = rand() % 9;						// 0~9까지 변수 저장
		y = rand() % 9;						// 0~9까지 변수 저장

		printf("%8d %8d\n", x, y);			// 변수를 화면에 출력
		fprintf(f, "%8d %8d\n", x, y);		// 변수를 파일에 출력
	}

	fclose(f);								// 파일 닫기
}

DLLH* getDronePath(FILE * fp)				// 드론의 경로를 받는 함수 (파일입출력 파이프라인)
{
	DLLH* head = createDoubleLinkedList();	// 더블 링크드 리스트를 이용하여 드론의 경로를 저장함
	DLLH* temp = head;						// 더블 링크드 리스트에서 자유롭게 이동하기 위한 변수
	int x, y;								// x좌표 y좌표

	for (int i = 0; i < MAX; i++)
	{
		fscanf(fp, "%8d %8d\n", &x, &y);		// fscanf 함수로 파일을 받음
		temp = insertNode(head, temp, x, y);	// 더블 링크드 리스트에 좌표 저장
	}

	return head;							// 더블 링크드 리스트의 헤드 주소를 반환
}

int patrol()								// 순찰 기능 (파이프라인)
{
	FILE* f = fopen("drone_path.txt", "r");			// 드론의 경로를 파일에서 읽음
	FILE* fp = fopen("drone_path_log.txt", "a+");	// 드론이 움직인 경로를 출력
	DLLH* pathListHead = getDronePath(f);			// 파일에서 드론의 경로를 읽고 더블 링크드 리스트로 만듬
	DLL* temp = pathListHead->dhead;				// 링크드 리스트를 자유롭게 움직일 수 있는 temp

	int i;											// for문을 위한 i
	for (i = 0; i < MAX; i++)						// 경로를 모두 읽어들임
	{
		printf("%8d %8d\n", temp->xdata, temp->ydata);				// 드론의 경로를 화면에 출력
		if (battery <= 0) { fclose(f); fclose(fp); return 0; }		// 베터리가 방전될 경우 종료
		battery--;													// 베터리가 닳도록 설계

		if (temp->rlink != NULL)
		{
			temp = temp->rlink;						// 다음 노드로 이동
		}
	}
	printf("목적지 도착, 본부로 귀환 \n");
	for (i = 0; i < MAX - 1; i++)					// 본부로 복귀
	{
		temp = temp->llink;										// 본부로 복귀하기 위한 이전 노드로 이동
		printf("%8d %8d\n", temp->xdata, temp->ydata);			// 경로의 좌표 출력
		if (battery <= 0) { fclose(f); fclose(fp); return 0; }	// 베터리가 방전될 경우 종료
		battery--;												// 베터리가 닳도록 설계
	}

	fclose(f);										// 파일 닫기
	fclose(fp);										// 파일 닫기
	freeDNode(pathListHead);						// 링크드 리스트 해제(메모리 누수 방지)

	return 1;
}

int suicide()
{
	FILE* f = fopen("drone_path.txt", "r");			// 파일에서 드론의 경로를 읽어들임
	int x, y;										// x, y 좌표

	int i;											// for문을 위한 i
	for (i = 0; i < MAX; i++)						// 경로만큼 진행
	{
		if(fscanf(f, "%8d %8d", &x, &y) == EOF) break;	// 파일 읽기가 끝나면 for문을 빠져나옴
		push(x, y);										// stack에 경로 저장
	}
	fclose(f);										// 파일 닫기

	reverseStack();									// 스택을 뒤집는 함수

	while (!isStackEmpty())							// 스택 안의 데이터가 없을 때 까지 진행
	{
		dt* current = pop();									// 현재 경로를 스택에서 없애고 받음
		if (battery <= 0) { free(current); return 0; }			// 베터리가 방전될 경우 종료
		printf("%8d %8d\n", *(current + 0), *(current + 1));	// 화면에 좌표 출력
		battery--;												// 베터리가 닳도록 설계
		free(current);											// 동적할당 받은 리스트를 해제
	}
	return 1;
}

void chargeBattery(int n)
{
	if (n > MAX_B - battery) { battery = MAX_B; }		// 배터리가 최대 용량 이상으로 충전되지 않도록 설계
	else { battery += n; }								// 배터리를 n만큼 충전
}

void showMenu()
{
	createDronePath();									// 드론의 경로 생성
	int menu;											// 매뉴를 받음
	int b;												// 배터리 입력받음

	int i = 0;											// while문을 위한 i
	while (i < 1)
	{
		printf("1. 순찰\t2. 자폭 공격\t3. 드론 배터리 잔량 확인\n");		// 매뉴
		printf("4. 드론 베터리 충전\t5. 경로 재설정\t6. 종료 >> ");			// 매뉴
		scanf("%d", &menu);													// 매뉴를 받음
		switch (menu) {
		case 1:
			if (patrol() == 1) { printf("드론이 본부로 도착하였습니다. \n"); }		// 1이 반환되면 무사 귀환
			else { printf("드론이 중간에 불시착하였습니다."); i++; }				// 0이 반환되면 베터리 방전으로 인한 불시착
			break;
		case 2:
			if (suicide() == 1) { printf("임무를 완수하였습니다.\n"); }				// 1이 반환되면 무사 귀환
			else { printf("드론이 중간에 불시착하였습니다."); }						// 0이 반환되면 베터리 방전으로 인한 불시착
			i++;
			break;
		case 3:
			printf("%d\n", battery);						// 베터리 잔량 표기
			break;
		case 4:
			printf("충전할 양 입력 >> ");
			scanf("%d", &b);												// 충전량 입력
			chargeBattery(b);												// 베터리 충전
			printf("충전이 완료되었습니다. 현재 잔량 : %d", battery);		// 충전 후 베터리 잔량 표기
			break;
		case 5:
			createDronePath();								// 경로를 재설정
			break;
		case 6:
			i++;											// 종료
			break;
		default:
			printf("번호를 다시 입력하세요\n");				// 1~6 이외의 다른 수나 문자를 입력할 경우
			break;
		}
	}
}