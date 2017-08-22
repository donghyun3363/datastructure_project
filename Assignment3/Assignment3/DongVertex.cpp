#include "DongVertex.h"
#include <iostream>//������� ����

DongVertex::DongVertex(void)//������ ������ �ʱ�ȭ/
{
	Gu = NULL;
	DongName = NULL;
	pView = NULL;
	pNext = NULL;
	dongedgHead = NULL;
	Mstflag = 0;
}

DongVertex::~DongVertex(void)//�Ҹ���
{
	delete []Gu;
	delete []DongName;
	delete []pView;
}

void DongVertex::SetguName(char *name)//�� �̸��� �����Ѵ�
{
	int i=0;
	while(name[i]!=NULL)//�Է¹��� ������ ���̸� �����ش�
		i++;
	Gu = new char[i+1];//Ŭ���� ������ ���̸�ŭ �޸� �Ҵ� �Ѵ�
	memset(Gu,NULL,i+1);//�迭 �ʱ�ȭ �Ѵ�
	strcpy(Gu,name);//���� �����Ѵ�
}

void DongVertex::SetDongName(char *name)//�� �̸��� �����Ѵ�
{
	int i=0;
	while(name[i]!=NULL)//�Է¹��� ������ ���̸� �����ش�
		i++;
	DongName = new char[i+1];//Ŭ���� ������ ���̸�ŭ �޸� �Ҵ� �Ѵ�
	memset(DongName,NULL,i+1);//�迭 �ʱ�ȭ �Ѵ�
	strcpy(DongName,name);//���� �����Ѵ�
}

void DongVertex::SetView(char *view)//��������� ���� ����
{
	int i=0;
	while(view[i]!=NULL)//�Է¹��� ������ ���̸� �����ش�
		i++;
	pView = new char[i+1];//Ŭ���� ������ ���̸�ŭ �޸� �Ҵ� �Ѵ�
	memset(pView,NULL,i+1);//�迭 �ʱ�ȭ �Ѵ�
	strcpy(pView,view);//���� �����Ѵ�
}

void DongVertex::SetdongNext(DongVertex *pNode)//�� next�� ����
{
	pNext = pNode;
}

char *DongVertex::GetguName()//���̸� ��ȯ
{
	return Gu;
}

char *DongVertex::GetDongName()//���̸� ��ȯ
{
	return DongName;
}

char *DongVertex::GetView()//��������� ���� ��ȯ
{
	return pView;
}

DongVertex *DongVertex::GetdongNext()// �� next ��ȯ
{
	return pNext;
}

void DongVertex::SetdongedgHead(DongEdge *pNode)//���� edge ����� �����Ѵ�
{
	dongedgHead = pNode;
}

DongEdge *DongVertex::GetdongedgHead()//���� edge�� ��ȯ�Ѵ�
{
	return dongedgHead;
}

void DongVertex::SetMstflag(int num)//mst �迭 index �� ����
{
	Mstflag = num;
}

int DongVertex::GetMstflag()//mst �迭 index �� ��ȯ
{
	return Mstflag;
}