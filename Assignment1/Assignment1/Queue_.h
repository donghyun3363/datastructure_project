#pragma once
#include "RegionNode.h"

class Queue_//queue 클래스 선언
{
private://private 멤버변수 선언
	RegionNode* m_pHead;
public://public 멤버 함수 선언
	Queue_(void);
	~Queue_(void);
	bool IsEmpty();
	bool Push(RegionNode *pNode);
	RegionNode *Pop();
};
