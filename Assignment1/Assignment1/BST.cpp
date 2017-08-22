#include "BST.h"
#include<iostream> // �ش����� ����

BST::BST()//������
{
	pRoot=NULL;
}

BST::~BST(void)//�Ҹ���
{
}

RegionNode *BST::GetRoot() // pRoot�� ��ȯ�Ѵ�
{
	return pRoot;
}

bool BST::BSTInsert(RegionNode *pNode) //BST insert �Լ� 
{
	return BSTinsert_position(pRoot,pNode); //BSTinsert_position �Լ� ȣ��
}

bool BST::BSTinsert_position(RegionNode *current, RegionNode *pNode)
{
	int currenttemp, pNodetemp;//�����ڵ带 �ӽ÷� �����Ѵ�
	if(pRoot==NULL)//root�� ����ִٸ� 
	{
		pRoot=pNode;//pNode�� root�� �־��ش�
		return true;//�Լ� ����
	}

	currenttemp = atoi ( current->GetRegionNumber() );
	pNodetemp = atoi ( pNode->GetRegionNumber() ); // ������ �� ��ȯ ���ش�

	if(currenttemp > pNodetemp)//���� ���� �� �ڸ��� ã�´�
	{
		if(current->GetLeftNext() == NULL)//pNode�� �� �ڸ��� ã�´ٸ�
		{
			current->SetLeftNext(pNode);//��带 �������ش�
			return true;//����ȯ
		}
		return BSTinsert_position(current->GetLeftNext(),pNode);//����Լ� ȣ��
	}
	else if(currenttemp < pNodetemp)//���� ���� �� �ڸ��� ã�´�
	{
		if(current->GetRightNext()==NULL)//pNode�� �� �ڸ��� ã�´ٸ�
		{
			current->SetRightNext(pNode);//��带 �������ش�
			return true;
		}
		return BSTinsert_position(current->GetRightNext(),pNode);//����Լ� ȣ��
	}

	return false;//������ȯ
}

RegionNode *BST::Serch(char *Num)//����� ��ȣ�� �ش� ��带 ã�´�
{
	RegionNode *temp = pRoot;//temp�� root ��带 �־��ش�.
	while(temp !=NULL )//����� ������ ��� �ݺ��Ѵ�
	{
		if( strcmp(temp->GetRegionNumber(), Num ) ==0 ) //����� ��ȣ�� ��ġ�Ѵٸ� temp ��ȯ
			return temp;
		if( strcmp( temp->GetRegionNumber(), Num ) == 1)//temp�� num���� ũ�ٸ� temp�� temp->GetLeftNext()�� �־��ش�
			temp=temp->GetLeftNext();
		else                            //temp�� num���� �۴ٸ� temp�� temp->GetRightNext()�� �־��ش�
			temp = temp->GetRightNext();
	}
	return NULL;//ã�� ��尡 ���ٸ� NULL ��ȯ
}

bool BST::Delete(RegionNode *pNode)
{
	RegionNode *par = pRoot; // Ŭ���� ������ ���� ����
	RegionNode *del = pRoot;
	RegionNode *pretemp = NULL;
	RegionNode *temp = NULL;

	while( del != NULL )
	{
		if( strcmp(del->GetRegionNumber(), pNode->GetRegionNumber() ) ==0 ) //������ȣ�� ��ġ�ϴ� node�� ���� �Ѵٸ�
		{
			if( (del->GetLeftNext() != NULL) && (del->GetRightNext() != NULL) ) // �����ؾߵǴ³���� �ڽĳ�尡 �Ѵ� ���� �Ѵٸ� 
			{
				if(del==pRoot) //������ �ϴ� ��尡 Root ���
				{
					temp = del->GetLeftNext(); //���� subtree���� ���� ū �� temp�� ã�´�.
					pretemp = del->GetLeftNext();
					while(temp->GetRightNext() != NULL)//temp�� rightNext�� NULL�϶� ���� ��������
					{
						pretemp = temp;
						temp = temp->GetRightNext();
					}
					pretemp->SetRightNext( temp->GetLeftNext() );//temp�� Root �ڸ��� ��ġ��Ű�� ���� ����ٽ��������ش�
					temp->SetLeftNext( del->GetLeftNext() );
					temp->SetRightNext( del->GetRightNext() );
					pRoot=temp;//Root�� �ٲ��ش�
					delete del;//del �� �����ش�
					return true;
				}
				else //Root�� �ƴ϶��
				{
					temp = del->GetLeftNext();//���� subtree���� ���� ū �� temp�� ã�´�.
					pretemp = del->GetLeftNext();
					while(temp->GetRightNext() != NULL)//temp�� rightnext�� NULL�϶� ���� ��������
					{
						pretemp = temp;
						temp = temp->GetRightNext();
					}
					pretemp->SetRightNext( temp->GetLeftNext() );//temp�� del �ڸ��� ��ġ��Ű�� ���� ����ٽ��������ش�
					temp->SetLeftNext( del->GetLeftNext() );
					temp->SetRightNext( del->GetRightNext() );

					if(par->GetLeftNext()==del)//del�� ��ġ�� �θ���� ���� �ٽ��ѹ� Ȯ���Ѵ�
					{
						par->SetLeftNext(temp);//�������ְ� 
						delete del;//�����Ѵ�
						return true;
					}
					else if(par->GetRightNext()==del)
					{
						par->SetRightNext(temp);//�������ְ�
						delete del;//�����Ѵ�
						return true;
					}
				}
			}

			else if((del->GetLeftNext() != NULL) && (del->GetRightNext() == NULL) ) //�ڽĳ�尡 left�� �����Ҷ�
			{
				if(del==pRoot) //������ �ϴ� ��尡 Root ���
				{
					temp = del->GetLeftNext(); //���� subtree���� ���� ū �� temp�� ã�´�.
					pretemp = del->GetLeftNext();
					while(temp->GetRightNext() != NULL)//temp�� rightnext�� NULL�϶� ���� ��������
					{
						pretemp = temp;
						temp = temp->GetRightNext();
					}
					pretemp->SetRightNext( temp->GetLeftNext() );//temp�� Root �ڸ��� ��ġ��Ű�� ���� ����ٽ��������ش�
					temp->SetLeftNext( del->GetLeftNext() );
					pRoot=temp;//Root�� �ٲ��ش�
					delete del;//�����Ѵ�
					return true;
				}
				else //Root�� �ƴ϶��
				{
					temp = del->GetLeftNext();//���� subtree���� ���� ū �� temp�� ã�´�.
					pretemp = del->GetLeftNext();
					while(temp->GetRightNext() != NULL)//temp�� rightnext�� NULL�϶� ���� ��������
					{
						pretemp = temp;
						temp = temp->GetRightNext();
					}
					pretemp->SetRightNext( temp->GetLeftNext() );//temp�� del �ڸ��� ��ġ��Ű�� ���� ����ٽ��������ش�
					temp->SetLeftNext( del->GetLeftNext() );

					if(par->GetLeftNext()==del)//del�� ��ġ�� �θ���� ���� �ٽ��ѹ� Ȯ���Ѵ�
					{
						par->SetLeftNext(temp);//�������ְ� 
						delete del;//�����Ѵ�
						return true;
					}
					else if(par->GetRightNext()==del)
					{
						par->SetRightNext(temp);
						delete del;
						return true;
					}
				}
			}

			else if( (del->GetLeftNext() == NULL) && (del->GetRightNext() != NULL) )//�ڽĳ�尡 righr�� �����Ҷ�
			{
				if(del==pRoot) //������ �ϴ� ��尡 Root ���
				{
					temp = del->GetRightNext(); //������ subtree���� ���� ���� �� temp�� ã�´�.
					pretemp = del->GetRightNext();
					while(temp->GetLeftNext() != NULL)//temp�� leftnext�� NULL�϶� ���� ��������
					{
						pretemp = temp;
						temp = temp->GetLeftNext();
					}
					pretemp->SetLeftNext( temp->GetRightNext() );//temp�� Root �ڸ��� ��ġ��Ű�� ���� ����ٽ��������ش�
					temp->SetRightNext( del->GetRightNext() );
					pRoot=temp;//Root�� �ٲ��ش�
					delete del;//�����Ѵ�
					return true;
				}
				else //Root�� �ƴ϶��
				{
					temp = del->GetRightNext(); //������ subtree���� ���� ���� �� temp�� ã�´�.
					pretemp = del->GetRightNext();
					while(temp->GetLeftNext() != NULL)//temp�� leftnext�� NULL�϶� ���� ��������
					{
						pretemp = temp;
						temp = temp->GetLeftNext();
					}
					pretemp->SetLeftNext( temp->GetRightNext() );//temp�� Root �ڸ��� ��ġ��Ű�� ���� ����ٽ��������ش�
					temp->SetRightNext( del->GetRightNext() );

					if(par->GetRightNext()==del)//del�� ��ġ�� �θ���� ���� �ٽ��ѹ� Ȯ���Ѵ�
					{
						par->SetRightNext(temp);//�������ְ� 
						delete del;//�����Ѵ�
						return true;
					}
					else if(par->GetLeftNext()==del)
					{
						par->SetLeftNext(temp);
						delete del;
						return true;
					}
				}
			}

			else//�ڽ� ��尡 ���� ���
			{
				if(del==pRoot)//������ �ϴ� ��尡 Root �϶�
				{
					pRoot=NULL;//Root�� NULL
					delete del;//del�� �����
					return true;
				}
				else//Root ��尡 �ƴҶ�
				{
					if(par->GetLeftNext()==del) //������ �ϴ� ��尡 �θ����� ��� ��ġ�ϴ��� �ľ��Ѵ�
					{
						par->SetLeftNext(NULL);//�������ְ�
						delete del;//�����Ѵ�
						return true;
					}
					else if(par->GetRightNext()==del)
					{
						par->SetRightNext(NULL);
						delete del;
						return true;
					}
				}
			}

		}
		par = del;//par�� ���� del�� �־��ش�
		if( strcmp( del->GetRegionNumber(), pNode->GetRegionNumber() ) == 1)//del�� ���� ���� �ٲ��ش�
			del = del->GetLeftNext();
		else
			del = del->GetRightNext();
	}
	return 0;
}