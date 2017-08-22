#include "Manager.h"
#include <iostream>
#include <fstream>//헤더파일 선언

using namespace std;//이름 공간에 std 저장후 사용

Manager::Manager(void)//생성자
{
}

Manager::~Manager(void)//소멸자
{
}

bool Manager::Load_User(char *file)//유저 정보를 load하기 위한 함수
{
	EXIT();//초기화
	avl.~AVL();

	ifstream fin;//파일 스트림 형성
	User *user=NULL;
	char str[200];//한줄씩 받기 위한 배열 선언
	memset(str,NULL,sizeof(str));//배열 초기화

	char *temp1 = NULL;
	char *temp2 = NULL;//문자열을 짜르기 위한 char형 임시 포인터 선언

	fin.open(file,ios::in);//입력 받은 파일명으로 파일을 읽기 모드로 열어준다
	if( !(fin.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	for(int i=0;i<3;i++)//메모장에 필요 없는 라인을 지워준다
		fin.getline(str,sizeof(str));
	memset(str,NULL,sizeof(str));//배열을 NULL로 초기화

	while( !(fin.eof()) )//파일의 끝까지 반복한다
	{
		fin.getline(str,sizeof(str));//파일에서 한줄을 받아온다

		temp1 = strtok(str,"	 /");//학번을 짜른다
		temp2 = strtok(NULL,"	 /");//이름을 짜른다

		User *check = avl.NumSearch(temp1);//해당 학번을 가지고 있는 유저가 있는지 조사한다
		if(check == NULL)//저장된 유저가 아니라면
		{
			user = new User();//User 노드 메모리 할당
			user->SetNumber(temp1);//User Node에 학번을 저장한다
			user->SetName(temp2);//User Node에 이름을 저장한다
			if( !(avl.NameAVL(user)) )//Name AVL insert 호출
			{
				cout<<"AVL insert에 실패하였습니다."<<endl;//실패했다면 문구 출력
				return false;//거짓반환
			}
			if( !(avl.NumberAVL(user)) )//Number AVL insert 호출
			{
				cout<<"AVL insert에 실패하였습니다."<<endl;//실패했다면 문구 출력
				return false;//거짓 반환
			}
		}
		else//이미 저장된 유저라면
		{
			cout<<"이미 존재하는 유저의 정보 입니다."<<endl;//해당 문구 출력
		}
		check = NULL;
		temp1=NULL;//temp를 NULL로 초기화
		temp2=NULL;//temp2를 NULL로 초기화 한다
		memset(str,NULL,sizeof(str));//배열들을 NULL로 초기화한다
	}

	fin.close();//파일을 닫아준다
	return true;//참반환
}

bool Manager::Load_Friend(char *file)//친구 정보를 load하기 위한 함수
{
	ifstream fin;//파일 스트림 형성
	char str[200];//한줄씩 받기 위한 배열 선언
	memset(str,NULL,sizeof(str));//배열 초기화

	User *MeNode = NULL;//임시 포인터 선언
	User *FriNode = NULL;

	char *Me = NULL;
	char *Fri = NULL;//문자열을 짜르기 위한 char형 임시 포인터 선언

	fin.open(file,ios::in);//입력 받은 파일명으로 파일을 읽기 모드로 열어준다
	if( !(fin.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	for(int i=0;i<3;i++)//메모장에 필요 없는 라인을 지워준다
		fin.getline(str, sizeof(str));
	memset(str, NULL, sizeof(str));//배열을 NULL로 초기화

	while( !(fin.eof()) )//파일의 끝까지 반복한다
	{
		fin.getline(str,sizeof(str));//파일에서 한줄을 받아온다

		Me = strtok(str,"	 /");//나의 학번을 저장한다
		Fri = strtok(NULL,"	 /");//친구의 학번을 저장한다

		MeNode = avl.NumSearch(Me);
		FriNode = avl.NumSearch(Fri);//해당하는 학번의 노드를 찾아준다

		if( (MeNode == NULL) || (FriNode == NULL) )//찾는 노드가 없다면 해당문구 출력후 거짓 반환
		{
			cout<<"해당하는 학번의 사용자가 없습니다."<<endl;
			return false;
		}
		else//찾는 노드가 있다면 2DList insert 함수 호출한다.
		{
			if( List.SearchFri(MeNode, FriNode) )//친구중 존재한다면
			{
				cout<<"이미 존재하는 친구 입니다."<<endl;
			}
			else
			{
				if( !(List.Insert(MeNode, FriNode)) )//insert에 실패하였다면
				{
					cout<<"친구 연결에 실패 하였습니다."<<endl;//해당문구 출력 거짓 반환
					return false;
				}
			}
		}

		MeNode = NULL;
		FriNode = NULL;
		Me=NULL;
		Fri=NULL;//임시 변수들을 NULL로 초기화 시켜준다
		memset(str,NULL,sizeof(str));//배열들을 NULL로 초기화한다
	}

	fin.close();
	return true;//파일을 닫아주고 true 반환
}

bool Manager::Load_Memo(char *file)//메모 정보를 load하기 위한 함수
{
	ifstream fin;//파일 스트림 형성
	char str[400];//한줄씩 받기 위한 배열 선언
	memset(str,NULL,sizeof(str));

	User *MeNode = NULL;
	MemoNode *mNode = NULL;//메모와 사용자를 위한 포인터객체 생성

	char *me = NULL;
	char *time = NULL;
	char *memo = NULL;//문자열을 짜르기 위한 char형 임시 포인터 선언

	fin.open(file,ios::in);//입력 받은 파일명으로 파일을 읽기 모드로 열어준다
	if( !(fin.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	for(int i=0;i<3;i++)//메모장에 필요 없는 라인을 지워준다
		fin.getline(str,sizeof(str));
	memset(str,NULL,sizeof(str));//배열을 NULL로 초기화

	while( !(fin.eof()) )//파일의 끝까지 반복한다
	{
		fin.getline(str,sizeof(str));//파일에서 한줄을 받아온다

		me = strtok(str,"	/");//나의 학번을 저장한다
		time = strtok(NULL,"	/");//시간메을 저장한다
		memo = strtok(NULL,"	/");//메모를 저장한다
		MeNode = avl.NumSearch(me);

		if(MeNode == NULL)//찾는 노드가 없다면 해당문구 출력후 거짓 반환
		{
			cout<<"해당하는 학번의 사용자가 없습니다."<<endl;
			return false;
		}
		else//찾는 노드가 있다면 메모노드 생성후 저장 하고 메모 연결 노드를 호출한다
		{
			if((time!=NULL) && (memo !=NULL))//메모에 내용과 시간이 존재 한다면
			{
				if( !(Line.MemoSearch(MeNode, time)) )//같은 메모가 존재 하지않는다면
				{
					mNode = new MemoNode();//memo노드 생성한다

					strcpy(memo,ALARM(MeNode, memo, time));//ALARM 함수 호출을 통해 메모내용을 수정해준다
					mNode->SetTime(time);
					mNode->SetWrite(memo);//메모 노드에 정보를 저장한다
					mNode->SetWho(MeNode->GetName());

					if( !(Line.MemoInsert(MeNode, mNode)) )//insert에 실패하였다면
					{
						cout<<"메모 연결에 실패 하였습니다."<<endl;//해당문구 출력 거짓 반환
						return false;
					}
				}
			}
		}

		MeNode = NULL;
		me = NULL;
		time = NULL;
		memo = NULL;//임시 변수들을 NULL로 초기화 시켜준다
		memset(str,NULL,sizeof(str));//배열들을 NULL로 초기화한다
	}

	fin.close();
	return true;//파일을 닫아주고 true 반환
}

char *Manager::ALARM(User *mNode, char *before, char *time)//알람 함수
{
	char str[200];
	memset(str,NULL,sizeof(str) );//메모정보를 위한 배열                           
	strncpy( str, before, sizeof(str) );
	User *FriNode = NULL;
	Linked *del = mNode->GetFri();//탈퇴여부를 파악하기 위한 임시 포인터 변수

	if(del != NULL)//친구가 존재한다면
	{
		while(del !=NULL)//탈퇴여부 flag가 1인 친구를 찾아서 지워주는 코드이다
		{
			if( ((del->GetDown())->GetCheckDelete()) == 1 )
			{
				if( !(List.DeleteFrt(mNode, del->GetDown()) ) )//친구 삭제에 실패 하였다면
					cout<<"친구 삭제에 실패하였습니다."<<endl;//문구 출력
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
	memset(FriName4, NULL ,sizeof(FriName4));//알람을 해야되는 친구들의 이름을 저장하기 위한 배열 선언

	int i=0;
	int check = 0;//동명이인 check 변수
	int Number = 0;//친구 명수 check 변수
	while(str[i] !=NULL )//메모내용을 검사한다
	{
		if( (str[i]=='@') && (str[i+7]==';') && (Number==0) )//메모의 내용이 친구 형태고 태그한 친구가 없다면
		{
			check = 0;
			FriName1[0]=str[i+1];
			FriName1[1]=str[i+2];
			FriName1[2]=str[i+3];
			FriName1[3]=str[i+4];
			FriName1[4]=str[i+5];
			FriName1[5]=str[i+6];//메모에 저장되어있는 사람이름을 친구 배열에 일단 저장한다

			if(avl.CheckSameName(FriName1))//동명이인이 있는지 체크한다
			{
				check = List.SearchFri(mNode, FriName1);//동명이인이 존재 한다면 
				//이함수를 호출하면 동명이인 친구 두명이 나와 서로친구인지 확인한다
			}
			else//동명이인이 없다면
			{
				FriNode = avl.NameSearch(FriName1);//해당이름을 가지는 노드를 찾는다
				if(FriNode != NULL)//유저 노드가 존재한다면
				{
					if( List.SearchFri(FriNode, mNode) )//서로친구인지 확인한다
						check =1;
				}
			}

			if(check == 1 || check == 2)//서로 친구인 친구가 존재한다면
			{
				if(check==2)//서로친구인 친구가 동명이인 둘다라면
				{
					FriName1[6]=' ';
					FriName1[7]=str[i+1];
					FriName1[8]=str[i+2];
					FriName1[9]=str[i+3];
					FriName1[10]=str[i+4];
					FriName1[11]=str[i+5];
					FriName1[12]=str[i+6];//친구 이름을 한번더 적어준다.
				}
				int j=0;
				str[i]=FriName1[0];
				str[i+1]=FriName1[1];
				str[i+2]=FriName1[2];
				str[i+3]=FriName1[3];
				str[i+4]=FriName1[4];
				str[i+5]=FriName1[5];// @ , ; 이부분을 제외한 이름만 다시 저장한다
				while(str[j+8] !=NULL)//메모 배열을 다시 저장해준다
				{
					str[i+6+j]=str[i+8+j];
					j++;
				}
				str[i+6+j]=NULL;//NULL을 넣어준다
				i=i+6;//i는 그 다음으로 초기화해준다
				FriNode = NULL;//친구 노드 초기화
				Number++;//태그 명수 증가
			}
			else//친구가 아니라면
			{
				i++;
				memset(FriName1, NULL, sizeof(FriName1) );//친구가 아니기때문에 배열초기화
				continue;
			}
		}

		else if( (str[i]=='@') && (str[i+7]==';') && (Number==1) )//메모의 내용이 친구 형태고 태그한 친구가 1명있다면
		{
			check =0;
			FriName2[0]=str[i+1];
			FriName2[1]=str[i+2];
			FriName2[2]=str[i+3];
			FriName2[3]=str[i+4];
			FriName2[4]=str[i+5];
			FriName2[5]=str[i+6];//메모에 저장되어있는 사람이름을 친구 배열에 일단 저장한다

			if(avl.CheckSameName(FriName2))//동명이인이 있는지 체크한다
			{
				check = List.SearchFri(mNode, FriName2);//동명이인이 존재 한다면 
				//이함수를 호출하면 동명이인 친구 두명이 나와 서로친구인지 확인한다
			}
			else//동명이인이 없다면
			{
				FriNode = avl.NameSearch(FriName2);//해당이름을 가지는 노드를 찾는다
				if(FriNode != NULL)//유저 노드가 존재한다면
				{
					if( List.SearchFri(FriNode, mNode) )//서로친구인지 확인한다
						check =1;
				}
			}

			if(check == 1 || check == 2)//친구가존재한다면
			{
				if(check==2)//동명이인이 존재한다면
				{
					FriName2[6]=' ';
					FriName2[7]=str[i+1];
					FriName2[8]=str[i+2];
					FriName2[9]=str[i+3];
					FriName2[10]=str[i+4];
					FriName2[11]=str[i+5];
					FriName2[12]=str[i+6];//친구 이름을 한번더 저장해준다
				}
				int j=0;
				str[i]=FriName2[0];
				str[i+1]=FriName2[1];
				str[i+2]=FriName2[2];
				str[i+3]=FriName2[3];
				str[i+4]=FriName2[4];
				str[i+5]=FriName2[5]; // @ , ; 이부분을 제외한 이름만 다시 저장한다
				while(str[j+8] != NULL)//메모 배열을 다시 저장해준다
				{
					str[i+j+6]=str[i+j+8];
					j++;
				}
				str[i+6+j]=NULL;//NULL을 넣어준다
				i=i+6;//i는 그 다음으로 초기화해준다
				FriNode = NULL;//친구 노드 초기화
				Number++;//태그 명수 증가
			}
			else//친구가 아니라면
			{
				i++;
				memset(FriName2,NULL,sizeof(FriName2)); //친구가 아니기때문에 배열초기화
				continue;
			}
		}

		else if( (str[i]=='@') && (str[i+7]==';') && (Number==2) )//메모의 내용이 친구 형태고 태그한 친구가 2명있다면
		{
			check =0;
			FriName3[0]=str[i+1];
			FriName3[1]=str[i+2];
			FriName3[2]=str[i+3];
			FriName3[3]=str[i+4];
			FriName3[4]=str[i+5];
			FriName3[5]=str[i+6];//메모에 저장되어있는 사람이름을 친구 배열에 일단 저장한다

			if(avl.CheckSameName(FriName3))//동명이인이 있는지 체크한다
			{
				check = List.SearchFri(mNode, FriName3);//동명이인이 존재 한다면 
				//이함수를 호출하면 동명이인 친구 두명이 나와 서로친구인지 확인한다
			}
			else//동명이인이 없다면
			{
				FriNode = avl.NameSearch(FriName3);//해당이름을 가지는 노드를 찾는다
				if(FriNode != NULL)//유저 노드가 존재한다면
				{
					if( List.SearchFri(FriNode, mNode) )//서로친구인지 확인한다
						check =1;
				}
			}

			if(check == 1 || check == 2)//친구가 존재한다면
			{
				if(check==2)//동명이인이 존재한다면
				{
					FriName3[6]=' ';
					FriName3[7]=str[i+1];
					FriName3[8]=str[i+2];
					FriName3[9]=str[i+3];
					FriName3[10]=str[i+4];
					FriName3[11]=str[i+5];
					FriName3[12]=str[i+6];//친구 이름을 한번더 저장해준다
				}
				int j=0;
				str[i]=FriName3[0];
				str[i+1]=FriName3[1];
				str[i+2]=FriName3[2];
				str[i+3]=FriName3[3];
				str[i+4]=FriName3[4];
				str[i+5]=FriName3[5];// @ , ; 이부분을 제외한 이름만 다시 저장한다
				while(str[j+8] !=NULL)//메모 배열을 다시 저장해준다
				{
					str[j+i+6]=str[i+j+8];
					j++;
				}
				str[i+6+j]=NULL;//NULL을 넣어준다
				i=i+6;//i는 그 다음으로 초기화해준다
				FriNode = NULL;//친구 노드 초기화
				Number++;//태그 명수 증가
			}
			else//친구가 아니라면
			{
				i++;
				memset(FriName3,NULL,sizeof(FriName3));//친구가 아니기때문에 배열초기화
				continue;
			}
		}

		else if( (str[i]=='@') && (str[i+7]==';') && (Number==3) )//메모의 내용이 친구 형태고 태그한 친구가 3명있다면
		{
			check =0;
			FriName4[0]=str[i+1];
			FriName4[1]=str[i+2];
			FriName4[2]=str[i+3];
			FriName4[3]=str[i+4];
			FriName4[4]=str[i+5];
			FriName4[5]=str[i+6];//메모에 저장되어있는 사람이름을 친구 배열에 일단 저장한다

			if(avl.CheckSameName(FriName4))//동명이인이 있는지 체크한다
			{
				check = List.SearchFri(mNode, FriName4);//동명이인이 존재 한다면 
				//이함수를 호출하면 동명이인 친구 두명이 나와 서로친구인지 확인한다
			}
			else//동명이인이 없다면
			{
				FriNode = avl.NameSearch(FriName4);//해당이름을 가지는 노드를 찾는다
				if(FriNode != NULL)//유저 노드가 존재한다면
				{
					if( List.SearchFri(FriNode, mNode) )//서로친구인지 확인한다
						check =1;
				}
			}

			if(check == 1 || check == 2)//친구가 존재한다면
			{
				if(check==2)//동명이인이 존재한다면
				{
					FriName4[6]=' ';
					FriName4[7]=str[i+1];
					FriName4[8]=str[i+2];
					FriName4[9]=str[i+3];
					FriName4[10]=str[i+4];
					FriName4[11]=str[i+5];
					FriName4[12]=str[i+6];//친구이름을 한번더 저장해준다
				}
				int j=0;
				str[i]=FriName4[0];
				str[i+1]=FriName4[1];
				str[i+2]=FriName4[2];
				str[i+3]=FriName4[3];
				str[i+4]=FriName4[4];
				str[i+5]=FriName4[5];// @ , ; 이부분을 제외한 이름만 다시 저장한다
				while(str[j+8] !=NULL)//메모 배열을 다시 저장해준다
				{
					str[i+j+6]=str[i+j+8];
					j++;
				}
				str[i+6+j]=NULL;//NULL을 넣어준다
				i=i+6;//i는 그 다음으로 초기화해준다
				FriNode =NULL;
				Number++;//태그명수 증가
			}
			else//친구가 아니라면
			{
				i++;
				memset(FriName4,NULL,sizeof(FriName4));//친구가 아니라면 배열을 초기화 해준다
				continue;
			}
		}

		else//태그 형태가 아니라면
		{
			i++;//i 증가
			continue;
		}
	}

	if(Number!=0)//태그된 친구가 있다면
	{
		ofstream f("alarm.txt",ios_base::app);//alarm.txt 파일객체 생성과 동시에 file open
		f<<time<<"	/	"<<mNode->GetName()<<"	->	";//파일에 출력

		if(Number==1)//태그된 친구가 한명이라면
			f<<FriName1<<endl;//파일에 출력
		else if(Number==2)//태그된 친구가 두명이라면
			f<<FriName1<<"	"<<FriName2<<endl;//파일에 출력
		else if(Number==3)//태그된 친구가 세명이라면
			f<<FriName1<<"	"<<FriName2<<"	"<<FriName3<<endl;//파일에 출력
		else if(Number==4)//태그된 친구가 네명이라면
			f<<FriName1<<"	"<<FriName2<<"	"<<FriName3<<"	"<<FriName4<<endl;//파일에 출력

		f.close();//파일을 닫아준다
	}
	return str;//수정한 메모를 반환한다.
}

bool Manager::FriendList(char *num)//FriendList 함수
{
	ofstream f("friend_list.txt",ios_base::app);//friend_list.txt파일을 열어준다.
	User *MeNode = avl.NumSearch(num);//해당하는 학번으로 사용자를 찾아준다.
	int i=0;

	if(MeNode == NULL)//해당하는 학번의 사용자가 없다면
	{
		for(i=0; i<21;i++)
			f<<"==";
		f<<endl<<num<<" 유저에 대한 데이터가 없습니다."<<endl;
		for(i=0; i<21;i++)
			f<<"==";//다음 문구를 파일에 적어주고 함수 종료 한다.
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
	//파일에 출력해줘야 하는 문구 출력
	Linked *temp = MeNode->GetFri();//친구 연결 List의 head를 temp에 저장한다

	if(temp==NULL)//친구가 존재 하지 않는다면
	{
		f.close();//파일을 닫아준다
		return true;
	}

	while(temp !=NULL)//탈퇴여부 flag가 1인 친구를 찾아서 지워주는 코드이다
	{
		if( ((temp->GetDown())->GetCheckDelete()) == 1 )
		{
			if( !(List.DeleteFrt(MeNode, temp->GetDown()) ) )//연결을 끊어준다
				cout<<"친구 삭제에 실패하였습니다."<<endl;//실패시 문구 출력
		}
		temp = temp->GetNext();
	}

	temp = MeNode->GetFri();
	User *Friend = NULL;//친구 노드를 저장하기위한 User 포인터변수
	while(temp != NULL)//친구 끝까지 반복한다
	{
		Friend = temp->GetDown();//친구 노드를 저장한다.
		if( List.SearchFri(Friend, MeNode) )//친구가 날 친구로 생각하는지 확인한다
			f<<Friend->GetName()<<"씨는 나와 친구 입니다."<<endl;//해당 문구 출력
		else//서로 친구 사이가 아니라면
			f<<Friend->GetName()<<"씨는 나만 친구 입니다."<<endl;//해당 문구 출력

		temp = temp->GetNext();//다음 친구를 가리키게 한다
	}

	f.close();//파일을 닫아준다
	return true;//참반환
}

bool Manager::INTIMACY(char *me, char *target)//INTIMACY함수
{
	User *MeNode = NULL;
	User *TargetNode1 = NULL;
	User *TargetNode2 = NULL;
	User *Friend = NULL;//사용자 노드를 저장하기위한 임시포인터 변수

	if( (me[0]>='0' && me[0]<='9') && ( target[0]>= '0' && target[0]<='9') )//입력받은 인자가 모두 학번이라면
	{
		MeNode = avl.NumSearch(me);
		TargetNode1 = avl.NumSearch(target);//학번으로 유저 노드를 찾아준다
		if( (MeNode == NULL) || (TargetNode1 == NULL) )//하나의 노드라도 해당하는 학번을 찾지 못한다면
		{
			cout<<"해당하는 학번의 사용자를 찾을 수 없습니다."<<endl;
			return false;//해당문구 출력 거짓 반환
		}
	}

	else//이름이 끼여 있다면
	{
		if( avl.CheckSameName(target) )//동명이인이 있는지 check 하는 함수를 호출한다
		{
			MeNode = avl.NumSearch(me);
			TargetNode1 = avl.NameSearch(target);
			TargetNode2 = avl.NameSearch(target, TargetNode1->GetNumber() );
			//나에대한 정보와 동명이인 두명의 정보를 모두 찾아 유저 노드에 저장한다
			if( (MeNode == NULL) || (TargetNode1 == NULL) || ((TargetNode2 == NULL)) )//하나의 노드라도 해당하는 유저정보를 찾지 못한다면
			{
				cout<<"해당하는 학번의 사용자를 찾을 수 없습니다."<<endl;
				return false;//해당문구 출력 거짓 반환
			}
		}
		else//동명이인이 존재 하지 않는다면
		{
			MeNode = avl.NumSearch(me);
			TargetNode1 = avl.NameSearch(target);//학번으로 해당하는 유저 정보를 찾아준다
			if( (MeNode == NULL) || (TargetNode1 == NULL) )//하나의 노드라도 해당하는 학번을 찾지 못한다면
			{
				cout<<"해당하는 학번의 사용자를 찾을 수 없습니다."<<endl;
				return false;//해당문구 출력 거짓 반환
			}
		}
	}
	int intimacy1, intimacy2;//관계를 확인 하기 위한 int형 변수

	if(TargetNode2 == NULL)//동명이인이 없다면
	{
		ofstream f("intimacy.txt",ios_base::app);//intimacy.txt파일을 열어준다.
		Linked *temp = MeNode->GetFri();//나의 친구 연결리스트 반환

		if(temp==NULL)//친구가 존재 하지 않는다면
		{
			f.close();//파일을 닫아준다
			return true;
		}

		while(temp !=NULL)//탈퇴여부 flag가 1인 친구를 찾아서 지워주는 코드이다
		{
			if( ((temp->GetDown())->GetCheckDelete()) == 1 )
			{
				if( !(List.DeleteFrt(MeNode, temp->GetDown()) ) )//친구 연결을 끊어준다
					cout<<"친구 삭제에 실패하였습니다."<<endl;//해당문구출력
			}
			temp = temp->GetNext();
		}
		temp = MeNode->GetFri();//temp 다시 지정


		Linked *temp2 = TargetNode1->GetFri();//타깃 친구 연결리스트 반환
		if(temp2==NULL)//친구가 존재 하지 않는다면
		{
			f.close();//파일을 닫아준다
			return true;
		}

		while(temp2 != NULL)//탈퇴여부 flag가 1인 친구를 찾아서 지워주는 코드이다
		{
			if( ((temp2->GetDown())->GetCheckDelete()) == 1 )
			{
				if( !(List.DeleteFrt(TargetNode1, temp2->GetDown()) ) )//친구 연결을 끊어준다
					cout<<"친구 삭제에 실패하였습니다."<<endl;//해당문구 출력
			}
			temp2 = temp2->GetNext();
		}
		temp2 = TargetNode1->GetFri();//temp 다시 지정


		while(temp != NULL)//나의 친구 끝까지 반복한다
		{
			Friend = temp->GetDown();
			temp2 = TargetNode1->GetFri();
			while(temp2 != NULL)//타깃의 친구 끝까지 반복한다
			{
				if( strcmp(Friend->GetNumber(), (temp2->GetDown())->GetNumber() )==0 )//동일한 친구가 존재한다면
				{
					intimacy1 = List.SearchFri(Friend, MeNode);
					intimacy2 = List.SearchFri(Friend,TargetNode1);
					//관계 확인 함수를 호출해서 동일한 친구가 나와 타깃을 어떻게 생각하는지 확인한다
					if((intimacy1 ==1) && (intimacy2 ==1) )//S<-->F<-->D
						f<<MeNode->GetName()<<"와 "<<TargetNode1->GetName()<<"은 "<<Friend->GetName()<<"를 통한 친구 관계입니다."<<endl;
					//파일에 출력
					else if((intimacy1 ==0) && (intimacy2 ==0))//S->F<-D
						f<<MeNode->GetName()<<"와 "<<TargetNode1->GetName()<<"은 "<<Friend->GetName()<<"를 통한 어색한 관계입니다."<<endl;
					//파일에 출력
					else//S<-->F<-D OR //S->F<-->D
						f<<MeNode->GetName()<<"와 "<<TargetNode1->GetName()<<"은 "<<Friend->GetName()<<"를 통한 괜찮은 관계입니다."<<endl;
					intimacy1 = 0;
					intimacy2 = 0;//관계를 확인 하기 위한 int형 변수 초기화
				}
				temp2 = temp2->GetNext();//타깃의 다음친구를 가리킨다
			}
			temp = temp->GetNext();//나의 다음친구를 가리킨다
		}

		f.close();//파일을 닫아준다
		return true;//참반환
	}

	else//동명이인 있다
	{
		ofstream f("intimacy.txt",ios_base::app);//intimacy.txt파일을 열어준다.
		Linked *temp = MeNode->GetFri();//나의 친구 연결리스트 반환

		if(temp==NULL)//친구가 존재 하지 않는다면
		{
			f.close();//파일을 닫아준다
			return true;
		}

		while(temp !=NULL)//탈퇴여부 flag가 1인 친구를 찾아서 지워주는 코드이다
		{
			if( ((temp->GetDown())->GetCheckDelete()) == 1 )
			{
				if( !(List.DeleteFrt(MeNode, temp->GetDown()) ) )//친구 연결을 끊어준다
					cout<<"친구 삭제에 실패하였습니다."<<endl;//해당문구 출력
			}
			temp = temp->GetNext();
		}
		temp = MeNode->GetFri();//temp 다시 지정


		Linked *temp2 = TargetNode1->GetFri();//타겟1의 친구 연결리스트 반환
		if(temp2==NULL)//친구가 존재 하지 않는다면
		{
			f.close();//파일을 닫아준다
			return true;
		}
		while(temp2 !=NULL)
		{
			if( ((temp2->GetDown())->GetCheckDelete()) == 1 )//탈퇴여부 flag가 1인 친구를 찾아서 지워주는 코드이다
			{
				if( !(List.DeleteFrt(TargetNode1, temp2->GetDown()) ) )//친구 연결을 끊어준다
					cout<<"친구 삭제에 실패하였습니다."<<endl;//해당문구 출력
			}
			temp2 = temp2->GetNext();
		}
		temp2 = TargetNode1->GetFri();//temp2 다시 지정




		while(temp != NULL)//나의 친구 끝까지 반복한다
		{
			Friend = temp->GetDown();
			temp2 = TargetNode1->GetFri();
			while(temp2 != NULL)//타깃의 친구 끝까지 반복한다
			{
				if( strcmp(Friend->GetNumber(), (temp2->GetDown())->GetNumber() )==0 )//동일한 친구가 존재한다면
				{
					intimacy1 = List.SearchFri(Friend, MeNode);
					intimacy2 = List.SearchFri(Friend, TargetNode1);
					//관계 확인 함수를 호출해서 동일한 친구가 나와 타깃을 어떻게 생각하는지 확인한다
					if((intimacy1 ==1) && (intimacy2 ==1) )//S<-->F<-->D
						f<<MeNode->GetName()<<"와 "<<TargetNode1->GetName()<<"("<<TargetNode1->GetNumber()<<")은 "<<Friend->GetName()<<"를 통한 친구 관계입니다."<<endl;
					//파일에 출력
					else if((intimacy1 ==0) && (intimacy2 ==0))//S->F<-D
						f<<MeNode->GetName()<<"와 "<<TargetNode1->GetName()<<"("<<TargetNode1->GetNumber()<<")은 "<<Friend->GetName()<<"를 통한 어색한 관계입니다."<<endl;
					//파일에 출력
					else//S<-->F<-D OR //S->F<-->D
						f<<MeNode->GetName()<<"와 "<<TargetNode1->GetName()<<"("<<TargetNode1->GetNumber()<<")은 "<<Friend->GetName()<<"를 통한 괜찮은 관계입니다."<<endl;
					//파일에 출력
					intimacy1 = 0;
					intimacy2 = 0;//관계를 확인 하기 위한 int형 변수 초기화
				}
				temp2 = temp2->GetNext();//타깃의 다음친구를 가리킨다
			}
			temp = temp->GetNext();//나의 다음친구를 가리킨다
		}

		temp = MeNode->GetFri();//나의 친구 연결리스트 반환
		temp2 = TargetNode2->GetFri();//타깃2의 친구 연결리스트 반환
		if(temp2==NULL)//친구가 존재 하지 않는다면
		{
			f.close();//파일을 닫아준다
			return true;
		}
		while(temp2 !=NULL)
		{
			if( ((temp2->GetDown())->GetCheckDelete()) == 1 )//탈퇴여부 flag가 1인 친구를 찾아서 지워주는 코드이다
			{
				if( !(List.DeleteFrt(TargetNode2, temp2->GetDown()) ) )//친구 연결을 끊어준다
					cout<<"친구 삭제에 실패하였습니다."<<endl;//해당문구 출력
			}
			temp2 = temp2->GetNext();
		}
		temp2 = TargetNode2->GetFri();//temp2 다시 지정


		while(temp != NULL)//나의 친구 끝까지 반복한다
		{
			Friend = temp->GetDown();
			temp2 = TargetNode2->GetFri();
			while(temp2 != NULL)//타깃의 친구 끝까지 반복한다
			{
				if( strcmp(Friend->GetNumber(), (temp2->GetDown())->GetNumber() )==0 )//동일한 친구가 존재한다면
				{
					intimacy1 = List.SearchFri(Friend, MeNode);
					intimacy2 = List.SearchFri(Friend, TargetNode2);
					//관계 확인 함수를 호출해서 동일한 친구가 나와 타깃을 어떻게 생각하는지 확인한다
					if((intimacy1 ==1) && (intimacy2 ==1) )//S<-->F<-->D
						f<<MeNode->GetName()<<"와 "<<TargetNode2->GetName()<<"("<<TargetNode2->GetNumber()<<")은 "<<Friend->GetName()<<"를 통한 친구 관계입니다."<<endl;
					//파일에 출력
					else if((intimacy1 ==0) && (intimacy2 ==0))//S->F<-D
						f<<MeNode->GetName()<<"와 "<<TargetNode2->GetName()<<"("<<TargetNode2->GetNumber()<<")은 "<<Friend->GetName()<<"를 통한 어색한 관계입니다."<<endl;
					//파일에 출력
					else//S<-->F<-D OR //S->F<-->D
						f<<MeNode->GetName()<<"와 "<<TargetNode2->GetName()<<"("<<TargetNode2->GetNumber()<<")은 "<<Friend->GetName()<<"를 통한 괜찮은 관계입니다."<<endl;
					//파일에 출력
					intimacy1 = 0;
					intimacy2 = 0;//관계를 확인 하기 위한 int형 변수 초기화
				}
				temp2 = temp2->GetNext();//타깃의 다음친구를 가리킨다
			}
			temp = temp->GetNext();//나의 다음친구를 가리킨다
		}

		f.close();//파일을 닫아준다
		return true;//참반환
	}
}

bool Manager::Save_User(char *file)//유저 저장 함수
{
	User *pCur = avl.GetNameRoot();

	ofstream ff(file,ios::out);//입력 받은 파일명으로 객체ff 생성
	if( !(ff.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	if( pCur ==NULL )//AVL 저장되어있는 정보가 없다면
	{
		cout<<"저장하고자 하는 정보가 없습니다."<<endl;
		return false;//위에문구 출력과 false 반환
	}

	for(int k=0;k<30;k++)
		ff<<"=";
	ff<<endl;
	ff<<"	학번	/	이름	"<<endl;
	for(int k=0;k<30;k++)
		ff<<"=";
	ff<<endl;//해당 문구를 파일에 출력해준다.

	while(pCur != NULL) //AVL 정보를 출력해주기 위한 while문
	{
		if( (Que.IsEmpty()) && (pCur !=avl.GetNameRoot() ) )//마지막 라인이라면
			ff<<pCur->GetNumber()<<"	/	"<<pCur->GetName();

		else//마지막 라인이 아니라면
			ff<<pCur->GetNumber()<<"	/	"<<pCur->GetName()<<endl;

		if( pCur->GetNameLeft() !=NULL)
			Que.Push( pCur->GetNameLeft() );

		if( pCur->GetNameRight() !=NULL )
			Que.Push( pCur->GetNameRight() );

		if( Que.IsEmpty() )//que가 비어있다면 
			break;//while문 종료
		pCur = Que.Pop();// current는 que에서 pop 해준다
	}
	ff.close();//파일을 닫아준다
	return true;//참반환
}

bool Manager::Save_Friend(char *file)//Save_Friend 함수
{
	User *pCur = avl.GetNameRoot();//Name AVL root를 반환 받는다
	Linked *temp = NULL;//연결 임시 포인터 변수 선언

	ofstream ff(file,ios::out);//입력 받은 파일명으로 객체ff 생성
	if( !(ff.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	if( pCur ==NULL )//AVL에 저장되어있는 정보가 없다면
	{
		cout<<"저장하고자 하는 정보가 없습니다."<<endl;
		return false;//위에문구 출력과 false 반환
	}

	for(int k=0;k<37;k++)
		ff<<"=";
	ff<<endl;
	ff<<"본인학번	/	친구학번"<<endl;
	for(int k=0;k<37;k++)
		ff<<"=";
	ff<<endl;//해당 문구를 파일에 출력해준다

	while(pCur != NULL) //AVL각 노드의 친구들을 출력해준다
	{
		temp = pCur->GetFri();//친구 연결 노드의 head를 저장한다
		if(temp !=NULL)//친구가 존재 한다면
		{
			while(temp !=NULL)
			{
				if( ((temp->GetDown())->GetCheckDelete()) == 1 )//탈퇴여부 flag 1인 경우 친구 연결을 끊어준다
				{
					if( !(List.DeleteFrt(pCur, temp->GetDown()) ) )
						cout<<"친구 삭제에 실패하였습니다."<<endl;
				}
				temp = temp->GetNext();
			}
			temp = pCur->GetFri();//친구 연결 노드의 head를 저장한다

			while(temp != NULL)//친구의 끝까지 반복한다.
			{
				if( (Que.IsEmpty()) && (pCur !=avl.GetNameRoot() ) && (temp->GetNext()==NULL) )//마지막 라인이라면
					ff<<pCur->GetNumber()<<"	/	"<<(temp->GetDown())->GetNumber();
				//enter를 지우고 위 정보들을 출력해준다
				else//마지막 라인이 아니라면
					ff<<pCur->GetNumber()<<"	/	"<<(temp->GetDown())->GetNumber()<<endl;
				//해당정보를 출력해준다
				temp=temp->GetNext();//다음 자식노드를 가리키게 한다
			}
		}
		//Lever-order 방식으로 que에 저장해놓기 위한 조건문
		if(pCur->GetNameLeft() !=NULL)
			Que.Push( pCur->GetNameLeft() );

		if( pCur->GetNameRight() !=NULL )
			Que.Push( pCur->GetNameRight() );

		if( Que.IsEmpty())//que가 비어있다면 
			break;//while문 종료
		pCur = Que.Pop();// current는 que에서 pop 해준다
	}

	ff.close();//파일을 닫아주고 참 반환
	return true;
}

bool Manager::Save_Memo(char *file)
{
	User *pCur = avl.GetNameRoot();
	MemoNode *temp = NULL;

	ofstream ff(file,ios::out);//입력 받은 파일명으로 객체ff 생성
	if( !(ff.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	if( pCur == NULL )//AVL에 정보가 없다면
	{
		cout<<"저장하고자 하는 정보가 없습니다."<<endl;
		if( Del.Delete() )//leave 노드에 저장되어있는 정보들을 모두 지워준다.
			cout<<"탈퇴 요청한 유저들의 정보를 모두 제거 삭제하였습니다 "<<endl;
		else
			cout<<"탈퇴 요청한 유저들의 정보를 모두 제거하는데 실패하였습니다 "<<endl;
		return false;//위에문구 출력과 false 반환
	}

	for(int k=0;k<35;k++)
		ff<<"==";
	ff<<endl;
	ff<<"유저학번	/	작성시간	/	글내용"<<endl;
	for(int k=0;k<35;k++)
		ff<<"==";
	ff<<endl;//해당 문구를 파일에 출력해준다

	while(pCur != NULL) //AVL 정보를 출력해주기 위한 while문
	{
		temp = pCur->GetMyMemo();//자식노드의 head를 저장한다
		if(temp !=NULL)//저장되어있는 메모가 있다면 다음을 수행한다
		{
			while(temp != NULL)//자식 노드 끝까지 반복한다
			{
				if( (Que.IsEmpty()) && (pCur !=avl.GetNameRoot() ) && (temp->GetNext() == NULL) )//마지막 라인이라면
					ff<<pCur->GetNumber()<<"	/	"<<temp->GetTime()<<"	/	"<<temp->GetMemo();
				//enter를 지우고 위 정보들을 출력해준다
				else//마지막 라인이 아니라면
					ff<<pCur->GetNumber()<<"	/	"<<temp->GetTime()<<"	/	"<<temp->GetMemo()<<endl;
				//해당정보를 출력해준다
				temp=temp->GetNext();//다음 자식노드를 가리키게 한다
			}
		}
		//Lever-order 방식으로 que에 저장해놓기 위한 조건문
		if(pCur->GetNameLeft() !=NULL)
			Que.Push( pCur->GetNameLeft() );

		if( pCur->GetNameRight() !=NULL )
			Que.Push( pCur->GetNameRight() );

		if( Que.IsEmpty())//que가 비어있다면 
			break;//while문 종료
		pCur = Que.Pop();// current는 que에서 pop 해준다
	}
	if( Del.Delete() )//leave 노드에 저장되어있는 정보들을 삭제한다
		cout<<"탈퇴 요청한 유저들의 정보를 모두 제거 삭제하였습니다 "<<endl;
	else
		cout<<"탈퇴 요청한 유저들의 정보를 모두 제거하는데 실패하였습니다 "<<endl;

	ff.close();//파일을 닫아준다
	return true;//참반환
}

bool Manager::TimeLine(char *num)//TimeLine함수
{
	ofstream f("timeline.txt",ios_base::app);//timeline.txtt파일을 열어준다.
	User *MeNode = avl.NumSearch(num);//학번으로 입력 받은 사용자의 로드를 찾아준다
	User *Friend = NULL;//친구를 저장하기 위한 임시변수

	if(MeNode == NULL)//해당하는 학번의 사용자가 존재 하지 않는다면
	{
		for(int i=0; i<21;i++)//해당 문구를 파일에 적어준다
			f<<"==";
		f<<endl<<num<<" 유저에 대한 데이터가 없습니다."<<endl;
		for(int i=0; i<21;i++)
			f<<"==";
		f<<endl;
		f.close();//파일을 닫아준다
		return false;//거짓 반환
	}

	MemoNode *Memo = MeNode->GetMyMemo();
	while(Memo!=NULL)//내가 작성한 메모를 저장해주기위한 반복문
	{
		if( !(heap.pushMinHeap(Memo)) )// heap에 push 해준다
			cout<<"메모 삽입 실패"<<endl;
		Memo = Memo->GetNext();//다음 메모를 가리킨다
	}


	Linked *temp = MeNode->GetFri();//임시 포인터 변수 선언
	while(temp != NULL)
	{
		if( ((temp->GetDown())->GetCheckDelete()) == 1 )//탈퇴여부 flag1인 친구를 끊어준다
		{
			if( !(List.DeleteFrt(MeNode, temp->GetDown()) ) )//친구 연결을 끊어준다
				cout<<"친구 삭제에 실패하였습니다."<<endl;
		}
		temp = temp->GetNext();
	}
	temp = MeNode->GetFri();

	while(temp != NULL)//친구 끝까지 반복한다
	{
		Memo = NULL;//Memo를 초기화 해준다
		Friend = temp->GetDown();//친구 노드를 저장한다.
		if( List.SearchFri(Friend, MeNode) )//친구가 날 친구로 생각하는지 확인한다
		{
			Memo = Friend->GetMyMemo();//친구 사이가 맞다면 유저의 메모 헤더를 Memo에 저장한다
			if(Memo != NULL)
			{
				while(Memo!=NULL)//메모의 끝까지 반복한다
				{
					if( !(heap.pushMinHeap(Memo)) )//메모의 내용을 heap에 넣어준다
						cout<<"메모 삽입 실패"<<endl;
					Memo = Memo->GetNext();//다음 메모를 가리킨다
				}
			}
		}
		temp = temp->GetNext();//다음 친구를 가리키게 한다
	}

	MemoNode *Write = NULL;//pop 내용을 임시로 저장하기위한 포인터 변수

	if( !(heap.Heap_IsEmpty()) )//heap이 비어있지않다면
	{
		for(int i=0; i<20;i++)
			f<<"=";
		f<<endl<<MeNode->GetName()<<"  "<<MeNode->GetNumber()<<endl;
		for(int i=0; i<20;i++)
			f<<"=";
		f<<endl;//파일에 해당 정보를 적어준다

		while(1)//heap이 빌때까지 반복하기위한 무한루프
		{
			if( heap.Heap_IsEmpty() )//heap이 empty라면
				break;//무한루프 종료
			Write = heap.popMinHeap();//heap에서 pop 한다
			f<<Write->GetTime()<<"	/	"<<Write->GetWho()<<"	/	"<<Write->GetMemo()<<endl;//파일에 다음을 적어준다
		}
		f.close();
		return true;//파일을 닫아주고 참반환
	}
	else//heap이 비어있다면
	{
		for(int i=0; i<20;i++)
			f<<"=";
		f<<endl<<MeNode->GetName()<<"  "<<MeNode->GetNumber()<<endl;
		for(int i=0; i<20;i++)
			f<<"=";
		f<<endl;//파일에 해당 정보를 적어준다
		f.close();
		return true;//파일을 닫아주고 참반환
	}
}

bool Manager::Update_User(char *file)
{
	ifstream fin;//파일 스트림 형성
	User *user=NULL;
	User *Delete = NULL;
	char str[200];//한줄씩 받기 위한 배열 선언
	memset(str,NULL,sizeof(str));//배열 초기화

	char *temp1 = NULL;
	char *temp2 = NULL;//문자열을 짜르기 위한 char형 임시 포인터 선언

	fin.open(file,ios::in);//입력 받은 파일명으로 파일을 읽기 모드로 열어준다
	if( !(fin.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	for(int i=0;i<3;i++)//메모장에 필요 없는 라인을 지워준다
		fin.getline(str,sizeof(str));
	memset(str,NULL,sizeof(str));//배열을 NULL로 초기화

	while( !(fin.eof()) )//파일의 끝까지 반복한다
	{
		fin.getline(str,sizeof(str));//파일에서 한줄을 받아온다

		temp1 = strtok(str,"	 /");//학번을 짜른다
		temp2 = strtok(NULL,"	 /");//이름을 짜른다
		Delete = avl.NumSearch(temp1);

		if(Delete == NULL)//찾는 노드가 없다면
		{
			user = new User();//User 노드 메모리 할당
			user->SetNumber(temp1);//User Node에 학번을 저장한다
			user->SetName(temp2);//User Node에 이름을 저장한다
			if( !(avl.NameAVL(user)) )//Name AVL insert 호출
			{
				cout<<"Name AVL insert에 실패하였습니다."<<endl;//실패했다면 문구 출력
				return false;//거짓반환
			}
			if( !(avl.NumberAVL(user)) )//Number AVL insert 호출
			{
				cout<<"Number AVL insert에 실패하였습니다."<<endl;//실패했다면 문구 출력
				return false;//거짓 반환
			}
		}
		else//존재하는 노드라면
		{
			//삭제할것 삭제 함수 호출
		}

		Delete=NULL;//delete 초기화
		temp1=NULL;//temp를 NULL로 초기화
		temp2=NULL;//temp2를 NULL로 초기화 한다
		memset(str,NULL,sizeof(str));//배열들을 NULL로 초기화한다
	}
	fin.close();//파일을 닫아준다
	return true;//참반환
}

bool Manager::Update_Friend(char *file)
{
	ifstream fin;//파일 스트림 형성
	char str[200];//한줄씩 받기 위한 배열 선언
	memset(str,NULL,sizeof(str));//배열 초기화

	User *MeNode = NULL;//임시 포인터 선언
	User *FriNode = NULL;

	char *Me = NULL;
	char *Fri = NULL;//문자열을 짜르기 위한 char형 임시 포인터 선언

	fin.open(file,ios::in);//입력 받은 파일명으로 파일을 읽기 모드로 열어준다
	if( !(fin.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	for(int i=0;i<3;i++)//메모장에 필요 없는 라인을 지워준다
		fin.getline(str, sizeof(str));
	memset(str, NULL, sizeof(str));//배열을 NULL로 초기화

	while( !(fin.eof()) )//파일의 끝까지 반복한다
	{
		fin.getline(str,sizeof(str));//파일에서 한줄을 받아온다

		Me = strtok(str,"	 /");//나의 학번을 저장한다
		Fri = strtok(NULL,"	 /");//친구의 학번을 저장한다

		MeNode = avl.NumSearch(Me);
		FriNode = avl.NumSearch(Fri);//해당하는 학번의 노드를 찾아준다

		if( (MeNode == NULL) || (FriNode == NULL) )//찾는 노드가 없다면 해당문구 출력후 거짓 반환
		{
			cout<<"해당하는 학번의 사용자가 없습니다."<<endl;
			return false;
		}
		else
		{
			if( List.SearchFri(MeNode, FriNode) )//친구중 존재한다면
			{
				if( !(List.DeleteFrt(MeNode, FriNode)) )
					cout<<"친구 삭제에 실패하였습니다."<<endl;
			}

			if( !(List.Insert(MeNode, FriNode)) )//친구중에 존재 안함 인설트 함수 호출
			{
				cout<<"친구 추가에 실패 하였습니다."<<endl;//해당문구 출력 거짓 반환
				return false;
			}
		}

		MeNode = NULL;
		FriNode = NULL;
		Me=NULL;
		Fri=NULL;//임시 변수들을 NULL로 초기화 시켜준다
		memset(str,NULL,sizeof(str));//배열들을 NULL로 초기화한다
	}

	fin.close();
	return true;//파일을 닫아주고 true 반환
}

bool Manager::Update_Memo(char *file)
{
	ifstream fin;//파일 스트림 형성
	char str[300];//한줄씩 받기 위한 배열 선언
	memset(str,NULL,sizeof(str));

	User *MeNode = NULL;
	MemoNode *mNode = NULL;//메모와 사용자를 위한 포인터객체 생성

	char *me = NULL;
	char *time = NULL;
	char *memo = NULL;//문자열을 짜르기 위한 char형 임시 포인터 선언

	fin.open(file,ios::in);//입력 받은 파일명으로 파일을 읽기 모드로 열어준다
	if( !(fin.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	for(int i=0;i<3;i++)//메모장에 필요 없는 라인을 지워준다
		fin.getline(str,sizeof(str));
	memset(str,NULL,sizeof(str));//배열을 NULL로 초기화

	while( !(fin.eof()) )//파일의 끝까지 반복한다
	{
		fin.getline(str,sizeof(str));//파일에서 한줄을 받아온다

		me = strtok(str,"	/");//나의 학번을 저장한다
		time = strtok(NULL,"	/");//시간메을 저장한다
		memo = strtok(NULL,"	/");//메모를 저장한다
		MeNode = avl.NumSearch(me);

		if(MeNode == NULL)//찾는 노드가 없다면 해당문구 출력후 거짓 반환
		{
			cout<<"해당하는 학번의 사용자가 없습니다."<<endl;
			return false;
		}
		else//찾는 노드가 있다면 메모노드 생성후 저장 하고 메모 연결 노드를 호출한다
		{
			if(memo == NULL)//메모내용 없다
			{
				if( Line.MemoSearch( MeNode, time ) )//시간이 같은 메모가 존재 한다면
				{
					if( !(Line.MemoDelete(MeNode, time)) )//메모 삭제
					{
						cout<<"메모 삭제에 실패하였습니다."<<endl;
						return false;
					}

				}
			}
			else//메모내용 있다
			{
				if( !(Line.MemoSearch( MeNode, time)) )//같은 시간 메모가 존재 하지않는다면
				{
					mNode = new MemoNode();//memo노드 생성한다

					strcpy(memo,ALARM(MeNode, memo, time));//ALARM 함수 호출을 통해 메모내용을 수정해준다
					mNode->SetTime(time);
					mNode->SetWrite(memo);//메모 노드에 정보를 저장한다
					mNode->SetWho(MeNode->GetName());

					if( !(Line.MemoInsert(MeNode, mNode)) )//insert에 실패하였다면
					{
						cout<<"메모 연결에 실패 하였습니다."<<endl;//해당문구 출력 거짓 반환
						return false;
					}
				}
			}
		}

		MeNode = NULL;
		me = NULL;
		time = NULL;
		memo = NULL;//임시 변수들을 NULL로 초기화 시켜준다
		memset(str,NULL,sizeof(str));//배열들을 NULL로 초기화한다
	}

	fin.close();
	return true;//파일을 닫아주고 true 반환
}

bool Manager::EXIT()//종료 함수
{
	User *pCur = avl.GetNumRoot();//Name AVL root를 반환 받는다
	User *usertemp = NULL;
	Linked *frnhead = NULL;//연결 임시 포인터 변수 선언
	Linked *frntemp = NULL;
	MemoNode *memohead = NULL;
	MemoNode *memotemp = NULL;

	while(pCur != NULL) //AVL각각에 접근
	{
		usertemp = pCur;//메모정보를 모두 삭제
		memohead = pCur->GetMyMemo();
		while(memohead !=NULL)
		{
			memotemp = memohead;
			memohead = memohead->GetNext();
			delete memotemp;
		}

		frnhead = pCur->GetFri();
		while(frnhead !=NULL)//친구 정보를 모두 삭제
		{
			frntemp = frnhead;
			frnhead = frnhead->GetNext();
			delete frntemp;
		}
		//Lever-order 방식으로 que에 저장해놓기 위한 조건문
		if(pCur->GetNumLeft() !=NULL)
			Que.Push( pCur->GetNumLeft() );

		if( pCur->GetNumRight() !=NULL )
			Que.Push( pCur->GetNumRight() );

		if( Que.IsEmpty())//que가 비어있다면 
		{
			delete usertemp;
			break;//while문 종료
		}
		pCur = Que.Pop();// current는 que에서 pop 해준다

		delete usertemp;
	}
	Del.Delete();//leave list에 남아있는 것 삭제해준다
	return true;
}