#include "Manager.h"

Manager::Manager(void)//������
{
}

Manager::~Manager(void)//�Ҹ���
{
}

bool Manager::LoadFile(char* pFileName)
{
	ifstream fin;//���� ��Ʈ�� ����
	char str[200]={0,};//���پ� �ޱ� ���� �迭 ����
	char r_str[10]={0,};//���� �ڵ带 ���� �迭 ����

	char *temp_fi = NULL;
	char *temp_num=NULL;//���ڿ��� ¥���� ���� char�� �ӽ� ������ ����
	char *temp=NULL;

	NumNode *n=NULL;//��ü ������ ����
	RegionNode *r=NULL;


	fin.open(pFileName,ios::in);//�Է� ���� ���ϸ����� ������ �б� ���� �����ش�
	if( !(fin.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	for(int i=0;i<3;i++)//�޸��忡 �ʿ� ���� ������ �����ش�
		fin.getline(str,200);
	memset(str,NULL,sizeof(str));//�迭�� NULL�� �ʱ�ȭ

	while( !(fin.eof()) )//������ ������ �ݺ��Ѵ�
	{
		RegionNode *N_temp=list.GetHead();
		NumNode *down = NULL;
		int conre=0;
		int connum=0;

		fin.getline(str,200);//���Ͽ��� ������ �޾ƿ´�
		strncpy(r_str, str, sizeof(r_str) ); //r_str ũ�⸸ŭ str�� �ִ� ������ �������ش�

		temp=strtok(r_str,"	-");//���� �ڵ带 ������� strtok
		temp_num=strtok(str,"	/");//��,/ �������� ���ڿ��� ©�� �����Ѵ�
		temp_fi=strtok(NULL,"	/");//��,/ �������� ���ڿ��� ©�� �����Ѵ�

		if( strcmp( temp_fi, "Y" ) == 0 )
		{
			n = new NumNode();//NumNode �޸� �Ҵ�                               
			n->SetFinish(temp_fi);//��ۿ��θ� �����Ѵ�
			n->SetNum(temp_num);//����� ��ȣ�� �����Ѵ�
			informationinsert(n);
			cir.Insert(n);
		}
		else if(strcmp( temp_fi, "N" ) == 0)//����� �Ϸ���� �ʾҴٸ�
		{
			while(N_temp != NULL)//������ ���� �ڵ尡 ���� �ϴ��� Ȯ���Ѵ�
			{
				if(strcmp( temp, N_temp->GetRegionNumber() ) == 0)
				{
					down = N_temp->GetN_Head();
					conre++; // �����ڵ� ī����
				}
				N_temp = N_temp->GetNext();
			}

			while(down != NULL)//������ ����� ��ȣ�� ����Ǿ��ִ��� Ȯ���Ѵ�
			{
				if( strcmp(temp_num, down->GetNum() ) ==0)
				{
					connum++;
					break;
				}
				down = down->GetNext();
			}

			if(connum == 0)//����� ��ȣ�� ����Ǿ����� �ʴٸ�
			{
				if(conre==0)//���� ��尡 ����Ǿ����� �ʴٸ�
				{
					r = new RegionNode();//RegionNode �޸� �Ҵ�
					n = new NumNode();//NumNode �޸� �Ҵ� 
					n->SetFinish(temp_fi);//��ۿ��θ� �����Ѵ�
					n->SetNum(temp_num);//����� ��ȣ�� �����Ѵ�
					r->SetRegionNumber(temp);//�����ڵ带 �����Ѵ�
					if( !(list.pInsert(r)) ) //�����ڵ���� �����ϱ����� 2D pInsert �Լ� ȣ��
						return false;//���� �ߴٸ� false ��ȯ
				}

				else//���� ��尡 ����Ǿ��ִٸ�
				{
					n = new NumNode();//NumNode �޸� �Ҵ� 
					n->SetFinish(temp_fi);//��ۿ��θ� �����Ѵ�
					n->SetNum(temp_num);//����� ��ȣ�� �����Ѵ�
				}
				if( ! (list.cInsert(temp,n)) ) //������ȣ�� �����ϱ����� cInsert �Լ� ȣ��
					return false;//���� �ߴٸ� false ��ȯ
			}
		}
		temp=NULL;//temp�� NULL�� �ʱ�ȭ
		temp_fi=NULL;//temp2�� NULL�� �ʱ�ȭ �Ѵ�
		temp_num=NULL;
		memset(str,NULL,sizeof(str));//�迭���� NULL�� �ʱ�ȭ�Ѵ�
		memset(r_str,NULL,sizeof(r_str));
	}

	fin.close();

	cityinsert();
	informationinsert();
	BST_insert();
	return true;
}

bool Manager::cityinsert()
{
	ifstream f; //���� ��Ʈ�� ����
	char str[100]={0,};//���پ� �ޱ� ���� �迭 ����
	char r_str[20]={0,};//���ڿ��� ¥���� ���� char�� ������ ����
	char *temp=NULL; 
	char *temp2=NULL;

	RegionNode *Rhead = NULL;

	f.open("region_code.txt",ios::in);//���ϸ����� ������ �б� ���� �����ش�
	if( !(f.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	for(int i=0;i<3;i++)//�޸��忡 �ʿ� ���� ������ �����ش�
		f.getline(str,100);
	memset(str,NULL,sizeof(str));

	while( !(f.eof()) )//������ ������ �ݺ��Ѵ�
	{
		Rhead = list.GetHead() ;
		f.getline(str,200);//���Ͽ��� ������ �޾ƿ´�

		strncpy( r_str, str, sizeof(r_str) );//������ �����ϱ����� �迭
		temp=strtok(r_str,"	/");//��,/ �������� ���ڿ��� ©�� �����Ѵ�
		temp2=strtok(str,"	/");//��,/ �������� ���ڿ��� ©�� �����Ѵ�
		temp2=strtok(NULL,"	/");//��,/ �������� ���ڿ��� ©�� �����Ѵ�

		while( Rhead != NULL)
		{
			if(strcmp( temp2, Rhead->GetRegionNumber() ) == 0)//��ġ�ϴ� ����� ��ȣ�� �ִٸ�
			{
				Rhead->SetCity(temp);//���ø� �����Ѵ�
				break;//while ����
			}
			Rhead = Rhead->GetNext();
		}

		temp=NULL;//temp�� NULL�� �ʱ�ȭ
		temp2=NULL;
		memset(str,NULL,sizeof(str)); //�ʱ�ȭ ���ش�
		memset(r_str,NULL,sizeof(r_str));

	}
	f.close();//���� ��Ʈ���� �޾��ش�
	return true;
}

bool Manager::informationinsert()
{
	ifstream f;
	char str[100]={0,};
	char i_str[20]={0,};
	char *temp=NULL;//���ڿ��� ¥���� ���� char�� ������ ����
	char *temp2=NULL;

	RegionNode *head=NULL;
	NumNode *Ntemp=NULL;

	f.open("item_code.txt",ios::in);//�Է� ���� ���ϸ����� ������ �б� ���� �����ش�
	if( !(f.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	for(int i=0;i<3;i++)//�޸��忡 �ʿ� ���� ������ �����ش�
		f.getline(str,100);
	memset(str,NULL,sizeof(str));

	while( !(f.eof()) )//������ ������ �ݺ��Ѵ�
	{
		f.getline(str,200);//���Ͽ��� ������ �޾ƿ´�

		strncpy( i_str, str, sizeof(i_str) );

		temp=strtok(i_str,"	/");//��,/ �������� ���ڿ��� ©�� �����Ѵ�
		temp2=strtok(str,"	/");//��,/ �������� ���ڿ��� ©�� �����Ѵ�
		temp2=strtok(NULL,"	/");//��,/ �������� ���ڿ��� ©�� �����Ѵ�
		//temp�� ǰ���̸��� temp2�� ��ǰ����

		head=list.GetHead();
		while(head !=NULL)
		{
			char cur[2]={0,};
			Ntemp=head->GetN_Head();
			while(Ntemp!=NULL)
			{
				cur[0]=Ntemp->GetNum()[10];
				if( strcmp(temp2, cur) == 0 )
				{
					Ntemp->SetItem(temp);//��ǰ����

					if(Ntemp->GetNum()[11]=='1')//��� ����
						Ntemp->SetTreat("Y");
					else if(Ntemp->GetNum()[11]=='0')
						Ntemp->SetTreat("N");
				}
				Ntemp=Ntemp->GetNext();//���� ���������� ����
			}

			head=head->GetNext();//���� �����ڵ� ��� ����
		}
		temp=NULL;//temp�� NULL�� �ʱ�ȭ
		temp2=NULL;
		memset(str,NULL,sizeof(str));
		memset(i_str,NULL,sizeof(i_str));
	}
	f.close();
	return true;
}

bool Manager::BST_insert()
{
	RegionNode *temp=list.GetHead();
	while(temp !=NULL)
	{
		Root.BSTInsert(temp);
		temp=temp->GetNext();
	}
	return true;
}

bool Manager::FIND(char *Fnum)
{
	RegionNode *FindNode = NULL;// ã�����ϴ� ���� ��ȣ�� ��带 �����ϱ����� ������
	NumNode *Ctemp=NULL;//�ڽ� ������  �����ϱ� ���� ������
	int con=0;

	ofstream ff("find_parcel.txt",ios_base::app);//find_parcel.txt��� ���� ��ü ff����
	//��������� �����ϵ��� ����
	if( !(ff.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	FindNode = Root.Serch(Fnum);//BST�� �̿��Ͽ� ã���� �ϴ� ������ȣ�� ��带 ã�´�
	if(FindNode == NULL)//ã�� ��尡 ���ٸ�
	{
		ifstream f;//region_code.txt��� ���� ��ü���� f
		char str[100]={0,}; //�޸����� ������ �ޱ����� str ����
		char r_str[20]={0,};
		char *temp=NULL; //�ʿ��� ������ ©�� �����ϱ����� char ������
		char *temp2=NULL;
		f.open("region_code.txt",ios::in);//������ �б� ���� �����ش�

		if( !(f.is_open()) )//���� ������ �����ߴٸ�
			return false;//������ ��ȯ�Ѵ�

		for(int i=0;i<3;i++)//�޸��忡 �ʿ� ���� ������ �����ش�
			f.getline(str,100);
		memset(str,NULL,sizeof(str));

		while( !(f.eof()) )//������ ������ �ݺ��Ѵ�
		{
			f.getline(str,200);//���Ͽ��� ������ �޾ƿ´�

			strncpy( r_str, str, sizeof(r_str) );//������ �����ϱ����� �迭
			temp=strtok(r_str,"	/");//��,/ �������� ���ڿ��� ©�� ������ �����Ѵ�
			temp2=strtok(str,"	/");//��,/ �������� ���ڿ��� ©�� �����Ѵ�
			temp2=strtok(NULL,"	/");//��,/ �������� ���ڿ��� ©�� ������ȣ�� �����Ѵ�
			if( strcmp(temp2, Fnum) == 0)//ã���� �ϴ� ��ȣ�� ���ٸ�
				break;
			temp=NULL;//temp�� NULL�� �ʱ�ȭ
			temp2=NULL;
			memset(str,NULL,sizeof(str)); //�迭�� �ʱ�ȭ ���ش�
			memset(r_str,NULL,sizeof(r_str));
		}
		ff<<endl<<temp<<"�� ��۵Ǵ� ��ǰ�� �����ϴ�."<<endl;
		f.close();//region_code.txt�� �ݾ��ش�.
	}

	else//ã�� ��尡 �ִٸ�
	{
		for(int k=0;k<50;k++)//���� ���
			ff<<"==";
		ff<<endl;
		ff<<"�������	|	��۹�ǰ	|  �������	|	��ۿ���	|	������ȣ	|"<<endl;
		for(int k=0;k<50;k++)
			ff<<"==";
		ff<<endl;//����

		Ctemp = FindNode->GetN_Head();//�ڽ� ����� ����� �����Ѵ�
		while( Ctemp !=NULL )//�ڽĳ���� ������ �������� while ��
		{
			if(Ctemp->GetNext() == NULL)//������ ������ ������ٶ� ����Ű�� �����ش�
			{ //���� �������� ������ش�.
				ff<<FindNode->GetCity()<<"		/	"<<Ctemp->GetItem()<<"	/	"<<Ctemp->GetTreat()<<"		/	"<<Ctemp->GetFinish()<<"		/	";
				ff<<Ctemp->GetNum()<<"	/	";
			}
			else//������ ������ �ƴ϶�� ����Ű�� �־��ش�
			{
				ff<<FindNode->GetCity()<<"		/	"<<Ctemp->GetItem()<<"	/	"<<Ctemp->GetTreat()<<"		/	"<<Ctemp->GetFinish()<<"		/	";
				ff<<Ctemp->GetNum()<<"	/	"<<endl;
			}
			Ctemp = Ctemp->GetNext();//���� �ڽĳ�带 ����Ű�� �Ѵ�
		}
	}
	ff.close();//find_parcel.txt ������ �ݾ��ش�.
	return true;//�� ��ȯ

}

bool Manager::SAVE(char* pFileName)
{
	RegionNode *current = Root.GetRoot(); //BST�� root�� �����Ѵ�
	NumNode *temp=NULL;//NumNode ������ ������ �����Ѵ�
	NumNode *Cirhead = cir.GetCirHead();//���� ����Ʈ�� head�� �����Ѵ�

	ofstream ff(pFileName,ios::out);//�Է� ���� ���ϸ����� ��üff ����

	if( !(ff.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	if( (current ==NULL) && (Cirhead==NULL) )//BST�� ������ ����Ǿ��ִ� ������ ���ٸ�
	{
		cout<<"�����ϰ��� �ϴ� ������ �����ϴ�."<<endl;
		return false;//�������� ��°� false ��ȯ
	}
	for(int k=0;k<27;k++)
		ff<<"==";
	ff<<endl;
	ff<<"|	������ȣ	|	��ۿ���	|"<<endl;
	for(int k=0;k<27;k++)
		ff<<"==";
	ff<<endl;//�ش� ������ ���Ͽ� ������ش�.

	while(current != NULL) //BST ������ ������ֱ� ���� while��
	{
		temp = current->GetN_Head();//�ڽĳ���� head�� �����Ѵ�
		while(temp != NULL)//�ڽ� ��� ������ �ݺ��Ѵ�
		{
			if( (Que.IsEmpty() ) && (Cirhead==NULL) )//������ �����̶��
			{
				ff<<"	"<<temp->GetNum()<<"	/	"<<temp->GetFinish()<<"	/	";
			}//enter�� ����� �� �������� ������ش�
			else//������ ������ �ƴ϶��
			{
				ff<<"	"<<temp->GetNum()<<"	/	"<<temp->GetFinish()<<"	/	"<<endl;
			}//�ش������� ������ش�
			temp=temp->GetNext();//���� �ڽĳ�带 ����Ű�� �Ѵ�
		}
		//Lever-order ������� que�� �����س��� ���� ���ǹ�
		if(current->GetLeftNext() !=NULL)
			Que.Push( current->GetLeftNext() );
		if( current->GetRightNext() !=NULL )
			Que.Push( current->GetRightNext() );
		if( Que.IsEmpty())//que�� ����ִٸ� 
			break;//while�� ����
		current = Que.Pop();// current�� que���� pop ���ش�
	}
	if(Cirhead !=NULL )
	{
		NumNode *pCur = Cirhead->GetCirNext();//���� ����Ʈ�� ������ش�
		while( 1 )//���ѷ���
		{
			if( pCur->GetCirNext() == Cirhead )//��������Ʈ�� �������̶��
			{
				ff<<"	"<<pCur->GetNum()<<"	/	"<<pCur->GetFinish()<<"	/";
				break;//�ش�������� ���ѷ��� ����
			}
			else
			{
				ff<<"	"<<pCur->GetNum()<<"	/	"<<pCur->GetFinish()<<"	/"<<endl;
			}//�ش����� ���
			pCur = pCur->GetCirNext();//���� ����Ʈ�� ����Ű�� �Ѵ�.
		}
	}
	return true;
}

bool Manager::PRINT()
{
	RegionNode *current = Root.GetRoot();//BST�� root�� �����Ѵ�
	RegionNode *del = Root.GetRoot();
	NumNode *temp=NULL;//�ӽ� ������ ����
	NumNode *Cirhead = cir.GetCirHead();//���� ����Ʈ�� head�� �����Ѵ�

	ofstream ff("print_parcel.txt",ios_base::app);//print_parcel.txt��� ���� ��ü ff����
	if( !(ff.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	if( (current ==NULL) && (Cirhead==NULL) )//BST�� ������ ����Ǿ��ִ� ������ ���ٸ�
	{
		cout<<"�����ϰ��� �ϴ� ������ �����ϴ�."<<endl;
		return false;//�������� ��°� false ��ȯ
	}

	for(int k=0;k<45;k++)
		ff<<"==";
	ff<<endl;
	ff<<"	�������		|	��۹�ǰ	|  �������		|	��ۿ���	|	������ȣ	|"<<endl;
	for(int k=0;k<45;k++)
		ff<<"==";
	ff<<endl;//���Ͽ� �ش� ������ ������ش�

	if(! ( Que.IsEmpty()) )//Que�� �����ִ� ��尡 �ִٸ�
	{
		while(1)//que�� ����ش�
		{
			del=Que.Pop();//pop�� ��带 �������ش�.
			delete del;
			if( Que.IsEmpty() )//que�� ��ٸ� 
				break;//���ѷ��� 
		}
	}
	temp=NULL;//temp�� NULL�� �ʱ�ȭ
	inorder_print(current);//inorder_print�Լ��� ȣ���ؼ� que�� �����Ѵ�

	while(1)//que�� �������� �ݺ��ϱ����� ���ѷ���
	{
		if( Que.IsEmpty() )//que�� ����Ǿ��ִ� ������ ���ٸ� 
			break;//���ѷ��� ����
		current=Que.Pop();//current�� pop�� ����� �ִ´�
		temp=current->GetN_Head();//temp���� �ڽĳ���� ����� �־��ش�.
		while(temp != NULL)//�ڽĳ�� ������ �ݺ��Ѵ�
		{
			ff<<current->GetCity()<<"	/	"<<temp->GetItem()<<"	/	"<<temp->GetTreat()<<"		/	"<<temp->GetFinish()<<"		/	";
			ff<<temp->GetNum()<<"	/	"<<endl;//���������� ����Ѵ�
			temp = temp->GetNext();//�����ڽĳ�带 ����Ų��.
		}
	}
	if(Cirhead !=NULL)
	{
		NumNode *pCur = Cirhead->GetCirNext();//���� ����Ʈ�� ������ش�
		if(pCur != NULL) //���� ����Ʈ�� ����Ǿ��ִ� ������ �ִٸ�
		{
			while( 1 )//���ѷ���
			{
				ifstream f; //���� ��Ʈ�� ����
				char str[100]={0,};//���پ� �ޱ� ���� �迭 ����
				char r_str[20]={0,};//���ڿ��� ¥���� ���� char�� ������ ����
				char *city=NULL; 
				char *temp2=NULL;

				f.open("region_code.txt",ios::in);//���ϸ����� ������ �б� ���� �����ش�
				if( !(f.is_open()) )//���� ������ �����ߴٸ�
					return false;//������ ��ȯ�Ѵ�

				for(int i=0;i<3;i++)//�޸��忡 �ʿ� ���� ������ �����ش�
					f.getline(str,100);
				memset(str,NULL,sizeof(str));

				while( !(f.eof()) )//������ ������ �ݺ��Ѵ�
				{
					f.getline(str,200);//���Ͽ��� ������ �޾ƿ´�

					strncpy( r_str, str, sizeof(r_str) );//������ �����ϱ����� �迭
					city=strtok(r_str,"	/");//��,/ �������� ���ڿ��� ©�� �����Ѵ�
					temp2=strtok(str,"	/");//��,/ �������� ���ڿ��� ©�� �����Ѵ�
					temp2=strtok(NULL,"	/");//��,/ �������� ���ڿ��� ©�� �����Ѵ�
					if( strncmp(pCur->GetNum(), temp2, 3) == 0)
					{
						break;
					}

					city=NULL;//temp�� NULL�� �ʱ�ȭ
					temp2=NULL;
					memset(str,NULL,sizeof(str)); //�ʱ�ȭ ���ش�
					memset(r_str,NULL,sizeof(r_str));
				}
				f.close();//���� ��Ʈ���� �޾��ش�

				if( pCur->GetCirNext() == Cirhead )//��������Ʈ�� �������̶��
				{
					ff<<city<<"	/	"<<pCur->GetItem()<<"	/	"<<pCur->GetTreat()<<"		/	"<<pCur->GetFinish()<<"		/	";
					ff<<pCur->GetNum()<<"	/	"<<endl;//���������� ����Ѵ�
					break;//�ش�������� ���ѷ��� ����
				}
				else
				{
					ff<<city<<"	/	"<<pCur->GetItem()<<"	/	"<<pCur->GetTreat()<<"		/	"<<pCur->GetFinish()<<"		/	";
					ff<<pCur->GetNum()<<"	/	";//���������� ����Ѵ�
				}//�ش����� ���
				pCur = pCur->GetCirNext();//���� ����Ʈ�� ����Ű�� �Ѵ�.
			}
		}
	}

	ff.close();
	return true;//�� ��ȯ
}

void Manager::inorder_print(RegionNode *current)//inorder�� �����ϱ� ���� �Լ�
{
	if(current == NULL)
		return ;
	inorder_print( current->GetLeftNext() ); //���� ���� subtree�� �����Ͽ� �ű⼭ ���� queue�� �־��ش�
	Que.Push(current);
	inorder_print( current->GetRightNext() );//������ subtree�� �����ڵ带 �����Ѵ�
}

bool Manager::UPDATE(char* pFileName)
{
	ifstream fin;//���� ��Ʈ�� ����
	char str[200]={0,};//���پ� �ޱ� ���� �迭 ����
	char tempstr[60]={0,};//���� �ڵ带 ���� �迭 ����

	char *before_num=NULL;
	char *before_re=NULL;
	char *after_num=NULL;
	char *after_re=NULL;

	char *temp=NULL;//���ڿ��� ¥���� ���� char�� �ӽ� ������ ����
	char *temp2=NULL;

	NumNode *n=NULL;//��ü ������ ����
	RegionNode *r=NULL;

	fin.open(pFileName,ios::in);//�Է� ���� ���ϸ����� ������ �б� ���� �����ش�
	if( !(fin.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	for(int i=0;i<3;i++)//�޸��忡 �ʿ� ���� ������ �����ش�
		fin.getline(str,200);
	memset(str,NULL,sizeof(str));//�迭�� NULL�� �ʱ�ȭ

	while( !(fin.eof()) )//������ ������ �ݺ��Ѵ�
	{
		RegionNode *N_temp=list.GetHead();
		RegionNode *findNode=NULL;
		NumNode *cNode=NULL;;
		int conre=0;
		int connum=0;

		fin.getline(str,200);//���Ͽ��� ������ �޾ƿ´�

		strncpy(tempstr,str, sizeof(tempstr) ); //r_str ũ�⸸ŭ str�� �ִ� ������ �������ش�

		before_re = strtok(tempstr,"	-");
		after_re = strtok(NULL,"	-");
		after_re = strtok(NULL,"	-");
		after_re = strtok(NULL,"	-");
		after_re = strtok(NULL,"	-");

		before_num = strtok(str,"	/");
		after_num = strtok(NULL,"	/");
		temp = strtok(NULL,"	/");

		if( strcmp(temp,"Y") == 0)
		{
			int re_num=0;
			findNode=Root.Serch(before_re);
			if(findNode != NULL)
			{
				cNode=findNode->GetN_Head();
				while(cNode !=NULL)
				{
					re_num++;
					cNode = cNode->GetNext();
				}
			}
			if(re_num>1)
			{
				list.Delete(after_num,after_re);
				n = new NumNode();//NumNode �޸� �Ҵ�
				n->SetNum(after_num);
				n->SetFinish(temp);
				cir.Insert(n);
			}
			else
			{
				list.Delete(after_num,after_re);
				list.Pdelete(findNode);
				Root.Delete(findNode);
				n = new NumNode();//NumNode �޸� �Ҵ�
				n->SetNum(after_num);
				n->SetFinish(temp);
				cir.Insert(n);
			}
		}

		else if(strcmp(temp,"N") == 0) //��� no
		{
			if( strcmp(before_num, after_num) == 0) //�յ� ����� ������
			{
				n = new NumNode();//NumNode �޸� �Ҵ�
				r = new RegionNode();//RegionNode �޸� �Ҵ�
				r->SetRegionNumber(after_re);
				n->SetNum(after_num);
				n->SetFinish(temp);
				list.pInsert(r);
				list.cInsert(after_re,n);
			}
			else
			{
				int re_num=0;
				findNode=Root.Serch(before_re);
				if(findNode != NULL)
				{
					cNode=findNode->GetN_Head();
					while(cNode !=NULL)
					{
						re_num++;
						cNode = cNode->GetNext();
					}
				}
				if(re_num>1)
				{
					list.Delete(before_num,before_re);
					n = new NumNode();//NumNode �޸� �Ҵ�
					r = new RegionNode();//RegionNode �޸� �Ҵ�
					r->SetRegionNumber(after_re);
					n->SetNum(after_num);
					n->SetFinish(temp);
					list.pInsert(r);
					list.cInsert(after_re,n);
				}
				else
				{
					list.Delete(before_num,before_re);
					list.Pdelete(findNode);
					Root.Delete(findNode);
					n = new NumNode();//NumNode �޸� �Ҵ�
					r = new RegionNode();//RegionNode �޸� �Ҵ�
					r->SetRegionNumber(after_re);
					n->SetNum(after_num);
					n->SetFinish(temp);
					list.pInsert(r);
					list.cInsert(after_re,n);
				}
			}
			cityinsert();
			informationinsert();
			BST_insert();
		}
		before_num=NULL;
		before_re=NULL;
		after_num=NULL;
		after_re=NULL;
		temp=NULL;//temp2�� NULL�� �ʱ�ȭ �Ѵ�
		memset(str,NULL,sizeof(str));//�迭���� NULL�� �ʱ�ȭ�Ѵ�
		memset(tempstr,NULL,sizeof(tempstr));
	}
	fin.close();
	return true;

}

bool Manager::EXIT()
{
	//2D ����Ʈ�� ������ �ش�
	RegionNode *Phead = list.GetHead();
	RegionNode *parCur = NULL;
	NumNode *Chead = Phead->GetN_Head();
	NumNode *chilCur = NULL;
	RegionNode *temp=NULL;

	while(Phead !=NULL )//�θ��带 �ݺ��Ѵ�
	{
		NumNode *Chead = Phead->GetN_Head();//�ڽĳ���� head ���� �����Ѵ�
		while(Chead !=NULL )//�ڽĳ�带 �ݺ��Ѵ�
		{
			chilCur = Chead;//�ڽĳ���� head�� �ٲ��ְ�
			Chead = Chead->GetNext();
			delete chilCur;//chilCur�� �������ش�
		}
		parCur = Phead;//�θ����� head�� �ٲ��ش�
		Phead = Phead->GetNext();
		delete parCur;//parCur�� �������ش�
	}

	if(! ( Que.IsEmpty()) )//Que�� �����ִ� ��尡 �ִٸ�
	{
		while(1)//que�� ����ش�
		{
			temp=Que.Pop();//pop�� ��带 �������ش�.
			delete temp;
			if( Que.IsEmpty() )//que�� ��ٸ� 
				break;//���ѷ��� 
		}
	}

	NumNode* Cirhead = cir.GetCirHead();
	if(Cirhead !=NULL)
	{
		NumNode* pCur= Cirhead->GetCirNext();//��������Ʈ�� �������ش�
		while(1)//��������Ʈ�� �׳� ����Ʈ�� �ٲ��ش�.
		{
			if(pCur->GetCirNext() == Cirhead )//��������带 ã�´�
			{
				pCur->SetCirNext(NULL);//����������� next �ڸ��� NULL�� �־��ش�
				break;//���ѷ��� ����
			}
			pCur = pCur->GetCirNext();
		}
		pCur = Cirhead ;//�ٽ� head�� �־��ش�
		while(Cirhead!=NULL) //�Ҵ��� ������ �������ش�
		{
			pCur=Cirhead;
			Cirhead = Cirhead->GetCirNext(); 
			delete pCur; 
		}
	}
	return true;//�� ��ȯ
}

bool Manager::informationinsert(NumNode *pNode) //����� ��ȣ�� �޾Ƽ� ������ �����ϴ� informationinsert �Լ� �����ε�
{
	ifstream f;
	char str[100]={0,};
	char i_str[20]={0,};
	char *temp=NULL;//���ڿ��� ¥���� ���� char�� ������ ����
	char *temp2=NULL;

	f.open("item_code.txt",ios::in);//�Է� ���� ���ϸ����� ������ �б� ���� �����ش�
	if( !(f.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	for(int i=0;i<3;i++)//�޸��忡 �ʿ� ���� ������ �����ش�
		f.getline(str,100);
	memset(str,NULL,sizeof(str));

	while( !(f.eof()) )//������ ������ �ݺ��Ѵ�
	{
		f.getline(str,200);//���Ͽ��� ������ �޾ƿ´�

		strncpy( i_str, str, sizeof(i_str) );

		temp=strtok(i_str,"	/");//��,/ �������� ���ڿ��� ©�� �����Ѵ�
		temp2=strtok(str,"	/");//��,/ �������� ���ڿ��� ©�� �����Ѵ�
		temp2=strtok(NULL,"	/");//��,/ �������� ���ڿ��� ©�� �����Ѵ�
		//temp�� ǰ���̸��� temp2�� ��ǰ����

		char cur[2]={0,};

		cur[0]=pNode->GetNum()[10];
		if( strcmp(temp2, cur) == 0 )
		{
			pNode->SetItem(temp);//��ǰ����

			if(pNode->GetNum()[11]=='1')//��� ����
				pNode->SetTreat("Y");
			else if(pNode->GetNum()[11]=='0')
				pNode->SetTreat("N");
		}


		temp=NULL;//temp�� NULL�� �ʱ�ȭ
		temp2=NULL;
		memset(str,NULL,sizeof(str));
		memset(i_str,NULL,sizeof(i_str));
	}
	f.close();
	return true;
}
