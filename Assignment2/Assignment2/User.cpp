#include "User.h"
#include <iostream>//헤더파일 선언

User::User(void)//생성자
{
	mNumber = NULL;
	mName = NULL;
	bf = 0;
	numbf = 0;
	NameLeft = NULL;
	NameRight = NULL;
	NumLeft = NULL;
	NumRight = NULL;
	qNext = NULL;
	Mfriend = NULL;
	Mymemo = NULL;//private 변수들을 초기화 해준다
	checkDelete =0;
}

User::~User(void)//소멸자
{
	delete []mNumber;
	delete []mName;
}

void User::SetName(char *name)//이름을 저장한다
{
	int i=0;
	while(name[i]!=NULL)//입력받은 정보의 길이를 구해준다
		i++;
	mName = new char[i+1];//클래스 변수에 길이만큼 메모리 할당 한다
	memset(mName,NULL,i+1);//배열 초기화 한다
	strcpy(mName,name);//값을 복사한다
}

void User::SetNumber(char *number)//학번을 저장한다
{
	int i=0;
	while(number[i]!=NULL)//입력받은 정보의 길이를 구해준다
		i++;
	mNumber = new char[i+1];//클래스 변수에 길이만큼 메모리 할당 한다
	memset(mNumber,NULL,i+1);//배열 초기화 한다
	strcpy(mNumber,number);//값을 복사한다
}

void User::Setbf(int num)//blance factor를 저장한다
{
	bf = num;
}

void User::SetNbf(int num)//number의 blance factor를 저장한다
{
	numbf = num;
}

char *User::GetName()//이름을 반환한다
{
	return mName;
}

char *User::GetNumber()//학번을 반환한다
{
	return mNumber;
}

int User::Getbf()//name의 blance factor를 반환한다
{
	return bf;
}

int User::GetNbf()//number의 blance factor를 반환한다
{
	return numbf;
}

void User::SetNameLeft(User *pNode)//name의 left를 저장한다
{
	NameLeft = pNode;
}

void User::SetNameRight(User *pNode)//name의 right를 저장한다
{
	NameRight = pNode;
}

void User::SetNumLeft(User *pNode)//numbe의 left를 저장한다
{
	NumLeft = pNode;
}

void User::SetNumRight(User *pNode)//number의 right를 저장한다
{
	NumRight = pNode;
}

void User::SetqNext(User *pNode)//Queue의 next를 저장한다
{
	qNext = pNode;
}

void User::SetFri(Linked *pNode)//friend의 head를 저장한다
{
	Mfriend = pNode;
}

void User::SetLNext(User *pNode)//leave next를 저장한다
{
	LeaveNext = pNode;
}

void User::SetMyMemo(MemoNode *pNode)//Memo의 head를 저장한다
{
	Mymemo=pNode;
}

User *User::GetNameLeft()//name의 left를 반환한다
{
	return NameLeft;
}

User *User::GetNameRight()//name의 right를 반환한다
{
	return NameRight;
}

User *User::GetNumLeft()//numbe의 left를 반환한다
{
	return NumLeft;
}

User *User::GetNumRight()//number의 right를 반환한다
{
	return NumRight;
}

User *User::GetqNext()//Queue의 next를 반환한다
{
	return qNext;
}

Linked *User::GetFri()//friend의 head를 반환한다
{
	return Mfriend;
}

User *User::GetLNext()//leave next를 반환한다
{
	return LeaveNext;
}

MemoNode *User::GetMyMemo()//Memo의 head를 반환한다
{
	return Mymemo;
}

void User::SetCheckDelete(int num)//탈퇴여부를 저장한다
{
	checkDelete = num;
}

int User::GetCheckDelete()//탈퇴여부를 반환한다
{
	return checkDelete;
}