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
private://private À¸·Î ¸â¹ö °´Ã¼ ¼±¾ð
	D2List list;//2DList °´Ã¼ 
	BST Root;//BST °´Ã¼ 
	Circular cir;
	Queue_ Que;

public://public À¸·Î ¸â¹ö ÇÔ¼ö ¼±¾ð
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