#pragma once
#include "singleLinkedList.h"

extern SLL* top;					// top 변수가 어딘가에서 선언될 것이라고 암시


// 함수의 선언
int isStackEmpty();
void push(dt xitem, dt yitem);
dt* pop();
dt* peek();
void insertAtBottom(dt x, dt y);
void reverseStack();