#include "NumNode.h"
#include<iostream>//������� ����

NumNode::NumNode(void)//������
{
	m_Num=NULL;
	m_Finish=NULL;
	m_Item=NULL;
	m_Treat=NULL;
	pNext=NULL;
	CircularNext;
}

NumNode::~NumNode(void)//�Ҹ���
{
	delete []m_Num;
	delete []m_Finish;
	delete []m_Item;
	delete []m_Treat;
}

char *NumNode::GetNum()//������ȣ�� ��ȯ�Ѵ�
{
	return m_Num;
}

char *NumNode::GetFinish()//��ۿ��θ� ��ȯ�Ѵ�
{
	return m_Finish;
}

char *NumNode::GetItem()//ǰ���� ��ȯ�Ѵ�
{
	return m_Item;
}

char *NumNode::GetTreat()//������Ǹ� ��ȯ�Ѵ�
{
	return m_Treat;
}

void NumNode::SetNum(char *num)//����� ��ȣ�� �����Ѵ�
{
	int i=0;
	while(num[i]!=NULL)//�Է¹��� ������ ���̸� �����ش�
		i++;
	m_Num = new char[i+1];//Ŭ���� ������ ���̸�ŭ �޸� �Ҵ� �Ѵ�
	memset(m_Num,NULL,i+1);//�迭 �ʱ�ȭ �Ѵ�
	strcpy(m_Num,num);//���� �����Ѵ�
}

void NumNode::SetFinish(char *finish)//��ۿ��θ� �����Ѵ�
{
	int i=0;
	while(finish[i]!=NULL)//�Է¹��� ������ ���̸� �����ش�
		i++;
	m_Finish = new char[i+1];//Ŭ���� ������ ���̸�ŭ �޸� �Ҵ� �Ѵ�
	memset(m_Finish,NULL,i+1);//�迭 �ʱ�ȭ �Ѵ�
	strcpy(m_Finish,finish);//���� �����Ѵ�
}

void NumNode::SetItem(char *item)//ǰ���� �����Ѵ�
{
	int i=0;
	while(item[i]!=NULL)//�Է¹��� ������ ���̸� �����ش�
		i++;
	m_Item = new char[i+1];//Ŭ���� ������ ���̸�ŭ �޸� �Ҵ� �Ѵ�
	memset(m_Item,NULL,i+1);//�迭 �ʱ�ȭ �Ѵ�
	strcpy(m_Item,item);//���� �����Ѵ�
}

void NumNode::SetTreat(char *treat)//������Ǹ� �����Ѵ�
{
	int i=0;
	while(treat[i]!=NULL)//�Է¹��� ������ ���̸� �����ش�
		i++;
	m_Treat = new char[i+1];//Ŭ���� ������ ���̸�ŭ �޸� �Ҵ� �Ѵ�
	memset(m_Treat,NULL,i+1);//�迭 �ʱ�ȭ �Ѵ�
	strcpy(m_Treat,treat);//���� �����Ѵ�
}

NumNode *NumNode::GetNext()//Next�� ��ȯ�Ѵ�
{
	return pNext;
}

void NumNode::SetNext(NumNode *pNode)//Next�� �����Ѵ�
{
	pNext=pNode;
}

NumNode *NumNode::GetCirNext()//circularNext�� ��ȯ�Ѵ�
{
	return CircularNext;
}

void NumNode::SetCirNext(NumNode *pNode)//circularNext�� �����Ѵ�
{
	CircularNext=pNode;
}