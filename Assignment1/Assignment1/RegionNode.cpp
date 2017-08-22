#include "RegionNode.h"
#include <iostream>//������� ����

RegionNode::RegionNode(void)//������
{
	re_Num = NULL;
	m_City=NULL;
	pNext=NULL;
	Left=NULL;
	Right=NULL;
	p_Head=NULL;
	Qnext=NULL;
}

RegionNode::~RegionNode(void)//�Ҹ���
{
	delete []re_Num;
	delete []m_City;
}

char* RegionNode::GetRegionNumber()//�����ڵ带 ��ȯ�Ѵ�
{
	return re_Num;
}

char* RegionNode::GetCity()//���ø� ��ȯ�Ѵ�
{
	return m_City;
}
void RegionNode::SetCity(char *city)//���ø� ��ȯ�Ѵ�
{
	int i=0;
	while(city[i]!=NULL)//�Է¹��� ������ ���̸� �����ش�
		i++;
	m_City = new char[i+1];//Ŭ���� ������ ���� ���̸�ŭ �޸� �Ҵ� �Ѵ�
	memset(m_City,NULL,i+1);//�迭 �ʱ�ȭ �Ѵ�
	strcpy(m_City,city);//���� �����Ѵ�
}

void RegionNode::SetRegionNumber(char *Num)//�����ڵ带 �����Ѵ�
{
	int i=0;
	while(Num[i]!=NULL)//�Է¹��� ������ ���̸� �����ش�
		i++;
	re_Num = new char[i+1];//Ŭ���� ������ ���� ���̸�ŭ �޸� �Ҵ� �Ѵ�
	memset(re_Num,NULL,i+1);//�迭 �ʱ�ȭ �Ѵ�
	strcpy(re_Num,Num);
}

RegionNode* RegionNode::GetNext()//next�� ��ȯ�Ѵ�
{
	return pNext;
}

NumNode* RegionNode::GetN_Head()//head�� ��ȯ�Ѵ�
{
	return p_Head;
}

RegionNode* RegionNode::GetLeftNext()//left�� ��ȯ�Ѵ�
{
	return Left;
}

RegionNode* RegionNode::GetRightNext()//right�� ��ȯ�Ѵ�
{
	return Right;
}
RegionNode* RegionNode::GetQNext()//Qnext�� ��ȯ�Ѵ�
{
	return Qnext;
}

void RegionNode::SetN_Head(NumNode *Node)//head�� �����Ѵ�
{
	p_Head=Node;
}

void RegionNode::SetNext(RegionNode* Node)//next�� �����Ѵ�
{
	pNext=Node;
}

void RegionNode::SetLeftNext(RegionNode* Node)//left�� �����Ѵ�
{
	Left=Node;
}

void RegionNode::SetRightNext(RegionNode* Node)//right�������Ѵ�
{
	Right=Node;
}

void RegionNode::SetQNext(RegionNode* Node)//Qnext�� �����Ѵ�.
{
	Qnext=Node;
}