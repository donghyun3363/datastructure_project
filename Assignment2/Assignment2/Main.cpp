#include "Manager.h"
#include<iostream>
#include<fstream>//�ش����� ����

using namespace std;//�̸������� std������ ���

int main(void)
{
	Manager manager;//Manager ��ü ����
	ifstream file;//���� ��ü����
	char str[100];//Ŀ�ǵ��� �� ���ξ� �ޱ����� �迭
	memset(str,NULL,sizeof(str));//�迭�� NULL�� �ʱ�ȭ�Ѵ�
	char *File=NULL;
	char *File2=NULL;
	char *File3=NULL;//�ӽ÷� ������ �����ϱ� ���� ������ ����

	file.open("command.txt",ios::in);//command������ open �Ѵ�
	if( !(file.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	cout<<"<<<<<  KW Social Networking Service Start  >>>>>"<<endl;// ȭ�鿡 ���
	while( !(file.eof()) )//������ ������ �ݺ��Ѵ�
	{
		file.getline(str,100);//txt������ ���پ� �޴´� 

		if( strncmp( str,"LOAD", sizeof(4) ) == 0 )//��ɾ LOAD ���
		{
			File = strtok(str,"	 /");
			File = strtok(NULL,"	 /");
			File2 = strtok(NULL,"	 /");
			File3 = strtok(NULL,"	 /");//Load �ؾ� �ϴ� ���ϸ��� �ӽ÷� �����صд�
			if( manager.Load_User(File) )//����� ���� �ε尡 ���� �ߴٸ�
				cout<<"Load_User�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
			else//����� ���� �ε尡 ���� �ߴٸ�
				cout<<"Load_User�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���

			if( manager.Load_Friend(File2) )//ģ�� ���� �ε尡 ���� �ߴٸ�
				cout<<"Load_Friend�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
			else//ģ�� ���� �ε尡 ���� �ߴٸ�
				cout<<"Load_Friend�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���

			if( manager.Load_Memo(File3) )//�޸� ���� �ε尡 ���� �ߴٸ�
				cout<<"Load_Memo�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
			else//�޸� ���� �ε尡 ���� �ߴٸ�
				cout<<"Load_Memo�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
		}

		else if(strncmp( str,"SAVE", sizeof(4) ) == 0)//��ɾ SAVE ���
		{
			File = strtok(str,"	 /");
			File = strtok(NULL,"	 /");
			File2 = strtok(NULL,"	 /");
			File3 = strtok(NULL,"	 /");//Load �ؾ� �ϴ� ���ϸ��� �ӽ÷� �����صд�
			if( manager.Save_User(File) )//����� ���� ������ ���� �ߴٸ�
				cout<<"Save_User�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
			else//����� ���� ������ ���� �ߴٸ�
				cout<<"Save_User�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���

			if( manager.Save_Friend(File2) )//ģ�� ���� ������ ���� �ߴٸ�
				cout<<"Save_Friend�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
			else//ģ�� ���� ������ ���� �ߴٸ�
				cout<<"Save_Friend�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���

			if( manager.Save_Memo(File3) )//�޸� ���� ������ ���� �ߴٸ�
				cout<<"Save_Friend�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
			else//�޸� ���� ������ ���� �ߴٸ�
				cout<<"Save_Friend�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
		}

		else if( strncmp( str,"FRNDLIST", sizeof(8) ) == 0)//��ɾ FRNDLIST ���
		{
			File = strtok(str,"	 /");
			File = strtok(NULL,"	 /");//������ �й��� �����Ѵ�
			if( manager.FriendList(File) )//FriendList �Լ� ȣ�⿡ �����Ͽ��ٸ�
				cout<<"FRNDLIST ��¿� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
			else//�����Ͽ��ٸ�
				cout<<"FRNDLIST ��¿� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
		}
		
		else if( strncmp( str,"INTIMACY", sizeof(8) ) == 0)//��ɾ INTIMACY ���                    
		{
			File = strtok(str,"	 /");
			File = strtok(NULL,"	 /");
			File2 = strtok(NULL,"	 /");//�θ��� ����� ������ �Է� �޴´�.
			if( manager.INTIMACY(File,File2) )//Manager Ŭ���� INTIMACY �Լ� ȣ��
				cout<<"INTIMACY ��¿� �����Ͽ����ϴ�"<<endl;//ȭ�鿡 ���
			else//�����Ͽ��ٸ�
				cout<<"INTIMACY ��¿� �����Ͽ����ϴ�"<<endl;//ȭ�鿡 ���
		}
		
		else if( strncmp( str,"TIMELINE", sizeof(8) ) == 0 )//��ɾ TIMELINE ���                         
		{
			File = strtok(str,"	 /");
			File = strtok(NULL,"	 /");
			if( manager.TimeLine(File) )//Manager Ŭ���� TIMELINE �Լ� ȣ��
				cout<<"TIMELINE ��¿� �����Ͽ����ϴ�"<<endl;//ȭ�鿡 ���
			else//�����Ͽ��ٸ�
				cout<<"TIMELINE ��¿� �����Ͽ����ϴ�"<<endl;//ȭ�鿡 ���
		}

		else if( strncmp( str,"UPDATE", sizeof(6) ) == 0 )//��ɾ LOAD ���
		{
			File = strtok(str,"	 /");
			File = strtok(NULL,"	 /");
			File2 = strtok(NULL,"	 /");
			File3 = strtok(NULL,"	 /");//Load �ؾ� �ϴ� ���ϸ��� �ӽ÷� �����صд�

			if( manager.Update_User(File) )//����� ���� �ε尡 ���� �ߴٸ�
				cout<<"Load_User�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
			else//����� ���� �ε尡 ���� �ߴٸ�
				cout<<"Load_User�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���

			if( manager.Update_Friend(File2) )//ģ�� ���� �ε尡 ���� �ߴٸ�
				cout<<"Update_Friend�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
			else//ģ�� ���� �ε尡 ���� �ߴٸ�
				cout<<"Update_Friend�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���

			if( manager.Update_Memo (File3) )//�޸� ���� �ε尡 ���� �ߴٸ�
				cout<<"Load_Memo�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
			else//�޸� ���� �ε尡 ���� �ߴٸ�
				cout<<"Load_Memo�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
		}
		
		else if( strncmp( str,"EXIT", sizeof(4) ) == 0 )//��ɾ EXIT ���                         
		{
			if( manager.EXIT() )//Manager Ŭ���� EXIT �Լ� ȣ��
			{
				cout<<"���ῡ �����Ͽ����ϴ�"<<endl;
				file.close();
				return 0;
			}
			else//�����Ͽ��ٸ�
				cout<<"���ῡ �����Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
		}

		else //�ٸ� ��ɾ ���Դٸ�
			cout<<"��ɾ �� �� �Է� �Ǿ��ֽ��ϴ�."<<endl;//ȭ�鿡 ���
		memset(str,NULL,sizeof(str)); //�迭���� NULL�� �ʱ�ȭ ���ش�
		File=NULL;
		File2=NULL;
		File3=NULL;
	}

	cout<<"Command ������ ����Ǿ����ϴ�."<<endl;//ȭ�鿡 ���
	file.close();//������ �ݾ��ش�
	return 0;//�Լ� ����
}