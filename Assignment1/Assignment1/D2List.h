#pragma once
#include "RegionNode.h"

class D2List//2d list Ŭ���� ����
{
private://private ��� ���� ����
	RegionNode *pHead;

public://public ��� �Լ� ����
	D2List(void);
	~D2List(void);
	RegionNode *GetHead();
	bool pInsert(RegionNode *pNode);
	bool cInsert(char *Rnum, NumNode *cNode);
	bool Delete(char *num, char *re);
	void D2List::Pdelete(RegionNode *del);
};

