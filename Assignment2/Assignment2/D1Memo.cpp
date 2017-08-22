#include "D1Memo.h"
#include<iostream>//헤더파일 선언

using namespace std;

D1Memo::D1Memo(void)//생성자
{
	pHead=NULL;

}

D1Memo::~D1Memo(void)//소멸자
{
}

bool D1Memo::MemoInsert(User *MeNode, MemoNode *pNode)//MemoInsert 함수 
{
	pHead = MeNode->GetMyMemo();//MeNode의 memo head를 저장한다

	MemoNode *temp = NULL;
	MemoNode *pretemp = NULL;//임시 포인터 선언

	int check =0;//check를 위한 변수 선언
	if( pHead == NULL )//헤더가 비어있다면
	{
		MeNode->SetMyMemo(pNode);
		check++;//head로 저장하고 check 증가
	}
	else//자료가 있다면
	{
		if( strcmp( pHead->GetTime(), pNode->GetTime() ) > 0 ) //새로운 노드의 시간이 헤더보다 빠르다면
		{
			pNode->SetNext(pHead);
			MeNode->SetMyMemo(pNode);//헤더를 바꿔주고 연결을 다시 지정해 준다.
			check++;//check 증가
		}
		else//헤더의 이름보다 느리다면
		{
			pretemp=pHead;
			while(1)//들어갈 자리를 찾기위한 무한 루프
			{
				if(pretemp->GetNext() == NULL)//맨마지막에 위치해야한다면
				{
					pretemp->SetNext(pNode);//맨마지막에 연결을 해준다.
					check++;//check 증가
					break;//무한루프 종료
				}
				temp = pretemp->GetNext();
				if( strcmp( temp->GetTime(), pNode->GetTime() ) > 0)//temp의 시간보다 빠르다면
				{
					pNode->SetNext(temp);
					pretemp->SetNext(pNode);//temp와 pretemp사이에 위치시킨다
					check++;//check증가
					break;//무한루프 종료
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

bool D1Memo::MemoSearch(User *MeNode, char *time )//메모를 찾아준다
{
	MemoNode *temp = MeNode->GetMyMemo();//사용자의 메모 헤더를 반환 받는다
	if(temp ==NULL)
	{
		cout<<"사용자에게 저장되어있는 메모는 없습니다"<<endl;
		return false;
	}

	while(temp !=NULL)//메모의 끝까지 반복한다
	{
		if(strcmp(temp->GetTime(), time)==0)//동시간 메모가 존재한다면
			return true;//참 반환
		temp = temp->GetNext();
	}
	return false;
}

bool D1Memo::MemoDelete(User *MeNode, char *time )//메모의 연결을 삭제 해준다.
{
	pHead = MeNode->GetMyMemo();//친구의 헤더를 반환한다
	MemoNode *temp =MeNode->GetMyMemo();//친구의 헤더를 반환한다

	MemoNode *pretemp = NULL;//임시 변수 선언
	int check=0;//확인을 위한 int형 변수

	if(temp ==NULL)//친구가 존재 하지 않는다면
	{
		cout<<"해당사용자의 친구가 존재하지 않습니다."<<endl;//해당문구 출력
		return false;//거짓반환
	}

	while(temp!=NULL)//친구 리스트 마지막까지 반복한다
	{
		if( strcmp( pHead->GetTime() , time) == 0 )//삭제해야할 노드가 헤더라면
		{
			MeNode->SetMyMemo(pHead->GetNext());
			pHead = pHead->GetNext();//헤더를 바꿔주고 헤더가 가지고있는 유저노드연결을 끊어준다
			delete temp;//연결노드 삭제
			check++;//check 변수 증가
		}
		else if( ( strcmp( temp->GetTime(), time) ==0 ) && ( temp->GetNext() == NULL ) )
		{//삭제해야할 노드가 마지막 노드라면
			pretemp->SetNext(NULL);//마지막 노드이전노드의 next 값에 NULL를 넣어준다
			delete temp;//연결노드 삭제
			check++;//check 변수 증가
		}

		else if( strcmp( temp->GetTime() , time ) == 0 )
		{//삭제해야할 노드가 가운데 있다면
			pretemp->SetNext( temp->GetNext() );//pretemp의 다음 노드로 temp의 다음 노드를 넣어준다
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