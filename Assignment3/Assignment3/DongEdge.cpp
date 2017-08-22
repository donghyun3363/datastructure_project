#include "DongEdge.h"
#include <iostream>

DongEdge::DongEdge(void)//생성자 값들 초기화
{
	GuName = NULL;
	FromDong = NULL;
	ToDong = NULL;
	Lossrate = NULL;
	Mst = 0;
	Broken = 0;
	pNext = NULL;
}

DongEdge::~DongEdge(void)//소멸자
{
	delete []GuName;
	delete []FromDong;
	delete []ToDong;//동적할당한 배열 삭제
}

void DongEdge::SetGuName(char *name)//구이름 저장
{
	int i=0;
	while(name[i] != NULL)//입력받은 정보의 길이를 구해준다
		i++;
	GuName = new char[i+1];//클래스 변수에 길이만큼 메모리 할당 한다
	memset(GuName,NULL,i+1);//배열 초기화 한다
	strcpy(GuName,name);//값을 복사한다
}

void DongEdge::SetfromDong(char *name)//from 동을 저장한다
{
	int i=0;
	while(name[i] != NULL)//입력받은 정보의 길이를 구해준다
		i++;
	FromDong = new char[i+1];//클래스 변수에 길이만큼 메모리 할당 한다
	memset(FromDong,NULL,i+1);//배열 초기화 한다
	strcpy(FromDong,name);//값을 복사한다
}

void DongEdge::SettoDong(char *name)//to 동을 저장한다
{
	int i=0;
	while(name[i] != NULL)//입력받은 정보의 길이를 구해준다
		i++;
	ToDong = new char[i+1];//클래스 변수에 길이만큼 메모리 할당 한다
	memset(ToDong,NULL,i+1);//배열 초기화 한다
	strcpy(ToDong,name);//값을 복사한다
}

void DongEdge::SetLossrate(int rate)//열손실률을 저장한다
{
	Lossrate = rate;//입력 받은 문자열을 int형으로 형 변환
}

void DongEdge::SetDongEdgeNext(DongEdge *pNode)//next 저장
{
	pNext = pNode;
}

char *DongEdge::GetGuName()//구이름 반환
{
	return GuName;
}

char *DongEdge::GetfromDong()//from 동 반환
{
	return FromDong;
}

char *DongEdge::GettoDong()//to 동 반환
{
	return ToDong;
}

int DongEdge::GetLossrate()//열 손실률 반환
{
	return Lossrate;
}

DongEdge *DongEdge::GetDongEdgeNext()//next 반환
{
	return pNext;
}

void DongEdge::SetMst(int num)//mst flag 저장
{
	Mst = num;
}

int DongEdge::GetMst()//mst flag 반환
{
	return Mst;
}

void DongEdge::SetBroken(int num)
{
	Broken = num;
}

int DongEdge::GetBroken()
{
	return Broken;
}