#include "MemoNode.h"
#include <iostream>//헤더파일 선언

MemoNode::MemoNode(void)//생성자
{
	pTime = NULL;
	memset(pMemo,NULL,sizeof(pMemo));
	pNext = NULL;
	pWho = NULL;//변수들 초기화
}

MemoNode::~MemoNode(void)//소멸자
{
	memset(pMemo,NULL,sizeof(pMemo));
	delete []pTime;
	delete []pWho;
}

void MemoNode::SetTime(char *time)//시간정보 저장
{
	int i=0;
	while(time[i]!=NULL)//입력받은 정보의 길이를 구해준다
		i++;
	pTime = new char[i+1];//메모리 할당 한다
	memset(pTime,NULL,i+1);//배열 초기화 한다
	strcpy(pTime,time);//값을 복사한다
}

void MemoNode::SetWrite(char *memo)//메모정보를 저장
{
	strncpy(pMemo, memo, sizeof(pMemo) );//메모크기만큼 복사한다
}

void MemoNode::SetWho(char *man)//작성자 정보를 저장한다
{
	int i=0;
	while(man[i]!=NULL)//입력받은 정보의 길이를 구해준다
		i++;
	pWho = new char[i+1];//메모리 할당 한다
	memset(pWho,NULL,i+1);//배열 초기화 한다
	strcpy(pWho,man);//값을 복사한다
}

void MemoNode::SetNext(MemoNode *pNode)//pNext를 저장해준다
{
	pNext=pNode;
}

char *MemoNode::GetTime()//시간정보 반환
{
	return pTime;
}

char *MemoNode::GetMemo()//메모정보 반환
{
	return pMemo;
}

char *MemoNode::GetWho()//작성자정보 반환
{
	return pWho;
}

MemoNode *MemoNode::GetNext()//Next 반환
{
	return pNext;
}
