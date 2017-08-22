#include "Leave.h"
#include "User.h"
#include <iostream>//헤더파일을 참조한다

Leave::Leave(void)//생성자
{
	pRoot = NULL;
}

Leave::~Leave(void)//소멸자
{
}

bool Leave::Insert(User *pNode)//insert 함수
{
	pNode->SetCheckDelete(1);//탈퇴여부 flag 를 저장한다

	User *temp=pRoot;//head가 비어있다면
	if(pRoot==NULL)
	{
		pRoot = pNode;
		return true;
	}//head로 지정후 참 반환

	while(temp->GetLNext() !=NULL)
		temp = temp->GetLNext();//next가 NULL이 될때까지 반복한다

	temp->SetLNext(pNode);//그자리에 insert해준다
	return true;//참반환
}

bool Leave::Delete()//삭제함수
{
	User *pCur = NULL;
	while(pRoot !=NULL )//root 부터 반복한다
	{
		pCur = pRoot;
		pRoot = pRoot->GetLNext();
		delete pCur;//현재 노드를 delete 해준다
	}
	return true;//참반환
}