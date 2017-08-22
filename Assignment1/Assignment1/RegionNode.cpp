#include "RegionNode.h"
#include <iostream>//헤더파일 선언

RegionNode::RegionNode(void)//생성자
{
	re_Num = NULL;
	m_City=NULL;
	pNext=NULL;
	Left=NULL;
	Right=NULL;
	p_Head=NULL;
	Qnext=NULL;
}

RegionNode::~RegionNode(void)//소멸자
{
	delete []re_Num;
	delete []m_City;
}

char* RegionNode::GetRegionNumber()//지역코드를 반환한다
{
	return re_Num;
}

char* RegionNode::GetCity()//도시를 반환한다
{
	return m_City;
}
void RegionNode::SetCity(char *city)//도시를 반환한다
{
	int i=0;
	while(city[i]!=NULL)//입력받은 정보의 길이를 구해준다
		i++;
	m_City = new char[i+1];//클래스 변수에 성의 길이만큼 메모리 할당 한다
	memset(m_City,NULL,i+1);//배열 초기화 한다
	strcpy(m_City,city);//값을 복사한다
}

void RegionNode::SetRegionNumber(char *Num)//지역코드를 저장한다
{
	int i=0;
	while(Num[i]!=NULL)//입력받은 정보의 길이를 구해준다
		i++;
	re_Num = new char[i+1];//클래스 변수에 성의 길이만큼 메모리 할당 한다
	memset(re_Num,NULL,i+1);//배열 초기화 한다
	strcpy(re_Num,Num);
}

RegionNode* RegionNode::GetNext()//next를 반환한다
{
	return pNext;
}

NumNode* RegionNode::GetN_Head()//head를 반환한다
{
	return p_Head;
}

RegionNode* RegionNode::GetLeftNext()//left를 반환한다
{
	return Left;
}

RegionNode* RegionNode::GetRightNext()//right를 반환한다
{
	return Right;
}
RegionNode* RegionNode::GetQNext()//Qnext를 반환한다
{
	return Qnext;
}

void RegionNode::SetN_Head(NumNode *Node)//head를 저장한다
{
	p_Head=Node;
}

void RegionNode::SetNext(RegionNode* Node)//next를 저장한다
{
	pNext=Node;
}

void RegionNode::SetLeftNext(RegionNode* Node)//left를 저장한다
{
	Left=Node;
}

void RegionNode::SetRightNext(RegionNode* Node)//right를저장한다
{
	Right=Node;
}

void RegionNode::SetQNext(RegionNode* Node)//Qnext를 저장한다.
{
	Qnext=Node;
}