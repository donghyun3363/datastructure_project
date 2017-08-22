#pragma once
#include "RegionNode.h"

class D2List//2d list 클래스 선언
{
private://private 멤버 변수 선언
	RegionNode *pHead;

public://public 멤버 함수 선언
	D2List(void);
	~D2List(void);
	RegionNode *GetHead();
	bool pInsert(RegionNode *pNode);
	bool cInsert(char *Rnum, NumNode *cNode);
	bool Delete(char *num, char *re);
	void D2List::Pdelete(RegionNode *del);
};

