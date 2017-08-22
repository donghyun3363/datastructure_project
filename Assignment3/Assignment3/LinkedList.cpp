#include "LinkedList.h"
#include <iostream>//��������� �����Ѵ�

LinkedList::LinkedList(void)//������
{
	pHead = NULL;
}

LinkedList::~LinkedList(void)//�Ҹ���
{

}

void LinkedList::SetHead()
{
	pHead = NULL;
}
Mechanic *LinkedList::GetMechanicHead()//����� ����Ʈ�� ����� ��ȯ�Ѵ�
{
	return pHead;
}

bool LinkedList::InsertMechanic(Mechanic *node)//����縦 ��������ִ� �Լ�
{
	Mechanic *temp = pHead;//�ش��� �ӽ� ������ �־��ش�

	if(pHead == NULL)//����� ����ִٸ�
	{
		pHead = node;//����� ����
		return true;//����ȯ
	}

	else//����� ������ �ִٸ�
	{
		while(temp->GetMechanicNext() != NULL)
			temp = temp->GetMechanicNext();//����� ����Ʈ�� ������ �ݺ��Ѵ�

		temp->SetMechanicNext(node);//�� �������� ��������ش�
		return true;//����ȯ
	}

	return false;//������ �Լ��� ���� ���� �ʾҴٸ� ������ȯ
}

bool LinkedList::CheckMechanic(char *gu)//������ �ٹ����� �˻��Ѵ�
{
	Mechanic *temp = pHead;//�ӽ� ������ head�� �־��ش�
	int check = 0;//check ����

	while(temp != NULL )//temp ������ �ݺ�
	{
		if( strcmp(temp->GetMechanicGu(), gu) == 0 )//������ �� �ٹ����� �����Ѵٸ�
			check++;//check ����
		temp = temp->GetMechanicNext();//temp�� ���� ����縦 ����Ų��
	}

	if(check == 0) //���� �� �ٹ����� �������� �ʴ´ٸ�
		return true;//����ȯ
	else//�׷��� �ʴٸ�
		return false;//������ȯ

}



