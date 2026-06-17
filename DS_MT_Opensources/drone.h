#pragma once
#define _CRT_SECURE_NO_WARNINGS  //scanf_s() 또는 printf_s()를 사용하지 않아서 발생하는 오류 무시
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "doubleLinkedList.h"
#include "singleLinkedList.h"
#include "stackL.h"


// 함수의 선언
void createDronePath();
DLLH* getDronePath(FILE* fp);
int patrol();
int suicide();
void chargeBattery(int n);
void showMenu();