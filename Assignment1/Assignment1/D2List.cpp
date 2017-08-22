#include "D2List.h"
#include <iostream>//������� ����

using namespace std;//�̸� ������ std ������ ���

D2List::D2List(void)//������
{
	pHead=NULL;
}

D2List::~D2List(void)//�Ҹ���
{
}

RegionNode *D2List::GetHead()//pHead�� ��ȯ�Ѵ�.
{
	return pHead;
}

bool D2List::pInsert(RegionNode *pNode)//2D���� �θ������ �������ش�.
{
	RegionNode *temp=pHead;//temp�� head�� �־��ش�

	if(pHead==NULL)//head�� ����ִٸ�
	{
		pHead=pNode;//pNode�� head�� ������ �ش�
		return true; //true ��ȯ�ϰ� �Լ� ����
	}
	else//����Ǿ��ִ� ��尡 �ִٸ�
	{
		while(temp->GetNext() != NULL )//�� �ڸ��� ã�� �ݺ���
			temp=temp->GetNext();

		temp->SetNext(pNode);//�� �������� pNode�� �������ش�
		return true;//true�� ��ȯ�ϰ� �Լ� ����
	}
	return false;// pNode�� �ڸ��� ��ã�� ������ false ��ȯ
}

bool D2List::cInsert(char *Rnum, NumNode *cNode)//2D���� �ڽĳ����� �������ش�.
{
	RegionNode *Rtemp=pHead;
	NumNode *cHead=NULL;
	NumNode *temp=NULL;
	NumNode *pretemp=NULL;

	while(Rtemp !=NULL)//���� ���� �ڵ� �˻�
	{
		if(strcmp( Rnum, Rtemp->GetRegionNumber() ) == 0)//������ ���� �ڵ带 ã�´ٸ�
		{
			cHead=Rtemp->GetN_Head();//cHead�� �ش������ڵ��� ������ȣ head�� �����Ѵ�
			break;//while�� ����
		}
		Rtemp = Rtemp->GetNext();
	}

	int con=0;
	if(cHead==NULL)//�ԷµǾ��ִ� ����� ��ȣ ��尡 ���ٸ�
	{
		Rtemp->SetN_Head(cNode);//����� �������ش�
		con++;//con���� ����
	}

	else//����Ǿ��ִ� ��尡 �ִٸ�
	{
		temp = cHead;//temp�� �ڽĳ����� ��������͸� �־��ش�
		if( cNode->GetNum()[10] < cHead->GetNum()[10])//����� ����Ǿ��ִ� ��ǰ �������� �����ٸ�
		{
			cNode->SetNext(cHead);//����� �ٲ��ش�
			Rtemp->SetN_Head(cNode);
			con++;//ī���� ����
		}

		else if(cNode->GetNum()[10] == cHead->GetNum()[10])//����� ����Ǿ��ִ� ��ǰ������ ���ٸ�
		{
			if(cNode->GetNum()[11]=='1') //��� ���Ƕ��
			{
				cNode->SetNext(cHead);//����� �ٲ��ش�
				Rtemp->SetN_Head(cNode);
				con++;//ī���� ����
			}
			else//��� ���ǰ� �ƴ϶��
			{
				cNode->SetNext( cHead->GetNext() );//��� ���� �ڸ��� ��ġ��Ų��.
				cHead->SetNext(cNode);
				con++;//ī���� ����
			}
		}

		else//����� ����Ǿ��ִ� ��ǰ���� ���� �����ٸ�
		{
			pretemp=cHead;//�����ӽ� �����Ϳ� ������� �־��ش�
			while(1)//���� ����� �ڸ��� ã�������� �ݺ��Ѵ�
			{
				if( pretemp->GetNext() == NULL )//������ ������ ���ٸ�
				{
					pretemp->SetNext(cNode);//�������� �Է� ���� ��带 �������ش�
					con++;//ī���� ����
					break;//���ѷ��� ����
				}

				temp = pretemp->GetNext();//�ӽ������Ϳ� �����ӽ������� ������带 �����Ѵ�
				if( cNode->GetNum()[10] < temp->GetNum()[10]) //�ԷµǴ� ����� ��ǰ������ �� �����ٸ�
				{
					cNode->SetNext( temp );//�������� next�ڸ��� �ӽó���� ���� �־��ش�
					pretemp->SetNext( cNode );//�����ӽó���� next���� �������� �ּҰ��� �־��ش�
					con++;//ī���� ����
					break;//���ѷ��� ����
				}
				else if( cNode->GetNum()[10] == temp->GetNum()[10])//��ǰ ������ ���ٸ�
				{
					if(cNode->GetNum()[11]=='1')//��� ������ǰ�̶��
					{
						cNode->SetNext( temp );//�������� next�ڸ��� �ӽó���� ���� �־��ش�
						pretemp->SetNext( cNode );//�����ӽó���� next���� �������� �ּҰ��� �־��ش�
						con++;//ī���� ����
						break;//���ѷ��� ����
					}
					else//������ǰ� �ƴ϶��
					{
						cNode->SetNext( temp->GetNext() );//�ӽ� ��� ������ ��ġ��Ų��.
						temp->SetNext(cNode);
						con++;//ī���� ����
						break;
					}
				}
				pretemp=pretemp->GetNext();//�����ӽó��� ������带 ����Ű�����Ѵ�
			}
		}
	}

	if(con==0)//Insert�� �̷�� ���� �ʾҴٸ�
		return false;//���� ��ȯ
	else//Insert�� �̷�� ���ٸ�       
		return true;//�� ��ȯ
}

bool D2List::Delete(char *num, char *re)
{
	RegionNode *re_temp = pHead;
	NumNode *cHead = NULL;
	NumNode *temp = NULL ;
	NumNode *pretemp = NULL;
	while(re_temp !=NULL)
	{
		if(strcmp( re_temp->GetRegionNumber(), re)==0)
		{
			cHead = re_temp->GetN_Head();
			temp=re_temp->GetN_Head();
			pretemp=re_temp->GetN_Head();
			break;
		}
		re_temp=re_temp->GetNext();
	}

	while(temp!=NULL)//����Ʈ ���������� �ݺ��Ѵ�
	{
		if( strcmp( cHead->GetNum(),num) == 0 )//����� ����Ǿ��ִ� �̸��� ���ٸ�
		{
			re_temp->SetN_Head( (re_temp->GetN_Head())->GetNext() );
			delete temp;
			return true;
		}
		else if( ( strcmp( temp->GetNum(), num) == 0 ) && ( temp->GetNext()==NULL ) )//������ ����� �̸��� ���ٸ�
		{
			pretemp->SetNext(NULL);//������ ������������ next ���� NULL�� �־��ش�
			delete temp;
			return true;//�� ��ȯ
		}

		else if( strcmp( temp->GetNum(), num)==0 )//��� ��忡 ����Ǿ��ִ� �̸��� ���ٸ�
		{
			pretemp->SetNext( temp->GetNext() );//pretemp�� ���� ���� temp�� ���� ��带 �־��ش�
			delete temp;
			return true;//�� ��ȯ
		}

		pretemp=temp;//pretemp�� temp�� �־��ش�
		temp = temp->GetNext();//temp�� temp���� ��带 �־��ش�
	}
}

void D2List::Pdelete(RegionNode *del)
{
	RegionNode *temp=pHead;;
	RegionNode *pretemp=pHead;
	while(temp!=NULL)
	{
		if(del == pHead)
			pHead = pHead->GetNext();
		else if(temp==del)
		{
			pretemp->SetNext(temp->GetNext());
		}
		pretemp = temp;
		temp= temp->GetNext();
	}
}