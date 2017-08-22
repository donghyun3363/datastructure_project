#include "Queue_.h"
#include<iostream>//헤더파일 선언

Queue_::Queue_(void)//생성자
{
	m_pHead=NULL;
}

Queue_::~Queue_(void)//소멸자
{
}

bool Queue_::IsEmpty()//que가 비어있는지 확인한다
{
	if(m_pHead==NULL)//입력되어있는 노드가 없다면
		return true;//참 반환
	else//있다면
		return false;//거짓 반환
}

bool Queue_::Push(User *pNode)//Push함수 초기화
{
	User *temp=NULL;//유저의 객체포인터 temp를 선언 하고 초기화 해준다
	if(m_pHead==NULL)//저장되어있는 노드가 없다면
	{
		m_pHead=pNode;//헤더포인터로 지정해준다
		return true;//참을 반환한다
	}
	else//들어가 있는  자료가 있다면
	{
		temp=m_pHead;//temp에 헤더포인터를 넣어준다
		while(temp->GetqNext() !=NULL)//temp가 맨마지막 클래스 객체 까지 가기 위한 while문
			temp=temp->GetqNext();
		temp->SetqNext(pNode);//마지막에 넣어준다
		return true;//참반환
	}
	return false;//push가 실패 했다면 거짓반환
}

User *Queue_::Pop()//pop함수 초기화
{
	User *temp=m_pHead;//temp에 헤더포인터를 넣어준다
	m_pHead=m_pHead->GetqNext();//헤더포인터를 다음노드를 가리키게 한다
	temp->SetqNext(NULL);//next를 끊어주고 값을 반환한다
	return temp;//pop할 노드의 주소값을 반환한다
}
