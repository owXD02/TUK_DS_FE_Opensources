#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int dt;			// 자료형이 다른 것을 사용할 때 유연하게 바꾸기 위함

typedef struct doubleLinkedList			// 구조체 선언
{
	struct doubleLinkedList* llink;
	dt xdata;
	dt ydata;
	struct doubleLinkedList* rlink;
}DLL;

typedef struct doubleLinkedListHead		// 헤드 변수 저장을 위한 구조체 선언
{
	DLL* dhead;
}DLLH;


// 함수 선언
DLLH* createDoubleLinkedList();
DLLH* insertNode(DLLH* DL, DLL* pre, dt xd, dt yd);
void deleteDNode(DLLH* DL, DLL* old);
void freeDNode(DLLH* L);