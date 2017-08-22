#pragma once
#include "NumNode.h"
#include "Circular.h"
#include "D2List.h"
#include "BST.h"
#include "Queue_.h"

#include <iostream>
#include<fstream>

using namespace std;

class Manager
{
private://private ���� ��� ��ü ����
	D2List list;//2DList ��ü 
	BST Root;//BST ��ü 
	Circular cir;
	Queue_ Que;

public://public ���� ��� �Լ� ����
	Manager(void);
	~Manager(void);
	bool LoadFile(char* pFileName);
	bool cityinsert();
	bool informationinsert();
	bool informationinsert(NumNode *pNode);
	bool BST_insert();
	bool FIND(char *Fnum);
	bool SAVE(char* pFileName);
	bool PRINT();
	void inorder_print(RegionNode *current);
	bool UPDATE(char* pFileName);
	bool EXIT();

};