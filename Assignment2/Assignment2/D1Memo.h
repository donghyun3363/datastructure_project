#pragma once
#include "MemoNode.h"
#include "User.h"//������� ���� ����

class D1Memo//D1Memo Ŭ���� ����
{
private://private ��� ���� ����
	MemoNode *pHead;
public://public ��� ���� ����
	D1Memo(void);
	~D1Memo(void);
	bool MemoInsert(User *MeNode, MemoNode *pNode);
	bool MemoSearch(User *MeNode, char *time );
	bool MemoDelete(User *MeNode, char *time );
};

