#include "Mechanic.h"
#include <iostream>//������� ����

Mechanic::Mechanic(void)//������
{
	Gu = NULL;
	Name = NULL;
	pNext = NULL;
	dis = 0;
}

Mechanic::~Mechanic(void)//�Ҹ���
{
	delete []Gu;
	delete []Name;
}

void Mechanic::SetMechanicGu(char *gu)//�� ����
{
	int i=0;
	while(gu[i]!=NULL)//�Է¹��� ������ ���̸� �����ش�
		i++;
	Gu = new char[i+1];//Ŭ���� ������ ���̸�ŭ �޸� �Ҵ� �Ѵ�
	memset(Gu,NULL,i+1);//�迭 �ʱ�ȭ �Ѵ�
	strcpy(Gu,gu);//���� �����Ѵ�
}

char *Mechanic::GetMechanicGu()//�� ��ȯ
{
	return Gu;
}

void Mechanic::SetMechanicName(char *name)//����� �̸� ����
{
	int i=0;
	while(name[i]!=NULL)//�Է¹��� ������ ���̸� �����ش�
		i++;
	Name = new char[i+1];//Ŭ���� ������ ���̸�ŭ �޸� �Ҵ� �Ѵ�
	memset(Name,NULL,i+1);//�迭 �ʱ�ȭ �Ѵ�
	strcpy(Name,name);//���� �����Ѵ�
}
char *Mechanic::GetMechanicName()//����� �̸� ��ȯ
{
	return Name;
}

void Mechanic::SetMechanicNext(Mechanic *node)//���� ����縦 ����Ų��
{
	pNext = node;
}

Mechanic *Mechanic::GetMechanicNext()//���� ����縦 ��ȯ�Ѵ�
{
	return pNext;
}

void Mechanic::SetDistence(int num)//������� �Ÿ��� �����Ѵ�
{
	dis = num;
}

int Mechanic::GetDistence()//������� �Ÿ� ��ȯ�Ѵ�
{
	return dis;
}