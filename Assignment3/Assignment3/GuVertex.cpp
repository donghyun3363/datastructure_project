#include "GuVertex.h"
#include <iostream>//������� ����

GuVertex::GuVertex(void)//������ ���� �ʱ�ȭ
{
	GuName = NULL;
	pNext = NULL;
	edgHead = NULL;
	dongHead = NULL;
	MstHead = NULL;
	shflag = 0;
}

GuVertex::~GuVertex(void)//�Ҹ���
{
	delete []GuName;
}

void GuVertex::SetGuName(char *name)//���̸� ����
{
	int i=0;
	while(name[i]!=NULL)//�Է¹��� ������ ���̸� �����ش�
		i++;
	GuName = new char[i+1];//Ŭ���� ������ ���̸�ŭ �޸� �Ҵ� �Ѵ�
	memset(GuName,NULL,i+1);//�迭 �ʱ�ȭ �Ѵ�
	strcpy(GuName,name);//���� �����Ѵ�
}

char *GuVertex::GetGuName()//���̸� ��ȯ
{
	return GuName;
}

void GuVertex::SetGuNext(GuVertex *pNode)//�� next ����
{
	pNext = pNode;
}

GuVertex *GuVertex::GetGuNext()//�� next ��ȯ
{
	return pNext;
}

void GuVertex::SetGuedgHead(GuEdge *pNode)//�� edge ����� �����Ѵ�
{
	edgHead = pNode;
}

GuEdge *GuVertex::GetGuedgHead()//�� edge ����� ��ȯ�Ѵ�
{
	return edgHead;
}

void GuVertex::SetDongHead(DongVertex *pNode)//���� ����� �����Ѵ�
{
	dongHead = pNode;
}

DongVertex *GuVertex::GetDongHead()//���� ����� ��ȯ�Ѵ�
{
	return dongHead;
}

void GuVertex::SetMstHead(DongVertex *pNode)//���� MST ����� �����Ѵ�
{
	MstHead = pNode;
}

DongVertex *GuVertex::GetMstHead()//���� MST ����� ��ȯ�Ѵ�
{
	return MstHead;
}

void GuVertex::SetShortflag(int num)
{
	shflag = num;
}

int GuVertex::GetShortflag()
{
	return shflag;
}
