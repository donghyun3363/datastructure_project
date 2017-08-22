#include "Manager.h"
#include<iostream>
#include<fstream>//�ش����� ����

using namespace std;//�̸������� std������ ���

int main(void)
{
	ifstream file;//���� ��ü����
	char str[50];//Ŀ�ǵ��� �� ���ξ� �ޱ����� �迭
	char filename[20];//���� ���� �ޱ����� �迭
	char f_num[20];//�ڵ带 �ޱ����� �迭

	memset(str,NULL,sizeof(str));//�迭�� NULL�� �ʱ�ȭ�Ѵ�
	memset(filename,NULL,sizeof(filename));
	memset(f_num,NULL,sizeof(f_num));
	Manager Main; //�Ŵ��� ��ü ����

	file.open("command.txt",ios::in);//command������ open �Ѵ�
	if( !(file.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	cout<<"Parcel Service Management System Start"<<endl;
	while( !(file.eof()) )//������ ������ �ݺ��Ѵ�
	{

		file.getline(str,50);//txt������ ���پ� �޴´� 

		if(str[0]=='L')//��ɾ LOAD ���
		{
			for(int i=0; ; i++)
			{
				if( (str[i]==' ') || (str[i]=='	') )//��ɾ�ڿ� ���ϸ��� �ޱ����� �ݺ���
				{
					for(int j=0;  ; j++)
					{
						filename[j]=str[i+j+1];//filename �迭�� �����Ѵ�.
						if((str[i+j+1]=='\n') || (str[i+j+1]==NULL))
							break;
					}
					break;
				}
			}
			if( Main.LoadFile(filename) ) //Manager Ŭ���� LoadFile �Լ� ȣ��
				cout<<"���Ϸε忡 �����Ͽ����ϴ�"<<endl;
			else
				cout<<"���Ϸε忡 �����Ͽ����ϴ�"<<endl;
		}

		else if(str[0]=='F')//��ɾ FIND ���
		{
			for(int i=0; ; i++)
			{
				if( (str[i]==' ') || (str[i]=='	') )
				{
					for(int j=0;  ; j++)
					{
						f_num[j]=str[i+j+1];
						if((str[i+j+1]=='\n') || (str[i+j+1]==NULL))
							break;
					}
					break;
				}
			}
			if( Main.FIND(f_num) )//Manager Ŭ���� FIND �Լ� ȣ��
				cout<<"ã�⿡ �����Ͽ����ϴ�"<<endl;
			else
				cout<<"ã�⿡ �����Ͽ����ϴ�"<<endl;
		}
		//������Ʈ�� ���� ���� ���Ͽ����ϴ�.
		/*else if(str[0]=='U')//��ɾ UPDATE ���
		{
			for(int i=0; ; i++)
			{
				if( (str[i]==' ') || (str[i]=='	') )//��ɾ�ڿ� ���ϸ��� �ޱ����� �ݺ���
				{
					for(int j=0;  ; j++)
					{
						filename[j]=str[i+j+1];//filename �迭�� �����Ѵ�.
						if((str[i+j+1]=='\n') || (str[i+j+1]==NULL))
							break;
					}
					break;
				}
			}
			if( Main.UPDATE(filename) )//Manager Ŭ���� LoadFile �Լ� ȣ��
				cout<<"������Ʈ�� �����Ͽ����ϴ�"<<endl;
			else
				cout<<"������Ʈ�� �����Ͽ����ϴ�"<<endl;
		}*/

		else if(str[0]=='S')//��ɾ SAVE ���
		{
			for(int i=0; ; i++)
			{
				if( (str[i]==' ') || (str[i]=='	') )//��ɾ�ڿ� ���ϸ��� �ޱ����� �ݺ���
				{
					for(int j=0;  ; j++)
					{
						filename[j]=str[i+j+1];//filename �迭�� �����Ѵ�.
						if((str[i+j+1]=='\n') || (str[i+j+1]==NULL))
							break;
					}
					break;
				}
			}
			if( Main.SAVE(filename) )//Manager Ŭ���� SAVE �Լ� ȣ��
				cout<<"���忡 �����Ͽ����ϴ�"<<endl;
			else
				cout<<"���忡 �����Ͽ����ϴ�"<<endl;
		}

		else if(str[0]=='P')//��ɾ PRINT ���                    
		{
			if( Main.PRINT() )//Manager Ŭ���� PRINT �Լ� ȣ��
				cout<<"��¿��� �����Ͽ����ϴ�"<<endl;
			else
				cout<<"��¿� �����Ͽ����ϴ�"<<endl;
		}

		else if(str[0]=='E')//��ɾ EXIT ���                         
		{
			if( Main.EXIT() )//Manager Ŭ���� EXIT �Լ� ȣ��
			{
				cout<<"���ῡ �����Ͽ����ϴ�"<<endl;
				file.close();
				return 0;
			}
			else//�����Ͽ��ٸ�
			{
				cout<<"���ῡ �����Ͽ����ϴ�."<<endl;
			}
		}
		else //�ٸ� ��ɾ ���Դٸ�
			cout<<"��ɾ �� �� �Է� �Ǿ��ֽ��ϴ�."<<endl;

		memset(str,NULL,sizeof(str)); //�迭���� NULL�� �ʱ�ȭ ���ش�
		memset(filename,NULL,sizeof(filename));
		memset(f_num,NULL,sizeof(f_num));

	}
	cout<<"Command ������ ����Ǿ����ϴ�."<<endl;//ȭ�鿡 ���
	file.close();//������ �ݾ��ش�
	return 0;//�Լ� ����
}