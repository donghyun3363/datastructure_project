#pragma once
#include "NumNode.h"

class Circular//원형리스트 클래스 선언
{
private://private 멤버 변수 선언
	NumNode *cirHead;
public://public 멤버 함수 선언
	Circular(void);
	~Circular(void);
	bool Insert(NumNode *pNode);
	NumNode *GetCirHead();
};

