#include "AVL.h"
#include <iostream>//������� ����

using namespace std;//�̸������� std ������ ���

AVL::AVL(void)//������
{
	NameRoot = NULL;
	NumberRoot = NULL;
}

AVL::~AVL(void)//�Ҹ���
{
	NameRoot = NULL;
	NumberRoot = NULL;
}

User *AVL::GetNameRoot()//Name AVL�� ����� ��ȯ�Ѵ�
{
	return NameRoot;
}

User *AVL::GetNumRoot()//Number AVL�� ����� ��ȯ�Ѵ�
{
	return NumberRoot;
}

bool AVL::NameAVL(User *pNode)//�̸� ���� AVL TREE
{
	User *Cur = NameRoot;
	User *pCur = NULL;
	User *Break = NULL;
	User *pBreak = NULL;//AVL�� ���� ������ ���� ����

	if(NameRoot==NULL)//����Ǿ��ִ� ��尡 ���ٸ�
	{
		NameRoot=pNode;//����� ������ �� ��ȯ
		return true;
	}

	while(Cur!=NULL)//�� ��ġ�� ã���ֱ� ���� �ݺ���
	{
		if( Cur->Getbf() )//�������� ���� ��带 ã���ش�
		{
			Break = Cur;
			pBreak = pCur;//Break, pBreak�� �����Ѵ�
		}

		if( strcmp( Cur->GetName(), pNode->GetName() ) > 0)//���ο� ����� �̸��� �� �����ٸ�
		{
			pCur = Cur;
			Cur = Cur->GetNameLeft();//left next�� ����
		}
		else if(strcmp( Cur->GetName(), pNode->GetName() ) < 0)//���ο� ����� �̸��� �� �����ٸ�
		{
			pCur = Cur;
			Cur = Cur->GetNameRight();//right next�� ����
		}
		else if(strcmp( Cur->GetName(), pNode->GetName() ) == 0)//���ο� ����� �̸��� ���ٸ�
		{
			if(strcmp( Cur->GetNumber(), pNode->GetNumber() ) > 0)//�й��� �� �����ٸ�
			{
				pCur = Cur;
				Cur = Cur->GetNameLeft();//left next�� ����
			}
			else//�й��� �� �����ٸ�
			{
				pCur = Cur;
				Cur = Cur->GetNameRight();//right next�� ����
			}
		}
	}
	//���ο� ��尡 ���� �� ��ġ�� �������ش�.
	if( strcmp( pCur->GetName(), pNode->GetName() ) > 0)//���� sub tree�� ����
		pCur->SetNameLeft(pNode);
	else if(strcmp( pCur->GetName(), pNode->GetName() ) < 0)//������ sub tree�� ����
		pCur->SetNameRight(pNode);
	else//�������� ����ó��
	{
		if(strcmp( pCur->GetNumber(), pNode->GetNumber() ) > 0)//�й��� ���� ���� sub tree�� ����
			pCur->SetNameLeft(pNode);
		else//������ sub tree�� ����
			pCur->SetNameRight(pNode);
	}

	Cur = NameRoot;//Cur�� Root�� ����
	if( ( pNode == NameRoot->GetNameLeft() ) || ( pNode == NameRoot->GetNameRight() ) )//����Ǿ��ִ� ����� ���� ������ ����ó��
	{
		if( (strcmp(Cur->GetName(),pNode->GetName() ) < 0) && (Cur->GetNameLeft() == NULL) )//root���� ������ sub tree�� ���� �Ѵٸ�
			Cur->Setbf(-1);//blance factor�� -1 ����
		else if( (strcmp( Cur->GetName(),pNode->GetName() ) > 0) && (Cur->GetNameRight() == NULL) )//root���� ���� sub tree�� ���� �Ѵٸ�
			Cur->Setbf(1);//blance factor�� 1 ����
		else
			Cur->Setbf(0);//�Ѵ� ������ 0����
		return true;//�� ��ȯ
	}

	else if( (pCur == NameRoot->GetNameRight()) || (pCur == NameRoot->GetNameLeft()) )//����Ǿ��ִ� ����� ���� ������ ����ó��
	{
		if( (NameRoot->GetNameLeft()!=NULL) && (NameRoot->GetNameRight() !=NULL ) )//root�� sub tree�� �Ѵ� �����Ѵٸ�
		{
			Cur = NameRoot;
			while(Cur !=pNode )//insert�� ������ �ݺ��ϴ� while��
			{
				if( strcmp( Cur->GetName(), pNode->GetName() ) > 0)//���� sub tree���
				{
					Cur->Setbf(1);//blance factor �ٽ� ����
					Cur = Cur->GetNameLeft();
				}
				else if(strcmp( Cur->GetName(), pNode->GetName() ) < 0)//������ sub tree���
				{
					Cur->Setbf(-1);//blance factor �ٽ� ����
					Cur = Cur->GetNameRight();
				}
				else if(strcmp( Cur->GetName(), pNode->GetName() ) == 0)//�̸��� ���ٸ� �й� ��
				{
					if(strcmp( Cur->GetNumber(), pNode->GetNumber() ) > 0)//���� sub tree���
					{
						Cur->Setbf(1);//blance factor �ٽ� ����
						Cur = Cur->GetNameLeft();
					}
					else//������ sub tree���
					{
						Cur->Setbf(-1);//blance factor �ٽ� ����
						Cur = Cur->GetNameRight();
					}
				}
			}
			return true;//����ȯ
		}
	}

	if(Break==NULL)//�� ����� ���� sub tree�� ��� blance�� �����ǰ� �ִٸ�
	{
		Cur=NameRoot;//Cur�� Root�� ����
		while(Cur !=pNode) //���ο� ��尡 ������ blance�� �ٽ� �������ش�
		{
			if( strcmp( Cur->GetName(), pNode->GetName() ) > 0)//���� sub tree���
			{
				Cur->Setbf(1);//blance factor �ٽ� ����
				Cur = Cur->GetNameLeft();
			}
			else if(strcmp( Cur->GetName(), pNode->GetName() ) < 0)//������ sub tree���
			{
				Cur->Setbf(-1);//blance factor �ٽ� ����
				Cur = Cur->GetNameRight();
			}
			else if(strcmp( Cur->GetName(), pNode->GetName() ) == 0)//�̸��� ���ٸ� �й� ��
			{
				if(strcmp( Cur->GetNumber(), pNode->GetNumber() ) > 0)//���� sub tree���
				{
					Cur->Setbf(1);//blance factor �ٽ� ����
					Cur = Cur->GetNameLeft();
				}
				else//������ sub tree���
				{
					Cur->Setbf(-1);//blance factor �ٽ� ����
					Cur = Cur->GetNameRight();
				}
			}
		}
		return true;//����ȯ
	}

	int check=0;//Right,Left������ �������ش�.
	User *b,*c;//blance�� ���߱� ���� User �����Ϳ� check ����

	if(strcmp( Break->GetName(), pNode->GetName() ) < 0)//blance �� ���� ����� ������ sub tree�� ���ο� ��尡 ���ٸ�
	{
		b=Break->GetNameRight();
		Cur=Break->GetNameRight();
		check = -1;//������ ������ �ٲ��ش�
	}
	else//blance �� ���� ����� ���� sub tree�� ���ο� ��尡 ���ٸ�
	{
		b=Break->GetNameLeft();
		Cur=Break->GetNameLeft();
		check = 1;//������ ������ �ٲ��ش�
	}

	while(Cur != pNode)//���� ���Ե� ����� �θ������ blance factor�� �ٽ� �������ش�
	{
		if( strcmp(Cur->GetName(), pNode->GetName() )  < 0)//������ sub tree���
		{
			Cur->Setbf(-1);
			Cur=Cur->GetNameRight();//���� �������ش�
		}
		else if(strcmp(Cur->GetName(), pNode->GetName() )  > 0)//���� sub tree���
		{
			Cur->Setbf(1);
			Cur= Cur->GetNameLeft();//���� �������ش�
		}
		else//�̸��� ���ٸ� => �й� ��
		{
			if(strcmp( Cur->GetNumber(), pNode->GetNumber() ) < 0)//������ sub tree���
			{
				Cur->Setbf(-1);
				Cur=Cur->GetNameRight();//���� �������ش�
			}
			else//���� sub tree��� 
			{
				Cur->Setbf(1);
				Cur= Cur->GetNameLeft();//���� �������ش�
			}
		}
	}

	if( !(Break->Getbf()) || !(Break->Getbf() + check) )//����� �̵��� ��� �Ǵ� �����
	{
		Break->Setbf( (Break->Getbf() + check) );//blance factor �ٽ� ������ 
		return true;//����ȯ
	}

	if(check ==1 )//���� sub tree���
	{
		if(b->Getbf() ==1 )// LL �������
		{
			Break->SetNameLeft( b->GetNameRight() );
			b->SetNameRight(Break);
			Break->Setbf(0);
			b->Setbf(0);//������ ��ġ�� �ٲ��ְ� blance factor�� �ٽ� �������ش�
		}
		else// LR �������
		{
			c = b->GetNameRight();
			b->SetNameRight( c->GetNameLeft() );
			Break->SetNameLeft( c->GetNameRight() );
			c->SetNameLeft(b);
			c->SetNameRight(Break);//������ ��ġ�� �ٲ㼭 �������ش�

			if(c->Getbf() == 1)//�� ��쿡 ���� blance factor�� �ٽ� �������ش�
			{
				Break->Setbf(-1);
				b->Setbf(0);
			}
			else if(c->Getbf() == -1)
			{
				b->Setbf(1);
				Break->Setbf(0);
			}
			else if(c->Getbf() == 0)
			{
				b->Setbf(0);
				Break->Setbf(0);
			}
			c->Setbf(0);//blance factor�� �ٽ� �������ش�
			b=c;
		}
	}

	else//������ sub tree���
	{
		if(b->Getbf() == -1 )// RR �������
		{
			Break->SetNameRight( b->GetNameLeft() );
			b->SetNameLeft(Break);
			Break->Setbf(0);
			b->Setbf(0);//������ ��ġ�� �ٲ��ְ� blance factor�� �ٽ� �������ش�
		}
		else// RL �������
		{
			c = b->GetNameLeft();
			b->SetNameLeft( c->GetNameRight() );
			Break->SetNameRight( c->GetNameLeft() );
			c->SetNameRight(b);
			c->SetNameLeft(Break);//������ ��ġ�� �ٲ㼭 �������ش�

			if(c->Getbf() == 1)//�� ��쿡 ���� blance factor�� �ٽ� �������ش�
			{
				Break->Setbf(0);
				b->Setbf(-1);
			}
			else if(c->Getbf() == -1)
			{
				b->Setbf(0);
				Break->Setbf(1);
			}
			else if(c->Getbf() == 0)
			{
				b->Setbf(0);
				Break->Setbf(0);
			}
			c->Setbf(0);//blance factor�� �ٽ� �������ش�
			b=c;
		}
	}

	if( !(pBreak) )//���� ��尡 Root���
		NameRoot = b;//Root �ٽ�����
	else if(Break == pBreak->GetNameLeft() )//���� ������ blance�� ���߰� ���� ���� �������ش�
		pBreak->SetNameLeft(b);//����
	else
		pBreak->SetNameRight(b);//����

	return true;//����ȯ
}

bool AVL::NumberAVL(User *pNode)//�й� ���� AVL TREE
{
	User *Cur = NumberRoot;
	User *pCur = NULL;
	User *Break = NULL;
	User *pBreak = NULL;//AVL�� ���� ������ ���� ����

	if(NumberRoot==NULL)//����Ǿ��ִ� ��尡 ���ٸ�
	{
		NumberRoot=pNode;//����� ������ �� ��ȯ
		return true;
	}

	while(Cur!=NULL)//�� ��ġ�� ã���ֱ� ���� �ݺ���
	{
		if( Cur->Getbf() )//�������� ���� ��带 ã���ش�
		{
			Break = Cur;
			pBreak = pCur;//Break, pBreak�� �����Ѵ�
		}

		if( strcmp( Cur->GetNumber(), pNode->GetNumber() ) > 0)//���ο� ����� �й��� �����ٸ�
		{
			pCur = Cur;
			Cur = Cur->GetNumLeft();//left next�� ����
		}
		else //���ο� ����� �й��� �� �����ٸ�
		{
			pCur = Cur;
			Cur = Cur->GetNumRight();//right next�� ����
		}
	}
	//���ο� ��尡 ���� �� ��ġ�� �������ش�.
	if( strcmp( pCur->GetNumber(), pNode->GetNumber() ) > 0)//���� sub tree�� ����
		pCur->SetNumLeft(pNode);
	else//������ sub tree�� ����
		pCur->SetNumRight(pNode);

	Cur = NumberRoot;//Cur�� Root�� ����
	if( ( pNode == NumberRoot->GetNumLeft() ) || ( pNode == NumberRoot->GetNumRight() ) )//����Ǿ��ִ� ����� ���� ������ ����ó��
	{
		if( (strcmp(Cur->GetNumber(),pNode->GetNumber() ) < 0) && (Cur->GetNumLeft() == NULL) )//root���� ������ sub tree�� ���� �Ѵٸ�
			Cur->SetNbf(-1);//blance factor�� -1 ����
		else if( (strcmp( Cur->GetNumber(), pNode->GetNumber() ) > 0) && (Cur->GetNumRight() == NULL) )//root���� ���� sub tree�� ���� �Ѵٸ�
			Cur->SetNbf(1);//blance factor�� 1 ����
		else
			Cur->SetNbf(0);//�Ѵ� ������ 0����
		return true;//�� ��ȯ
	}

	else if( (pCur == NumberRoot->GetNumRight()) || (pCur == NumberRoot->GetNumLeft()) )//����Ǿ��ִ� ����� ���� ������ ����ó��
	{
		if( (NumberRoot->GetNumLeft()!=NULL) && (NumberRoot->GetNumRight() !=NULL ) )//root�� sub tree�� �Ѵ� �����Ѵٸ�
		{
			Cur = NumberRoot;
			while(Cur !=pNode )//insert�� ������ �ݺ��ϴ� while��
			{
				if( strcmp( Cur->GetNumber(), pNode->GetNumber() ) > 0)//���� sub tree���
				{
					Cur->SetNbf(1);//blance factor �ٽ� ����                                                           
					Cur = Cur->GetNumLeft();
				}
				else if(strcmp( Cur->GetNumber(), pNode->GetNumber() ) < 0)//������ sub tree���
				{
					Cur->SetNbf(-1);//blance factor �ٽ� ����
					Cur = Cur->GetNumRight();
				}
			}
			return true;//����ȯ
		}
	}

	if(Break==NULL)//�� ����� ���� sub tree�� ��� blance�� �����ǰ� �ִٸ�
	{
		Cur=NumberRoot;
		while(Cur !=pNode) //���ο� ��尡 ������ blance�� �ٽ� �������ش�
		{
			if( strcmp( Cur->GetNumber(), pNode->GetNumber() ) > 0)//���� sub tree���
			{
				Cur->SetNbf(1);//blance factor �ٽ� ����
				Cur = Cur->GetNumLeft();
			}
			else if(strcmp( Cur->GetNumber(), pNode->GetNumber() ) < 0)//������ sub tree���
			{
				Cur->SetNbf(-1);//blance factor �ٽ� ����
				Cur = Cur->GetNumRight();
			}
		}
		return true;//����ȯ
	}

	int check=0;//Right,Left������ �Ǵ��ϴ� ����
	User *b,*c;//blance�� ���߱� ���� User �����Ϳ� check ����

	if(strcmp( Break->GetNumber(), pNode->GetNumber() ) < 0)//blance �� ���� ����� ������ sub tree�� ���ο� ��尡 ���ٸ�
	{
		b=Break->GetNumRight();
		Cur=Break->GetNumRight();
		check = -1;//������ ������ �ٲ��ش�
	}
	else//blance �� ���� ����� ���� sub tree�� ���ο� ��尡 ���ٸ�
	{
		b=Break->GetNumLeft();
		Cur=Break->GetNumLeft();
		check = 1;//������ ������ �ٲ��ش�
	}

	while(Cur != pNode)//���� ���Ե� ����� �θ������ blance factor�� �ٽ� �������ش�
	{
		if( strcmp(Cur->GetNumber(), pNode->GetNumber() )  < 0)//������ sub tree���
		{
			Cur->SetNbf(-1);
			Cur=Cur->GetNumRight();//���� �������ش�
		}
		else//���� sub tree���
		{
			Cur->SetNbf(1);
			Cur= Cur->GetNumLeft();//���� �������ش�
		}
	}

	if( !(Break->GetNbf()) || !(Break->GetNbf() + check) )//����� �̵��� ��� �Ǵ� �����
	{
		Break->SetNbf( (Break->GetNbf()+check) );//blance factor �ٽ� ������ 
		return true;//����ȯ
	}

	if(check ==1 )//���� sub tree���
	{
		if(b->GetNbf() ==1 )// LL �������
		{
			Break->SetNumLeft( b->GetNumRight() );
			b->SetNumRight(Break);
			Break->SetNbf(0);
			b->SetNbf(0);//������ ��ġ�� �ٲ��ְ� blance factor�� �ٽ� �������ش�
		}
		else// LR �������
		{
			c = b->GetNumRight();
			b->SetNumRight( c->GetNumLeft() );
			Break->SetNumLeft( c->GetNumRight() );
			c->SetNumLeft(b);
			c->SetNumRight(Break);//������ ��ġ�� �ٲ㼭 �������ش�

			if(c->GetNbf() == 1)//�� ��쿡 ���� blance factor�� �ٽ� �������ش�
			{
				Break->SetNbf(-1);
				b->SetNbf(0);
			}
			else if(c->GetNbf() == -1)
			{
				b->SetNbf(1);
				Break->SetNbf(0);
			}
			else if(c->GetNbf() == 0)
			{
				b->SetNbf(0);
				Break->SetNbf(0);
			}
			c->SetNbf(0);//blance factor�� �ٽ� �������ش�
			b=c;
		}
	}

	else//������ sub tree���
	{
		if(b->GetNbf() == -1 )// RR �������
		{
			Break->SetNumRight( b->GetNumLeft() );
			b->SetNumLeft(Break);
			Break->SetNbf(0);
			b->SetNbf(0);//������ ��ġ�� �ٲ��ְ� blance factor�� �ٽ� �������ش�
		}
		else// RL �������
		{
			c = b->GetNumLeft();
			b->SetNumLeft( c->GetNumRight() );
			Break->SetNumRight( c->GetNumLeft() );
			c->SetNumRight(b);
			c->SetNumLeft(Break);//������ ��ġ�� �ٲ㼭 �������ش�

			if(c->GetNbf() == 1)//�� ��쿡 ���� blance factor�� �ٽ� �������ش�
			{
				Break->SetNbf(0);
				b->SetNbf(-1);
			}
			else if(c->GetNbf() == -1)
			{
				b->SetNbf(0);
				Break->SetNbf(1);
			}
			else if(c->GetNbf() == 0)
			{
				b->SetNbf(0);
				Break->SetNbf(0);
			}
			c->SetNbf(0);//blance factor�� �ٽ� �������ش�
			b=c;
		}
	}

	if( !(pBreak) )//���� ��尡 Root���
		NumberRoot = b;//Root �ٽ�����
	else if(Break == pBreak->GetNumLeft() )//���� ������ blance�� ���߰� ���� ���� �������ش�
		pBreak->SetNumLeft(b);//����
	else
		pBreak->SetNumRight(b);//����

	return true;//����ȯ

}

User *AVL::NumSearch(char *Num)//�й����� �ش� ��带 ã�´�
{
	User *temp = NumberRoot;//temp�� NumberRoot ��带 �־��ش�.

	if(temp==NULL)//����Ǿ��ִ� ������ ���ٸ�
	{
		cout<<"����Ǿ��ִ� �����Ͱ� �����ϴ�"<<endl;
		return NULL;//�ش繮�� ��� ���� ��ȯ
	}

	while( temp !=NULL )//����� ������ ���� �ݺ��Ѵ�
	{
		if( strcmp(temp->GetNumber(), Num ) == 0 ) //�й��� ��ġ�Ѵٸ� temp ��ȯ
			return temp;
		if( strcmp( temp->GetNumber(), Num ) > 0)//temp�� num���� ũ�ٸ� temp�� ���� sub tree�� �־��ش�
			temp = temp->GetNumLeft();
		else                            //temp�� num���� �۴ٸ� temp�� ������ sub tree�� �־��ش�
			temp = temp->GetNumRight();
	}
	return NULL;//ã�� ��尡 ���ٸ� NULL ��ȯ
}

bool AVL::CheckSameName(char *Name)//�������� check �Լ�
{
	User *temp = NameRoot;//temp�� NameRoot ��带 �־��ش�.
	User *temp2 = NULL;
	int check =0;

	if(temp==NULL)//����Ǿ��ִ� ������ ���ٸ�
	{
		cout<<"����Ǿ��ִ� �����Ͱ� �����ϴ�"<<endl;
		return false;//�ش繮�� ��� ���� ��ȯ
	}

	while( temp !=NULL )//����� ������ ���� �ݺ��Ѵ�
	{
		if( strcmp(temp->GetName(), Name ) == 0 ) //�̸��� ��ġ�Ѵٸ� �� ����� sub tree�� Ȯ���Ѵ�
		{
			temp2 = temp->GetNameLeft();//���� sub tree
			while( temp2 !=NULL )//����� ������ ���� �ݺ��Ѵ�
			{
				if( strcmp(temp2->GetName(), Name ) == 0 ) //���������� �����Ѵٸ�
					return true;//����ȯ
				if( strcmp( temp2->GetName(), Name ) > 0)//temp2�� �̸����� �����ٸ�
					temp2 = temp2->GetNameLeft();//left sub tree ����
				else                           //temp2�� �̸����� �����ٸ�
					temp2 = temp2->GetNameRight();//right sub tree ����
			}

			temp2 = temp->GetNameRight();//������ sub tree
			while( temp2 !=NULL )//����� ������ ���� �ݺ��Ѵ�
			{
				if( strcmp(temp2->GetName(), Name ) == 0 )//���������� �����Ѵٸ�
					return true;//����ȯ
				if( strcmp( temp2->GetName(), Name ) > 0)//temp2�� �̸����� �����ٸ�
					temp2 = temp2->GetNameLeft();//left sub tree ����
				else                            //temp2�� �̸����� �����ٸ�
					temp2 = temp2->GetNameRight();//right sub tree ����
			}
			return false;//������ �̸��� sub tree�ȿ� ���������� �����Ƿ� false ��ȯ
		}
		if( strcmp( temp->GetName(), Name ) > 0)//temp1�� �̸����� �����ٸ�
			temp = temp->GetNameLeft();//left sub tree ����
		else                            //temp2�� �̸����� �����ٸ�
			temp = temp->GetNameRight();//right sub tree ����
	}
	return false;
}

User *AVL::NameSearch(char *Name)//�̸����� �ش������� ã�� ��ȯ�Ѵ�
{
	User *temp = NameRoot;//temp�� NameRoot ��带 �־��ش�.
	if(temp==NULL)//����Ǿ��ִ� ������ ���ٸ�
	{
		cout<<"����Ǿ��ִ� �����Ͱ� �����ϴ�"<<endl;
		return NULL;//�ش繮�� ��� ���� ��ȯ
	}

	while( temp !=NULL )//����� ������ ���� �ݺ��Ѵ�
	{
		if( strcmp(temp->GetName(), Name ) == 0 ) //�̸��� ��ġ�Ѵٸ� temp ��ȯ
			return temp;
		if( strcmp( temp->GetName(), Name ) > 0)//temp�� �̸����� �����ٸ�
			temp = temp->GetNameLeft();//left sub tree ����
		else                            //temp2�� �̸����� �����ٸ�
			temp = temp->GetNameRight();//right sub tree ����
	}
	return NULL;//ã�� ���� ������ NULL ��ȯ
}

User *AVL::NameSearch(char *Name, char *Num)//���������� ������带 ��ȯ �ϰ� ������ ���
{
	User *temp = NameRoot;//temp�� NameRoot ��带 �־��ش�.
	User *temp2 = NULL;
	int check =0;
	if(temp==NULL)//����Ǿ��ִ� ������ ���ٸ�
	{
		cout<<"����Ǿ��ִ� �����Ͱ� �����ϴ�"<<endl;
		return NULL;//�ش繮�� ��� ���� ��ȯ
	}

	while( temp !=NULL )//����� ������ ���� �ݺ��Ѵ�
	{
		if( strcmp(temp->GetName(), Name ) == 0 ) //�̸��� ��ġ�Ѵٸ� sub tree ����
		{
			temp2 = temp->GetNameLeft();//���� sub tree
			while( temp2 !=NULL )//����� ������ ���� �ݺ��Ѵ�
			{
				if( (strcmp(temp2->GetName(), Name ) == 0) && (strcmp(temp2->GetNumber(),Num)!=0) )//���������̶��
					return temp2;//�������� ��� ��ȯ
				if( strcmp( temp2->GetName(), Name ) > 0)//temp2�� �̸����� �����ٸ�
					temp2 = temp2->GetNameLeft();//left sub tree ����
				else                             //temp2�� �̸����� �����ٸ�
					temp2 = temp2->GetNameRight();//right sub tree ����
			}
			temp2 = temp->GetNameRight();//������ sub tree
			while( temp2 !=NULL )//����� ������ ���� �ݺ��Ѵ�
			{
				if( (strcmp(temp2->GetName(), Name ) == 0) && (strcmp(temp2->GetNumber(),Num)!=0) )//���������̶��
					return temp2;//�������� ��� ��ȯ
				if( strcmp( temp2->GetName(), Name ) > 0)//temp2�� �̸����� �����ٸ�
					temp2 = temp2->GetNameLeft();//left sub tree ����
				else                            //temp2�� �̸����� �����ٸ�
					temp2 = temp2->GetNameRight();//right sub tree ����
			}
			return NULL;//ã�� ���� ������ NULL ��ȯ
		}
		if( strcmp( temp->GetName(), Name ) > 0)//temp�� �̸����� �����ٸ�
			temp = temp->GetNameLeft();//left sub tree ����
		else                           //temp�� �̸����� �����ٸ�
			temp = temp->GetNameRight();//right sub tree ����
	}
}
#ifdef aa//������ ���� ���� ���Ͽ����ϴ�.
bool AVL::NumberDelete(User *pNode)
{
}

bool AVL::NameDelete(User *pNode)
{

	int found = false;
	User *p=NameRoot;
	User *q = NULL;
	User *r = NULL;
	User *s = NULL;
	User *t = NULL;

	while ( p && (!found) ) 
	{
		if ( strcmp(p->GetName(),pNode->GetName())==0 ) 
			found = true;
		else 
		{
			q = p;
			if ( strcmp(p->GetName(), pNode->GetName()) > 0 )
				p = p->GetNameLeft();
			else
				p = p->GetNameRight();
		}
	}

	if (!p) 
		return;

	if ( p->GetNameLeft() == NULL ) 
		r = p->GetNameRight();
	else 
	{
		if ( p->GetNameRight() == NULL ) 
			r = p->GetNameLeft(); 
		else 
		{ /* node with two children */
			t = p; /* find smallest node in right subtree */
			r = p->GetNameRight();
			s = r->GetNameLeft();
			while (s) 
			{
				t = r; /* parent of replacing node */
				r = s; /* replacing node */
				s = r->GetNameLeft(); 
				/* lf child of replacing node*/
			}
			if (t != p)
			{ /* r is not right child of p */
				t->SetNameLeft(r->GetNameRight());
				r->SetNameRight(p->GetNameRight();
			}
			r->SetNameLeft(p->GetNameLeft());
		}
	}

	if (!q) 
		NameRoot = r; /* root is replaced by r */
	else if (p == q->GetNameLeft() ) 
		q->SetNameLeft(r);
	else 
		q->SetNameRight(r);

	Del.Delete(p);

	while (p != y)
	{
		// Is tree unbalanced?
		if (!(a->bf || !(a->bf+d)) 
		{ // tree still balanced
			a->bf+=d; return;
		}
		if (d == 1) 
		{ // left imbalance
			if (b->bf == 1) 
			{ // rotation type LL
				a->leftChild = b->rightChild;
				b->rightChild = a; a->bf = 0; b->bf = 0;
			} 
			else
			{ // rotation type LR
				c = b->rightChild;
				b->rightChild = c->leftChild;
				a->leftChild = c->rightChild; 
				c->leftChild = b; 
				c->rightChild = a;
				switch (c->bf) 
				{
				case 1:
					a->bf = -1; b->bf = 0;
					break;
				case -1:
					b->bf = 1; a->bf = 0;
					break; 
				case 0:
					b->bf = 0; a->bf = 0;
					break; 
				}
				c->bf = 0; b = c; // b is the new root
			} // end of LR 
		} // end of left imbalance

	}
}
}*/
#endif