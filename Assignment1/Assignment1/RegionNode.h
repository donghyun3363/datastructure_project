#pragma once
#include "NumNode.h"

class RegionNode//RegionNode 초기화
{
private://private 멤버 변수 선언
	char *re_Num;
	char *m_City;
	RegionNode *pNext;
	RegionNode *Left;
	RegionNode *Right;
	NumNode *p_Head;  
	RegionNode *Qnext;

public://public 멤버 함수 선언
	RegionNode(void);
	~RegionNode(void);

	char* GetRegionNumber();
	void SetRegionNumber(char *Num);
	char* GetCity();
	void SetCity(char *city);

	NumNode* GetN_Head();
	RegionNode* GetNext();
	RegionNode* GetLeftNext();
	RegionNode* GetRightNext();
	RegionNode* GetQNext();

	void SetN_Head(NumNode *Node);
	void SetNext(RegionNode* Node);
	void SetLeftNext(RegionNode* Node);
	void SetRightNext(RegionNode* Node);
	void SetQNext(RegionNode* Node);
};