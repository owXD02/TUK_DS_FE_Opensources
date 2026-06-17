#include "singleLinkedList.h"

SLLH* createSingleLinkedList()
{
	SLLH* h;
	h = (SLLH*)malloc(sizeof(SLLH));
	h->head = NULL;
	return h;
}

void freeLinkedList(SLLH* L) 
{
	SLL* p;
	while (L->head != NULL) {
		p = L->head;
		L->head = L->head->next;
		free(p);
		p = NULL;
	}
}

void insertFirstNode(SLLH* L, dt xd, dt yd) 
{
	SLL* newNode;
	newNode = (SLL*)malloc(sizeof(SLL));
	newNode->xdata = xd;
	newNode->ydata = yd;
	newNode->next = L->head;
	L->head = newNode;
}

void insertLastNode(SLLH* L, dt xd, dt yd) 
{
	SLL* newNode;
	SLL* temp;
	newNode = (SLL*)malloc(sizeof(SLL));
	newNode->xdata = xd;
	newNode->ydata = yd;
	newNode->next = NULL;
	if (L->head == NULL) {
		L->head = newNode;
		return;
	}

	temp = L->head;
	while (temp->next != NULL) temp = temp->next;
	temp->next = newNode;
}

void deleteSNode(SLLH* L, SLL* p)
{
	SLL* pre;
	if (L->head == NULL) return;
	if (L->head->next == NULL)	// 리스트가 한개만 있는 경우
	{
		free(L->head);
		L->head = NULL;
		return;
	}
	else if (p == NULL) return;
	else
	{
		pre = L->head;
		while (pre->next != p)
		{
			pre = pre->next;
		}
		pre->next = p->next;
		free(p);
	}
}

void freeSNode(SLLH* L)
{
	if (L == NULL)
	{
		return;
	}

	SLL* p = L->head;
	SLL* nextNode;
	while (p != NULL)
	{
		nextNode = p->next;
		free(p);
		p = nextNode;
	}

	L->head = NULL;
}