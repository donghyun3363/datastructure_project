#include "Linked.h"
#include <iostream>//������� ����

Linked::Linked(void)//������ 
{
	pNext = NULL;
	pDown = NULL;
}

Linked::~Linked(void)//�Ҹ���
{
}

void Linked::SetNext(Linked *Node)//������带 �������ش�
{
	pNext = Node;
}

void Linked::SetDown(User *Node)//�����尡 ������ ģ���� �����Ѵ�
{
	pDown = Node;
}

Linked *Linked::GetNext()//������带 ��ȯ�Ѵ�
{
	return pNext;
}

User *Linked::GetDown()//�����尡 ������ ģ���� ��ȯ�Ѵ�
{
	return pDown;
}
