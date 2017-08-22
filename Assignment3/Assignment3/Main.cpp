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

	char *Cmd = NULL;
	char *File = NULL;
	char *File1 = NULL;
	char *File2 = NULL;
	char *File3 = NULL;
	char *File4 = NULL;//���ϸ��� �ޱ����� �ӽ� ������ ����

	file.open("cmd.txt",ios::in);//command������ open �Ѵ�
	if( !(file.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	for(int i=0;i<3;i++)//�޸��忡 �ʿ� ���� ������ �����ش�
		file.getline(str,sizeof(str));
	memset(str,NULL,sizeof(str));//�迭�� NULL�� �ʱ�ȭ

	cout<<"<<<<<  KW heating maintenance Service Start  >>>>>"<<endl;// ȭ�鿡 ���
	while( !(file.eof()) )//������ ������ �ݺ��Ѵ�
	{
		file.getline(str,100);//txt������ ���پ� �޴´�
		if(str[0]==NULL)//Enter�� ���´ٸ� ���� ����
			break;

		File = strtok(str,"	 /");
		if( strcmp( File,"LOAD")  == 0 )//��ɾ LOAD ���
		{
			File = strtok(NULL,"	 /");
			File1 = strtok(NULL,"	 /");
			File2 = strtok(NULL,"	 /");
			File3 = strtok(NULL,"	 /");
			File4 = strtok(NULL,"	 /");//Load �ؾ� �ϴ� ���ϸ��� �ӽ÷� �����صд�

			if( manager.Load_gu(File, File1) )//�� ���� �ε尡 ���� �ߴٸ�
				cout<<"Load_gu�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
			else//�� ���� �ε尡 ���� �ߴٸ�
				cout<<"Load_gu�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���

			if( manager.Load_dong(File2, File3) )//�� ���� �ε尡 ���� �ߴٸ�
				cout<<"Load_dong�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
			else//�� ���� �ε尡 ���� �ߴٸ�
				cout<<"Load_dong�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���

			if( manager.Load_Mehanic(File4) )//����� ���� �ε尡 ���� �ߴٸ�
				cout<<"Load_Mehanic�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
			else//����� ���� �ε尡 ���� �ߴٸ�
				cout<<"Load_Mehanic�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
		}

		else if(strcmp( File,"UPDATE") == 0)//��ɾ UPDATE ���
		{
			File = strtok(NULL,"	 /");//UPDATE�� ���ϸ��� �Է� �޴´�

			if( manager.Update(File) )//UPDETE�� ���� �ߴٸ�
				cout<<"Dong_Edge_cost Update�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
			else//UPDATE�� ���� �ߴٸ�
				cout<<"Dong_Edge_cost Update�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
		}

		else if(strcmp( File,"PIPE_REPAIR") == 0)//��ɾ PIPE_REPAIR ���
		{
			File = strtok(NULL,"	 /");//������ ���� �Է� �޴´�

			if( manager.Pipe_Repair(File) )//PIPE_REPAIR�� ���� �ߴٸ�
				cout<<"Pipe_Repair�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
			else//PIPE_REPAIR�� ���� �ߴٸ�
				cout<<"Pipe_Repair�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
		}

		else if(strcmp( File,"PIPE_BROKEN") == 0)//��ɾ PIPE_BROKEN ���
		{
			File = strtok(NULL,"	 /");
			File1 = strtok(NULL,"	 /");
			File2 = strtok(NULL,"	 /");//���� Edge ������ �Է� �޴´�

			if( manager.Pipe_Broken(File, File1, File2) )//Pipe_Broken�� ���� �ߴٸ�
				cout<<"Pipe_Broken�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
			else//Pipe_Broken�� ���� �ߴٸ�
				cout<<"Pipe_Broken�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
		}

		else if(strcmp( File,"SAVE") == 0)//��ɾ SAVE ���
		{
			if( manager.Save_Gu() )//�� ���� ������ ���� �ߴٸ�
				cout<<"Save_Gu�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
			else//�� ���� ������ ���� �ߴٸ�
				cout<<"Save_Gu�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���

			if( manager.Save_Dong() )//�� ���� ������ ���� �ߴٸ�
				cout<<"Save_Dong�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
			else//�� ���� ������ ���� �ߴٸ�
				cout<<"Save_Dong�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���

			if( manager.Save_Mechanic() )//����� ���� ������ ���� �ߴٸ�
				cout<<"Save_Mechanic�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
			else//����� ���� ������ ���� �ߴٸ�
				cout<<"Save_Mechanic�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
		}

		else if(strcmp( File,"PRINT") == 0)//��ɾ PRINT ���
		{
			File = strtok(NULL,"	 /");//PRINT ���� �׸��� �Է� �޴´�

			if( strcmp(File, "����") == 0 )//���� ����̶��
			{
				if( manager.Print_Map() )//Print_Map�� ���� �ߴٸ�
					cout<<"Print_Map�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
				else//Print_Map�� ���� �ߴٸ�
					cout<<"Print_Map�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
			}

			else if( strcmp(File, "�����") == 0)//����� ����̶��
			{
				if( manager.Print_Mechanic() )//Print_Mechanic�� ���� �ߴٸ�
					cout<<"Print_Mechanic�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
				else//Print_Mechanic�� ���� �ߴٸ�
					cout<<"Print_Mechanic�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
			}

			else//�׿� ��� ���� �Է� �޴´�
			{
				if( manager.Print_Gu(File) )//Print_Gu�� ���� �ߴٸ�
					cout<<"Print_Gu�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
				else//Print_Gu�� ���� �ߴٸ�
					cout<<"Print_Gu�� ���� �Ͽ����ϴ�."<<endl;//ȭ�鿡 ���
			}
		}

		else if( strcmp( File,"EXIT") == 0 )//��ɾ EXIT ���                         
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
		File1=NULL;
		File2=NULL;
		File3=NULL;
		File4=NULL;
	}

	cout<<"Command ������ ����Ǿ����ϴ�."<<endl;//ȭ�鿡 ���
	file.close();//������ �ݾ��ش�
	return 0;//�Լ� ����
}