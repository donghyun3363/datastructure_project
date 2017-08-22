#pragma once
#include "GuVertex.h"
#include "MinHeap.h"
#include "DongVertex.h"
#include "DongEdge.h"
#include "ADJLIST.h"//헤더파일 참조
class Manager;
class DongSpanningTree//DongSpanningTree 클래스 생성
{
private://private 멤버 변수와 객체 생성
	int *parent;
	MinHeap Heap;
	ADJLIST ADJList;
	Manager *manager;
public://public 멤버 함수 선언
	DongSpanningTree();
	~DongSpanningTree(void);
	int find(int v);
	void Union(int v, int w);
	bool MST(GuVertex *pGu, int num);

};

