#pragma once
#include "User.h"//������� ����
#include "Leave.h"
class AVL//AVL Ŭ���� ����
{
private://private������ Root ����
	User *NameRoot;
	User *NumberRoot;
	Leave Del;
public://public���� ��� �Լ� ����
	AVL(void);
	~AVL(void);
	User *GetNameRoot();
	User *GetNumRoot();
	bool NameAVL(User *pNode);
	bool NumberAVL(User *pNode);
	//bool NumberDelete(User *pNode);
	//bool NameDelete(User *pNode);
	User *NumSearch(char *Num);
	User *NameSearch(char *Name);
	User *NameSearch(char *Name, char *Num);
	bool CheckSameName(char *Name);
};

