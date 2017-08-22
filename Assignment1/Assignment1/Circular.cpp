#include "Circular.h"
#include <iostream>

Circular::Circular(void)//생성자
{
	cirHead=NULL;
}

Circular::~Circular(void)//소멸자
{
}

bool Circular::Insert(NumNode *pNode)//원형리스트를 구성하는 함수
{
	if(cirHead == NULL)//원형리스트가 비어있다면
	{
		cirHead=pNode;//head로 지정해준다
		cirHead->SetCirNext(cirHead);//next 자리에 head를 넣어준다
		return true;//참반환
	}
	else//저장되어있는 노드가 있다면
	{
		NumNode *pCur = cirHead->GetCirNext();
		while(pCur->GetCirNext() != cirHead)//마지막 노드라면
		{
			pCur = pCur->GetCirNext();
		}
		pCur->SetCirNext(pNode);//마지막 노드에 넣어준다
		pNode->SetCirNext(cirHead);//next 자리에 헤더를 넣어준다
		return true;//참반환
	}
	return false;//여기까지 오면 들어갈 자리를 찾지 못했기 때문에 false 반환
}

NumNode *Circular::GetCirHead()//circular의 head를 반환한다
{
	return cirHead;
}