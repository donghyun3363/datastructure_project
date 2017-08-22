#include "Manager.h"
#include<iostream>
#include<fstream>//헤더파일 선언

using namespace std;//이름 공간에 std 저장후 사용

Manager::Manager(void)//생성자
{
	for(int i= 0;i<3;i++) // 3*100 배열 초기화
	{
		for(int j=0; j<100; j++)
			Short[i][j]=0;
	}
}

Manager::~Manager(void)//소멸자
{

}

bool Manager::Load_gu(char *file1, char *file2)//구 관련 파일 로드
{
	ifstream fin;//Gu Vertex 파일 오픈
	GuVertex *Gu = NULL;

	char str[200];//한줄씩 받기 위한 배열 선언
	memset(str,NULL,sizeof(str));//배열 초기화

	char *temp1 = NULL;
	char *temp2 = NULL;//문자열을 짜르기 위한 char형 임시 포인터 선언
	int flag = 0;

	fin.open(file1,ios::in);//입력 받은 파일명으로 파일을 읽기 모드로 열어준다
	if( !(fin.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	for(int i=0;i<3;i++)//메모장에 필요 없는 라인을 지워준다
		fin.getline(str,sizeof(str));
	memset(str,NULL,sizeof(str));//배열을 NULL로 초기화

	while( !(fin.eof()) )//파일의 끝까지 반복한다
	{
		fin.getline(str,sizeof(str));//파일에서 한줄을 받아온다
		if(str[0]==NULL)//Enter가 나온다면 파일 종료
			break;
		temp1 = strtok(str,"	 /");//구를 짜른다.

		if( ADJList.SearchGuVertex(temp1) == NULL )//해당하는 이름을 가진 구가 없다면
		{
			Gu = new GuVertex();//구 Vertex 동적할당
			Gu->SetGuName(temp1);//구 이름을 넣어준다

			Gu->SetShortflag(flag);//구에 최단 거리 flag를 넣어준다
			flag++;
			if( !(ADJList.Guinsert(Gu)) )//구 연결리스트 함수 호출
				cout<<"구 정보 Insert에 실패 하였습니다."<<endl;//실패 하였다면 해당문구 출력
		}
		else//이미 저장된 구 라면
			cout<<"존재하는 구Vertex 입니다."<<endl;//해당 문구 출력

		temp1=NULL;//temp를 NULL로 초기화
		memset(str,NULL,sizeof(str));//배열들을 NULL로 초기화한다
	}
	fin.close();//파일을 닫아준다

	///////////////////////////////////////////////////////////////////////////GuEdge
	ifstream fin2;//파일 스트림 형성
	GuVertex *tempGu = NULL;
	GuEdge *guEdge = NULL;

	char *dis = NULL;//임시 포인터 변수들 선언
	int dis2 = 0;

	memset(str,NULL,sizeof(str));
	temp1 = NULL;
	temp2 = NULL;//포인터 변수들을 초기화 해준다

	fin2.open(file2,ios::in);//구 Edge파일을 open해준다
	if( !(fin2.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	for(int i=0;i<3;i++)//메모장에 필요 없는 라인을 지워준다
		fin2.getline(str,sizeof(str));
	memset(str,NULL,sizeof(str));//배열을 NULL로 초기화

	while( !(fin2.eof()) )//파일의 끝까지 반복한다
	{
		fin2.getline(str,sizeof(str));//파일에서 한줄을 받아온다
		if(str[0]==NULL)//Enter가 나온다면 파일 종료
			break;

		temp1 = strtok(str,"	 /");//from Gu
		temp2 = strtok(NULL,"	 /");//to Gu
		dis = strtok(NULL,"	 /");//거리
		dis2 = atoi(dis);

		tempGu = ADJList.SearchGuVertex(temp1);//from에 해당하는 구 Vertex를 찾아준다
		if( tempGu != NULL )//from에 해당하는 구가 존재 한다면
		{
			if( ADJList.SearchGuEdge(tempGu, temp2) == NULL )//다음  from, to edge가 존재 하지 않는다면
			{
				guEdge = new GuEdge();
				guEdge->SetfromGu(temp1);
				guEdge->SettoGu(temp2);
				guEdge->SetDis(dis2);//Gu Edge 생성후 다음 정보들을 저장한다.

				if( !( ADJList.GuEdgeinsert(tempGu, guEdge) ) )
					cout<<"인접 리스트 인설트 실패"<<endl;
			}
			else//Edge가 존재 한다면
				cout<<"이미 존재하는 구 Edge 입니다."<<endl;//해당 문구 출력
		}
		else//from에 해당하는 구가 존재 하지 않는다면
			cout<<"존재하지 않는 구Vertex 입니다."<<endl;//해당 문구 출력

		tempGu = NULL;
		guEdge = NULL;
		temp1 = NULL;
		temp2 = NULL;
		dis = NULL;
		memset(str,NULL,sizeof(str));//배열과 포인터 변수들을 NULL로 초기화한다
	}

	fin2.close();//guEdge 파일을 닫아준다
	return true;//참반환
}

bool Manager::Load_dong(char *file1, char *file2)//동 관련 파일 로드
{
	ifstream fin;//파일 스트림 형성
	GuVertex *tempGu = NULL;
	DongVertex *Dong = NULL;//임시 포인터 변수 선언

	char str[200];//한줄씩 받기 위한 배열 선언
	memset(str,NULL,sizeof(str));//배열 초기화
	char *temp1 = NULL;
	char *temp2 = NULL;
	char *temp3 = NULL;//문자열을 짜르기 위한 char형 임시 포인터 선언

	fin.open(file1,ios::in);//입력 받은 파일명으로 파일을 읽기 모드로 열어준다
	if( !(fin.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	for(int i=0;i<3;i++)//메모장에 필요 없는 라인을 지워준다
		fin.getline(str,sizeof(str));
	memset(str,NULL,sizeof(str));//배열을 NULL로 초기화

	while( !(fin.eof()) )//파일의 끝까지 반복한다
	{
		fin.getline(str,sizeof(str));//파일에서 한줄을 받아온다
		if(str[0]==NULL)//Enter가 나온다면 파일 종료
			break;
		temp1 = strtok(str,"	 /");//구를 짜른다
		temp2 = strtok(NULL,"	 /");//동을 짜른다
		temp3 = strtok(NULL,"	 /");//남방 관제소 여부를 짜른다

		tempGu = ADJList.SearchGuVertex(temp1);//구 이름에 해당하는 Vertex를 찾는다
		if( tempGu != NULL ) //존재하는 구라면
		{
			if( ADJList.SearchDongVertex(tempGu, temp2) == NULL )//이미존재하는 동 vertex인지 확인한다
			{
				Dong = new DongVertex();
				Dong->SetguName(temp1);
				Dong->SetDongName(temp2);
				Dong->SetView(temp3);//동 Vertex 생성후 해당 정보들을 저장한다.

				if( !( ADJList.Donginsert(tempGu, Dong) ) )//동을 연결해준다
					cout<<"동 정보 Insert에 실패 하였습니다."<<endl;
			}

			else//이미 존재하는 동 Vertex라면
				cout<<"이미 존재하는 동vertex 입니다."<<endl;//해당 문구 출력
		}

		else//다음 구가 존재 하지 않는다면
			cout<<"존재하지 않는 구 Vertex 입니다."<<endl;//해당 문구 출력

		temp1 = NULL;
		temp2 = NULL;
		temp3 = NULL;
		tempGu = NULL;
		Dong = NULL;
		memset(str,NULL,sizeof(str));//배열과 임시 포인터 변수들을 NULL로 초기화한다
	}
	fin.close();//파일을 닫아준다

	tempGu = ADJList.GetGuHead();//서울시 구 Vertex의 헤더를 반환 받는다
	while(tempGu !=NULL)//구 Vertex의 끝까지 반복한다
	{
		ADJList.SetDongHead(tempGu);//헤더지정함수 호출
		tempGu = tempGu->GetGuNext();//다음 구를 가리킨다
	}//각 구들의 동Vertex 헤더를 난방관제소로 바꾸기 위한 반복문이다.

	////////////////////////////////////////////////////////////////////////////////////Dongedge
	ifstream fin2;//파일 스트림 형성

	tempGu = NULL;
	Dong = NULL;
	DongEdge *dongEdge = NULL;

	temp1 = NULL;
	temp2 = NULL;
	temp3 = NULL;
	char *lossrate = NULL;
	int lossrate2 = 0;

	memset(str,NULL,sizeof(str));//배열과 포인터 변수들을 다시 초기화

	fin2.open(file2,ios::in);//입력 받은 파일명으로 파일을 읽기 모드로 열어준다
	if( !(fin2.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	for(int i=0;i<3;i++)//메모장에 필요 없는 라인을 지워준다
		fin2.getline(str,sizeof(str));
	memset(str,NULL,sizeof(str));//배열을 NULL로 초기화

	while( !(fin2.eof()) )//파일의 끝까지 반복한다
	{
		fin2.getline(str,sizeof(str));//파일에서 한줄을 받아온다
		if(str[0]==NULL)//Enter가 나온다면 파일 종료
			break;

		temp1 = strtok(str,"	 /");//구를 짜른다
		temp2 = strtok(NULL,"	 /");//from 동을 짜른다
		temp3 = strtok(NULL,"	 /");//to 동을 짜른다
		lossrate = strtok(NULL,"	 /");//열 손실률을 짜른다
		lossrate2 = atoi(lossrate);

		tempGu = ADJList.SearchGuVertex(temp1);//해당하는 구를 찾는다
		if( tempGu != NULL )//해당하는 구가 존재 한다면
		{
			Dong = ADJList.SearchDongVertex(tempGu, temp2);//해당구에 from 동이 있는지 찾는다
			if( Dong != NULL )//동이 존재 한다면
			{
				if( ADJList.SearchDongEdge(Dong, temp3) == NULL )//다음 edge가 존재 하지 않는다면
				{
					dongEdge = new DongEdge();
					dongEdge->SetGuName(temp1);
					dongEdge->SetfromDong(temp2);
					dongEdge->SettoDong(temp3);
					dongEdge->SetLossrate(lossrate2);//동 edge를 동적 할당 하고 해당 정보를 저장한다

					if( !( ADJList.DongEdgeinsert(Dong, dongEdge) ) )
						cout<<"동 인접리스트 insert에 실패 하였습니다."<<endl;
				}

				else//edge가 존재한다면
					cout<<"이미 존재하는 동 Edge 입니다."<<endl;//해당 문구 출력
			}

			else//존재 하지 않는 동vertex라면
				cout<<"존재하지 않는 동 Vertex 입니다."<<endl;//해당 문구 출력
		}

		else//존재하지 않는 구 vertex라면
			cout<<"존재하지 않는 구 Vertex 입니다."<<endl;//해당 문구 출력

		tempGu = NULL;
		Dong = NULL;
		dongEdge = NULL;
		temp1 = NULL;
		temp2 = NULL;
		temp3 = NULL;
		lossrate = NULL;
		memset(str,NULL,sizeof(str));//배열과 임시 포인터 변수들을 NULL로 초기화한다
	}

	DongMst();//로드가 완료된후 MST 함수를 호출해준다.

	fin2.close();//파일을 닫아준다
	return true;
}

bool Manager::DongMst()//MST 호출 함수
{
	GuVertex *tempGu = ADJList.GetGuHead();//구의 헤더를 반환한다
	int count =0;//동의 갯수를 받기위한 int 형 변수

	while( tempGu != NULL )//구의 끝까지 반복한다
	{
		count = ADJList.CountDong(tempGu);//해당하는 구의 동 갯수를 반환받는다

		if( !(DoMst.MST(tempGu, count)) )//MST가 구성되지 않는다면 
		{
			Pipe_Repair( tempGu->GetGuName() );//Pipe_Repair 함수 호출
		}
		tempGu = tempGu->GetGuNext();
		count = 0;//다음 구를 가리키고 카운터를 0으로 초기화 한다
	}
	return true;//참 반환
}

bool Manager::Load_Mehanic(char *file)//기술자 정보를 로드하는 함수
{
	ifstream fin;//파일객체생성
	Mechanic *Per = NULL;
	char str[100];//한줄씩 받기 위한 배열 선언
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
		if(str[0]==NULL)//Enter가 나온다면 파일 종료
			break;

		temp1 = strtok(str,"	 ");//근무지를 짜른다
		temp2 = strtok(NULL,"	 ");//정비사 이름을 짜른다.

		if( MechanicList.CheckMechanic(temp1) )//동일한 근무지가 존재 하지 않는다면
		{
			Per = new Mechanic();//동적 할당
			Per->SetMechanicGu(temp1);
			Per->SetMechanicName(temp2);//다음 정보를 넣어준다

			if( !(MechanicList.InsertMechanic(Per)) )//정비사 연결에 실패 하였다면
				cout<<"정비사 정보 Insert에 실패 하였습니다."<<endl;//해당문구 출력
		}

		else//근무지가 동일 하다면
			cout<<"동일한 근무지 입니다."<<endl;//해당문구 출력

		temp1 = NULL;
		temp2 = NULL;
		memset(str,NULL,sizeof(str));//배열들을 NULL로 초기화한다
	}

	fin.close();//파일을 닫아준다
	return true;
}

bool Manager::Update(char *file)//UPDATE 함수
{
	ifstream fin;//파일 스트림 형성
	GuVertex *Gu = NULL;
	DongVertex *Dong = NULL;
	DongVertex *ReverDong = NULL;

	DongEdge *tempEdge = NULL;
	DongEdge *reverEdge = NULL;//임시 포인터 변수 선언

	char str[200];//한줄씩 받기 위한 배열 선언
	memset(str,NULL,sizeof(str));//배열 초기화

	char *guname = NULL;
	char *fromdong = NULL;
	char *todong = NULL;
	char *lossrate = NULL;//문자열을 짜르기 위한 char형 임시 포인터 선언

	int lossrate2 = 0;
	memset(str,NULL,sizeof(str));//배열과 포인터 변수들을 다시 초기화

	fin.open(file,ios::in);//입력 받은 파일명으로 파일을 읽기 모드로 열어준다
	if( !(fin.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	for(int i=0;i<3;i++)//메모장에 필요 없는 라인을 지워준다
		fin.getline(str,sizeof(str));
	memset(str,NULL,sizeof(str));//배열을 NULL로 초기화

	while( !(fin.eof()) )//파일의 끝까지 반복한다
	{
		fin.getline(str,sizeof(str));//파일에서 한줄을 받아온다
		if(str[0]==NULL)//Enter가 나온다면 파일 종료
			break;

		guname = strtok(str,"	 /");//구를 짜른다
		fromdong = strtok(NULL,"	 /");//from 동을 짜른다
		todong = strtok(NULL,"	 /");//to 동을 짜른다
		lossrate = strtok(NULL,"	 /");//열 손실률을 짜른다
		lossrate2= atoi(lossrate); //열손실 int 형으로 바꿔준다

		Gu = ADJList.SearchGuVertex(guname);//해당하는 구를 찾는다
		if( Gu != NULL )//해당하는 구가 존재 한다면
		{
			Dong = ADJList.SearchDongVertex(Gu, fromdong);//해당구에 from 동이 있는지 찾는다
			ReverDong = ADJList.SearchDongVertex(Gu, todong);//해당구에 to 동이 있는지 찾는다

			if( Dong != NULL )//동이 존재 한다면
			{
				tempEdge = ADJList.SearchDongEdge(Dong, todong);//edge를 찾아준다
				if( tempEdge != NULL )//edge 존재 한다면
				{
					reverEdge = ADJList.SearchDongEdge(ReverDong, fromdong);//양방향 고려
					tempEdge->SetLossrate(lossrate2);
					reverEdge->SetLossrate(lossrate2);//열 손실률 수정
				}

				else//edge가 존재 하지 않는다면
				{
					tempEdge = new DongEdge();
					reverEdge = new DongEdge();//정방향 역방향 edge들을 동적할당한다

					tempEdge->SetGuName(guname);
					tempEdge->SetfromDong(fromdong);
					tempEdge->SettoDong(todong);
					tempEdge->SetLossrate(lossrate2);//동 edge를 동적 할당 하고 해당 정보를 저장한다

					reverEdge->SetGuName(guname);
					reverEdge->SetfromDong(todong);
					reverEdge->SettoDong(fromdong);
					reverEdge->SetLossrate(lossrate2);//동 Reveredge를 동적 할당 하고 해당 정보를 저장한다

					if( !( ADJList.DongEdgeinsert(Dong, tempEdge) ) )//edge를 인접리스트에 연결
						cout<<"동 인접리스트 insert에 실패 하였습니다."<<endl;

					if( !( ADJList.DongEdgeinsert(ReverDong, reverEdge) ) )//Rever edge를 인접리스트에 연결
						cout<<"동 인접리스트 insert에 실패 하였습니다."<<endl;
				}
			}

			else//존재 하지 않는 동vertex라면
				cout<<"존재하지 않는 동 Vertex 입니다."<<endl;//해당 문구 출력
		}
		else//존재하지 않는 구 vertex라면
			cout<<"존재하지 않는 구 Vertex 입니다."<<endl;//해당 문구 출력

		Gu = NULL;
		Dong = NULL;
		ReverDong = NULL;
		tempEdge = NULL;
		reverEdge = NULL;
		guname = NULL;
		fromdong = NULL;
		todong = NULL;
		lossrate = NULL;
		memset(str,NULL,sizeof(str));//배열과 임시 포인터 변수들을 NULL로 초기화한다
	}

	Gu = ADJList.GetGuHead();
	while(Gu !=NULL)//모든 Edge의 MST 값을 0으로 해주고 다시 MST 함수를 호출해준다
	{
		Dong = Gu->GetDongHead();
		while(1)
		{
			tempEdge = Dong->GetdongedgHead();
			while( tempEdge != NULL )
			{
				tempEdge->SetMst(0);
				tempEdge = tempEdge->GetDongEdgeNext();
			}
			Dong = Dong->GetdongNext();
			if(Dong == Gu->GetDongHead())
				break;
		}
		Gu = Gu->GetGuNext();//모든 서울시 로드맵을 반복하면서 MST 값을 0으로 해준다
	}

	DongMst();//로드가 완료된후 MST 함수를 호출해준다.

	fin.close();//파일을 닫아준다
	return true;
}

bool Manager::Pipe_Broken(char *gu, char *from, char *to)//PIPE BROKEN 함수
{
	GuVertex *Gu = ADJList.SearchGuVertex(gu);//해당하는 구를 찾는다

	DongVertex *Dong = ADJList.SearchDongVertex(Gu, from);
	DongVertex *ReverDong = ADJList.SearchDongVertex(Gu, to);//from, to 동 두개다 찾아준다

	DongEdge *Edge = ADJList.SearchDongEdge(Dong,to);
	DongEdge *ReverEdge = ADJList.SearchDongEdge(ReverDong, from);//양방향 edge를 모두 찾아준다

	if(Gu !=NULL)
	{
		if(Dong != NULL)
		{
			if(Edge != NULL)
			{
				Edge->SetBroken(1);
				ReverEdge->SetBroken(1);//존재하는 edge라면 BROKEN flag 값을 set 해준다
			}
			else
				cout<<"찾고자 하는 Edge가 없습니다."<<endl;
		}
		else
			cout<<"찾고자 하는 동이 없습니다."<<endl;
	}
	else
		cout<<"찾는 구가 존재 하지 않습니다."<<endl;

	Gu = ADJList.GetGuHead();//모든 Edge의 MST 값을 0으로 해주고 다시 MST 함수를 호출해준다
	while(Gu !=NULL)
	{
		Dong = Gu->GetDongHead();
		while(1)
		{
			Edge = Dong->GetdongedgHead();
			while( Edge != NULL )
			{
				Edge->SetMst(0);
				Edge = Edge->GetDongEdgeNext();
			}
			Dong = Dong->GetdongNext();
			if(Dong == Gu->GetDongHead())
				break;
		}
		Gu = Gu->GetGuNext();
	}  /////////////////////MST flag 값을 0으로 다시 다 초기화 시켜 준다

	DongMst();//로드가 완료된후 MST 함수를 호출해준다.

	return true;
}

bool Manager::Pipe_Repair(char *gu)//Pipe_Repair 함수
{
	ofstream f("repair_log.txt",ios_base::app);//repair_log.txt파일을 열어준다.
	if( !(f.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	GuVertex *Gu = ADJList.SearchGuVertex(gu);
	Mechanic *Man = NULL;
	Man = ShortestPath(Gu);//최단 거리를 가지는 정비사를 찾아준다

	for(int i=0; i<35; i++)
		f<<"==";
	f<<endl<<"			PIPE REPAIR"<<endl;
	for(int i=0; i<35; i++)
		f<<"==";
	f<<endl; 
	f<<Man->GetMechanicName()<<"  /  "<<Gu->GetGuName()<<endl;
	f<<"수리 전 수도 맵 구성"<<endl;//해당 문구를 파일에 출력해준다

	DongVertex *Dong = NULL;
	DongEdge *Edge = NULL;//임시 동, 동 엣지 포인터 변수

	if(Gu != NULL)//해당하는 구가 존재한다면
	{
		Dong = Gu->GetDongHead();//구의 동헤더를 반환한다

		while(1)//동을 반복하기위한 무한루프
		{
			if(Dong == NULL)//저장된 동이 없다면 
				break;
			Edge = Dong->GetdongedgHead();//동에 edge 헤더를 반환한다
			while( Edge != NULL )//edge의 끝까지 반복한다
			{
				if(Edge->GetMst() == 1)//MST edge라면
					f<<"	"<<Edge->GetfromDong()<<"  ->  "<<Edge->GettoDong()<<" ( "<<Edge->GetLossrate()<<" ) "<<endl;
				//다음 문구를 파일에 출력해준다
				Edge = Edge->GetDongEdgeNext();//다음 edge를 가리킨다
			}
			Dong = Dong->GetdongNext();//다음 동을가리킨다
			if(Dong == Gu->GetDongHead())//원형리스트 반복이 끝났다면
				break;//무한루프종료
		}
	}

	f<<"수리 수도"<<endl;//파일에 출력

	int lossrate = 0;
	Dong = NULL;

	if(Gu!=NULL)
	{
		Dong = Gu->GetDongHead();//구의 동헤더를 반환한다
		while(1)
		{
			if(Dong == NULL)//저장된 동이 없다면 
				break;

			Edge = Dong->GetdongedgHead();//edge를 찾아준다
			while( Edge != NULL )//edge의 끝까지 반복한다
			{
				lossrate = Edge->GetLossrate();
				if( Edge->GetBroken() == 1 )
				{
					f<<"	[BROKEN]  "<<Edge->GetfromDong()<<"  ->  "<<Edge->GettoDong()<<" ( "<<Edge->GetLossrate()<<" )";

					if( lossrate*2 > 50)//열손실률을 수정해준다
						Edge->SetLossrate(50);
					else
					{
						lossrate = lossrate*2;
						Edge->SetLossrate(lossrate);
					}

					f<<"  ->  ( "<<Edge->GetLossrate()<<" )"<<endl;//파일에 출력
					Edge->SetBroken(0);//broken flag를 reset 해준다
				}
				Edge = Edge->GetDongEdgeNext();
			}
			Dong = Dong->GetdongNext();
			if(Dong == Gu->GetDongHead())//원형리스트를 모두 돌았다면
				break;//무한루프 종료
		}
	}

	Gu = ADJList.GetGuHead();//모든 Edge의 MST 값을 0으로 해주고 다시 MST 함수를 호출해준다
	while(Gu !=NULL)
	{
		Dong = Gu->GetDongHead();
		while(1)
		{
			Edge = Dong->GetdongedgHead();
			while( Edge != NULL )
			{
				Edge->SetMst(0);
				Edge = Edge->GetDongEdgeNext();
			}
			Dong = Dong->GetdongNext();
			if(Dong == Gu->GetDongHead())
				break;
		}
		Gu = Gu->GetGuNext();
	}

	DongMst();//로드가 완료된후 MST 함수를 호출해준다.

	f<<"수리 후 수도 맵 구성"<<endl;

	Gu = ADJList.SearchGuVertex(gu);
	if(Gu != NULL)//해당하는 구가 존재한다면
	{
		Dong = Gu->GetDongHead();//구의 동헤더를 반환한다

		while(1)//동을 반복하기위한 무한루프
		{
			if(Dong == NULL)//저장된 동이 없다면 
				break;
			Edge = Dong->GetdongedgHead();//동에 edge 헤더를 반환한다
			while( Edge != NULL )//edge의 끝까지 반복한다
			{
				if(Edge->GetMst() == 1)//MST edge라면
					f<<"	"<<Edge->GetfromDong()<<"  ->  "<<Edge->GettoDong()<<" ( "<<Edge->GetLossrate()<<" ) "<<endl;
				//다음 문구를 파일에 출력해준다
				Edge = Edge->GetDongEdgeNext();//다음 edge를 가리킨다
			}
			Dong = Dong->GetdongNext();//다음 동을가리킨다
			if(Dong == Gu->GetDongHead())//원형리스트 반복이 끝났다면
				break;//무한루프종료
		}
	}
	f<<Man->GetMechanicName()<<" 정비사의 이동경로"<<endl;

	int num_to = 0;//정비사의 이동경로를 출력해주기 위한 부분이다
	int num_dis = 0;
	GuVertex *toGu = NULL;
	GuEdge *guEdge = NULL;

	f<<Man->GetMechanicGu()<<" ( 0 ) ";
	Gu = ADJList.SearchGuVertex(Man->GetMechanicGu());

	if(strcmp(Man->GetMechanicGu(),gu)==0)//정비사가 해당구에 있을 경우 예외처리
	{
		f<<endl;
		f.close();
		return true;//파일 닫아준다
	}
	else
		f<<" -> ";
	while(1)//도착지까지 왔다면 무한루프 종료
	{

		num_to = Short[2][Gu->GetShortflag()];
		toGu = ADJList.SearchGuVertex(num_to);
		guEdge = ADJList.SearchGuEdge(Gu,toGu->GetGuName());
		num_dis = num_dis + guEdge->Getdis();
		if(strcmp(toGu->GetGuName(), gu) ==0 )
		{
			f<<toGu->GetGuName()<<" ( "<<num_dis<<" )"<<endl;//파일에출력
			Man->SetMechanicGu(toGu->GetGuName());
			break;
		}
		f<<toGu->GetGuName()<<" ( "<<num_dis<<" ) -> ";//파일에출력
		Gu = toGu;//다음 경로를 가리킨다
	}

	f.close();
	return true;//파일 닫아준다
}

bool Manager::Print_Map()//서울시 로드맵을 출력해준다
{
	ofstream f("map.txt",ios_base::app);//map.txt파일을 열어준다.
	if( !(f.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	for(int i=0; i<15; i++)
		f<<"==";
	f<<endl<<"	PRINT MAP"<<endl;
	for(int i=0; i<15; i++)
		f<<"==";
	f<<endl; //해당 문구를 출력해준다

	GuVertex *tempGu = ADJList.GetGuHead();//서울시의 구 헤더를 반환받는다

	if(tempGu==NULL)//예외처리
		f<<"서울시에 구가 존재 하지 않습니다"<<endl;

	GuEdge *Edge = NULL;//edge 임시 포인터 변수

	while(tempGu != NULL)//구의 끝까지 반복한다
	{
		Edge = tempGu->GetGuedgHead();//구의 edge 헤더를 반환 받는다

		while( Edge != NULL )//edge의 끝까지 반복한다
		{
			f<<Edge->GetfromGu()<<"  ->  "<<Edge->GettoGu()<<"  ( "<<Edge->Getdis()<<" )"<<endl;//파일에 출력

			Edge = Edge->GetGuEdgeNext();//다음edge를 가리킨다
		}
		tempGu = tempGu->GetGuNext();//다음 구를 가리킨다
	}

	f.close();//파일을 닫아준다
	return true;//참 반환
}

bool Manager::Print_Gu(char *gu)//해당구에 존재하는 MST를 출력해준다
{
	ofstream f("pipe.txt",ios_base::app);//pipe.txt파일을 열어준다.
	if( !(f.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	for(int i=0; i<22; i++)
		f<<"==";
	f<<endl<<"		PIPE"<<endl;
	for(int i=0; i<22; i++)
		f<<"==";
	f<<endl;//해당문구를 파일에 출력해준다

	GuVertex *tempGu = ADJList.SearchGuVertex(gu);//구이름에 해당하는 구를 찾아준다

	DongVertex *Dong = NULL;
	DongEdge *Edge = NULL;//임시 동, 동 엣지 포인터 변수

	if(tempGu != NULL)//해당하는 구가 존재한다면
	{
		Dong = tempGu->GetDongHead();//구의 동헤더를 반환한다

		while(1)//동을 반복하기위한 무한루프
		{
			if(Dong == NULL)//저장된 동이 없다면 
				break;
			Edge = Dong->GetdongedgHead();//동에 edge 헤더를 반환한다
			while( Edge != NULL )//edge의 끝까지 반복한다
			{
				if(Edge->GetMst() == 1)//MST edge라면
					f<<gu<<" : "<<Edge->GetfromDong()<<"  ->  "<<Edge->GettoDong()<<" ( "<<Edge->GetLossrate()<<" ) "<<endl;
				//다음 문구를 파일에 출력해준다
				Edge = Edge->GetDongEdgeNext();//다음 edge를 가리킨다
			}

			Dong = Dong->GetdongNext();//다음 동을가리킨다
			if(Dong == tempGu->GetDongHead())//원형리스트 반복이 끝났다면
				break;//무한루프종료
		}
	}

	f.close();//파일을 닫아준다
	return true;//참 반환
}

bool Manager::Print_Mechanic()//정비사를 출력해준다
{
	ofstream f("mechanic_list.txt",ios_base::app);//mechanic_list.txt파일을 열어준다.
	if( !(f.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	for(int i=0; i<14; i++)
		f<<"==";

	f<<endl<<"	MECHANIC INFO"<<endl;
	for(int i=0; i<14; i++)
		f<<"==";
	f<<endl;//파일에 해당문구를 출력해준다

	Mechanic *temp = MechanicList.GetMechanicHead();//정비사 리스트의 헤더를 반환한다

	if(temp == NULL)//예외처리
		f<<"저장되어있는 정비사 목록이 없습니다"<<endl;

	while(temp != NULL)//temp의 끝까지 반복한다
	{
		f<<"   "<<temp->GetMechanicName()<<"  -  "<<temp->GetMechanicGu()<<endl;//해당 문구를 출력해준다

		temp = temp->GetMechanicNext();//다음 정비사를 가리킨다
	}
	f.close();//파일을 닫아준다
	return true;//참반환
}

bool Manager::Save_Gu()//구 관련 정보 저장
{
	ofstream f1("gu_vertex.bak",ios::out);//입력 받은 파일명으로 객체ff 생성
	if( !(f1.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	GuVertex *gu = ADJList.GetGuHead();//구의 헤더를 반환한다
	if(gu==NULL)
	{
		cout<<"저장되어있는 정보가 없습니다"<<endl;
		f1.close();
		return false;//동에 저장되어있는 값이없다면 화면에 출력 거짓 반환
	}

	for(int i=0; i<12; i++)
		f1<<"==";
	f1<<endl<<"    서울시 구 명칭"<<endl;
	for(int i=0; i<12; i++)
		f1<<"==";
	f1<<endl; //해당 문구를 출력해준다

	while(gu != NULL)
	{
		f1<<"	"<<gu->GetGuName()<<endl;
		gu = gu->GetGuNext();
	}
	f1.close();//화면에 출력해주고 파일을 닫아준다

	ofstream f2("gu_edge.bak",ios::out);//입력 받은 파일명으로 객체ff 생성
	if( !(f2.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	gu = ADJList.GetGuHead();
	GuEdge *Edge = NULL;

	for(int i=0; i<30; i++)
		f2<<"==";
	f2<<endl<<"	from(구)	to(구)		distance(km)"<<endl;
	for(int i=0; i<30; i++)
		f2<<"==";
	f2<<endl; //해당 문구를 출력해준다

	while(gu != NULL)//서울시의 구와 구edge를 반복한다
	{
		Edge = gu->GetGuedgHead();

		while(Edge != NULL)
		{
			f2<<"	"<<Edge->GetfromGu()<<"		"<<Edge->GettoGu()<<"		   "<<Edge->Getdis()<<endl;//파일에 출력
			Edge = Edge->GetGuEdgeNext();//다음 edge를 가리킨다
		}
		gu = gu->GetGuNext();
	}

	f2.close();
	return true;//파일을 닫아주고 참 반환
}

bool Manager::Save_Dong()//동 저장
{
	ofstream f1("dong_vertex.bak",ios::out);//입력 받은 파일명으로 객체ff 생성
	if( !(f1.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	GuVertex *gu = ADJList.GetGuHead();
	DongVertex *Dong = NULL;//구와 동을 위한 포인터 변수

	if(gu==NULL)
	{
		cout<<"저장되어있는 구 정보가 없습니다"<<endl;
		f1.close();
		return false;//저장되어있는 구가 없다면 화면에 출력 거짓 반환
	}

	for(int i=0; i<35; i++)
		f1<<"==";
	f1<<endl<<"	구 명칭		동 명칭		난방 관제소 여부(0/X)"<<endl;
	for(int i=0; i<35; i++)
		f1<<"==";
	f1<<endl; //해당 문구를 출력해준다

	while(gu != NULL)//모든 동을 출력해준다
	{
		Dong = gu->GetDongHead();
		if(Dong !=NULL)
		{
			do
			{
				f1<<"	"<<gu->GetGuName()<<"		"<<Dong->GetDongName()<<"			"<<Dong->GetView()<<endl;//파일에 출력
				Dong = Dong->GetdongNext();//다음 동을 가리킨다
			}while(Dong != gu->GetDongHead() );
		}
		gu = gu->GetGuNext();
	}

	f1.close();//파일을 닫아준다

	ofstream f2("dong_edge.bak",ios::out);//입력 받은 파일명으로 객체ff 생성
	if( !(f2.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	gu = ADJList.GetGuHead();
	Dong = NULL;
	DongEdge *Edge = NULL;//임시 포인터 변수

	for(int i=0; i<40; i++)
		f2<<"==";
	f2<<endl<<"	구 명칭		from(동)	to(동)		열 손실률(%)"<<endl;
	for(int i=0; i<40; i++)
		f2<<"==";
	f2<<endl; //해당 문구를 출력해준다

	while(gu != NULL)//모든 동 edge를 출력해주기 위한 반복문
	{
		Dong = gu->GetDongHead();

		if(Dong != NULL)//저장되어있는 동이 존재한다면
		{
			do//동의 끝까지 반복한다
			{
				Edge = Dong->GetdongedgHead();
				while(Edge !=NULL)
				{
					f2<<"	"<<gu->GetGuName()<<"		"<<Edge->GetfromDong()<<"		"<<Edge->GettoDong()<<"		"<<Edge->GetLossrate()<<endl;

					Edge = Edge->GetDongEdgeNext();//다음 edge를 가리킨다
				}
				Dong = Dong->GetdongNext();//다음 동을 가리킨다
			}while(Dong != gu->GetDongHead() );//원형링크드리스트 처음의 노드까지 반복한다
		}
		gu = gu->GetGuNext();
	}

	f2.close();
	return true;//파일을 닫아주고 참 반환
}

bool Manager::Save_Mechanic()//정비사 목록을 저장한다
{
	ofstream f("mechanic.bak",ios::out);//mechanic_list.txt파일을 열어준다.
	if( !(f.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	for(int i=0; i<22; i++)
		f<<"==";
	f<<endl<<"	근무지		정비사 이름"<<endl;
	for(int i=0; i<22; i++)
		f<<"==";
	f<<endl;//파일에 해당문구를 출력해준다

	Mechanic *temp = MechanicList.GetMechanicHead();//정비사 리스트의 헤더를 반환한다

	if(temp == NULL)//예외처리
	{
		cout<<"저장되어있는 정비사 목록이 없습니다"<<endl;
		return false;
	}

	while(temp != NULL)//temp의 끝까지 반복한다
	{
		f<<"	"<<temp->GetMechanicGu()<<"		 "<<temp->GetMechanicName()<<endl;//해당 문구를 출력해준다
		temp = temp->GetMechanicNext();//다음 정비사를 가리킨다
	}

	f.close();//파일을 닫아준다
	EXIT();
	return true;//참반환
}

Mechanic *Manager::ShortestPath(GuVertex *Gu)//최단 거리 구하는 함수
{
	for(int i= 0;i<3;i++) // 3*100 배열 초기화
	{
		if(i==0)
		{
			for(int j=0; j<100; j++)
				Short[i][j]=100;
		}
		else if(i==1)
		{
			for(int j=0; j<100; j++)
				Short[i][j]=0;
		}
		else
		{
			for(int j=0; j<100; j++)
				Short[i][j]=-1;
		}
	}

	GuVertex *tempGu = NULL;
	GuVertex *toGu = NULL;

	int From = Gu->GetShortflag();
	Short[0][From] = 0;
	Short[1][From] = 1;//출발지의 값들을 세팅해준다

	GuEdge *tempEdge = Gu->GetGuedgHead();
	while(tempEdge != NULL)
	{
		tempGu = ADJList.SearchGuVertex( tempEdge->GettoGu() );
		Short[0][tempGu->GetShortflag()] = tempEdge->Getdis();
		Short[2][tempGu->GetShortflag()] = From;
		tempEdge = tempEdge->GetGuEdgeNext();
	}//출발지와 연결된 모든 구 edge를 반복하면서 값을 셋팅해준다

	while(1)//최단거리를 구하기 위한 무한루프
	{
		if( FinishShortestPath() )//완료되었다면 
			break;//무한루프 종료
		else
		{
			From = MinDis();//저장되어있는 거리중 최소값의 index를 반환한다
			tempGu = ADJList.SearchGuVertex(From);
			Short[1][From] = 1;

			tempEdge = tempGu->GetGuedgHead();

			while(tempEdge !=NULL)//tempedge를 끝까지 반복한다
			{
				toGu = ADJList.SearchGuVertex( tempEdge->GettoGu() );
				//거리 값이 바뀌어야 한다면 
				if( (Short[0][From]) + ( tempEdge->Getdis() ) < Short[0][toGu->GetShortflag()] )
				{
					Short[0][toGu->GetShortflag()] = (Short[0][From]) + ( tempEdge->Getdis() );
					Short[2][toGu->GetShortflag()] = From;//바꿔주고 어디서부터 왔는지를 저장한다
				}
				tempEdge = tempEdge->GetGuEdgeNext();//다음 edge를 가리킨다
			}
		}
	}
	tempGu = NULL;

	Mechanic *tempMan = MechanicList.GetMechanicHead();
	Mechanic *Man = MechanicList.GetMechanicHead();

	while(tempMan !=NULL)//정비사를 반복한다
	{
		tempGu = ADJList.SearchGuVertex( tempMan->GetMechanicGu() );
		tempMan->SetDistence( Short[0][tempGu->GetShortflag()] );
		//목적지로 부터 가장 가까운 정비사를 찾아준다
		if( tempMan->GetDistence() < Man->GetDistence() )
			Man = tempMan;

		tempMan = tempMan->GetMechanicNext();
	}

	return Man;//가장가까운 위치에 있는 정비사를 반환한다
}

bool Manager::FinishShortestPath()//최단경로 완료 여부를 검사한다
{
	int column = ADJList.CountGu();
	int con =0;

	for(int i=0;i < column;i++)
	{
		if(Short[1][i]==0)//값이 0이라면 카운터 증가
			con++;
	}

	if(con==0)// 모든 구 방문 완료
		return true;//참반환
	else//방문이 완료되지 않았다면
		return false;//거짓반환
}

int Manager::MinDis()//거리값중 최소 값을 찾는 함수
{
	int pivot=100;
	int index;
	int column = ADJList.CountGu();//구의 갯수를 반환받는다

	for(int i=0; i<column;i++)
	{
		//더 작은 값을 찾게 된다면
		if( (Short[0][i] > 0) && (Short[0][i] < 100) && (Short[0][i] < pivot) && (Short[1][i] == 0) )
		{
			pivot = Short[0][i];
			index = i;//그 값의 index를 저장하고 pivot 값도 바꿔준다
		}
	}

	return index;//최소 값의 index를 반환한다
}

bool Manager::EXIT()//소멸자
{
	GuVertex *Gu = ADJList.GetGuHead();
	GuVertex *pGu = NULL;

	GuEdge *Edge = NULL;
	GuEdge *pEdge = NULL;

	DongVertex *Dong = NULL;
	DongVertex *pDong = NULL;

	DongEdge *Dong_edge = NULL;
	DongEdge *pDong_edge = NULL;//소멸을 위한 포인터 변수

	while(Gu != NULL)//동이 원형 리스트 인것을 1D list로 바꿔준다
	{
		Dong = Gu->GetDongHead();
		if(Dong !=NULL)
		{
			pDong = Dong->GetdongNext();
			while(1)
			{
				if(pDong->GetdongNext() == Dong)//마지막 동 노드라면
				{
					pDong->SetdongNext(NULL);//NULL을 넣어준다
					break;
				}
				pDong = pDong->GetdongNext();
			}
		}
		Gu = Gu->GetGuNext();
	}

	Gu = ADJList.GetGuHead();
	while(Gu != NULL)//동 에 관한 정보들을 삭제해 준다
	{
		Dong = Gu->GetDongHead();
		while(Dong !=NULL)
		{
			Dong_edge = Dong->GetdongedgHead();
			while(Dong_edge !=NULL)
			{
				pDong_edge = Dong_edge;
				Dong_edge = Dong_edge->GetDongEdgeNext();
				delete pDong_edge;
			}
			pDong = Dong;
			Dong = Dong->GetdongNext();
			delete pDong;
		}
		Gu = Gu->GetGuNext();
	}

	Gu = ADJList.GetGuHead();
	while(Gu != NULL)//구에 관한 정보들을 삭제해준다
	{
		Edge = Gu->GetGuedgHead();
		while(Edge !=NULL)
		{
			pEdge = Edge;
			Edge = Edge->GetGuEdgeNext();
			delete pEdge;
		}
		pGu = Gu;
		Gu = Gu->GetGuNext();
		delete pGu;
	}
	ADJList.SetHead();

	Mechanic *temp = MechanicList.GetMechanicHead();//정비사 리스트의 헤더를 반환한다
	Mechanic *ptemp = NULL;

	while(temp != NULL)//정비사 목록을 삭제해준다
	{
		ptemp = temp;
		temp = temp->GetMechanicNext();
		delete ptemp;
	}
	MechanicList.SetHead();

	return true;
}

