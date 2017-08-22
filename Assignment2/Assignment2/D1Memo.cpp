#include "D1Memo.h"
#include<iostream>//������� ����

using namespace std;

D1Memo::D1Memo(void)//������
{
	pHead=NULL;

}

D1Memo::~D1Memo(void)//�Ҹ���
{
}

bool D1Memo::MemoInsert(User *MeNode, MemoNode *pNode)//MemoInsert �Լ� 
{
	pHead = MeNode->GetMyMemo();//MeNode�� memo head�� �����Ѵ�

	MemoNode *temp = NULL;
	MemoNode *pretemp = NULL;//�ӽ� ������ ����

	int check =0;//check�� ���� ���� ����
	if( pHead == NULL )//����� ����ִٸ�
	{
		MeNode->SetMyMemo(pNode);
		check++;//head�� �����ϰ� check ����
	}
	else//�ڷᰡ �ִٸ�
	{
		if( strcmp( pHead->GetTime(), pNode->GetTime() ) > 0 ) //���ο� ����� �ð��� ������� �����ٸ�
		{
			pNode->SetNext(pHead);
			MeNode->SetMyMemo(pNode);//����� �ٲ��ְ� ������ �ٽ� ������ �ش�.
			check++;//check ����
		}
		else//����� �̸����� �����ٸ�
		{
			pretemp=pHead;
			while(1)//�� �ڸ��� ã������ ���� ����
			{
				if(pretemp->GetNext() == NULL)//�Ǹ������� ��ġ�ؾ��Ѵٸ�
				{
					pretemp->SetNext(pNode);//�Ǹ������� ������ ���ش�.
					check++;//check ����
					break;//���ѷ��� ����
				}
				temp = pretemp->GetNext();
				if( strcmp( temp->GetTime(), pNode->GetTime() ) > 0)//temp�� �ð����� �����ٸ�
				{
					pNode->SetNext(temp);
					pretemp->SetNext(pNode);//temp�� pretemp���̿� ��ġ��Ų��
					check++;//check����
					break;//���ѷ��� ����
				}
				pretemp = pretemp->GetNext();//pretemp�� pretemp���� ��带 ����Ű�� �Ѵ�.
			}
		}
	}

	if(check==0)//Insert�� �̷�� ���� �ʾҴٸ�
		return false;//���� ��ȯ
	else//Insert�� �̷�� ���ٸ�       
		return true;//�� ��ȯ
}

bool D1Memo::MemoSearch(User *MeNode, char *time )//�޸� ã���ش�
{
	MemoNode *temp = MeNode->GetMyMemo();//������� �޸� ����� ��ȯ �޴´�
	if(temp ==NULL)
	{
		cout<<"����ڿ��� ����Ǿ��ִ� �޸�� �����ϴ�"<<endl;
		return false;
	}

	while(temp !=NULL)//�޸��� ������ �ݺ��Ѵ�
	{
		if(strcmp(temp->GetTime(), time)==0)//���ð� �޸� �����Ѵٸ�
			return true;//�� ��ȯ
		temp = temp->GetNext();
	}
	return false;
}

bool D1Memo::MemoDelete(User *MeNode, char *time )//�޸��� ������ ���� ���ش�.
{
	pHead = MeNode->GetMyMemo();//ģ���� ����� ��ȯ�Ѵ�
	MemoNode *temp =MeNode->GetMyMemo();//ģ���� ����� ��ȯ�Ѵ�

	MemoNode *pretemp = NULL;//�ӽ� ���� ����
	int check=0;//Ȯ���� ���� int�� ����

	if(temp ==NULL)//ģ���� ���� ���� �ʴ´ٸ�
	{
		cout<<"�ش������� ģ���� �������� �ʽ��ϴ�."<<endl;//�ش繮�� ���
		return false;//������ȯ
	}

	while(temp!=NULL)//ģ�� ����Ʈ ���������� �ݺ��Ѵ�
	{
		if( strcmp( pHead->GetTime() , time) == 0 )//�����ؾ��� ��尡 ������
		{
			MeNode->SetMyMemo(pHead->GetNext());
			pHead = pHead->GetNext();//����� �ٲ��ְ� ����� �������ִ� ������忬���� �����ش�
			delete temp;//������ ����
			check++;//check ���� ����
		}
		else if( ( strcmp( temp->GetTime(), time) ==0 ) && ( temp->GetNext() == NULL ) )
		{//�����ؾ��� ��尡 ������ �����
			pretemp->SetNext(NULL);//������ ������������ next ���� NULL�� �־��ش�
			delete temp;//������ ����
			check++;//check ���� ����
		}

		else if( strcmp( temp->GetTime() , time ) == 0 )
		{//�����ؾ��� ��尡 ��� �ִٸ�
			pretemp->SetNext( temp->GetNext() );//pretemp�� ���� ���� temp�� ���� ��带 �־��ش�
			delete temp;//������ ����
			check++;//check ���� ����
		}
		pretemp=temp;//pretemp�� temp�� �־��ش�
		temp = temp->GetNext();//temp�� temp���� ��带 �־��ش�
	}

	if(check == 0)//������ �̷�� �����ʾҴٸ�
		return false;//���� ��ȯ
	else//������ �̷�� ���ٸ�
		return true;//����ȯ

}