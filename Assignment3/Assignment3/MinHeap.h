#pragma once
#include "DongEdge.h"//������� ����

class MinHeap//MinHeap Ŭ���� ����
{
private://public ��� ���� ����
	DongEdge *Minheap[2000];
	int index;

public://public ��� �Լ� ����
	MinHeap(void);
	~MinHeap(void);
	bool pushMinHeap(DongEdge *pNode);
	DongEdge *popMinHeap();
	bool Heap_IsEmpty();
	bool CheckEdge(DongEdge *pNode);

};