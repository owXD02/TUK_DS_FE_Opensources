#include "stackL.h"

SLL* top = NULL;			// 스택 top 선언

int isStackEmpty() 
{
	if (top == NULL) return 1;		// 스택이 비어있다면 1 반환
	else return 0;					// 스택에 무엇인가 있다면 0 반환
}

void push(dt xitem, dt yitem)		// 좌표 넣기
{
	SLL* temp = (SLL*)malloc(sizeof(SLL));		// 동적할당으로 스택 생성

	temp->xdata = xitem;						// x좌표 넣기
	temp->ydata = yitem;						// y좌표 넣기
	temp->next = top;							// 아래 노드에 top 좌표를 넣음
	top = temp;									// top 변경
}

dt* pop()
{
	dt xitem, yitem;							// x, y 좌표
	dt* items = (dt*)malloc(sizeof(dt) * 2);	// 동적할당으로 좌표를 저장
	SLL* temp = top;							// temp에 top 주소 저장

	if (isStackEmpty())
	{
		printf("스택이 비었습니다. \n");		// 비어있다면 함수 종료
		return 0;
	}
	else
	{
		xitem = temp->xdata;					// x좌표 꺼내기
		yitem = temp->ydata;					// y좌표 꺼내기
		top = temp->next;						// top을 아래 스택으로 이동
		free(temp);								// temp 동적할당 해제
		items[0] = xitem;						// 동적 할당 받은 리스트에 x좌표 저장
		items[1] = yitem;						// 동적 할당 받은 리스트에 y좌표 저장
		return items;							// 리스트 주소 반환
	}
}

dt* peek()
{
	dt* items = (dt*)malloc(sizeof(dt) * 2);	// 동적 할당으로 리스트 생성
	if (isStackEmpty())
	{
		printf("스택이 비었습니다.\n");			// 스택이 비어있는지 확인
		return 0;
	}
	else
	{
		items[0] = top->xdata;					// 동적 할당 리스트에 x좌표 저장
		items[1] = top->ydata;					// 동적 할당 리스트에 y좌표 저장
		return items;
	}
}

void insertAtBottom(dt x, dt y)
{
	if (isStackEmpty())		// 스택이 비었으면 더이상 넣을 것이 없으므로 마지막으로 좌표를 넣고 함수를 종료
	{
		push(x, y);			// 스택에 좌표 값 저장
		return;
	}

	dt* tempItems = pop();			// 스택에 들어 있는 주소가 제일 위에 있어야 하는데 제일 밑에 있으므로 임시로 가지고 있기
	dt tempX = tempItems[0];
	dt tempY = tempItems[1];
	free(tempItems);				// 동적 할당 해제

	insertAtBottom(x, y);			// 과정 반복

	push(tempX, tempY);				// insertAtBottom함수가 실행 되고 난 뒤, 스택 위에 값을 저장
}

void reverseStack()
{
	if (isStackEmpty()) return;				// 스택에 노드가 없다면 뒤집을 것이 없으므로 함수 종료

	dt* tempItems = pop();					// 제일 위에 있는 노드의 좌표들을 받아서 저장
	dt tempX = tempItems[0];				// x좌표 저장
	dt tempY = tempItems[1];				// y좌표 저장
	free(tempItems);						// 동적 할당 해제

	reverseStack();							// 재귀함수로 위와 같은 과정 반복

	insertAtBottom(tempX, tempY);			//
}