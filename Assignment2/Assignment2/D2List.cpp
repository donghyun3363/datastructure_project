#include "D2List.h"
#include <iostream>//������ϼ���

using namespace std;//�̸������� std ������ ���

D2List::D2List(void)//������
{
	pHead=NULL;
}

D2List::~D2List(void)//�Ҹ���
{
}

bool D2List::Insert(User *MeNode, User *FriNode)//ģ�� ���� �Լ�
{
	pHead = MeNode->GetFri();//���� ������ ��� ���� ��ȯ�Ѵ�.
	Linked *temp = NULL;
	Linked *pretemp = NULL;//�ӽ� ������ ����
	Linked *list = new Linked();//���ο� ģ���� ���� ��� ����

	int check =0;//check�� ���� ���� ����

	if( pHead == NULL )//����� ����ִٸ�
	{
		list->SetDown(FriNode);
		MeNode->SetFri(list);//����� �������ش�
		check++;//check ����
	}

	else//�ڷᰡ �ִٸ�
	{
		if( strcmp( (pHead->GetDown())->GetName(), FriNode->GetName() ) > 0 ) //���ο� ����� �̸��� ������� �����ٸ�
		{
			list->SetNext(pHead);
			list->SetDown(FriNode);
			MeNode->SetFri(list);//����� �ٲ��ְ� ������ �ٽ� ������ �ش�.
			check++;//check ����
		}

		else if(strcmp( (pHead->GetDown())->GetName(), FriNode->GetName() ) == 0)//����� �̸��� �������
		{
			if( strcmp( (pHead->GetDown())->GetNumber(), FriNode->GetNumber() ) > 0)//����� �й��� ���Ѵ�
			{
				list->SetNext(pHead);
				list->SetDown(FriNode);
				MeNode->SetFri(list);//����� �й����� �����ٸ� ����� �ٲ��ְ� ������ �ٽ� �������ش�
				check++;//check ����
			}
			else///����� �й����� �����ٸ�
			{
				list->SetNext(pHead->GetNext());
				list->SetDown(FriNode);
				pHead->SetNext(list);//��� ������ ���� ���ش�.
				check++;//check ����
			}
		}

		else//����� �̸����� �����ٸ�
		{
			pretemp=pHead;
			while(1)//�� �ڸ��� ã������ ���� ����
			{
				if(pretemp->GetNext() == NULL)//�Ǹ������� ��ġ�ؾ��Ѵٸ�
				{
					pretemp->SetNext(list);
					list->SetDown(FriNode);//�Ǹ������� ������ ���ش�.
					check++;
					break;//check ���� ���ѷ�������
				}

				temp = pretemp->GetNext();
				if( strcmp( (temp->GetDown())->GetName(), FriNode->GetName() ) > 0)//temp�� �̸����� �����ٸ�
				{
					list->SetNext(temp);
					list->SetDown(FriNode);
					pretemp->SetNext(list);//temp�� pretemp���̿� ��ġ��Ų��
					check++;
					break;//check ���� ���ѷ��� ����
				}
				else if(strcmp( (temp->GetDown())->GetName(), FriNode->GetName() ) == 0)//temp�� �̸��� ���ٸ�
				{
					if( strcmp( (temp->GetDown())->GetNumber(), FriNode->GetNumber() ) > 0)//temp�� �й����� �����ٸ�
					{
						list->SetNext(temp);
						list->SetDown(FriNode);
						pretemp->SetNext(list);//temp�� pretemp���̿� ��ġ��Ų��
						check++;
						break;//check ���� ���ѷ��� ����
					}
					else//temp�� �й����� �����ٸ�
					{
						list->SetNext(temp->GetNext());
						list->SetDown(FriNode);
						temp->SetNext(list);//temp �ڿ� ��ġ ��Ų��
						check++;
						break;//check ���� ���ѷ��� ����
					}
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

int D2List::SearchFri(User *Node, char *friName)//�̸����� ģ���� ã�Ƽ� �� ģ���� �ο����� ��ȯ�Ѵ�
{
	int check=0;//ģ�� ��� check ����
	Linked *temp = Node->GetFri();//ģ�� ���� ����Ʈ�� temp�� ����
	User *FriNode = NULL;
	if(temp==NULL)
	{
		cout<<"�ش������� ģ���� �������� �ʽ��ϴ�."<<endl;
		return false;//�ش繮�� ��� ���� ��ȯ
	}

	while(temp!=NULL)//temp ������ �ݺ��Ѵ�
	{
		if(strcmp( (temp->GetDown())->GetName(), friName) == 0 )//ã�����ϴ� �̸��� ������ģ���� �����Ѵٸ�
		{
			FriNode = temp->GetDown();
			if(SearchFri(FriNode, Node))
			{
				check++;//check ����
			}
		}
		temp = temp->GetNext();//temp�� ���� temp�� ����Ų��
	}
	return check;//ģ�� ����� ��ȯ�Ѵ�
}

bool D2List::SearchFri(User *MeNode, User *friNode)//User Node�� ģ���߿� ���� �ϴ��� �˻����ش�
{
	int check=0;//ģ�� ���翩�� 
	Linked *temp = MeNode->GetFri();//ģ�� ���� Linked�� head�� ��ȯ�Ѵ�
	if(temp==NULL)
	{
		cout<<"�ش������� ģ���� �������� �ʽ��ϴ�."<<endl;
		return false;//�ش繮�� ��� ���� ��ȯ
	}

	while(temp!=NULL)//ģ������ ��� �ϻ����ش�
	{
		//���������� ���� �� ���� �ֱ� ������ ������ �й����� ģ�������� Ȯ���Ѵ�.
		if(strcmp( (temp->GetDown())->GetNumber(), friNode->GetNumber() ) == 0 )
			check++;//check�� ������Ų��.
		temp = temp->GetNext();//���� ģ���� ����Ű�� �Ѵ�
	}

	if(check == 0)//ģ���� �ƴ϶��
		return false;//���� ��ȯ
	else//ģ�����
		return true;//����ȯ
}

bool D2List::DeleteFrt(User *MeNode, User *friNode)//ģ�� ���� ���� �Լ�
{
	pHead = MeNode->GetFri();//ģ���� ����� ��ȯ�Ѵ�
	Linked *temp =MeNode->GetFri();//ģ���� ����� ��ȯ�Ѵ�

	Linked *pretemp = NULL;//�ӽ� ���� ����
	int check=0;//Ȯ���� ���� int�� ����

	if(temp ==NULL)//ģ���� ���� ���� �ʴ´ٸ�
	{
		cout<<"�ش������� ģ���� �������� �ʽ��ϴ�."<<endl;//�ش繮�� ���
		return false;//������ȯ
	}

	while(temp!=NULL)//ģ�� ����Ʈ ���������� �ݺ��Ѵ�
	{
		if( strcmp( ( pHead->GetDown())->GetNumber(), friNode->GetNumber() ) == 0 )//�����ؾ��� ��尡 ������
		{
			MeNode->SetFri(pHead->GetNext());
			pHead->SetDown(NULL);
			pHead = pHead->GetNext();//����� �ٲ��ְ� ����� �������ִ� ������忬���� �����ش�
			delete temp;//������ ����
			check++;//check ���� ����
		}
		else if( ( strcmp( (temp->GetDown())->GetNumber(), friNode->GetNumber() ) ==0 ) && ( temp->GetNext() == NULL ) )
		{//�����ؾ��� ��尡 ������ �����
			pretemp->SetNext(NULL);//������ ������������ next ���� NULL�� �־��ش�
			temp->SetDown(NULL);//������ ��尡 ������ �ִ� ������忬���� �����ش�
			delete temp;//������ ����
			check++;//check ���� ����
		}

		else if( strcmp( (temp->GetDown())->GetNumber() , friNode->GetNumber() ) == 0 )
		{//�����ؾ��� ��尡 ��� �ִٸ�
			pretemp->SetNext( temp->GetNext() );//pretemp�� ���� ���� temp�� ���� ��带 �־��ش�
			temp->SetDown(NULL);//temp��尡 ������ �ִ� ������忬���� �����ش�
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