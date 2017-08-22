#pragma once
#include "Linked.h"
#include "MemoNode.h"//헤더파일 선언

class User//User클래스 생성
{
private://private 멤버 변수 선언
	char *mNumber;
	char *mName;
	int checkDelete;
	int bf;
	int numbf;
	User *NameLeft;
	User *NameRight;
	User *NumLeft;
	User *NumRight;
	User *qNext;
	User *LeaveNext;
	Linked *Mfriend;
	MemoNode *Mymemo;

public://public 멤버 함수 선언
	User(void);
	~User(void);
	void SetName(char *name);
	void SetNumber(char *number);
	void Setbf(int num);
	void SetNbf(int num);
	void SetNameLeft(User *pNode);
	void SetNameRight(User *pNode);
	void SetNumLeft(User *pNode);
	void SetNumRight(User *pNode);
	void SetLNext(User *pNode);
	void SetqNext(User *pNode);
	void SetFri(Linked *pNode);
	void SetMyMemo(MemoNode *pNode);
	void SetCheckDelete(int num);

	char *GetName();
	char *GetNumber();
	int Getbf();
	int GetNbf();
	int GetCheckDelete();
	User *GetNameLeft();
	User *GetNameRight();
	User *GetNumLeft();
	User *GetNumRight();
	User *GetqNext();
	User *GetLNext();
	Linked *GetFri();
	MemoNode *GetMyMemo();
};
