#include "User.h"
#include <iostream>//������� ����

User::User(void)//������
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
	Mymemo = NULL;//private �������� �ʱ�ȭ ���ش�
	checkDelete =0;
}

User::~User(void)//�Ҹ���
{
	delete []mNumber;
	delete []mName;
}

void User::SetName(char *name)//�̸��� �����Ѵ�
{
	int i=0;
	while(name[i]!=NULL)//�Է¹��� ������ ���̸� �����ش�
		i++;
	mName = new char[i+1];//Ŭ���� ������ ���̸�ŭ �޸� �Ҵ� �Ѵ�
	memset(mName,NULL,i+1);//�迭 �ʱ�ȭ �Ѵ�
	strcpy(mName,name);//���� �����Ѵ�
}

void User::SetNumber(char *number)//�й��� �����Ѵ�
{
	int i=0;
	while(number[i]!=NULL)//�Է¹��� ������ ���̸� �����ش�
		i++;
	mNumber = new char[i+1];//Ŭ���� ������ ���̸�ŭ �޸� �Ҵ� �Ѵ�
	memset(mNumber,NULL,i+1);//�迭 �ʱ�ȭ �Ѵ�
	strcpy(mNumber,number);//���� �����Ѵ�
}

void User::Setbf(int num)//blance factor�� �����Ѵ�
{
	bf = num;
}

void User::SetNbf(int num)//number�� blance factor�� �����Ѵ�
{
	numbf = num;
}

char *User::GetName()//�̸��� ��ȯ�Ѵ�
{
	return mName;
}

char *User::GetNumber()//�й��� ��ȯ�Ѵ�
{
	return mNumber;
}

int User::Getbf()//name�� blance factor�� ��ȯ�Ѵ�
{
	return bf;
}

int User::GetNbf()//number�� blance factor�� ��ȯ�Ѵ�
{
	return numbf;
}

void User::SetNameLeft(User *pNode)//name�� left�� �����Ѵ�
{
	NameLeft = pNode;
}

void User::SetNameRight(User *pNode)//name�� right�� �����Ѵ�
{
	NameRight = pNode;
}

void User::SetNumLeft(User *pNode)//numbe�� left�� �����Ѵ�
{
	NumLeft = pNode;
}

void User::SetNumRight(User *pNode)//number�� right�� �����Ѵ�
{
	NumRight = pNode;
}

void User::SetqNext(User *pNode)//Queue�� next�� �����Ѵ�
{
	qNext = pNode;
}

void User::SetFri(Linked *pNode)//friend�� head�� �����Ѵ�
{
	Mfriend = pNode;
}

void User::SetLNext(User *pNode)//leave next�� �����Ѵ�
{
	LeaveNext = pNode;
}

void User::SetMyMemo(MemoNode *pNode)//Memo�� head�� �����Ѵ�
{
	Mymemo=pNode;
}

User *User::GetNameLeft()//name�� left�� ��ȯ�Ѵ�
{
	return NameLeft;
}

User *User::GetNameRight()//name�� right�� ��ȯ�Ѵ�
{
	return NameRight;
}

User *User::GetNumLeft()//numbe�� left�� ��ȯ�Ѵ�
{
	return NumLeft;
}

User *User::GetNumRight()//number�� right�� ��ȯ�Ѵ�
{
	return NumRight;
}

User *User::GetqNext()//Queue�� next�� ��ȯ�Ѵ�
{
	return qNext;
}

Linked *User::GetFri()//friend�� head�� ��ȯ�Ѵ�
{
	return Mfriend;
}

User *User::GetLNext()//leave next�� ��ȯ�Ѵ�
{
	return LeaveNext;
}

MemoNode *User::GetMyMemo()//Memo�� head�� ��ȯ�Ѵ�
{
	return Mymemo;
}

void User::SetCheckDelete(int num)//Ż�𿩺θ� �����Ѵ�
{
	checkDelete = num;
}

int User::GetCheckDelete()//Ż�𿩺θ� ��ȯ�Ѵ�
{
	return checkDelete;
}