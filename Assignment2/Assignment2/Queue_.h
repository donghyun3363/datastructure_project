#pragma once
#include "User.h"//������� ����

class Queue_//queue Ŭ���� ����
{
private://private ������� ����
	User* m_pHead;
public://public ��� �Լ� ����
	Queue_(void);
	~Queue_(void);
	bool IsEmpty();
	bool Push(User *pNode);
	User *Pop();
};

