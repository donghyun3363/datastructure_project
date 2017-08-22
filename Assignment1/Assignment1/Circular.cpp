#include "Circular.h"
#include <iostream>

Circular::Circular(void)//������
{
	cirHead=NULL;
}

Circular::~Circular(void)//�Ҹ���
{
}

bool Circular::Insert(NumNode *pNode)//��������Ʈ�� �����ϴ� �Լ�
{
	if(cirHead == NULL)//��������Ʈ�� ����ִٸ�
	{
		cirHead=pNode;//head�� �������ش�
		cirHead->SetCirNext(cirHead);//next �ڸ��� head�� �־��ش�
		return true;//����ȯ
	}
	else//����Ǿ��ִ� ��尡 �ִٸ�
	{
		NumNode *pCur = cirHead->GetCirNext();
		while(pCur->GetCirNext() != cirHead)//������ �����
		{
			pCur = pCur->GetCirNext();
		}
		pCur->SetCirNext(pNode);//������ ��忡 �־��ش�
		pNode->SetCirNext(cirHead);//next �ڸ��� ����� �־��ش�
		return true;//����ȯ
	}
	return false;//������� ���� �� �ڸ��� ã�� ���߱� ������ false ��ȯ
}

NumNode *Circular::GetCirHead()//circular�� head�� ��ȯ�Ѵ�
{
	return cirHead;
}