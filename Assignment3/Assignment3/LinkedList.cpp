#include "LinkedList.h"
#include <iostream>//헤더파일을 참조한다

LinkedList::LinkedList(void)//생성자
{
	pHead = NULL;
}

LinkedList::~LinkedList(void)//소멸자
{

}

void LinkedList::SetHead()
{
	pHead = NULL;
}
Mechanic *LinkedList::GetMechanicHead()//정비사 리스트의 헤더를 반환한다
{
	return pHead;
}

bool LinkedList::InsertMechanic(Mechanic *node)//정비사를 연결시켜주는 함수
{
	Mechanic *temp = pHead;//해더를 임시 변수에 넣어준다

	if(pHead == NULL)//헤더가 비어있다면
	{
		pHead = node;//헤더로 지정
		return true;//참반환
	}

	else//저장된 정보가 있다면
	{
		while(temp->GetMechanicNext() != NULL)
			temp = temp->GetMechanicNext();//정비사 리스트의 끝까지 반복한다

		temp->SetMechanicNext(node);//맨 마지막에 연결시켜준다
		return true;//참반환
	}

	return false;//위에서 함수가 종료 되지 않았다면 거짓반환
}

bool LinkedList::CheckMechanic(char *gu)//동일한 근무지를 검사한다
{
	Mechanic *temp = pHead;//임시 변수에 head를 넣어준다
	int check = 0;//check 변수

	while(temp != NULL )//temp 끝까지 반복
	{
		if( strcmp(temp->GetMechanicGu(), gu) == 0 )//동일한 구 근무지가 존재한다면
			check++;//check 증가
		temp = temp->GetMechanicNext();//temp는 다음 정비사를 가리킨다
	}

	if(check == 0) //같은 구 근무지가 존재하지 않는다면
		return true;//참반환
	else//그렇지 않다면
		return false;//거짓반환

}



