#pragma once
#include "DongEdge.h"//헤더파일 참조

class MinHeap//MinHeap 클래스 생성
{
private://public 멤버 변수 선언
	DongEdge *Minheap[2000];
	int index;

public://public 멤버 함수 선언
	MinHeap(void);
	~MinHeap(void);
	bool pushMinHeap(DongEdge *pNode);
	DongEdge *popMinHeap();
	bool Heap_IsEmpty();
	bool CheckEdge(DongEdge *pNode);

};