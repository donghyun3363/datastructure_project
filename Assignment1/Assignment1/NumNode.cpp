#include "NumNode.h"
#include<iostream>//헤더파일 선언

NumNode::NumNode(void)//생선자
{
	m_Num=NULL;
	m_Finish=NULL;
	m_Item=NULL;
	m_Treat=NULL;
	pNext=NULL;
	CircularNext;
}

NumNode::~NumNode(void)//소멸자
{
	delete []m_Num;
	delete []m_Finish;
	delete []m_Item;
	delete []m_Treat;
}

char *NumNode::GetNum()//운송장번호를 반환한다
{
	return m_Num;
}

char *NumNode::GetFinish()//배송여부를 반환한다
{
	return m_Finish;
}

char *NumNode::GetItem()//품목을 반환한다
{
	return m_Item;
}

char *NumNode::GetTreat()//취급주의를 반환한다
{
	return m_Treat;
}

void NumNode::SetNum(char *num)//운송장 번호를 저장한다
{
	int i=0;
	while(num[i]!=NULL)//입력받은 정보의 길이를 구해준다
		i++;
	m_Num = new char[i+1];//클래스 변수에 길이만큼 메모리 할당 한다
	memset(m_Num,NULL,i+1);//배열 초기화 한다
	strcpy(m_Num,num);//값을 복사한다
}

void NumNode::SetFinish(char *finish)//배송여부를 저장한다
{
	int i=0;
	while(finish[i]!=NULL)//입력받은 정보의 길이를 구해준다
		i++;
	m_Finish = new char[i+1];//클래스 변수에 길이만큼 메모리 할당 한다
	memset(m_Finish,NULL,i+1);//배열 초기화 한다
	strcpy(m_Finish,finish);//값을 복사한다
}

void NumNode::SetItem(char *item)//품목을 저장한다
{
	int i=0;
	while(item[i]!=NULL)//입력받은 정보의 길이를 구해준다
		i++;
	m_Item = new char[i+1];//클래스 변수에 길이만큼 메모리 할당 한다
	memset(m_Item,NULL,i+1);//배열 초기화 한다
	strcpy(m_Item,item);//값을 복사한다
}

void NumNode::SetTreat(char *treat)//취금주의를 저장한다
{
	int i=0;
	while(treat[i]!=NULL)//입력받은 정보의 길이를 구해준다
		i++;
	m_Treat = new char[i+1];//클래스 변수에 길이만큼 메모리 할당 한다
	memset(m_Treat,NULL,i+1);//배열 초기화 한다
	strcpy(m_Treat,treat);//값을 복사한다
}

NumNode *NumNode::GetNext()//Next를 반환한다
{
	return pNext;
}

void NumNode::SetNext(NumNode *pNode)//Next를 저장한다
{
	pNext=pNode;
}

NumNode *NumNode::GetCirNext()//circularNext를 반환한다
{
	return CircularNext;
}

void NumNode::SetCirNext(NumNode *pNode)//circularNext을 저장한다
{
	CircularNext=pNode;
}