#pragma once
#include "RegionNode.h"

class BST//BST Ŭ���� ����
{
private://private ��� ���� ����
	RegionNode *pRoot;
public://public ��� ���� ����
	BST(void);
	~BST(void);
	bool BSTInsert(RegionNode *pNode);
	bool BSTinsert_position(RegionNode *current, RegionNode *pNode);

	RegionNode *GetRoot();
	bool BST::Delete(RegionNode *pNode);
	RegionNode *Serch(char *Num);
};