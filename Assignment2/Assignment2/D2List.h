#pragma once
#include "Linked.h"
#include "User.h"//������� ����

class D2List//2D ���� Ŭ����
{
private://private ������ ����� �����Ѵ�
	Linked *pHead;

public://public ��� �Լ� ����
	D2List(void);
	~D2List(void);
	bool Insert(User *MeNode, User *FriNode);
	int SearchFri(User *Node, char *friName);
	bool SearchFri(User *MeNode, User *friNode);
	bool DeleteFrt(User *MeNode, User *friNode);

};