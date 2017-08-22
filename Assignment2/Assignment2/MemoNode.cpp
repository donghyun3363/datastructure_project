#include "MemoNode.h"
#include <iostream>//������� ����

MemoNode::MemoNode(void)//������
{
	pTime = NULL;
	memset(pMemo,NULL,sizeof(pMemo));
	pNext = NULL;
	pWho = NULL;//������ �ʱ�ȭ
}

MemoNode::~MemoNode(void)//�Ҹ���
{
	memset(pMemo,NULL,sizeof(pMemo));
	delete []pTime;
	delete []pWho;
}

void MemoNode::SetTime(char *time)//�ð����� ����
{
	int i=0;
	while(time[i]!=NULL)//�Է¹��� ������ ���̸� �����ش�
		i++;
	pTime = new char[i+1];//�޸� �Ҵ� �Ѵ�
	memset(pTime,NULL,i+1);//�迭 �ʱ�ȭ �Ѵ�
	strcpy(pTime,time);//���� �����Ѵ�
}

void MemoNode::SetWrite(char *memo)//�޸������� ����
{
	strncpy(pMemo, memo, sizeof(pMemo) );//�޸�ũ�⸸ŭ �����Ѵ�
}

void MemoNode::SetWho(char *man)//�ۼ��� ������ �����Ѵ�
{
	int i=0;
	while(man[i]!=NULL)//�Է¹��� ������ ���̸� �����ش�
		i++;
	pWho = new char[i+1];//�޸� �Ҵ� �Ѵ�
	memset(pWho,NULL,i+1);//�迭 �ʱ�ȭ �Ѵ�
	strcpy(pWho,man);//���� �����Ѵ�
}

void MemoNode::SetNext(MemoNode *pNode)//pNext�� �������ش�
{
	pNext=pNode;
}

char *MemoNode::GetTime()//�ð����� ��ȯ
{
	return pTime;
}

char *MemoNode::GetMemo()//�޸����� ��ȯ
{
	return pMemo;
}

char *MemoNode::GetWho()//�ۼ������� ��ȯ
{
	return pWho;
}

MemoNode *MemoNode::GetNext()//Next ��ȯ
{
	return pNext;
}
