#pragma once
#include "MemoNode.h"//������� ����

class MinHeap//MinHeapŬ���� ����
{
private://private ��� ���� ����
	MemoNode *Minheap[2000];
	int index;
public://public ��� �Լ� ����
	MinHeap(void);
	~MinHeap(void);
	bool pushMinHeap(MemoNode *pNode);
	MemoNode *popMinHeap();
	bool Heap_IsEmpty();
};

