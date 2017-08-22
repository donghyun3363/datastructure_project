#pragma once
#include "GuVertex.h"
#include "MinHeap.h"
#include "DongVertex.h"
#include "DongEdge.h"
#include "ADJLIST.h"//������� ����
class Manager;
class DongSpanningTree//DongSpanningTree Ŭ���� ����
{
private://private ��� ������ ��ü ����
	int *parent;
	MinHeap Heap;
	ADJLIST ADJList;
	Manager *manager;
public://public ��� �Լ� ����
	DongSpanningTree();
	~DongSpanningTree(void);
	int find(int v);
	void Union(int v, int w);
	bool MST(GuVertex *pGu, int num);

};

