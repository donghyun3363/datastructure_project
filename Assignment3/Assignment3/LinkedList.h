#pragma once
#include "Mechanic.h"//��������� �����Ѵ�

class LinkedList//LinkedList Ŭ���� ����
{
private://private ��� ���� ����
	Mechanic *pHead;

public://public ��� �Լ� ����
	LinkedList(void);
	~LinkedList(void);

	void SetHead();
	Mechanic *GetMechanicHead();
	bool InsertMechanic(Mechanic *node);
	bool CheckMechanic(char *gu);
};

