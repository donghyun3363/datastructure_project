#pragma once
#include "MemoNode.h"//헤더파일 참조

class MinHeap//MinHeap클래스 생성
{
private://private 멤버 변수 선언
	MemoNode *Minheap[2000];
	int index;
public://public 멤버 함수 선언
	MinHeap(void);
	~MinHeap(void);
	bool pushMinHeap(MemoNode *pNode);
	MemoNode *popMinHeap();
	bool Heap_IsEmpty();
};

