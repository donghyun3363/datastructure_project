#pragma once
#include "RegionNode.h"

class Queue_//queue Ŭ���� ����
{
private://private ������� ����
	RegionNode* m_pHead;
public://public ��� �Լ� ����
	Queue_(void);
	~Queue_(void);
	bool IsEmpty();
	bool Push(RegionNode *pNode);
	RegionNode *Pop();
};
