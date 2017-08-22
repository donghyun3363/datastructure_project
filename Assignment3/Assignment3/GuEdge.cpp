#include "GuEdge.h"
#include <iostream>//헤더파일 참조

GuEdge::GuEdge(void)//생성자 변수들을 초기화 한다
{
	FromGu = NULL;
	ToGu = NULL;
	pDis = 0;
	pNext = NULL;
}

GuEdge::~GuEdge(void)//생성자 변수들을 초기화 한다
{
	delete []FromGu;
	delete []ToGu;
}
void GuEdge::SetfromGu(char *name)//from 구 이름을 저장한다
{
	int i=0;
	while(name[i]!=NULL)//입력받은 정보의 길이를 구해준다
		i++;
	FromGu = new char[i+1];//클래스 변수에 길이만큼 메모리 할당 한다
	memset(FromGu,NULL,i+1);//배열 초기화 한다
	strcpy(FromGu,name);//값을 복사한다

}

void GuEdge::SettoGu(char *name)//to 구 이름을 저장한다
{
	int i=0;
	while(name[i]!=NULL)//입력받은 정보의 길이를 구해준다
		i++;
	ToGu = new char[i+1];//클래스 변수에 길이만큼 메모리 할당 한다
	memset(ToGu,NULL,i+1);//배열 초기화 한다
	strcpy(ToGu,name);//값을 복사한다
}

void GuEdge::SetDis(int dis)//거리를 int형으로 저장한다
{
	pDis = dis;
}

void GuEdge::SetGuEdgeNext(GuEdge *pNode)//edge next를 저장한다
{
	pNext = pNode;
}

char *GuEdge::GetfromGu()//from 구 이름 반환
{
	return FromGu;
}

char *GuEdge::GettoGu()//to 구 이름 반환
{
	return ToGu;
}

int GuEdge::Getdis()//거리 반환
{
	return pDis;
}

GuEdge *GuEdge::GetGuEdgeNext()//edge next를 반환한다
{
	return pNext;
}
