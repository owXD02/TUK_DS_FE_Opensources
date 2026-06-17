#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int dt;

typedef struct SignleLinkedList {
	dt xdata;
	dt ydata;
	struct SingleLinkedList* next;
}SLL;

typedef struct SLLHead {
	SLL* head;
}SLLH;

SLLH* createSingleLinkedList();
void freeLinkedList(SLLH* L);
void insertFirstNode(SLLH* L, dt xd, dt yd);
void insertLastNode(SLLH* L, dt xd, dt yd);
void deleteSNode(SLLH* L, SLL* p);
void freeSNode(SLLH* L);