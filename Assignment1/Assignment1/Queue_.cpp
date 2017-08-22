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

bool Queue_::Push(RegionNode *pNode)//Push�Լ� �ʱ�ȭ
{
	RegionNode *temp=NULL;//Ŭ������ ��ü������ temp�� ���� �ϰ� �ʱ�ȭ ���ش�
	if(m_pHead==NULL)//����Ǿ��ִ� ��尡 ���ٸ�
	{
		m_pHead=pNode;//��������ͷ� �������ش�
		return true;//���� ��ȯ�Ѵ�
	}

	else//�� �ִ�  �ڷᰡ �ִٸ�
	{
		temp=m_pHead;//temp�� ���������͸� �־��ش�
		while(temp->GetQNext()!=NULL)//temp�� �Ǹ����� Ŭ���� ��ü ���� ���� ���� while��
			temp=temp->GetQNext();
		temp->SetQNext(pNode);
		return true;//����ȯ
	}
	return false;//push�� ���� �ߴٸ� ������ȯ
}

RegionNode *Queue_::Pop()//pop�Լ� �ʱ�ȭ
{
	RegionNode *temp=m_pHead;//temp�� ���������͸� �־��ش�
	m_pHead=m_pHead->GetQNext();//���������͸� ������带 ����Ű�� �Ѵ�

	temp->SetQNext(NULL);
	return temp;//pop�� ����� �ּҰ��� ��ȯ�Ѵ�
}
