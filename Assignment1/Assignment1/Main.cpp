#include "Manager.h"
#include<iostream>
#include<fstream>//해더파일 선언

using namespace std;//이름공간에 std저장후 사용

int main(void)
{
	ifstream file;//파일 객체생성
	char str[50];//커맨드의 한 라인씩 받기위한 배열
	char filename[20];//파일 명을 받기위한 배열
	char f_num[20];//코드를 받기위한 배열

	memset(str,NULL,sizeof(str));//배열을 NULL로 초기화한다
	memset(filename,NULL,sizeof(filename));
	memset(f_num,NULL,sizeof(f_num));
	Manager Main; //매니저 객체 생성

	file.open("command.txt",ios::in);//command파일을 open 한다
	if( !(file.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	cout<<"Parcel Service Management System Start"<<endl;
	while( !(file.eof()) )//파일의 끝까지 반복한다
	{

		file.getline(str,50);//txt파일을 한줄씩 받는다 

		if(str[0]=='L')//명령어가 LOAD 라면
		{
			for(int i=0; ; i++)
			{
				if( (str[i]==' ') || (str[i]=='	') )//명령어뒤에 파일명을 받기위한 반복문
				{
					for(int j=0;  ; j++)
					{
						filename[j]=str[i+j+1];//filename 배열에 복사한다.
						if((str[i+j+1]=='\n') || (str[i+j+1]==NULL))
							break;
					}
					break;
				}
			}
			if( Main.LoadFile(filename) ) //Manager 클래스 LoadFile 함수 호출
				cout<<"파일로드에 성공하였습니다"<<endl;
			else
				cout<<"파일로드에 실패하였습니다"<<endl;
		}

		else if(str[0]=='F')//명령어가 FIND 라면
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
			if( Main.FIND(f_num) )//Manager 클래스 FIND 함수 호출
				cout<<"찾기에 성공하였습니다"<<endl;
			else
				cout<<"찾기에 실패하였습니다"<<endl;
		}
		//업데이트는 구현 하지 못하였습니다.
		/*else if(str[0]=='U')//명령어가 UPDATE 라면
		{
			for(int i=0; ; i++)
			{
				if( (str[i]==' ') || (str[i]=='	') )//명령어뒤에 파일명을 받기위한 반복문
				{
					for(int j=0;  ; j++)
					{
						filename[j]=str[i+j+1];//filename 배열에 복사한다.
						if((str[i+j+1]=='\n') || (str[i+j+1]==NULL))
							break;
					}
					break;
				}
			}
			if( Main.UPDATE(filename) )//Manager 클래스 LoadFile 함수 호출
				cout<<"업데이트에 성공하였습니다"<<endl;
			else
				cout<<"업데이트에 실패하였습니다"<<endl;
		}*/

		else if(str[0]=='S')//명령어가 SAVE 라면
		{
			for(int i=0; ; i++)
			{
				if( (str[i]==' ') || (str[i]=='	') )//명령어뒤에 파일명을 받기위한 반복문
				{
					for(int j=0;  ; j++)
					{
						filename[j]=str[i+j+1];//filename 배열에 복사한다.
						if((str[i+j+1]=='\n') || (str[i+j+1]==NULL))
							break;
					}
					break;
				}
			}
			if( Main.SAVE(filename) )//Manager 클래스 SAVE 함수 호출
				cout<<"저장에 성공하였습니다"<<endl;
			else
				cout<<"저장에 실패하였습니다"<<endl;
		}

		else if(str[0]=='P')//명령어가 PRINT 라면                    
		{
			if( Main.PRINT() )//Manager 클래스 PRINT 함수 호출
				cout<<"출력에에 성공하였습니다"<<endl;
			else
				cout<<"출력에 실패하였습니다"<<endl;
		}

		else if(str[0]=='E')//명령어가 EXIT 라면                         
		{
			if( Main.EXIT() )//Manager 클래스 EXIT 함수 호출
			{
				cout<<"종료에 성공하였습니다"<<endl;
				file.close();
				return 0;
			}
			else//실패하였다면
			{
				cout<<"종료에 실패하였습니다."<<endl;
			}
		}
		else //다른 명령어가 들어왔다면
			cout<<"명령어가 잘 못 입력 되어있습니다."<<endl;

		memset(str,NULL,sizeof(str)); //배열들을 NULL로 초기화 해준다
		memset(filename,NULL,sizeof(filename));
		memset(f_num,NULL,sizeof(f_num));

	}
	cout<<"Command 파일이 종료되었습니다."<<endl;//화면에 출력
	file.close();//파일을 닫아준다
	return 0;//함수 종료
}