#include "DongEdge.h"
#include <iostream>

DongEdge::DongEdge(void)//������ ���� �ʱ�ȭ
{
	GuName = NULL;
	FromDong = NULL;
	ToDong = NULL;
	Lossrate = NULL;
	Mst = 0;
	Broken = 0;
	pNext = NULL;
}

DongEdge::~DongEdge(void)//�Ҹ���
{
	delete []GuName;
	delete []FromDong;
	delete []ToDong;//�����Ҵ��� �迭 ����
}

void DongEdge::SetGuName(char *name)//���̸� ����
{
	int i=0;
	while(name[i] != NULL)//�Է¹��� ������ ���̸� �����ش�
		i++;
	GuName = new char[i+1];//Ŭ���� ������ ���̸�ŭ �޸� �Ҵ� �Ѵ�
	memset(GuName,NULL,i+1);//�迭 �ʱ�ȭ �Ѵ�
	strcpy(GuName,name);//���� �����Ѵ�
}

void DongEdge::SetfromDong(char *name)//from ���� �����Ѵ�
{
	int i=0;
	while(name[i] != NULL)//�Է¹��� ������ ���̸� �����ش�
		i++;
	FromDong = new char[i+1];//Ŭ���� ������ ���̸�ŭ �޸� �Ҵ� �Ѵ�
	memset(FromDong,NULL,i+1);//�迭 �ʱ�ȭ �Ѵ�
	strcpy(FromDong,name);//���� �����Ѵ�
}

void DongEdge::SettoDong(char *name)//to ���� �����Ѵ�
{
	int i=0;
	while(name[i] != NULL)//�Է¹��� ������ ���̸� �����ش�
		i++;
	ToDong = new char[i+1];//Ŭ���� ������ ���̸�ŭ �޸� �Ҵ� �Ѵ�
	memset(ToDong,NULL,i+1);//�迭 �ʱ�ȭ �Ѵ�
	strcpy(ToDong,name);//���� �����Ѵ�
}

void DongEdge::SetLossrate(int rate)//���սǷ��� �����Ѵ�
{
	Lossrate = rate;//�Է� ���� ���ڿ��� int������ �� ��ȯ
}

void DongEdge::SetDongEdgeNext(DongEdge *pNode)//next ����
{
	pNext = pNode;
}

char *DongEdge::GetGuName()//���̸� ��ȯ
{
	return GuName;
}

char *DongEdge::GetfromDong()//from �� ��ȯ
{
	return FromDong;
}

char *DongEdge::GettoDong()//to �� ��ȯ
{
	return ToDong;
}

int DongEdge::GetLossrate()//�� �սǷ� ��ȯ
{
	return Lossrate;
}

DongEdge *DongEdge::GetDongEdgeNext()//next ��ȯ
{
	return pNext;
}

void DongEdge::SetMst(int num)//mst flag ����
{
	Mst = num;
}

int DongEdge::GetMst()//mst flag ��ȯ
{
	return Mst;
}

void DongEdge::SetBroken(int num)
{
	Broken = num;
}

int DongEdge::GetBroken()
{
	return Broken;
}