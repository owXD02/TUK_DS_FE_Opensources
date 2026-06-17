#include "doubleLinkedList.h"

DLLH* createDoubleLinkedList()					// 더블 링크드 리스트 생성
{
	DLLH* DL;
	DL = (DLLH*)malloc(sizeof(DLLH));			// 헤드 생성
	DL->dhead = NULL;							// 아직 노드가 없으므로 NULL 로 생성
	return DL;									// 헤드 주소 반환
}

DLLH* insertNode(DLLH* DL, DLL* pre, dt xd, dt yd)		// pre 뒤에 노드를 삽입
{
	DLL* newNode;
	newNode = (DLL*)malloc(sizeof(DLL));				// 새 노드를 생성
	newNode->xdata = xd;								// x 좌표 저장
	newNode->ydata = yd;								// y 좌표 저장
	newNode->rlink = NULL;								// rlink에 NULL 저장
	newNode->llink = NULL;								// llink에 NULL 저장

	if (DL->dhead == NULL)
	{
		DL->dhead = newNode;							// 노드가 아무것도 없을 경우
	}
	else
	{
		newNode->rlink = pre->rlink;					// newNode의 rlink에 이전노드의 rlink를 저장
		pre->rlink = newNode;							// 이전 노드의 rlink에 newNode의 주소 저장
		newNode->llink = pre;							// newNode의 llink에 이전 노드 주소 저장
		if (newNode->rlink != NULL)						// newNode가 중간삽입일 경우
		{
			newNode->rlink->llink = newNode;			// newNode의 다음 노드의 llink에 newNode의 주소 저장
		}
	}
	return newNode;
}

void deleteDNode(DLLH* DL, DLL* old)
{
	if (DL->dhead == NULL) return;						// 노드가 없으면 삭제할 것이 없음
	else if (old == NULL) return;						// 삭제할 노드가 없으면 종료
	else
	{
		old->llink->rlink = old->rlink;					// 이전 노드의 rlink에 삭제할 노드의 다음 노드의 주소를 저장
		old->rlink->llink = old->llink;					// 삭제할 노드의 다음 노드의 llink에 삭제할 노드의 이전 노드의 주소 저장
		free(old);										// 노드 삭제
	}
}

void freeDNode(DLLH* L)
{
	if (L == NULL)
	{
		return;			// 동적할당 해제할 노드가 없다면 함수 종료
	}

	DLL* p = L->dhead;		// 첫번째 노드 주소를 p에 저장
	DLL* nextNode;			// 다음 노드를 저장할 변수
	while (p != NULL)
	{
		nextNode = p->rlink;		// 다음 노드의 주소 저장
		free(p);					// p 삭제
		p = nextNode;				// p에 다음 노드 저장
	}

	L->dhead = NULL;				// L이 동적할당 해제된 주소를 가르키므로 NULL로 변경
}