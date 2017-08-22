#include "Queue_.h"
#include<iostream>//������� ����

Queue_::Queue_(void)//������
{
	m_pHead=NULL;
}

Queue_::~Queue_(void)//�Ҹ���
{
}

bool Queue_::IsEmpty()//que�� ����ִ��� Ȯ���Ѵ�
{
	if(m_pHead==NULL)//�ԷµǾ��ִ� ��尡 ���ٸ�
		return true;//�� ��ȯ
	else//�ִٸ�
		return false;//���� ��ȯ
}

bool Queue_::Push(User *pNode)//Push�Լ� �ʱ�ȭ
{
	User *temp=NULL;//������ ��ü������ temp�� ���� �ϰ� �ʱ�ȭ ���ش�
	if(m_pHead==NULL)//����Ǿ��ִ� ��尡 ���ٸ�
	{
		m_pHead=pNode;//��������ͷ� �������ش�
		return true;//���� ��ȯ�Ѵ�
	}
	else//�� �ִ�  �ڷᰡ �ִٸ�
	{
		temp=m_pHead;//temp�� ��������͸� �־��ش�
		while(temp->GetqNext() !=NULL)//temp�� �Ǹ����� Ŭ���� ��ü ���� ���� ���� while��
			temp=temp->GetqNext();
		temp->SetqNext(pNode);//�������� �־��ش�
		return true;//����ȯ
	}
	return false;//push�� ���� �ߴٸ� ������ȯ
}

User *Queue_::Pop()//pop�Լ� �ʱ�ȭ
{
	User *temp=m_pHead;//temp�� ��������͸� �־��ش�
	m_pHead=m_pHead->GetqNext();//��������͸� ������带 ����Ű�� �Ѵ�
	temp->SetqNext(NULL);//next�� �����ְ� ���� ��ȯ�Ѵ�
	return temp;//pop�� ����� �ּҰ��� ��ȯ�Ѵ�
}
