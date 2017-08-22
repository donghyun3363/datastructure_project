#include "Leave.h"
#include "User.h"
#include <iostream>//��������� �����Ѵ�

Leave::Leave(void)//������
{
	pRoot = NULL;
}

Leave::~Leave(void)//�Ҹ���
{
}

bool Leave::Insert(User *pNode)//insert �Լ�
{
	pNode->SetCheckDelete(1);//Ż�𿩺� flag �� �����Ѵ�

	User *temp=pRoot;//head�� ����ִٸ�
	if(pRoot==NULL)
	{
		pRoot = pNode;
		return true;
	}//head�� ������ �� ��ȯ

	while(temp->GetLNext() !=NULL)
		temp = temp->GetLNext();//next�� NULL�� �ɶ����� �ݺ��Ѵ�

	temp->SetLNext(pNode);//���ڸ��� insert���ش�
	return true;//����ȯ
}

bool Leave::Delete()//�����Լ�
{
	User *pCur = NULL;
	while(pRoot !=NULL )//root ���� �ݺ��Ѵ�
	{
		pCur = pRoot;
		pRoot = pRoot->GetLNext();
		delete pCur;//���� ��带 delete ���ش�
	}
	return true;//����ȯ
}