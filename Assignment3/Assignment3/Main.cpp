#include "Manager.h"
#include<iostream>
#include<fstream>//해더파일 선언

using namespace std;//이름공간에 std저장후 사용

int main(void)
{
	Manager manager;//Manager 객체 생성
	ifstream file;//파일 객체생성

	char str[100];//커맨드의 한 라인씩 받기위한 배열
	memset(str,NULL,sizeof(str));//배열을 NULL로 초기화한다

	char *Cmd = NULL;
	char *File = NULL;
	char *File1 = NULL;
	char *File2 = NULL;
	char *File3 = NULL;
	char *File4 = NULL;//파일명을 받기위한 임시 포인터 변수

	file.open("cmd.txt",ios::in);//command파일을 open 한다
	if( !(file.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	for(int i=0;i<3;i++)//메모장에 필요 없는 라인을 지워준다
		file.getline(str,sizeof(str));
	memset(str,NULL,sizeof(str));//배열을 NULL로 초기화

	cout<<"<<<<<  KW heating maintenance Service Start  >>>>>"<<endl;// 화면에 출력
	while( !(file.eof()) )//파일의 끝까지 반복한다
	{
		file.getline(str,100);//txt파일을 한줄씩 받는다
		if(str[0]==NULL)//Enter가 나온다면 파일 종료
			break;

		File = strtok(str,"	 /");
		if( strcmp( File,"LOAD")  == 0 )//명령어가 LOAD 라면
		{
			File = strtok(NULL,"	 /");
			File1 = strtok(NULL,"	 /");
			File2 = strtok(NULL,"	 /");
			File3 = strtok(NULL,"	 /");
			File4 = strtok(NULL,"	 /");//Load 해야 하는 파일명을 임시로 저장해둔다

			if( manager.Load_gu(File, File1) )//동 정보 로드가 성공 했다면
				cout<<"Load_gu에 성공 하였습니다."<<endl;//화면에 출력
			else//동 정보 로드가 실패 했다면
				cout<<"Load_gu에 실패 하였습니다."<<endl;//화면에 출력

			if( manager.Load_dong(File2, File3) )//구 정보 로드가 성공 했다면
				cout<<"Load_dong에 성공 하였습니다."<<endl;//화면에 출력
			else//구 정보 로드가 실패 했다면
				cout<<"Load_dong에 실패 하였습니다."<<endl;//화면에 출력

			if( manager.Load_Mehanic(File4) )//기술자 정보 로드가 성공 했다면
				cout<<"Load_Mehanic에 성공 하였습니다."<<endl;//화면에 출력
			else//기술자 정보 로드가 실패 했다면
				cout<<"Load_Mehanic에 실패 하였습니다."<<endl;//화면에 출력
		}

		else if(strcmp( File,"UPDATE") == 0)//명령어가 UPDATE 라면
		{
			File = strtok(NULL,"	 /");//UPDATE할 파일명을 입력 받는다

			if( manager.Update(File) )//UPDETE에 성공 했다면
				cout<<"Dong_Edge_cost Update에 성공 하였습니다."<<endl;//화면에 출력
			else//UPDATE에 실패 했다면
				cout<<"Dong_Edge_cost Update에 실패 하였습니다."<<endl;//화면에 출력
		}

		else if(strcmp( File,"PIPE_REPAIR") == 0)//명령어가 PIPE_REPAIR 라면
		{
			File = strtok(NULL,"	 /");//수리할 구를 입력 받는다

			if( manager.Pipe_Repair(File) )//PIPE_REPAIR에 성공 했다면
				cout<<"Pipe_Repair에 성공 하였습니다."<<endl;//화면에 출력
			else//PIPE_REPAIR에 실패 했다면
				cout<<"Pipe_Repair에 실패 하였습니다."<<endl;//화면에 출력
		}

		else if(strcmp( File,"PIPE_BROKEN") == 0)//명령어가 PIPE_BROKEN 라면
		{
			File = strtok(NULL,"	 /");
			File1 = strtok(NULL,"	 /");
			File2 = strtok(NULL,"	 /");//구와 Edge 정보를 입력 받는다

			if( manager.Pipe_Broken(File, File1, File2) )//Pipe_Broken에 성공 했다면
				cout<<"Pipe_Broken에 성공 하였습니다."<<endl;//화면에 출력
			else//Pipe_Broken에 실패 했다면
				cout<<"Pipe_Broken에 실패 하였습니다."<<endl;//화면에 출력
		}

		else if(strcmp( File,"SAVE") == 0)//명령어가 SAVE 라면
		{
			if( manager.Save_Gu() )//구 정보 저장이 성공 했다면
				cout<<"Save_Gu에 성공 하였습니다."<<endl;//화면에 출력
			else//구 정보 저장이 실패 했다면
				cout<<"Save_Gu에 실패 하였습니다."<<endl;//화면에 출력

			if( manager.Save_Dong() )//동 정보 저장이 성공 했다면
				cout<<"Save_Dong에 성공 하였습니다."<<endl;//화면에 출력
			else//동 정보 저장이 실패 했다면
				cout<<"Save_Dong에 실패 하였습니다."<<endl;//화면에 출력

			if( manager.Save_Mechanic() )//정비사 정보 저장이 성공 했다면
				cout<<"Save_Mechanic에 성공 하였습니다."<<endl;//화면에 출력
			else//정비사 정보 저장이 실패 했다면
				cout<<"Save_Mechanic에 실패 하였습니다."<<endl;//화면에 출력
		}

		else if(strcmp( File,"PRINT") == 0)//명령어가 PRINT 라면
		{
			File = strtok(NULL,"	 /");//PRINT 세부 항목을 입력 받는다

			if( strcmp(File, "지도") == 0 )//지도 출력이라면
			{
				if( manager.Print_Map() )//Print_Map에 성공 했다면
					cout<<"Print_Map에 성공 하였습니다."<<endl;//화면에 출력
				else//Print_Map에 실패 했다면
					cout<<"Print_Map에 실패 하였습니다."<<endl;//화면에 출력
			}

			else if( strcmp(File, "정비사") == 0)//정비사 출력이라면
			{
				if( manager.Print_Mechanic() )//Print_Mechanic에 성공 했다면
					cout<<"Print_Mechanic에 성공 하였습니다."<<endl;//화면에 출력
				else//Print_Mechanic에 실패 했다면
					cout<<"Print_Mechanic에 실패 하였습니다."<<endl;//화면에 출력
			}

			else//그외 경우 동을 입력 받는다
			{
				if( manager.Print_Gu(File) )//Print_Gu에 성공 했다면
					cout<<"Print_Gu에 성공 하였습니다."<<endl;//화면에 출력
				else//Print_Gu에 실패 했다면
					cout<<"Print_Gu에 실패 하였습니다."<<endl;//화면에 출력
			}
		}

		else if( strcmp( File,"EXIT") == 0 )//명령어가 EXIT 라면                         
		{
			if( manager.EXIT() )//Manager 클래스 EXIT 함수 호출
			{
				cout<<"종료에 성공하였습니다"<<endl;
				file.close();
				return 0;
			}
			else//실패하였다면
				cout<<"종료에 실패하였습니다."<<endl;//화면에 출력
		}

		else //다른 명령어가 들어왔다면
			cout<<"명령어가 잘 못 입력 되어있습니다."<<endl;//화면에 출력
		memset(str,NULL,sizeof(str)); //배열들을 NULL로 초기화 해준다

		File=NULL;
		File1=NULL;
		File2=NULL;
		File3=NULL;
		File4=NULL;
	}

	cout<<"Command 파일이 종료되었습니다."<<endl;//화면에 출력
	file.close();//파일을 닫아준다
	return 0;//함수 종료
}