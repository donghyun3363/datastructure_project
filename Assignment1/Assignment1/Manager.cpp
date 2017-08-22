#include "Manager.h"

Manager::Manager(void)//생성자
{
}

Manager::~Manager(void)//소멸자
{
}

bool Manager::LoadFile(char* pFileName)
{
	ifstream fin;//파일 스트림 형성
	char str[200]={0,};//한줄씩 받기 위한 배열 선언
	char r_str[10]={0,};//지역 코드를 위한 배열 선언

	char *temp_fi = NULL;
	char *temp_num=NULL;//문자열을 짜르기 위한 char형 임시 포인터 선언
	char *temp=NULL;

	NumNode *n=NULL;//객체 포인터 생성
	RegionNode *r=NULL;


	fin.open(pFileName,ios::in);//입력 받은 파일명으로 파일을 읽기 모드로 열어준다
	if( !(fin.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	for(int i=0;i<3;i++)//메모장에 필요 없는 라인을 지워준다
		fin.getline(str,200);
	memset(str,NULL,sizeof(str));//배열을 NULL로 초기화

	while( !(fin.eof()) )//파일의 끝까지 반복한다
	{
		RegionNode *N_temp=list.GetHead();
		NumNode *down = NULL;
		int conre=0;
		int connum=0;

		fin.getline(str,200);//파일에서 한줄을 받아온다
		strncpy(r_str, str, sizeof(r_str) ); //r_str 크기만큼 str에 있는 정보를 복사해준다

		temp=strtok(r_str,"	-");//지역 코드를 얻기위한 strtok
		temp_num=strtok(str,"	/");//탭,/ 기준으로 문자열을 짤라 저장한다
		temp_fi=strtok(NULL,"	/");//탭,/ 기준으로 문자열을 짤라 저장한다

		if( strcmp( temp_fi, "Y" ) == 0 )
		{
			n = new NumNode();//NumNode 메모리 할당                               
			n->SetFinish(temp_fi);//배송여부를 저장한다
			n->SetNum(temp_num);//운송장 번호를 저장한다
			informationinsert(n);
			cir.Insert(n);
		}
		else if(strcmp( temp_fi, "N" ) == 0)//배송이 완료되지 않았다면
		{
			while(N_temp != NULL)//동일한 지역 코드가 존재 하는지 확인한다
			{
				if(strcmp( temp, N_temp->GetRegionNumber() ) == 0)
				{
					down = N_temp->GetN_Head();
					conre++; // 지역코드 카운터
				}
				N_temp = N_temp->GetNext();
			}

			while(down != NULL)//동일한 운송장 번호가 저장되어있는지 확인한다
			{
				if( strcmp(temp_num, down->GetNum() ) ==0)
				{
					connum++;
					break;
				}
				down = down->GetNext();
			}

			if(connum == 0)//운송장 번호가 저장되어있지 않다면
			{
				if(conre==0)//지역 노드가 저장되어있지 않다면
				{
					r = new RegionNode();//RegionNode 메모리 할당
					n = new NumNode();//NumNode 메모리 할당 
					n->SetFinish(temp_fi);//배송여부를 저장한다
					n->SetNum(temp_num);//운송장 번호를 저장한다
					r->SetRegionNumber(temp);//지역코드를 저장한다
					if( !(list.pInsert(r)) ) //지역코드들을 연결하기위해 2D pInsert 함수 호출
						return false;//실패 했다면 false 반환
				}

				else//지역 노드가 저장되어있다면
				{
					n = new NumNode();//NumNode 메모리 할당 
					n->SetFinish(temp_fi);//배송여부를 저장한다
					n->SetNum(temp_num);//운송장 번호를 저장한다
				}
				if( ! (list.cInsert(temp,n)) ) //운송장번호를 저장하기위해 cInsert 함수 호출
					return false;//실패 했다면 false 반환
			}
		}
		temp=NULL;//temp를 NULL로 초기화
		temp_fi=NULL;//temp2를 NULL로 초기화 한다
		temp_num=NULL;
		memset(str,NULL,sizeof(str));//배열들을 NULL로 초기화한다
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
	ifstream f; //파일 스트림 형성
	char str[100]={0,};//한줄씩 받기 위한 배열 선언
	char r_str[20]={0,};//문자열을 짜르기 위한 char형 포인터 선언
	char *temp=NULL; 
	char *temp2=NULL;

	RegionNode *Rhead = NULL;

	f.open("region_code.txt",ios::in);//파일명으로 파일을 읽기 모드로 열어준다
	if( !(f.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	for(int i=0;i<3;i++)//메모장에 필요 없는 라인을 지워준다
		f.getline(str,100);
	memset(str,NULL,sizeof(str));

	while( !(f.eof()) )//파일의 끝까지 반복한다
	{
		Rhead = list.GetHead() ;
		f.getline(str,200);//파일에서 한줄을 받아온다

		strncpy( r_str, str, sizeof(r_str) );//지역을 저장하기위한 배열
		temp=strtok(r_str,"	/");//탭,/ 기준으로 문자열을 짤라 저장한다
		temp2=strtok(str,"	/");//탭,/ 기준으로 문자열을 짤라 저장한다
		temp2=strtok(NULL,"	/");//탭,/ 기준으로 문자열을 짤라 저장한다

		while( Rhead != NULL)
		{
			if(strcmp( temp2, Rhead->GetRegionNumber() ) == 0)//일치하는 운송장 번호가 있다면
			{
				Rhead->SetCity(temp);//도시를 설정한다
				break;//while 종료
			}
			Rhead = Rhead->GetNext();
		}

		temp=NULL;//temp를 NULL로 초기화
		temp2=NULL;
		memset(str,NULL,sizeof(str)); //초기화 해준다
		memset(r_str,NULL,sizeof(r_str));

	}
	f.close();//파일 스트림을 받아준다
	return true;
}

bool Manager::informationinsert()
{
	ifstream f;
	char str[100]={0,};
	char i_str[20]={0,};
	char *temp=NULL;//문자열을 짜르기 위한 char형 포인터 선언
	char *temp2=NULL;

	RegionNode *head=NULL;
	NumNode *Ntemp=NULL;

	f.open("item_code.txt",ios::in);//입력 받은 파일명으로 파일을 읽기 모드로 열어준다
	if( !(f.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	for(int i=0;i<3;i++)//메모장에 필요 없는 라인을 지워준다
		f.getline(str,100);
	memset(str,NULL,sizeof(str));

	while( !(f.eof()) )//파일의 끝까지 반복한다
	{
		f.getline(str,200);//파일에서 한줄을 받아온다

		strncpy( i_str, str, sizeof(i_str) );

		temp=strtok(i_str,"	/");//탭,/ 기준으로 문자열을 짤라 저장한다
		temp2=strtok(str,"	/");//탭,/ 기준으로 문자열을 짤라 저장한다
		temp2=strtok(NULL,"	/");//탭,/ 기준으로 문자열을 짤라 저장한다
		//temp에 품목이름이 temp2에 물품정보

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
					Ntemp->SetItem(temp);//물품정보

					if(Ntemp->GetNum()[11]=='1')//취급 정보
						Ntemp->SetTreat("Y");
					else if(Ntemp->GetNum()[11]=='0')
						Ntemp->SetTreat("N");
				}
				Ntemp=Ntemp->GetNext();//다음 운송정보노드 대입
			}

			head=head->GetNext();//다음 지역코드 노드 대입
		}
		temp=NULL;//temp를 NULL로 초기화
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
	RegionNode *FindNode = NULL;// 찾고자하는 지역 번호의 노드를 저장하기위한 포인터
	NumNode *Ctemp=NULL;//자식 노드들을  저장하기 위한 포인터
	int con=0;

	ofstream ff("find_parcel.txt",ios_base::app);//find_parcel.txt라는 파일 객체 ff생성
	//누적기록이 가능하도록 선언
	if( !(ff.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	FindNode = Root.Serch(Fnum);//BST를 이용하여 찾고자 하는 지역번호의 노드를 찾는다
	if(FindNode == NULL)//찾는 노드가 없다면
	{
		ifstream f;//region_code.txt라는 파일 객체생성 f
		char str[100]={0,}; //메모장의 내용을 받기위한 str 선언
		char r_str[20]={0,};
		char *temp=NULL; //필요한 정보를 짤라 저장하기위한 char 포인터
		char *temp2=NULL;
		f.open("region_code.txt",ios::in);//파일을 읽기 모드로 열어준다

		if( !(f.is_open()) )//파일 오픈이 실패했다면
			return false;//거짓을 반환한다

		for(int i=0;i<3;i++)//메모장에 필요 없는 라인을 지워준다
			f.getline(str,100);
		memset(str,NULL,sizeof(str));

		while( !(f.eof()) )//파일의 끝까지 반복한다
		{
			f.getline(str,200);//파일에서 한줄을 받아온다

			strncpy( r_str, str, sizeof(r_str) );//지역을 저장하기위한 배열
			temp=strtok(r_str,"	/");//탭,/ 기준으로 문자열을 짤라 지역을 저장한다
			temp2=strtok(str,"	/");//탭,/ 기준으로 문자열을 짤라 저장한다
			temp2=strtok(NULL,"	/");//탭,/ 기준으로 문자열을 짤라 지역번호를 저장한다
			if( strcmp(temp2, Fnum) == 0)//찾고자 하는 번호와 같다면
				break;
			temp=NULL;//temp를 NULL로 초기화
			temp2=NULL;
			memset(str,NULL,sizeof(str)); //배열을 초기화 해준다
			memset(r_str,NULL,sizeof(r_str));
		}
		ff<<endl<<temp<<"로 배송되는 물품은 없습니다."<<endl;
		f.close();//region_code.txt를 닫아준다.
	}

	else//찾는 노드가 있다면
	{
		for(int k=0;k<50;k++)//문구 출력
			ff<<"==";
		ff<<endl;
		ff<<"배송지역	|	배송물품	|  취급주의	|	배송여부	|	운송장번호	|"<<endl;
		for(int k=0;k<50;k++)
			ff<<"==";
		ff<<endl;//개행

		Ctemp = FindNode->GetN_Head();//자식 노드의 헤더를 저장한다
		while( Ctemp !=NULL )//자식노드의 끝까지 가기위한 while 문
		{
			if(Ctemp->GetNext() == NULL)//마지막 라인을 출력해줄때 엔터키를 지워준다
			{ //다음 정보들을 출력해준다.
				ff<<FindNode->GetCity()<<"		/	"<<Ctemp->GetItem()<<"	/	"<<Ctemp->GetTreat()<<"		/	"<<Ctemp->GetFinish()<<"		/	";
				ff<<Ctemp->GetNum()<<"	/	";
			}
			else//마지막 라인이 아니라면 엔터키를 넣어준다
			{
				ff<<FindNode->GetCity()<<"		/	"<<Ctemp->GetItem()<<"	/	"<<Ctemp->GetTreat()<<"		/	"<<Ctemp->GetFinish()<<"		/	";
				ff<<Ctemp->GetNum()<<"	/	"<<endl;
			}
			Ctemp = Ctemp->GetNext();//다음 자식노드를 가리키게 한다
		}
	}
	ff.close();//find_parcel.txt 파일을 닫아준다.
	return true;//참 반환

}

bool Manager::SAVE(char* pFileName)
{
	RegionNode *current = Root.GetRoot(); //BST의 root를 저장한다
	NumNode *temp=NULL;//NumNode 포인터 변수를 선언한다
	NumNode *Cirhead = cir.GetCirHead();//원형 리스트의 head를 저장한다

	ofstream ff(pFileName,ios::out);//입력 받은 파일명으로 객체ff 생성

	if( !(ff.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	if( (current ==NULL) && (Cirhead==NULL) )//BST와 원형에 저장되어있는 정보가 없다면
	{
		cout<<"저장하고자 하는 정보가 없습니다."<<endl;
		return false;//위에문구 출력과 false 반환
	}
	for(int k=0;k<27;k++)
		ff<<"==";
	ff<<endl;
	ff<<"|	운송장번호	|	배송여부	|"<<endl;
	for(int k=0;k<27;k++)
		ff<<"==";
	ff<<endl;//해당 문구를 파일에 출력해준다.

	while(current != NULL) //BST 정보를 출력해주기 위한 while문
	{
		temp = current->GetN_Head();//자식노드의 head를 저장한다
		while(temp != NULL)//자식 노드 끝까지 반복한다
		{
			if( (Que.IsEmpty() ) && (Cirhead==NULL) )//마지막 라인이라면
			{
				ff<<"	"<<temp->GetNum()<<"	/	"<<temp->GetFinish()<<"	/	";
			}//enter를 지우고 위 정보들을 출력해준다
			else//마지막 라인이 아니라면
			{
				ff<<"	"<<temp->GetNum()<<"	/	"<<temp->GetFinish()<<"	/	"<<endl;
			}//해당정보를 출력해준다
			temp=temp->GetNext();//다음 자식노드를 가리키게 한다
		}
		//Lever-order 방식으로 que에 저장해놓기 위한 조건문
		if(current->GetLeftNext() !=NULL)
			Que.Push( current->GetLeftNext() );
		if( current->GetRightNext() !=NULL )
			Que.Push( current->GetRightNext() );
		if( Que.IsEmpty())//que가 비어있다면 
			break;//while문 종료
		current = Que.Pop();// current는 que에서 pop 해준다
	}
	if(Cirhead !=NULL )
	{
		NumNode *pCur = Cirhead->GetCirNext();//원형 리스트를 출력해준다
		while( 1 )//무한루프
		{
			if( pCur->GetCirNext() == Cirhead )//원형리스트의 마지막이라면
			{
				ff<<"	"<<pCur->GetNum()<<"	/	"<<pCur->GetFinish()<<"	/";
				break;//해당저보출력 무한루프 종료
			}
			else
			{
				ff<<"	"<<pCur->GetNum()<<"	/	"<<pCur->GetFinish()<<"	/"<<endl;
			}//해당정보 출력
			pCur = pCur->GetCirNext();//다음 리스트를 가리키게 한다.
		}
	}
	return true;
}

bool Manager::PRINT()
{
	RegionNode *current = Root.GetRoot();//BST의 root를 저장한다
	RegionNode *del = Root.GetRoot();
	NumNode *temp=NULL;//임시 포인터 선언
	NumNode *Cirhead = cir.GetCirHead();//원형 리스트의 head를 저장한다

	ofstream ff("print_parcel.txt",ios_base::app);//print_parcel.txt라는 파일 객체 ff생성
	if( !(ff.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	if( (current ==NULL) && (Cirhead==NULL) )//BST와 원형에 저장되어있는 정보가 없다면
	{
		cout<<"저장하고자 하는 정보가 없습니다."<<endl;
		return false;//위에문구 출력과 false 반환
	}

	for(int k=0;k<45;k++)
		ff<<"==";
	ff<<endl;
	ff<<"	배송지역		|	배송물품	|  취급주의		|	배송여부	|	운송장번호	|"<<endl;
	for(int k=0;k<45;k++)
		ff<<"==";
	ff<<endl;//파일에 해당 문구를 출력해준다

	if(! ( Que.IsEmpty()) )//Que에 남아있는 노드가 있다면
	{
		while(1)//que를 비워준다
		{
			del=Que.Pop();//pop한 노드를 삭제해준다.
			delete del;
			if( Que.IsEmpty() )//que가 빈다면 
				break;//무한루프 
		}
	}
	temp=NULL;//temp를 NULL로 초기화
	inorder_print(current);//inorder_print함수를 호출해서 que에 저장한다

	while(1)//que가 빌때까지 반복하기위한 무한루프
	{
		if( Que.IsEmpty() )//que에 저장되어있는 정보가 없다면 
			break;//무한루프 종료
		current=Que.Pop();//current에 pop한 결과를 넣는다
		temp=current->GetN_Head();//temp에는 자식노드의 헤더를 넣어준다.
		while(temp != NULL)//자식노드 끝까지 반복한다
		{
			ff<<current->GetCity()<<"	/	"<<temp->GetItem()<<"	/	"<<temp->GetTreat()<<"		/	"<<temp->GetFinish()<<"		/	";
			ff<<temp->GetNum()<<"	/	"<<endl;//위정보들을 출력한다
			temp = temp->GetNext();//다음자식노드를 가리킨다.
		}
	}
	if(Cirhead !=NULL)
	{
		NumNode *pCur = Cirhead->GetCirNext();//원형 리스트를 출력해준다
		if(pCur != NULL) //원형 리스트에 저장되어있는 정보가 있다면
		{
			while( 1 )//무한루프
			{
				ifstream f; //파일 스트림 형성
				char str[100]={0,};//한줄씩 받기 위한 배열 선언
				char r_str[20]={0,};//문자열을 짜르기 위한 char형 포인터 선언
				char *city=NULL; 
				char *temp2=NULL;

				f.open("region_code.txt",ios::in);//파일명으로 파일을 읽기 모드로 열어준다
				if( !(f.is_open()) )//파일 오픈이 실패했다면
					return false;//거짓을 반환한다

				for(int i=0;i<3;i++)//메모장에 필요 없는 라인을 지워준다
					f.getline(str,100);
				memset(str,NULL,sizeof(str));

				while( !(f.eof()) )//파일의 끝까지 반복한다
				{
					f.getline(str,200);//파일에서 한줄을 받아온다

					strncpy( r_str, str, sizeof(r_str) );//지역을 저장하기위한 배열
					city=strtok(r_str,"	/");//탭,/ 기준으로 문자열을 짤라 저장한다
					temp2=strtok(str,"	/");//탭,/ 기준으로 문자열을 짤라 저장한다
					temp2=strtok(NULL,"	/");//탭,/ 기준으로 문자열을 짤라 저장한다
					if( strncmp(pCur->GetNum(), temp2, 3) == 0)
					{
						break;
					}

					city=NULL;//temp를 NULL로 초기화
					temp2=NULL;
					memset(str,NULL,sizeof(str)); //초기화 해준다
					memset(r_str,NULL,sizeof(r_str));
				}
				f.close();//파일 스트림을 받아준다

				if( pCur->GetCirNext() == Cirhead )//원형리스트의 마지막이라면
				{
					ff<<city<<"	/	"<<pCur->GetItem()<<"	/	"<<pCur->GetTreat()<<"		/	"<<pCur->GetFinish()<<"		/	";
					ff<<pCur->GetNum()<<"	/	"<<endl;//위정보들을 출력한다
					break;//해당저보출력 무한루프 종료
				}
				else
				{
					ff<<city<<"	/	"<<pCur->GetItem()<<"	/	"<<pCur->GetTreat()<<"		/	"<<pCur->GetFinish()<<"		/	";
					ff<<pCur->GetNum()<<"	/	";//위정보들을 출력한다
				}//해당정보 출력
				pCur = pCur->GetCirNext();//다음 리스트를 가리키게 한다.
			}
		}
	}

	ff.close();
	return true;//참 반환
}

void Manager::inorder_print(RegionNode *current)//inorder로 저장하기 위한 함수
{
	if(current == NULL)
		return ;
	inorder_print( current->GetLeftNext() ); //가장 왼쪽 subtree에 접근하여 거기서 부터 queue에 넣어준다
	Que.Push(current);
	inorder_print( current->GetRightNext() );//오른쪽 subtree의 지역코드를 저장한다
}

bool Manager::UPDATE(char* pFileName)
{
	ifstream fin;//파일 스트림 형성
	char str[200]={0,};//한줄씩 받기 위한 배열 선언
	char tempstr[60]={0,};//지역 코드를 위한 배열 선언

	char *before_num=NULL;
	char *before_re=NULL;
	char *after_num=NULL;
	char *after_re=NULL;

	char *temp=NULL;//문자열을 짜르기 위한 char형 임시 포인터 선언
	char *temp2=NULL;

	NumNode *n=NULL;//객체 포인터 생성
	RegionNode *r=NULL;

	fin.open(pFileName,ios::in);//입력 받은 파일명으로 파일을 읽기 모드로 열어준다
	if( !(fin.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	for(int i=0;i<3;i++)//메모장에 필요 없는 라인을 지워준다
		fin.getline(str,200);
	memset(str,NULL,sizeof(str));//배열을 NULL로 초기화

	while( !(fin.eof()) )//파일의 끝까지 반복한다
	{
		RegionNode *N_temp=list.GetHead();
		RegionNode *findNode=NULL;
		NumNode *cNode=NULL;;
		int conre=0;
		int connum=0;

		fin.getline(str,200);//파일에서 한줄을 받아온다

		strncpy(tempstr,str, sizeof(tempstr) ); //r_str 크기만큼 str에 있는 정보를 복사해준다

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
				n = new NumNode();//NumNode 메모리 할당
				n->SetNum(after_num);
				n->SetFinish(temp);
				cir.Insert(n);
			}
			else
			{
				list.Delete(after_num,after_re);
				list.Pdelete(findNode);
				Root.Delete(findNode);
				n = new NumNode();//NumNode 메모리 할당
				n->SetNum(after_num);
				n->SetFinish(temp);
				cir.Insert(n);
			}
		}

		else if(strcmp(temp,"N") == 0) //배송 no
		{
			if( strcmp(before_num, after_num) == 0) //앞뒤 운송장 같으면
			{
				n = new NumNode();//NumNode 메모리 할당
				r = new RegionNode();//RegionNode 메모리 할당
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
					n = new NumNode();//NumNode 메모리 할당
					r = new RegionNode();//RegionNode 메모리 할당
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
					n = new NumNode();//NumNode 메모리 할당
					r = new RegionNode();//RegionNode 메모리 할당
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
		temp=NULL;//temp2를 NULL로 초기화 한다
		memset(str,NULL,sizeof(str));//배열들을 NULL로 초기화한다
		memset(tempstr,NULL,sizeof(tempstr));
	}
	fin.close();
	return true;

}

bool Manager::EXIT()
{
	//2D 리스트를 삭제해 준다
	RegionNode *Phead = list.GetHead();
	RegionNode *parCur = NULL;
	NumNode *Chead = Phead->GetN_Head();
	NumNode *chilCur = NULL;
	RegionNode *temp=NULL;

	while(Phead !=NULL )//부모노드를 반복한다
	{
		NumNode *Chead = Phead->GetN_Head();//자식노드의 head 값을 저장한다
		while(Chead !=NULL )//자식노드를 반복한다
		{
			chilCur = Chead;//자식노드의 head를 바꿔주고
			Chead = Chead->GetNext();
			delete chilCur;//chilCur을 삭제해준다
		}
		parCur = Phead;//부모노드의 head를 바꿔준다
		Phead = Phead->GetNext();
		delete parCur;//parCur을 삭제해준다
	}

	if(! ( Que.IsEmpty()) )//Que에 남아있는 노드가 있다면
	{
		while(1)//que를 비워준다
		{
			temp=Que.Pop();//pop한 노드를 삭제해준다.
			delete temp;
			if( Que.IsEmpty() )//que가 빈다면 
				break;//무한루프 
		}
	}

	NumNode* Cirhead = cir.GetCirHead();
	if(Cirhead !=NULL)
	{
		NumNode* pCur= Cirhead->GetCirNext();//원형리스트를 삭제해준다
		while(1)//원형리스트를 그냥 리스트로 바꿔준다.
		{
			if(pCur->GetCirNext() == Cirhead )//마지막노드를 찾는다
			{
				pCur->SetCirNext(NULL);//마지막노드의 next 자리에 NULL을 넣어준다
				break;//무한루프 종료
			}
			pCur = pCur->GetCirNext();
		}
		pCur = Cirhead ;//다시 head를 넣어준다
		while(Cirhead!=NULL) //할당한 노드들을 삭제해준다
		{
			pCur=Cirhead;
			Cirhead = Cirhead->GetCirNext(); 
			delete pCur; 
		}
	}
	return true;//참 반환
}

bool Manager::informationinsert(NumNode *pNode) //운송장 번호를 받아서 정보를 저장하는 informationinsert 함수 오보로딩
{
	ifstream f;
	char str[100]={0,};
	char i_str[20]={0,};
	char *temp=NULL;//문자열을 짜르기 위한 char형 포인터 선언
	char *temp2=NULL;

	f.open("item_code.txt",ios::in);//입력 받은 파일명으로 파일을 읽기 모드로 열어준다
	if( !(f.is_open()) )//파일 오픈이 실패했다면
		return false;//거짓을 반환한다

	for(int i=0;i<3;i++)//메모장에 필요 없는 라인을 지워준다
		f.getline(str,100);
	memset(str,NULL,sizeof(str));

	while( !(f.eof()) )//파일의 끝까지 반복한다
	{
		f.getline(str,200);//파일에서 한줄을 받아온다

		strncpy( i_str, str, sizeof(i_str) );

		temp=strtok(i_str,"	/");//탭,/ 기준으로 문자열을 짤라 저장한다
		temp2=strtok(str,"	/");//탭,/ 기준으로 문자열을 짤라 저장한다
		temp2=strtok(NULL,"	/");//탭,/ 기준으로 문자열을 짤라 저장한다
		//temp에 품목이름이 temp2에 물품정보

		char cur[2]={0,};

		cur[0]=pNode->GetNum()[10];
		if( strcmp(temp2, cur) == 0 )
		{
			pNode->SetItem(temp);//물품정보

			if(pNode->GetNum()[11]=='1')//취급 정보
				pNode->SetTreat("Y");
			else if(pNode->GetNum()[11]=='0')
				pNode->SetTreat("N");
		}


		temp=NULL;//temp를 NULL로 초기화
		temp2=NULL;
		memset(str,NULL,sizeof(str));
		memset(i_str,NULL,sizeof(i_str));
	}
	f.close();
	return true;
}
