#pragma once
#include "NumNode.h"

class Circular//��������Ʈ Ŭ���� ����
{
private://private ��� ���� ����
	NumNode *cirHead;
public://public ��� �Լ� ����
	Circular(void);
	~Circular(void);
	bool Insert(NumNode *pNode);
	NumNode *GetCirHead();
};

