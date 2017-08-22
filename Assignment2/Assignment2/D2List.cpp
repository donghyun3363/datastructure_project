#include "D2List.h"
#include <iostream>//헤더파일선언

using namespace std;//이름공간에 std 저장후 사용

D2List::D2List(void)//생성자
{
	pHead=NULL;
}

D2List::~D2List(void)//소멸자
{
}

bool D2List::Insert(User *MeNode, User *FriNode)//친구 연결 함수
{
	pHead = MeNode->GetFri();//나의 연결노드 헤더 값을 반환한다.
	Linked *temp = NULL;
	Linked *pretemp = NULL;//임시 포인터 선언
	Linked *list = new Linked();//새로운 친구의 연결 노드 생성

	int check =0;//check를 위한 변수 선언

	if( pHead == NULL )//헤더가 비어있다면
	{
		list->SetDown(FriNode);
		MeNode->SetFri(list);//헤더로 지정해준다
		check++;//check 증가
	}

	else//자료가 있다면
	{
		if( strcmp( (pHead->GetDown())->GetName(), FriNode->GetName() ) > 0 ) //새로운 노드의 이름이 헤더보다 빠르다면
		{
			list->SetNext(pHead);
			list->SetDown(FriNode);
			MeNode->SetFri(list);//헤더를 바꿔주고 연결을 다시 지정해 준다.
			check++;//check 증가
		}

		else if(strcmp( (pHead->GetDown())->GetName(), FriNode->GetName() ) == 0)//헤더의 이름과 같은경우
		{
			if( strcmp( (pHead->GetDown())->GetNumber(), FriNode->GetNumber() ) > 0)//헤더의 학번과 비교한다
			{
				list->SetNext(pHead);
				list->SetDown(FriNode);
				MeNode->SetFri(list);//헤더의 학번보다 빠르다면 헤더를 바꿔주고 연결을 다시 지정해준다
				check++;//check 증가
			}
			else///헤더의 학번보다 느리다면
			{
				list->SetNext(pHead->GetNext());
				list->SetDown(FriNode);
				pHead->SetNext(list);//헤더 다음에 연결 해준다.
				check++;//check 증가
			}
		}

		else//헤더의 이름보다 느리다면
		{
			pretemp=pHead;
			while(1)//들어갈 자리를 찾기위한 무한 루프
			{
				if(pretemp->GetNext() == NULL)//맨마지막에 위치해야한다면
				{
					pretemp->SetNext(list);
					list->SetDown(FriNode);//맨마지막에 연결을 해준다.
					check++;
					break;//check 증가 무한루프종료
				}

				temp = pretemp->GetNext();
				if( strcmp( (temp->GetDown())->GetName(), FriNode->GetName() ) > 0)//temp의 이름보다 빠르다면
				{
					list->SetNext(temp);
					list->SetDown(FriNode);
					pretemp->SetNext(list);//temp와 pretemp사이에 위치시킨다
					check++;
					break;//check 증가 무한루프 종료
				}
				else if(strcmp( (temp->GetDown())->GetName(), FriNode->GetName() ) == 0)//temp의 이름과 같다면
				{
					if( strcmp( (temp->GetDown())->GetNumber(), FriNode->GetNumber() ) > 0)//temp의 학번보다 빠르다면
					{
						list->SetNext(temp);
						list->SetDown(FriNode);
						pretemp->SetNext(list);//temp와 pretemp사이에 위치시킨다
						check++;
						break;//check 증가 무한루프 종료
					}
					else//temp의 학번보다 느리다면
					{
						list->SetNext(temp->GetNext());
						list->SetDown(FriNode);
						temp->SetNext(list);//temp 뒤에 위치 시킨다
						check++;
						break;//check 증가 무한루프 종료
					}
				}
				pretemp = pretemp->GetNext();//pretemp를 pretemp다음 노드를 가리키게 한다.
			}
		}
	}

	if(check==0)//Insert가 이루어 지지 않았다면
		return false;//거짓 반환
	else//Insert가 이루어 졌다면       
		return true;//참 반환
}

int D2List::SearchFri(User *Node, char *friName)//이름으로 친구를 찾아서 그 친구의 인원수를 반환한다
{
	int check=0;//친구 명수 check 변수
	Linked *temp = Node->GetFri();//친구 연결 리스트를 temp에 저장
	User *FriNode = NULL;
	if(temp==NULL)
	{
		cout<<"해당사용자의 친구는 존재하지 않습니다."<<endl;
		return false;//해당문구 출력 거짓 반환
	}

	while(temp!=NULL)//temp 끝까지 반복한다
	{
		if(strcmp( (temp->GetDown())->GetName(), friName) == 0 )//찾고자하는 이름과 동일한친구가 존재한다면
		{
			FriNode = temp->GetDown();
			if(SearchFri(FriNode, Node))
			{
				check++;//check 증가
			}
		}
		temp = temp->GetNext();//temp는 다음 temp를 가리킨다
	}
	return check;//친구 명수를 반환한다
}

bool D2List::SearchFri(User *MeNode, User *friNode)//User Node의 친구중에 존재 하는지 검사해준다
{
	int check=0;//친구 존재여부 
	Linked *temp = MeNode->GetFri();//친구 연결 Linked의 head를 반환한다
	if(temp==NULL)
	{
		cout<<"해당사용자의 친구는 존재하지 않습니다."<<endl;
		return false;//해당문구 출력 거짓 반환
	}

	while(temp!=NULL)//친구들을 모두 겅사해준다
	{
		//동명이인이 존재 할 수도 있기 때문에 노드들의 학번으로 친구인지를 확인한다.
		if(strcmp( (temp->GetDown())->GetNumber(), friNode->GetNumber() ) == 0 )
			check++;//check를 증가시킨다.
		temp = temp->GetNext();//다음 친구를 가리키게 한다
	}

	if(check == 0)//친구가 아니라면
		return false;//거짓 반환
	else//친구라면
		return true;//참반환
}

bool D2List::DeleteFrt(User *MeNode, User *friNode)//친구 연결 삭제 함수
{
	pHead = MeNode->GetFri();//친구의 헤더를 반환한다
	Linked *temp =MeNode->GetFri();//친구의 헤더를 반환한다

	Linked *pretemp = NULL;//임시 변수 선언
	int check=0;//확인을 위한 int형 변수

	if(temp ==NULL)//친구가 존재 하지 않는다면
	{
		cout<<"해당사용자의 친구가 존재하지 않습니다."<<endl;//해당문구 출력
		return false;//거짓반환
	}

	while(temp!=NULL)//친구 리스트 마지막까지 반복한다
	{
		if( strcmp( ( pHead->GetDown())->GetNumber(), friNode->GetNumber() ) == 0 )//삭제해야할 노드가 헤더라면
		{
			MeNode->SetFri(pHead->GetNext());
			pHead->SetDown(NULL);
			pHead = pHead->GetNext();//헤더를 바꿔주고 헤더가 가지고있는 유저노드연결을 끊어준다
			delete temp;//연결노드 삭제
			check++;//check 변수 증가
		}
		else if( ( strcmp( (temp->GetDown())->GetNumber(), friNode->GetNumber() ) ==0 ) && ( temp->GetNext() == NULL ) )
		{//삭제해야할 노드가 마지막 노드라면
			pretemp->SetNext(NULL);//마지막 노드이전노드의 next 값에 NULL를 넣어준다
			temp->SetDown(NULL);//마지막 노드가 가지고 있는 유저노드연결을 끊어준다
			delete temp;//연결노드 삭제
			check++;//check 변수 증가
		}

		else if( strcmp( (temp->GetDown())->GetNumber() , friNode->GetNumber() ) == 0 )
		{//삭제해야할 노드가 가운데 있다면
			pretemp->SetNext( temp->GetNext() );//pretemp의 다음 노드로 temp의 다음 노드를 넣어준다
			temp->SetDown(NULL);//temp노드가 가지고 있는 유저노드연결을 끊어준다
			delete temp;//연결노드 삭제
			check++;//check 변수 증가
		}
		pretemp=temp;//pretemp에 temp를 넣어준다
		temp = temp->GetNext();//temp에 temp다음 노드를 넣어준다
	}

	if(check == 0)//삭제가 이루어 지지않았다면
		return false;//거짓 반환
	else//삭제가 이루어 졌다면
		return true;//참반환
}