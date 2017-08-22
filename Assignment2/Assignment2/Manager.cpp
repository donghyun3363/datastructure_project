#include "Manager.h"
#include <iostream>
#include <fstream>//������� ����

using namespace std;//�̸� ������ std ������ ���

Manager::Manager(void)//������
{
}

Manager::~Manager(void)//�Ҹ���
{
}

bool Manager::Load_User(char *file)//���� ������ load�ϱ� ���� �Լ�
{
	EXIT();//�ʱ�ȭ
	avl.~AVL();

	ifstream fin;//���� ��Ʈ�� ����
	User *user=NULL;
	char str[200];//���پ� �ޱ� ���� �迭 ����
	memset(str,NULL,sizeof(str));//�迭 �ʱ�ȭ

	char *temp1 = NULL;
	char *temp2 = NULL;//���ڿ��� ¥���� ���� char�� �ӽ� ������ ����

	fin.open(file,ios::in);//�Է� ���� ���ϸ����� ������ �б� ���� �����ش�
	if( !(fin.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	for(int i=0;i<3;i++)//�޸��忡 �ʿ� ���� ������ �����ش�
		fin.getline(str,sizeof(str));
	memset(str,NULL,sizeof(str));//�迭�� NULL�� �ʱ�ȭ

	while( !(fin.eof()) )//������ ������ �ݺ��Ѵ�
	{
		fin.getline(str,sizeof(str));//���Ͽ��� ������ �޾ƿ´�

		temp1 = strtok(str,"	 /");//�й��� ¥����
		temp2 = strtok(NULL,"	 /");//�̸��� ¥����

		User *check = avl.NumSearch(temp1);//�ش� �й��� ������ �ִ� ������ �ִ��� �����Ѵ�
		if(check == NULL)//����� ������ �ƴ϶��
		{
			user = new User();//User ��� �޸� �Ҵ�
			user->SetNumber(temp1);//User Node�� �й��� �����Ѵ�
			user->SetName(temp2);//User Node�� �̸��� �����Ѵ�
			if( !(avl.NameAVL(user)) )//Name AVL insert ȣ��
			{
				cout<<"AVL insert�� �����Ͽ����ϴ�."<<endl;//�����ߴٸ� ���� ���
				return false;//������ȯ
			}
			if( !(avl.NumberAVL(user)) )//Number AVL insert ȣ��
			{
				cout<<"AVL insert�� �����Ͽ����ϴ�."<<endl;//�����ߴٸ� ���� ���
				return false;//���� ��ȯ
			}
		}
		else//�̹� ����� �������
		{
			cout<<"�̹� �����ϴ� ������ ���� �Դϴ�."<<endl;//�ش� ���� ���
		}
		check = NULL;
		temp1=NULL;//temp�� NULL�� �ʱ�ȭ
		temp2=NULL;//temp2�� NULL�� �ʱ�ȭ �Ѵ�
		memset(str,NULL,sizeof(str));//�迭���� NULL�� �ʱ�ȭ�Ѵ�
	}

	fin.close();//������ �ݾ��ش�
	return true;//����ȯ
}

bool Manager::Load_Friend(char *file)//ģ�� ������ load�ϱ� ���� �Լ�
{
	ifstream fin;//���� ��Ʈ�� ����
	char str[200];//���پ� �ޱ� ���� �迭 ����
	memset(str,NULL,sizeof(str));//�迭 �ʱ�ȭ

	User *MeNode = NULL;//�ӽ� ������ ����
	User *FriNode = NULL;

	char *Me = NULL;
	char *Fri = NULL;//���ڿ��� ¥���� ���� char�� �ӽ� ������ ����

	fin.open(file,ios::in);//�Է� ���� ���ϸ����� ������ �б� ���� �����ش�
	if( !(fin.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	for(int i=0;i<3;i++)//�޸��忡 �ʿ� ���� ������ �����ش�
		fin.getline(str, sizeof(str));
	memset(str, NULL, sizeof(str));//�迭�� NULL�� �ʱ�ȭ

	while( !(fin.eof()) )//������ ������ �ݺ��Ѵ�
	{
		fin.getline(str,sizeof(str));//���Ͽ��� ������ �޾ƿ´�

		Me = strtok(str,"	 /");//���� �й��� �����Ѵ�
		Fri = strtok(NULL,"	 /");//ģ���� �й��� �����Ѵ�

		MeNode = avl.NumSearch(Me);
		FriNode = avl.NumSearch(Fri);//�ش��ϴ� �й��� ��带 ã���ش�

		if( (MeNode == NULL) || (FriNode == NULL) )//ã�� ��尡 ���ٸ� �ش繮�� ����� ���� ��ȯ
		{
			cout<<"�ش��ϴ� �й��� ����ڰ� �����ϴ�."<<endl;
			return false;
		}
		else//ã�� ��尡 �ִٸ� 2DList insert �Լ� ȣ���Ѵ�.
		{
			if( List.SearchFri(MeNode, FriNode) )//ģ���� �����Ѵٸ�
			{
				cout<<"�̹� �����ϴ� ģ�� �Դϴ�."<<endl;
			}
			else
			{
				if( !(List.Insert(MeNode, FriNode)) )//insert�� �����Ͽ��ٸ�
				{
					cout<<"ģ�� ���ῡ ���� �Ͽ����ϴ�."<<endl;//�ش繮�� ��� ���� ��ȯ
					return false;
				}
			}
		}

		MeNode = NULL;
		FriNode = NULL;
		Me=NULL;
		Fri=NULL;//�ӽ� �������� NULL�� �ʱ�ȭ �����ش�
		memset(str,NULL,sizeof(str));//�迭���� NULL�� �ʱ�ȭ�Ѵ�
	}

	fin.close();
	return true;//������ �ݾ��ְ� true ��ȯ
}

bool Manager::Load_Memo(char *file)//�޸� ������ load�ϱ� ���� �Լ�
{
	ifstream fin;//���� ��Ʈ�� ����
	char str[400];//���پ� �ޱ� ���� �迭 ����
	memset(str,NULL,sizeof(str));

	User *MeNode = NULL;
	MemoNode *mNode = NULL;//�޸�� ����ڸ� ���� �����Ͱ�ü ����

	char *me = NULL;
	char *time = NULL;
	char *memo = NULL;//���ڿ��� ¥���� ���� char�� �ӽ� ������ ����

	fin.open(file,ios::in);//�Է� ���� ���ϸ����� ������ �б� ���� �����ش�
	if( !(fin.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	for(int i=0;i<3;i++)//�޸��忡 �ʿ� ���� ������ �����ش�
		fin.getline(str,sizeof(str));
	memset(str,NULL,sizeof(str));//�迭�� NULL�� �ʱ�ȭ

	while( !(fin.eof()) )//������ ������ �ݺ��Ѵ�
	{
		fin.getline(str,sizeof(str));//���Ͽ��� ������ �޾ƿ´�

		me = strtok(str,"	/");//���� �й��� �����Ѵ�
		time = strtok(NULL,"	/");//�ð����� �����Ѵ�
		memo = strtok(NULL,"	/");//�޸� �����Ѵ�
		MeNode = avl.NumSearch(me);

		if(MeNode == NULL)//ã�� ��尡 ���ٸ� �ش繮�� ����� ���� ��ȯ
		{
			cout<<"�ش��ϴ� �й��� ����ڰ� �����ϴ�."<<endl;
			return false;
		}
		else//ã�� ��尡 �ִٸ� �޸��� ������ ���� �ϰ� �޸� ���� ��带 ȣ���Ѵ�
		{
			if((time!=NULL) && (memo !=NULL))//�޸� ����� �ð��� ���� �Ѵٸ�
			{
				if( !(Line.MemoSearch(MeNode, time)) )//���� �޸� ���� �����ʴ´ٸ�
				{
					mNode = new MemoNode();//memo��� �����Ѵ�

					strcpy(memo,ALARM(MeNode, memo, time));//ALARM �Լ� ȣ���� ���� �޸𳻿��� �������ش�
					mNode->SetTime(time);
					mNode->SetWrite(memo);//�޸� ��忡 ������ �����Ѵ�
					mNode->SetWho(MeNode->GetName());

					if( !(Line.MemoInsert(MeNode, mNode)) )//insert�� �����Ͽ��ٸ�
					{
						cout<<"�޸� ���ῡ ���� �Ͽ����ϴ�."<<endl;//�ش繮�� ��� ���� ��ȯ
						return false;
					}
				}
			}
		}

		MeNode = NULL;
		me = NULL;
		time = NULL;
		memo = NULL;//�ӽ� �������� NULL�� �ʱ�ȭ �����ش�
		memset(str,NULL,sizeof(str));//�迭���� NULL�� �ʱ�ȭ�Ѵ�
	}

	fin.close();
	return true;//������ �ݾ��ְ� true ��ȯ
}

char *Manager::ALARM(User *mNode, char *before, char *time)//�˶� �Լ�
{
	char str[200];
	memset(str,NULL,sizeof(str) );//�޸������� ���� �迭                           
	strncpy( str, before, sizeof(str) );
	User *FriNode = NULL;
	Linked *del = mNode->GetFri();//Ż�𿩺θ� �ľ��ϱ� ���� �ӽ� ������ ����

	if(del != NULL)//ģ���� �����Ѵٸ�
	{
		while(del !=NULL)//Ż�𿩺� flag�� 1�� ģ���� ã�Ƽ� �����ִ� �ڵ��̴�
		{
			if( ((del->GetDown())->GetCheckDelete()) == 1 )
			{
				if( !(List.DeleteFrt(mNode, del->GetDown()) ) )//ģ�� ������ ���� �Ͽ��ٸ�
					cout<<"ģ�� ������ �����Ͽ����ϴ�."<<endl;//���� ���
			}
			del = del->GetNext();
		}
	}

	char FriName1[15];
	memset(FriName1, NULL ,sizeof(FriName1));
	char FriName2[15];
	memset(FriName2, NULL ,sizeof(FriName2));
	char FriName3[15];
	memset(FriName3, NULL ,sizeof(FriName3));
	char FriName4[15];
	memset(FriName4, NULL ,sizeof(FriName4));//�˶��� �ؾߵǴ� ģ������ �̸��� �����ϱ� ���� �迭 ����

	int i=0;
	int check = 0;//�������� check ����
	int Number = 0;//ģ�� ��� check ����
	while(str[i] !=NULL )//�޸𳻿��� �˻��Ѵ�
	{
		if( (str[i]=='@') && (str[i+7]==';') && (Number==0) )//�޸��� ������ ģ�� ���°� �±��� ģ���� ���ٸ�
		{
			check = 0;
			FriName1[0]=str[i+1];
			FriName1[1]=str[i+2];
			FriName1[2]=str[i+3];
			FriName1[3]=str[i+4];
			FriName1[4]=str[i+5];
			FriName1[5]=str[i+6];//�޸� ����Ǿ��ִ� ����̸��� ģ�� �迭�� �ϴ� �����Ѵ�

			if(avl.CheckSameName(FriName1))//���������� �ִ��� üũ�Ѵ�
			{
				check = List.SearchFri(mNode, FriName1);//���������� ���� �Ѵٸ� 
				//���Լ��� ȣ���ϸ� �������� ģ�� �θ��� ���� ����ģ������ Ȯ���Ѵ�
			}
			else//���������� ���ٸ�
			{
				FriNode = avl.NameSearch(FriName1);//�ش��̸��� ������ ��带 ã�´�
				if(FriNode != NULL)//���� ��尡 �����Ѵٸ�
				{
					if( List.SearchFri(FriNode, mNode) )//����ģ������ Ȯ���Ѵ�
						check =1;
				}
			}

			if(check == 1 || check == 2)//���� ģ���� ģ���� �����Ѵٸ�
			{
				if(check==2)//����ģ���� ģ���� �������� �Ѵٶ��
				{
					FriName1[6]=' ';
					FriName1[7]=str[i+1];
					FriName1[8]=str[i+2];
					FriName1[9]=str[i+3];
					FriName1[10]=str[i+4];
					FriName1[11]=str[i+5];
					FriName1[12]=str[i+6];//ģ�� �̸��� �ѹ��� �����ش�.
				}
				int j=0;
				str[i]=FriName1[0];
				str[i+1]=FriName1[1];
				str[i+2]=FriName1[2];
				str[i+3]=FriName1[3];
				str[i+4]=FriName1[4];
				str[i+5]=FriName1[5];// @ , ; �̺κ��� ������ �̸��� �ٽ� �����Ѵ�
				while(str[j+8] !=NULL)//�޸� �迭�� �ٽ� �������ش�
				{
					str[i+6+j]=str[i+8+j];
					j++;
				}
				str[i+6+j]=NULL;//NULL�� �־��ش�
				i=i+6;//i�� �� �������� �ʱ�ȭ���ش�
				FriNode = NULL;//ģ�� ��� �ʱ�ȭ
				Number++;//�±� ��� ����
			}
			else//ģ���� �ƴ϶��
			{
				i++;
				memset(FriName1, NULL, sizeof(FriName1) );//ģ���� �ƴϱ⶧���� �迭�ʱ�ȭ
				continue;
			}
		}

		else if( (str[i]=='@') && (str[i+7]==';') && (Number==1) )//�޸��� ������ ģ�� ���°� �±��� ģ���� 1���ִٸ�
		{
			check =0;
			FriName2[0]=str[i+1];
			FriName2[1]=str[i+2];
			FriName2[2]=str[i+3];
			FriName2[3]=str[i+4];
			FriName2[4]=str[i+5];
			FriName2[5]=str[i+6];//�޸� ����Ǿ��ִ� ����̸��� ģ�� �迭�� �ϴ� �����Ѵ�

			if(avl.CheckSameName(FriName2))//���������� �ִ��� üũ�Ѵ�
			{
				check = List.SearchFri(mNode, FriName2);//���������� ���� �Ѵٸ� 
				//���Լ��� ȣ���ϸ� �������� ģ�� �θ��� ���� ����ģ������ Ȯ���Ѵ�
			}
			else//���������� ���ٸ�
			{
				FriNode = avl.NameSearch(FriName2);//�ش��̸��� ������ ��带 ã�´�
				if(FriNode != NULL)//���� ��尡 �����Ѵٸ�
				{
					if( List.SearchFri(FriNode, mNode) )//����ģ������ Ȯ���Ѵ�
						check =1;
				}
			}

			if(check == 1 || check == 2)//ģ���������Ѵٸ�
			{
				if(check==2)//���������� �����Ѵٸ�
				{
					FriName2[6]=' ';
					FriName2[7]=str[i+1];
					FriName2[8]=str[i+2];
					FriName2[9]=str[i+3];
					FriName2[10]=str[i+4];
					FriName2[11]=str[i+5];
					FriName2[12]=str[i+6];//ģ�� �̸��� �ѹ��� �������ش�
				}
				int j=0;
				str[i]=FriName2[0];
				str[i+1]=FriName2[1];
				str[i+2]=FriName2[2];
				str[i+3]=FriName2[3];
				str[i+4]=FriName2[4];
				str[i+5]=FriName2[5]; // @ , ; �̺κ��� ������ �̸��� �ٽ� �����Ѵ�
				while(str[j+8] != NULL)//�޸� �迭�� �ٽ� �������ش�
				{
					str[i+j+6]=str[i+j+8];
					j++;
				}
				str[i+6+j]=NULL;//NULL�� �־��ش�
				i=i+6;//i�� �� �������� �ʱ�ȭ���ش�
				FriNode = NULL;//ģ�� ��� �ʱ�ȭ
				Number++;//�±� ��� ����
			}
			else//ģ���� �ƴ϶��
			{
				i++;
				memset(FriName2,NULL,sizeof(FriName2)); //ģ���� �ƴϱ⶧���� �迭�ʱ�ȭ
				continue;
			}
		}

		else if( (str[i]=='@') && (str[i+7]==';') && (Number==2) )//�޸��� ������ ģ�� ���°� �±��� ģ���� 2���ִٸ�
		{
			check =0;
			FriName3[0]=str[i+1];
			FriName3[1]=str[i+2];
			FriName3[2]=str[i+3];
			FriName3[3]=str[i+4];
			FriName3[4]=str[i+5];
			FriName3[5]=str[i+6];//�޸� ����Ǿ��ִ� ����̸��� ģ�� �迭�� �ϴ� �����Ѵ�

			if(avl.CheckSameName(FriName3))//���������� �ִ��� üũ�Ѵ�
			{
				check = List.SearchFri(mNode, FriName3);//���������� ���� �Ѵٸ� 
				//���Լ��� ȣ���ϸ� �������� ģ�� �θ��� ���� ����ģ������ Ȯ���Ѵ�
			}
			else//���������� ���ٸ�
			{
				FriNode = avl.NameSearch(FriName3);//�ش��̸��� ������ ��带 ã�´�
				if(FriNode != NULL)//���� ��尡 �����Ѵٸ�
				{
					if( List.SearchFri(FriNode, mNode) )//����ģ������ Ȯ���Ѵ�
						check =1;
				}
			}

			if(check == 1 || check == 2)//ģ���� �����Ѵٸ�
			{
				if(check==2)//���������� �����Ѵٸ�
				{
					FriName3[6]=' ';
					FriName3[7]=str[i+1];
					FriName3[8]=str[i+2];
					FriName3[9]=str[i+3];
					FriName3[10]=str[i+4];
					FriName3[11]=str[i+5];
					FriName3[12]=str[i+6];//ģ�� �̸��� �ѹ��� �������ش�
				}
				int j=0;
				str[i]=FriName3[0];
				str[i+1]=FriName3[1];
				str[i+2]=FriName3[2];
				str[i+3]=FriName3[3];
				str[i+4]=FriName3[4];
				str[i+5]=FriName3[5];// @ , ; �̺κ��� ������ �̸��� �ٽ� �����Ѵ�
				while(str[j+8] !=NULL)//�޸� �迭�� �ٽ� �������ش�
				{
					str[j+i+6]=str[i+j+8];
					j++;
				}
				str[i+6+j]=NULL;//NULL�� �־��ش�
				i=i+6;//i�� �� �������� �ʱ�ȭ���ش�
				FriNode = NULL;//ģ�� ��� �ʱ�ȭ
				Number++;//�±� ��� ����
			}
			else//ģ���� �ƴ϶��
			{
				i++;
				memset(FriName3,NULL,sizeof(FriName3));//ģ���� �ƴϱ⶧���� �迭�ʱ�ȭ
				continue;
			}
		}

		else if( (str[i]=='@') && (str[i+7]==';') && (Number==3) )//�޸��� ������ ģ�� ���°� �±��� ģ���� 3���ִٸ�
		{
			check =0;
			FriName4[0]=str[i+1];
			FriName4[1]=str[i+2];
			FriName4[2]=str[i+3];
			FriName4[3]=str[i+4];
			FriName4[4]=str[i+5];
			FriName4[5]=str[i+6];//�޸� ����Ǿ��ִ� ����̸��� ģ�� �迭�� �ϴ� �����Ѵ�

			if(avl.CheckSameName(FriName4))//���������� �ִ��� üũ�Ѵ�
			{
				check = List.SearchFri(mNode, FriName4);//���������� ���� �Ѵٸ� 
				//���Լ��� ȣ���ϸ� �������� ģ�� �θ��� ���� ����ģ������ Ȯ���Ѵ�
			}
			else//���������� ���ٸ�
			{
				FriNode = avl.NameSearch(FriName4);//�ش��̸��� ������ ��带 ã�´�
				if(FriNode != NULL)//���� ��尡 �����Ѵٸ�
				{
					if( List.SearchFri(FriNode, mNode) )//����ģ������ Ȯ���Ѵ�
						check =1;
				}
			}

			if(check == 1 || check == 2)//ģ���� �����Ѵٸ�
			{
				if(check==2)//���������� �����Ѵٸ�
				{
					FriName4[6]=' ';
					FriName4[7]=str[i+1];
					FriName4[8]=str[i+2];
					FriName4[9]=str[i+3];
					FriName4[10]=str[i+4];
					FriName4[11]=str[i+5];
					FriName4[12]=str[i+6];//ģ���̸��� �ѹ��� �������ش�
				}
				int j=0;
				str[i]=FriName4[0];
				str[i+1]=FriName4[1];
				str[i+2]=FriName4[2];
				str[i+3]=FriName4[3];
				str[i+4]=FriName4[4];
				str[i+5]=FriName4[5];// @ , ; �̺κ��� ������ �̸��� �ٽ� �����Ѵ�
				while(str[j+8] !=NULL)//�޸� �迭�� �ٽ� �������ش�
				{
					str[i+j+6]=str[i+j+8];
					j++;
				}
				str[i+6+j]=NULL;//NULL�� �־��ش�
				i=i+6;//i�� �� �������� �ʱ�ȭ���ش�
				FriNode =NULL;
				Number++;//�±׸�� ����
			}
			else//ģ���� �ƴ϶��
			{
				i++;
				memset(FriName4,NULL,sizeof(FriName4));//ģ���� �ƴ϶�� �迭�� �ʱ�ȭ ���ش�
				continue;
			}
		}

		else//�±� ���°� �ƴ϶��
		{
			i++;//i ����
			continue;
		}
	}

	if(Number!=0)//�±׵� ģ���� �ִٸ�
	{
		ofstream f("alarm.txt",ios_base::app);//alarm.txt ���ϰ�ü ������ ���ÿ� file open
		f<<time<<"	/	"<<mNode->GetName()<<"	->	";//���Ͽ� ���

		if(Number==1)//�±׵� ģ���� �Ѹ��̶��
			f<<FriName1<<endl;//���Ͽ� ���
		else if(Number==2)//�±׵� ģ���� �θ��̶��
			f<<FriName1<<"	"<<FriName2<<endl;//���Ͽ� ���
		else if(Number==3)//�±׵� ģ���� �����̶��
			f<<FriName1<<"	"<<FriName2<<"	"<<FriName3<<endl;//���Ͽ� ���
		else if(Number==4)//�±׵� ģ���� �׸��̶��
			f<<FriName1<<"	"<<FriName2<<"	"<<FriName3<<"	"<<FriName4<<endl;//���Ͽ� ���

		f.close();//������ �ݾ��ش�
	}
	return str;//������ �޸� ��ȯ�Ѵ�.
}

bool Manager::FriendList(char *num)//FriendList �Լ�
{
	ofstream f("friend_list.txt",ios_base::app);//friend_list.txt������ �����ش�.
	User *MeNode = avl.NumSearch(num);//�ش��ϴ� �й����� ����ڸ� ã���ش�.
	int i=0;

	if(MeNode == NULL)//�ش��ϴ� �й��� ����ڰ� ���ٸ�
	{
		for(i=0; i<21;i++)
			f<<"==";
		f<<endl<<num<<" ������ ���� �����Ͱ� �����ϴ�."<<endl;
		for(i=0; i<21;i++)
			f<<"==";//���� ������ ���Ͽ� �����ְ� �Լ� ���� �Ѵ�.
		f<<endl;
		f.close();
		return false;
	}

	for(i=0; i<20;i++)
		f<<"=";
	f<<endl<<MeNode->GetName()<<"  "<<MeNode->GetNumber()<<endl;
	for(i=0; i<20;i++)
		f<<"=";
	f<<endl;
	//���Ͽ� �������� �ϴ� ���� ���
	Linked *temp = MeNode->GetFri();//ģ�� ���� List�� head�� temp�� �����Ѵ�

	if(temp==NULL)//ģ���� ���� ���� �ʴ´ٸ�
	{
		f.close();//������ �ݾ��ش�
		return true;
	}

	while(temp !=NULL)//Ż�𿩺� flag�� 1�� ģ���� ã�Ƽ� �����ִ� �ڵ��̴�
	{
		if( ((temp->GetDown())->GetCheckDelete()) == 1 )
		{
			if( !(List.DeleteFrt(MeNode, temp->GetDown()) ) )//������ �����ش�
				cout<<"ģ�� ������ �����Ͽ����ϴ�."<<endl;//���н� ���� ���
		}
		temp = temp->GetNext();
	}

	temp = MeNode->GetFri();
	User *Friend = NULL;//ģ�� ��带 �����ϱ����� User �����ͺ���
	while(temp != NULL)//ģ�� ������ �ݺ��Ѵ�
	{
		Friend = temp->GetDown();//ģ�� ��带 �����Ѵ�.
		if( List.SearchFri(Friend, MeNode) )//ģ���� �� ģ���� �����ϴ��� Ȯ���Ѵ�
			f<<Friend->GetName()<<"���� ���� ģ�� �Դϴ�."<<endl;//�ش� ���� ���
		else//���� ģ�� ���̰� �ƴ϶��
			f<<Friend->GetName()<<"���� ���� ģ�� �Դϴ�."<<endl;//�ش� ���� ���

		temp = temp->GetNext();//���� ģ���� ����Ű�� �Ѵ�
	}

	f.close();//������ �ݾ��ش�
	return true;//����ȯ
}

bool Manager::INTIMACY(char *me, char *target)//INTIMACY�Լ�
{
	User *MeNode = NULL;
	User *TargetNode1 = NULL;
	User *TargetNode2 = NULL;
	User *Friend = NULL;//����� ��带 �����ϱ����� �ӽ������� ����

	if( (me[0]>='0' && me[0]<='9') && ( target[0]>= '0' && target[0]<='9') )//�Է¹��� ���ڰ� ��� �й��̶��
	{
		MeNode = avl.NumSearch(me);
		TargetNode1 = avl.NumSearch(target);//�й����� ���� ��带 ã���ش�
		if( (MeNode == NULL) || (TargetNode1 == NULL) )//�ϳ��� ���� �ش��ϴ� �й��� ã�� ���Ѵٸ�
		{
			cout<<"�ش��ϴ� �й��� ����ڸ� ã�� �� �����ϴ�."<<endl;
			return false;//�ش繮�� ��� ���� ��ȯ
		}
	}

	else//�̸��� ���� �ִٸ�
	{
		if( avl.CheckSameName(target) )//���������� �ִ��� check �ϴ� �Լ��� ȣ���Ѵ�
		{
			MeNode = avl.NumSearch(me);
			TargetNode1 = avl.NameSearch(target);
			TargetNode2 = avl.NameSearch(target, TargetNode1->GetNumber() );
			//�������� ������ �������� �θ��� ������ ��� ã�� ���� ��忡 �����Ѵ�
			if( (MeNode == NULL) || (TargetNode1 == NULL) || ((TargetNode2 == NULL)) )//�ϳ��� ���� �ش��ϴ� ���������� ã�� ���Ѵٸ�
			{
				cout<<"�ش��ϴ� �й��� ����ڸ� ã�� �� �����ϴ�."<<endl;
				return false;//�ش繮�� ��� ���� ��ȯ
			}
		}
		else//���������� ���� ���� �ʴ´ٸ�
		{
			MeNode = avl.NumSearch(me);
			TargetNode1 = avl.NameSearch(target);//�й����� �ش��ϴ� ���� ������ ã���ش�
			if( (MeNode == NULL) || (TargetNode1 == NULL) )//�ϳ��� ���� �ش��ϴ� �й��� ã�� ���Ѵٸ�
			{
				cout<<"�ش��ϴ� �й��� ����ڸ� ã�� �� �����ϴ�."<<endl;
				return false;//�ش繮�� ��� ���� ��ȯ
			}
		}
	}
	int intimacy1, intimacy2;//���踦 Ȯ�� �ϱ� ���� int�� ����

	if(TargetNode2 == NULL)//���������� ���ٸ�
	{
		ofstream f("intimacy.txt",ios_base::app);//intimacy.txt������ �����ش�.
		Linked *temp = MeNode->GetFri();//���� ģ�� ���Ḯ��Ʈ ��ȯ

		if(temp==NULL)//ģ���� ���� ���� �ʴ´ٸ�
		{
			f.close();//������ �ݾ��ش�
			return true;
		}

		while(temp !=NULL)//Ż�𿩺� flag�� 1�� ģ���� ã�Ƽ� �����ִ� �ڵ��̴�
		{
			if( ((temp->GetDown())->GetCheckDelete()) == 1 )
			{
				if( !(List.DeleteFrt(MeNode, temp->GetDown()) ) )//ģ�� ������ �����ش�
					cout<<"ģ�� ������ �����Ͽ����ϴ�."<<endl;//�ش繮�����
			}
			temp = temp->GetNext();
		}
		temp = MeNode->GetFri();//temp �ٽ� ����


		Linked *temp2 = TargetNode1->GetFri();//Ÿ�� ģ�� ���Ḯ��Ʈ ��ȯ
		if(temp2==NULL)//ģ���� ���� ���� �ʴ´ٸ�
		{
			f.close();//������ �ݾ��ش�
			return true;
		}

		while(temp2 != NULL)//Ż�𿩺� flag�� 1�� ģ���� ã�Ƽ� �����ִ� �ڵ��̴�
		{
			if( ((temp2->GetDown())->GetCheckDelete()) == 1 )
			{
				if( !(List.DeleteFrt(TargetNode1, temp2->GetDown()) ) )//ģ�� ������ �����ش�
					cout<<"ģ�� ������ �����Ͽ����ϴ�."<<endl;//�ش繮�� ���
			}
			temp2 = temp2->GetNext();
		}
		temp2 = TargetNode1->GetFri();//temp �ٽ� ����


		while(temp != NULL)//���� ģ�� ������ �ݺ��Ѵ�
		{
			Friend = temp->GetDown();
			temp2 = TargetNode1->GetFri();
			while(temp2 != NULL)//Ÿ���� ģ�� ������ �ݺ��Ѵ�
			{
				if( strcmp(Friend->GetNumber(), (temp2->GetDown())->GetNumber() )==0 )//������ ģ���� �����Ѵٸ�
				{
					intimacy1 = List.SearchFri(Friend, MeNode);
					intimacy2 = List.SearchFri(Friend,TargetNode1);
					//���� Ȯ�� �Լ��� ȣ���ؼ� ������ ģ���� ���� Ÿ���� ��� �����ϴ��� Ȯ���Ѵ�
					if((intimacy1 ==1) && (intimacy2 ==1) )//S<-->F<-->D
						f<<MeNode->GetName()<<"�� "<<TargetNode1->GetName()<<"�� "<<Friend->GetName()<<"�� ���� ģ�� �����Դϴ�."<<endl;
					//���Ͽ� ���
					else if((intimacy1 ==0) && (intimacy2 ==0))//S->F<-D
						f<<MeNode->GetName()<<"�� "<<TargetNode1->GetName()<<"�� "<<Friend->GetName()<<"�� ���� ����� �����Դϴ�."<<endl;
					//���Ͽ� ���
					else//S<-->F<-D OR //S->F<-->D
						f<<MeNode->GetName()<<"�� "<<TargetNode1->GetName()<<"�� "<<Friend->GetName()<<"�� ���� ������ �����Դϴ�."<<endl;
					intimacy1 = 0;
					intimacy2 = 0;//���踦 Ȯ�� �ϱ� ���� int�� ���� �ʱ�ȭ
				}
				temp2 = temp2->GetNext();//Ÿ���� ����ģ���� ����Ų��
			}
			temp = temp->GetNext();//���� ����ģ���� ����Ų��
		}

		f.close();//������ �ݾ��ش�
		return true;//����ȯ
	}

	else//�������� �ִ�
	{
		ofstream f("intimacy.txt",ios_base::app);//intimacy.txt������ �����ش�.
		Linked *temp = MeNode->GetFri();//���� ģ�� ���Ḯ��Ʈ ��ȯ

		if(temp==NULL)//ģ���� ���� ���� �ʴ´ٸ�
		{
			f.close();//������ �ݾ��ش�
			return true;
		}

		while(temp !=NULL)//Ż�𿩺� flag�� 1�� ģ���� ã�Ƽ� �����ִ� �ڵ��̴�
		{
			if( ((temp->GetDown())->GetCheckDelete()) == 1 )
			{
				if( !(List.DeleteFrt(MeNode, temp->GetDown()) ) )//ģ�� ������ �����ش�
					cout<<"ģ�� ������ �����Ͽ����ϴ�."<<endl;//�ش繮�� ���
			}
			temp = temp->GetNext();
		}
		temp = MeNode->GetFri();//temp �ٽ� ����


		Linked *temp2 = TargetNode1->GetFri();//Ÿ��1�� ģ�� ���Ḯ��Ʈ ��ȯ
		if(temp2==NULL)//ģ���� ���� ���� �ʴ´ٸ�
		{
			f.close();//������ �ݾ��ش�
			return true;
		}
		while(temp2 !=NULL)
		{
			if( ((temp2->GetDown())->GetCheckDelete()) == 1 )//Ż�𿩺� flag�� 1�� ģ���� ã�Ƽ� �����ִ� �ڵ��̴�
			{
				if( !(List.DeleteFrt(TargetNode1, temp2->GetDown()) ) )//ģ�� ������ �����ش�
					cout<<"ģ�� ������ �����Ͽ����ϴ�."<<endl;//�ش繮�� ���
			}
			temp2 = temp2->GetNext();
		}
		temp2 = TargetNode1->GetFri();//temp2 �ٽ� ����




		while(temp != NULL)//���� ģ�� ������ �ݺ��Ѵ�
		{
			Friend = temp->GetDown();
			temp2 = TargetNode1->GetFri();
			while(temp2 != NULL)//Ÿ���� ģ�� ������ �ݺ��Ѵ�
			{
				if( strcmp(Friend->GetNumber(), (temp2->GetDown())->GetNumber() )==0 )//������ ģ���� �����Ѵٸ�
				{
					intimacy1 = List.SearchFri(Friend, MeNode);
					intimacy2 = List.SearchFri(Friend, TargetNode1);
					//���� Ȯ�� �Լ��� ȣ���ؼ� ������ ģ���� ���� Ÿ���� ��� �����ϴ��� Ȯ���Ѵ�
					if((intimacy1 ==1) && (intimacy2 ==1) )//S<-->F<-->D
						f<<MeNode->GetName()<<"�� "<<TargetNode1->GetName()<<"("<<TargetNode1->GetNumber()<<")�� "<<Friend->GetName()<<"�� ���� ģ�� �����Դϴ�."<<endl;
					//���Ͽ� ���
					else if((intimacy1 ==0) && (intimacy2 ==0))//S->F<-D
						f<<MeNode->GetName()<<"�� "<<TargetNode1->GetName()<<"("<<TargetNode1->GetNumber()<<")�� "<<Friend->GetName()<<"�� ���� ����� �����Դϴ�."<<endl;
					//���Ͽ� ���
					else//S<-->F<-D OR //S->F<-->D
						f<<MeNode->GetName()<<"�� "<<TargetNode1->GetName()<<"("<<TargetNode1->GetNumber()<<")�� "<<Friend->GetName()<<"�� ���� ������ �����Դϴ�."<<endl;
					//���Ͽ� ���
					intimacy1 = 0;
					intimacy2 = 0;//���踦 Ȯ�� �ϱ� ���� int�� ���� �ʱ�ȭ
				}
				temp2 = temp2->GetNext();//Ÿ���� ����ģ���� ����Ų��
			}
			temp = temp->GetNext();//���� ����ģ���� ����Ų��
		}

		temp = MeNode->GetFri();//���� ģ�� ���Ḯ��Ʈ ��ȯ
		temp2 = TargetNode2->GetFri();//Ÿ��2�� ģ�� ���Ḯ��Ʈ ��ȯ
		if(temp2==NULL)//ģ���� ���� ���� �ʴ´ٸ�
		{
			f.close();//������ �ݾ��ش�
			return true;
		}
		while(temp2 !=NULL)
		{
			if( ((temp2->GetDown())->GetCheckDelete()) == 1 )//Ż�𿩺� flag�� 1�� ģ���� ã�Ƽ� �����ִ� �ڵ��̴�
			{
				if( !(List.DeleteFrt(TargetNode2, temp2->GetDown()) ) )//ģ�� ������ �����ش�
					cout<<"ģ�� ������ �����Ͽ����ϴ�."<<endl;//�ش繮�� ���
			}
			temp2 = temp2->GetNext();
		}
		temp2 = TargetNode2->GetFri();//temp2 �ٽ� ����


		while(temp != NULL)//���� ģ�� ������ �ݺ��Ѵ�
		{
			Friend = temp->GetDown();
			temp2 = TargetNode2->GetFri();
			while(temp2 != NULL)//Ÿ���� ģ�� ������ �ݺ��Ѵ�
			{
				if( strcmp(Friend->GetNumber(), (temp2->GetDown())->GetNumber() )==0 )//������ ģ���� �����Ѵٸ�
				{
					intimacy1 = List.SearchFri(Friend, MeNode);
					intimacy2 = List.SearchFri(Friend, TargetNode2);
					//���� Ȯ�� �Լ��� ȣ���ؼ� ������ ģ���� ���� Ÿ���� ��� �����ϴ��� Ȯ���Ѵ�
					if((intimacy1 ==1) && (intimacy2 ==1) )//S<-->F<-->D
						f<<MeNode->GetName()<<"�� "<<TargetNode2->GetName()<<"("<<TargetNode2->GetNumber()<<")�� "<<Friend->GetName()<<"�� ���� ģ�� �����Դϴ�."<<endl;
					//���Ͽ� ���
					else if((intimacy1 ==0) && (intimacy2 ==0))//S->F<-D
						f<<MeNode->GetName()<<"�� "<<TargetNode2->GetName()<<"("<<TargetNode2->GetNumber()<<")�� "<<Friend->GetName()<<"�� ���� ����� �����Դϴ�."<<endl;
					//���Ͽ� ���
					else//S<-->F<-D OR //S->F<-->D
						f<<MeNode->GetName()<<"�� "<<TargetNode2->GetName()<<"("<<TargetNode2->GetNumber()<<")�� "<<Friend->GetName()<<"�� ���� ������ �����Դϴ�."<<endl;
					//���Ͽ� ���
					intimacy1 = 0;
					intimacy2 = 0;//���踦 Ȯ�� �ϱ� ���� int�� ���� �ʱ�ȭ
				}
				temp2 = temp2->GetNext();//Ÿ���� ����ģ���� ����Ų��
			}
			temp = temp->GetNext();//���� ����ģ���� ����Ų��
		}

		f.close();//������ �ݾ��ش�
		return true;//����ȯ
	}
}

bool Manager::Save_User(char *file)//���� ���� �Լ�
{
	User *pCur = avl.GetNameRoot();

	ofstream ff(file,ios::out);//�Է� ���� ���ϸ����� ��üff ����
	if( !(ff.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	if( pCur ==NULL )//AVL ����Ǿ��ִ� ������ ���ٸ�
	{
		cout<<"�����ϰ��� �ϴ� ������ �����ϴ�."<<endl;
		return false;//�������� ��°� false ��ȯ
	}

	for(int k=0;k<30;k++)
		ff<<"=";
	ff<<endl;
	ff<<"	�й�	/	�̸�	"<<endl;
	for(int k=0;k<30;k++)
		ff<<"=";
	ff<<endl;//�ش� ������ ���Ͽ� ������ش�.

	while(pCur != NULL) //AVL ������ ������ֱ� ���� while��
	{
		if( (Que.IsEmpty()) && (pCur !=avl.GetNameRoot() ) )//������ �����̶��
			ff<<pCur->GetNumber()<<"	/	"<<pCur->GetName();

		else//������ ������ �ƴ϶��
			ff<<pCur->GetNumber()<<"	/	"<<pCur->GetName()<<endl;

		if( pCur->GetNameLeft() !=NULL)
			Que.Push( pCur->GetNameLeft() );

		if( pCur->GetNameRight() !=NULL )
			Que.Push( pCur->GetNameRight() );

		if( Que.IsEmpty() )//que�� ����ִٸ� 
			break;//while�� ����
		pCur = Que.Pop();// current�� que���� pop ���ش�
	}
	ff.close();//������ �ݾ��ش�
	return true;//����ȯ
}

bool Manager::Save_Friend(char *file)//Save_Friend �Լ�
{
	User *pCur = avl.GetNameRoot();//Name AVL root�� ��ȯ �޴´�
	Linked *temp = NULL;//���� �ӽ� ������ ���� ����

	ofstream ff(file,ios::out);//�Է� ���� ���ϸ����� ��üff ����
	if( !(ff.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	if( pCur ==NULL )//AVL�� ����Ǿ��ִ� ������ ���ٸ�
	{
		cout<<"�����ϰ��� �ϴ� ������ �����ϴ�."<<endl;
		return false;//�������� ��°� false ��ȯ
	}

	for(int k=0;k<37;k++)
		ff<<"=";
	ff<<endl;
	ff<<"�����й�	/	ģ���й�"<<endl;
	for(int k=0;k<37;k++)
		ff<<"=";
	ff<<endl;//�ش� ������ ���Ͽ� ������ش�

	while(pCur != NULL) //AVL�� ����� ģ������ ������ش�
	{
		temp = pCur->GetFri();//ģ�� ���� ����� head�� �����Ѵ�
		if(temp !=NULL)//ģ���� ���� �Ѵٸ�
		{
			while(temp !=NULL)
			{
				if( ((temp->GetDown())->GetCheckDelete()) == 1 )//Ż�𿩺� flag 1�� ��� ģ�� ������ �����ش�
				{
					if( !(List.DeleteFrt(pCur, temp->GetDown()) ) )
						cout<<"ģ�� ������ �����Ͽ����ϴ�."<<endl;
				}
				temp = temp->GetNext();
			}
			temp = pCur->GetFri();//ģ�� ���� ����� head�� �����Ѵ�

			while(temp != NULL)//ģ���� ������ �ݺ��Ѵ�.
			{
				if( (Que.IsEmpty()) && (pCur !=avl.GetNameRoot() ) && (temp->GetNext()==NULL) )//������ �����̶��
					ff<<pCur->GetNumber()<<"	/	"<<(temp->GetDown())->GetNumber();
				//enter�� ����� �� �������� ������ش�
				else//������ ������ �ƴ϶��
					ff<<pCur->GetNumber()<<"	/	"<<(temp->GetDown())->GetNumber()<<endl;
				//�ش������� ������ش�
				temp=temp->GetNext();//���� �ڽĳ�带 ����Ű�� �Ѵ�
			}
		}
		//Lever-order ������� que�� �����س��� ���� ���ǹ�
		if(pCur->GetNameLeft() !=NULL)
			Que.Push( pCur->GetNameLeft() );

		if( pCur->GetNameRight() !=NULL )
			Que.Push( pCur->GetNameRight() );

		if( Que.IsEmpty())//que�� ����ִٸ� 
			break;//while�� ����
		pCur = Que.Pop();// current�� que���� pop ���ش�
	}

	ff.close();//������ �ݾ��ְ� �� ��ȯ
	return true;
}

bool Manager::Save_Memo(char *file)
{
	User *pCur = avl.GetNameRoot();
	MemoNode *temp = NULL;

	ofstream ff(file,ios::out);//�Է� ���� ���ϸ����� ��üff ����
	if( !(ff.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	if( pCur == NULL )//AVL�� ������ ���ٸ�
	{
		cout<<"�����ϰ��� �ϴ� ������ �����ϴ�."<<endl;
		if( Del.Delete() )//leave ��忡 ����Ǿ��ִ� �������� ��� �����ش�.
			cout<<"Ż�� ��û�� �������� ������ ��� ���� �����Ͽ����ϴ� "<<endl;
		else
			cout<<"Ż�� ��û�� �������� ������ ��� �����ϴµ� �����Ͽ����ϴ� "<<endl;
		return false;//�������� ��°� false ��ȯ
	}

	for(int k=0;k<35;k++)
		ff<<"==";
	ff<<endl;
	ff<<"�����й�	/	�ۼ��ð�	/	�۳���"<<endl;
	for(int k=0;k<35;k++)
		ff<<"==";
	ff<<endl;//�ش� ������ ���Ͽ� ������ش�

	while(pCur != NULL) //AVL ������ ������ֱ� ���� while��
	{
		temp = pCur->GetMyMemo();//�ڽĳ���� head�� �����Ѵ�
		if(temp !=NULL)//����Ǿ��ִ� �޸� �ִٸ� ������ �����Ѵ�
		{
			while(temp != NULL)//�ڽ� ��� ������ �ݺ��Ѵ�
			{
				if( (Que.IsEmpty()) && (pCur !=avl.GetNameRoot() ) && (temp->GetNext() == NULL) )//������ �����̶��
					ff<<pCur->GetNumber()<<"	/	"<<temp->GetTime()<<"	/	"<<temp->GetMemo();
				//enter�� ����� �� �������� ������ش�
				else//������ ������ �ƴ϶��
					ff<<pCur->GetNumber()<<"	/	"<<temp->GetTime()<<"	/	"<<temp->GetMemo()<<endl;
				//�ش������� ������ش�
				temp=temp->GetNext();//���� �ڽĳ�带 ����Ű�� �Ѵ�
			}
		}
		//Lever-order ������� que�� �����س��� ���� ���ǹ�
		if(pCur->GetNameLeft() !=NULL)
			Que.Push( pCur->GetNameLeft() );

		if( pCur->GetNameRight() !=NULL )
			Que.Push( pCur->GetNameRight() );

		if( Que.IsEmpty())//que�� ����ִٸ� 
			break;//while�� ����
		pCur = Que.Pop();// current�� que���� pop ���ش�
	}
	if( Del.Delete() )//leave ��忡 ����Ǿ��ִ� �������� �����Ѵ�
		cout<<"Ż�� ��û�� �������� ������ ��� ���� �����Ͽ����ϴ� "<<endl;
	else
		cout<<"Ż�� ��û�� �������� ������ ��� �����ϴµ� �����Ͽ����ϴ� "<<endl;

	ff.close();//������ �ݾ��ش�
	return true;//����ȯ
}

bool Manager::TimeLine(char *num)//TimeLine�Լ�
{
	ofstream f("timeline.txt",ios_base::app);//timeline.txtt������ �����ش�.
	User *MeNode = avl.NumSearch(num);//�й����� �Է� ���� ������� �ε带 ã���ش�
	User *Friend = NULL;//ģ���� �����ϱ� ���� �ӽú���

	if(MeNode == NULL)//�ش��ϴ� �й��� ����ڰ� ���� ���� �ʴ´ٸ�
	{
		for(int i=0; i<21;i++)//�ش� ������ ���Ͽ� �����ش�
			f<<"==";
		f<<endl<<num<<" ������ ���� �����Ͱ� �����ϴ�."<<endl;
		for(int i=0; i<21;i++)
			f<<"==";
		f<<endl;
		f.close();//������ �ݾ��ش�
		return false;//���� ��ȯ
	}

	MemoNode *Memo = MeNode->GetMyMemo();
	while(Memo!=NULL)//���� �ۼ��� �޸� �������ֱ����� �ݺ���
	{
		if( !(heap.pushMinHeap(Memo)) )// heap�� push ���ش�
			cout<<"�޸� ���� ����"<<endl;
		Memo = Memo->GetNext();//���� �޸� ����Ų��
	}


	Linked *temp = MeNode->GetFri();//�ӽ� ������ ���� ����
	while(temp != NULL)
	{
		if( ((temp->GetDown())->GetCheckDelete()) == 1 )//Ż�𿩺� flag1�� ģ���� �����ش�
		{
			if( !(List.DeleteFrt(MeNode, temp->GetDown()) ) )//ģ�� ������ �����ش�
				cout<<"ģ�� ������ �����Ͽ����ϴ�."<<endl;
		}
		temp = temp->GetNext();
	}
	temp = MeNode->GetFri();

	while(temp != NULL)//ģ�� ������ �ݺ��Ѵ�
	{
		Memo = NULL;//Memo�� �ʱ�ȭ ���ش�
		Friend = temp->GetDown();//ģ�� ��带 �����Ѵ�.
		if( List.SearchFri(Friend, MeNode) )//ģ���� �� ģ���� �����ϴ��� Ȯ���Ѵ�
		{
			Memo = Friend->GetMyMemo();//ģ�� ���̰� �´ٸ� ������ �޸� ����� Memo�� �����Ѵ�
			if(Memo != NULL)
			{
				while(Memo!=NULL)//�޸��� ������ �ݺ��Ѵ�
				{
					if( !(heap.pushMinHeap(Memo)) )//�޸��� ������ heap�� �־��ش�
						cout<<"�޸� ���� ����"<<endl;
					Memo = Memo->GetNext();//���� �޸� ����Ų��
				}
			}
		}
		temp = temp->GetNext();//���� ģ���� ����Ű�� �Ѵ�
	}

	MemoNode *Write = NULL;//pop ������ �ӽ÷� �����ϱ����� ������ ����

	if( !(heap.Heap_IsEmpty()) )//heap�� ��������ʴٸ�
	{
		for(int i=0; i<20;i++)
			f<<"=";
		f<<endl<<MeNode->GetName()<<"  "<<MeNode->GetNumber()<<endl;
		for(int i=0; i<20;i++)
			f<<"=";
		f<<endl;//���Ͽ� �ش� ������ �����ش�

		while(1)//heap�� �������� �ݺ��ϱ����� ���ѷ���
		{
			if( heap.Heap_IsEmpty() )//heap�� empty���
				break;//���ѷ��� ����
			Write = heap.popMinHeap();//heap���� pop �Ѵ�
			f<<Write->GetTime()<<"	/	"<<Write->GetWho()<<"	/	"<<Write->GetMemo()<<endl;//���Ͽ� ������ �����ش�
		}
		f.close();
		return true;//������ �ݾ��ְ� ����ȯ
	}
	else//heap�� ����ִٸ�
	{
		for(int i=0; i<20;i++)
			f<<"=";
		f<<endl<<MeNode->GetName()<<"  "<<MeNode->GetNumber()<<endl;
		for(int i=0; i<20;i++)
			f<<"=";
		f<<endl;//���Ͽ� �ش� ������ �����ش�
		f.close();
		return true;//������ �ݾ��ְ� ����ȯ
	}
}

bool Manager::Update_User(char *file)
{
	ifstream fin;//���� ��Ʈ�� ����
	User *user=NULL;
	User *Delete = NULL;
	char str[200];//���پ� �ޱ� ���� �迭 ����
	memset(str,NULL,sizeof(str));//�迭 �ʱ�ȭ

	char *temp1 = NULL;
	char *temp2 = NULL;//���ڿ��� ¥���� ���� char�� �ӽ� ������ ����

	fin.open(file,ios::in);//�Է� ���� ���ϸ����� ������ �б� ���� �����ش�
	if( !(fin.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	for(int i=0;i<3;i++)//�޸��忡 �ʿ� ���� ������ �����ش�
		fin.getline(str,sizeof(str));
	memset(str,NULL,sizeof(str));//�迭�� NULL�� �ʱ�ȭ

	while( !(fin.eof()) )//������ ������ �ݺ��Ѵ�
	{
		fin.getline(str,sizeof(str));//���Ͽ��� ������ �޾ƿ´�

		temp1 = strtok(str,"	 /");//�й��� ¥����
		temp2 = strtok(NULL,"	 /");//�̸��� ¥����
		Delete = avl.NumSearch(temp1);

		if(Delete == NULL)//ã�� ��尡 ���ٸ�
		{
			user = new User();//User ��� �޸� �Ҵ�
			user->SetNumber(temp1);//User Node�� �й��� �����Ѵ�
			user->SetName(temp2);//User Node�� �̸��� �����Ѵ�
			if( !(avl.NameAVL(user)) )//Name AVL insert ȣ��
			{
				cout<<"Name AVL insert�� �����Ͽ����ϴ�."<<endl;//�����ߴٸ� ���� ���
				return false;//������ȯ
			}
			if( !(avl.NumberAVL(user)) )//Number AVL insert ȣ��
			{
				cout<<"Number AVL insert�� �����Ͽ����ϴ�."<<endl;//�����ߴٸ� ���� ���
				return false;//���� ��ȯ
			}
		}
		else//�����ϴ� �����
		{
			//�����Ұ� ���� �Լ� ȣ��
		}

		Delete=NULL;//delete �ʱ�ȭ
		temp1=NULL;//temp�� NULL�� �ʱ�ȭ
		temp2=NULL;//temp2�� NULL�� �ʱ�ȭ �Ѵ�
		memset(str,NULL,sizeof(str));//�迭���� NULL�� �ʱ�ȭ�Ѵ�
	}
	fin.close();//������ �ݾ��ش�
	return true;//����ȯ
}

bool Manager::Update_Friend(char *file)
{
	ifstream fin;//���� ��Ʈ�� ����
	char str[200];//���پ� �ޱ� ���� �迭 ����
	memset(str,NULL,sizeof(str));//�迭 �ʱ�ȭ

	User *MeNode = NULL;//�ӽ� ������ ����
	User *FriNode = NULL;

	char *Me = NULL;
	char *Fri = NULL;//���ڿ��� ¥���� ���� char�� �ӽ� ������ ����

	fin.open(file,ios::in);//�Է� ���� ���ϸ����� ������ �б� ���� �����ش�
	if( !(fin.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	for(int i=0;i<3;i++)//�޸��忡 �ʿ� ���� ������ �����ش�
		fin.getline(str, sizeof(str));
	memset(str, NULL, sizeof(str));//�迭�� NULL�� �ʱ�ȭ

	while( !(fin.eof()) )//������ ������ �ݺ��Ѵ�
	{
		fin.getline(str,sizeof(str));//���Ͽ��� ������ �޾ƿ´�

		Me = strtok(str,"	 /");//���� �й��� �����Ѵ�
		Fri = strtok(NULL,"	 /");//ģ���� �й��� �����Ѵ�

		MeNode = avl.NumSearch(Me);
		FriNode = avl.NumSearch(Fri);//�ش��ϴ� �й��� ��带 ã���ش�

		if( (MeNode == NULL) || (FriNode == NULL) )//ã�� ��尡 ���ٸ� �ش繮�� ����� ���� ��ȯ
		{
			cout<<"�ش��ϴ� �й��� ����ڰ� �����ϴ�."<<endl;
			return false;
		}
		else
		{
			if( List.SearchFri(MeNode, FriNode) )//ģ���� �����Ѵٸ�
			{
				if( !(List.DeleteFrt(MeNode, FriNode)) )
					cout<<"ģ�� ������ �����Ͽ����ϴ�."<<endl;
			}

			if( !(List.Insert(MeNode, FriNode)) )//ģ���߿� ���� ���� �μ�Ʈ �Լ� ȣ��
			{
				cout<<"ģ�� �߰��� ���� �Ͽ����ϴ�."<<endl;//�ش繮�� ��� ���� ��ȯ
				return false;
			}
		}

		MeNode = NULL;
		FriNode = NULL;
		Me=NULL;
		Fri=NULL;//�ӽ� �������� NULL�� �ʱ�ȭ �����ش�
		memset(str,NULL,sizeof(str));//�迭���� NULL�� �ʱ�ȭ�Ѵ�
	}

	fin.close();
	return true;//������ �ݾ��ְ� true ��ȯ
}

bool Manager::Update_Memo(char *file)
{
	ifstream fin;//���� ��Ʈ�� ����
	char str[300];//���پ� �ޱ� ���� �迭 ����
	memset(str,NULL,sizeof(str));

	User *MeNode = NULL;
	MemoNode *mNode = NULL;//�޸�� ����ڸ� ���� �����Ͱ�ü ����

	char *me = NULL;
	char *time = NULL;
	char *memo = NULL;//���ڿ��� ¥���� ���� char�� �ӽ� ������ ����

	fin.open(file,ios::in);//�Է� ���� ���ϸ����� ������ �б� ���� �����ش�
	if( !(fin.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	for(int i=0;i<3;i++)//�޸��忡 �ʿ� ���� ������ �����ش�
		fin.getline(str,sizeof(str));
	memset(str,NULL,sizeof(str));//�迭�� NULL�� �ʱ�ȭ

	while( !(fin.eof()) )//������ ������ �ݺ��Ѵ�
	{
		fin.getline(str,sizeof(str));//���Ͽ��� ������ �޾ƿ´�

		me = strtok(str,"	/");//���� �й��� �����Ѵ�
		time = strtok(NULL,"	/");//�ð����� �����Ѵ�
		memo = strtok(NULL,"	/");//�޸� �����Ѵ�
		MeNode = avl.NumSearch(me);

		if(MeNode == NULL)//ã�� ��尡 ���ٸ� �ش繮�� ����� ���� ��ȯ
		{
			cout<<"�ش��ϴ� �й��� ����ڰ� �����ϴ�."<<endl;
			return false;
		}
		else//ã�� ��尡 �ִٸ� �޸��� ������ ���� �ϰ� �޸� ���� ��带 ȣ���Ѵ�
		{
			if(memo == NULL)//�޸𳻿� ����
			{
				if( Line.MemoSearch( MeNode, time ) )//�ð��� ���� �޸� ���� �Ѵٸ�
				{
					if( !(Line.MemoDelete(MeNode, time)) )//�޸� ����
					{
						cout<<"�޸� ������ �����Ͽ����ϴ�."<<endl;
						return false;
					}

				}
			}
			else//�޸𳻿� �ִ�
			{
				if( !(Line.MemoSearch( MeNode, time)) )//���� �ð� �޸� ���� �����ʴ´ٸ�
				{
					mNode = new MemoNode();//memo��� �����Ѵ�

					strcpy(memo,ALARM(MeNode, memo, time));//ALARM �Լ� ȣ���� ���� �޸𳻿��� �������ش�
					mNode->SetTime(time);
					mNode->SetWrite(memo);//�޸� ��忡 ������ �����Ѵ�
					mNode->SetWho(MeNode->GetName());

					if( !(Line.MemoInsert(MeNode, mNode)) )//insert�� �����Ͽ��ٸ�
					{
						cout<<"�޸� ���ῡ ���� �Ͽ����ϴ�."<<endl;//�ش繮�� ��� ���� ��ȯ
						return false;
					}
				}
			}
		}

		MeNode = NULL;
		me = NULL;
		time = NULL;
		memo = NULL;//�ӽ� �������� NULL�� �ʱ�ȭ �����ش�
		memset(str,NULL,sizeof(str));//�迭���� NULL�� �ʱ�ȭ�Ѵ�
	}

	fin.close();
	return true;//������ �ݾ��ְ� true ��ȯ
}

bool Manager::EXIT()//���� �Լ�
{
	User *pCur = avl.GetNumRoot();//Name AVL root�� ��ȯ �޴´�
	User *usertemp = NULL;
	Linked *frnhead = NULL;//���� �ӽ� ������ ���� ����
	Linked *frntemp = NULL;
	MemoNode *memohead = NULL;
	MemoNode *memotemp = NULL;

	while(pCur != NULL) //AVL������ ����
	{
		usertemp = pCur;//�޸������� ��� ����
		memohead = pCur->GetMyMemo();
		while(memohead !=NULL)
		{
			memotemp = memohead;
			memohead = memohead->GetNext();
			delete memotemp;
		}

		frnhead = pCur->GetFri();
		while(frnhead !=NULL)//ģ�� ������ ��� ����
		{
			frntemp = frnhead;
			frnhead = frnhead->GetNext();
			delete frntemp;
		}
		//Lever-order ������� que�� �����س��� ���� ���ǹ�
		if(pCur->GetNumLeft() !=NULL)
			Que.Push( pCur->GetNumLeft() );

		if( pCur->GetNumRight() !=NULL )
			Que.Push( pCur->GetNumRight() );

		if( Que.IsEmpty())//que�� ����ִٸ� 
		{
			delete usertemp;
			break;//while�� ����
		}
		pCur = Que.Pop();// current�� que���� pop ���ش�

		delete usertemp;
	}
	Del.Delete();//leave list�� �����ִ� �� �������ش�
	return true;
}