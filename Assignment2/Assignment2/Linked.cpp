#include "Linked.h"
#include <iostream>//헤더파일 참조

Linked::Linked(void)//생성자 
{
	pNext = NULL;
	pDown = NULL;
}

Linked::~Linked(void)//소멸자
{
}

void Linked::SetNext(Linked *Node)//다음노드를 지정해준다
{
	pNext = Node;
}

void Linked::SetDown(User *Node)//연결노드가 가지는 친구를 저장한다
{
	pDown = Node;
}

Linked *Linked::GetNext()//다음노드를 반환한다
{
	return pNext;
}

User *Linked::GetDown()//연결노드가 가지는 친구를 반환한다
{
	return pDown;
}
