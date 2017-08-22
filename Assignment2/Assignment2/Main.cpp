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
	char *File=NULL;
	char *File2=NULL;
	char *File3=NULL;//임시로 정보를 저장하기 위한 포인터 변수

	file.open("command.txt",ios::in);//command파일을 open 한다
	if( !(file.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	cout<<"<<<<<  KW Social Networking Service Start  >>>>>"<<endl;// 화면에 출력
	while( !(file.eof()) )//파일의 끝까지 반복한다
	{
		file.getline(str,100);//txt파일을 한줄씩 받는다 

		if( strncmp( str,"LOAD", sizeof(4) ) == 0 )//명령어가 LOAD 라면
		{
			File = strtok(str,"	 /");
			File = strtok(NULL,"	 /");
			File2 = strtok(NULL,"	 /");
			File3 = strtok(NULL,"	 /");//Load 해야 하는 파일명을 임시로 저장해둔다
			if( manager.Load_User(File) )//사용자 정보 로드가 성공 했다면
				cout<<"Load_User에 성공 하였습니다."<<endl;//화면에 출력
			else//사용자 정보 로드가 실패 했다면
				cout<<"Load_User에 실패 하였습니다."<<endl;//화면에 출력

			if( manager.Load_Friend(File2) )//친구 정보 로드가 성공 했다면
				cout<<"Load_Friend에 성공 하였습니다."<<endl;//화면에 출력
			else//친구 정보 로드가 실패 했다면
				cout<<"Load_Friend에 실패 하였습니다."<<endl;//화면에 출력

			if( manager.Load_Memo(File3) )//메모 정보 로드가 성공 했다면
				cout<<"Load_Memo에 성공 하였습니다."<<endl;//화면에 출력
			else//메모 정보 로드가 실패 했다면
				cout<<"Load_Memo에 실패 하였습니다."<<endl;//화면에 출력
		}

		else if(strncmp( str,"SAVE", sizeof(4) ) == 0)//명령어가 SAVE 라면
		{
			File = strtok(str,"	 /");
			File = strtok(NULL,"	 /");
			File2 = strtok(NULL,"	 /");
			File3 = strtok(NULL,"	 /");//Load 해야 하는 파일명을 임시로 저장해둔다
			if( manager.Save_User(File) )//사용자 정보 저장이 성공 했다면
				cout<<"Save_User에 성공 하였습니다."<<endl;//화면에 출력
			else//사용자 정보 저장이 실패 했다면
				cout<<"Save_User에 실패 하였습니다."<<endl;//화면에 출력

			if( manager.Save_Friend(File2) )//친구 정보 저장이 성공 했다면
				cout<<"Save_Friend에 성공 하였습니다."<<endl;//화면에 출력
			else//친구 정보 저장이 실패 했다면
				cout<<"Save_Friend에 실패 하였습니다."<<endl;//화면에 출력

			if( manager.Save_Memo(File3) )//메모 정보 저장이 성공 했다면
				cout<<"Save_Friend에 성공 하였습니다."<<endl;//화면에 출력
			else//메모 정보 저장이 실패 했다면
				cout<<"Save_Friend에 실패 하였습니다."<<endl;//화면에 출력
		}

		else if( strncmp( str,"FRNDLIST", sizeof(8) ) == 0)//명령어가 FRNDLIST 라면
		{
			File = strtok(str,"	 /");
			File = strtok(NULL,"	 /");//유저의 학번을 저장한다
			if( manager.FriendList(File) )//FriendList 함수 호출에 성공하였다면
				cout<<"FRNDLIST 출력에 성공 하였습니다."<<endl;//화면에 출력
			else//실패하였다면
				cout<<"FRNDLIST 출력에 실패 하였습니다."<<endl;//화면에 출력
		}
		
		else if( strncmp( str,"INTIMACY", sizeof(8) ) == 0)//명령어가 INTIMACY 라면                    
		{
			File = strtok(str,"	 /");
			File = strtok(NULL,"	 /");
			File2 = strtok(NULL,"	 /");//두명의 사용자 정보를 입력 받는다.
			if( manager.INTIMACY(File,File2) )//Manager 클래스 INTIMACY 함수 호출
				cout<<"INTIMACY 출력에 성공하였습니다"<<endl;//화면에 출력
			else//실패하였다면
				cout<<"INTIMACY 출력에 실패하였습니다"<<endl;//화면에 출력
		}
		
		else if( strncmp( str,"TIMELINE", sizeof(8) ) == 0 )//명령어가 TIMELINE 라면                         
		{
			File = strtok(str,"	 /");
			File = strtok(NULL,"	 /");
			if( manager.TimeLine(File) )//Manager 클래스 TIMELINE 함수 호출
				cout<<"TIMELINE 출력에 성공하였습니다"<<endl;//화면에 출력
			else//실패하였다면
				cout<<"TIMELINE 출력에 실패하였습니다"<<endl;//화면에 출력
		}

		else if( strncmp( str,"UPDATE", sizeof(6) ) == 0 )//명령어가 LOAD 라면
		{
			File = strtok(str,"	 /");
			File = strtok(NULL,"	 /");
			File2 = strtok(NULL,"	 /");
			File3 = strtok(NULL,"	 /");//Load 해야 하는 파일명을 임시로 저장해둔다

			if( manager.Update_User(File) )//사용자 정보 로드가 성공 했다면
				cout<<"Load_User에 성공 하였습니다."<<endl;//화면에 출력
			else//사용자 정보 로드가 실패 했다면
				cout<<"Load_User에 실패 하였습니다."<<endl;//화면에 출력

			if( manager.Update_Friend(File2) )//친구 정보 로드가 성공 했다면
				cout<<"Update_Friend에 성공 하였습니다."<<endl;//화면에 출력
			else//친구 정보 로드가 실패 했다면
				cout<<"Update_Friend에 실패 하였습니다."<<endl;//화면에 출력

			if( manager.Update_Memo (File3) )//메모 정보 로드가 성공 했다면
				cout<<"Load_Memo에 성공 하였습니다."<<endl;//화면에 출력
			else//메모 정보 로드가 실패 했다면
				cout<<"Load_Memo에 실패 하였습니다."<<endl;//화면에 출력
		}
		
		else if( strncmp( str,"EXIT", sizeof(4) ) == 0 )//명령어가 EXIT 라면                         
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
		File2=NULL;
		File3=NULL;
	}

	cout<<"Command 파일이 종료되었습니다."<<endl;//화면에 출력
	file.close();//파일을 닫아준다
	return 0;//함수 종료
}