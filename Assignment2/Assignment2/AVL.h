#pragma once
#include "User.h"//헤더파일 참조
#include "Leave.h"
class AVL//AVL 클래스 생성
{
private://private변수로 Root 선언
	User *NameRoot;
	User *NumberRoot;
	Leave Del;
public://public으로 멤버 함수 선언
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

