#pragma once
#include "RegionNode.h"

class BST//BST 클래스 선언
{
private://private 멤버 변수 선언
	RegionNode *pRoot;
public://public 멤버 변수 선언
	BST(void);
	~BST(void);
	bool BSTInsert(RegionNode *pNode);
	bool BSTinsert_position(RegionNode *current, RegionNode *pNode);

	RegionNode *GetRoot();
	bool BST::Delete(RegionNode *pNode);
	RegionNode *Serch(char *Num);
};