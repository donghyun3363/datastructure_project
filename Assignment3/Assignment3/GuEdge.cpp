#include "GuEdge.h"
#include <iostream>//������� ����

GuEdge::GuEdge(void)//������ �������� �ʱ�ȭ �Ѵ�
{
	FromGu = NULL;
	ToGu = NULL;
	pDis = 0;
	pNext = NULL;
}

GuEdge::~GuEdge(void)//������ �������� �ʱ�ȭ �Ѵ�
{
	delete []FromGu;
	delete []ToGu;
}
void GuEdge::SetfromGu(char *name)//from �� �̸��� �����Ѵ�
{
	int i=0;
	while(name[i]!=NULL)//�Է¹��� ������ ���̸� �����ش�
		i++;
	FromGu = new char[i+1];//Ŭ���� ������ ���̸�ŭ �޸� �Ҵ� �Ѵ�
	memset(FromGu,NULL,i+1);//�迭 �ʱ�ȭ �Ѵ�
	strcpy(FromGu,name);//���� �����Ѵ�

}

void GuEdge::SettoGu(char *name)//to �� �̸��� �����Ѵ�
{
	int i=0;
	while(name[i]!=NULL)//�Է¹��� ������ ���̸� �����ش�
		i++;
	ToGu = new char[i+1];//Ŭ���� ������ ���̸�ŭ �޸� �Ҵ� �Ѵ�
	memset(ToGu,NULL,i+1);//�迭 �ʱ�ȭ �Ѵ�
	strcpy(ToGu,name);//���� �����Ѵ�
}

void GuEdge::SetDis(int dis)//�Ÿ��� int������ �����Ѵ�
{
	pDis = dis;
}

void GuEdge::SetGuEdgeNext(GuEdge *pNode)//edge next�� �����Ѵ�
{
	pNext = pNode;
}

char *GuEdge::GetfromGu()//from �� �̸� ��ȯ
{
	return FromGu;
}

char *GuEdge::GettoGu()//to �� �̸� ��ȯ
{
	return ToGu;
}

int GuEdge::Getdis()//�Ÿ� ��ȯ
{
	return pDis;
}

GuEdge *GuEdge::GetGuEdgeNext()//edge next�� ��ȯ�Ѵ�
{
	return pNext;
}
