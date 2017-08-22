#include "DongVertex.h"
#include <iostream>//헤더파일 참조

DongVertex::DongVertex(void)//생성자 변수들 초기화/
{
	Gu = NULL;
	DongName = NULL;
	pView = NULL;
	pNext = NULL;
	dongedgHead = NULL;
	Mstflag = 0;
}

DongVertex::~DongVertex(void)//소멸자
{
	delete []Gu;
	delete []DongName;
	delete []pView;
}

void DongVertex::SetguName(char *name)//구 이름을 저장한다
{
	int i=0;
	while(name[i]!=NULL)//입력받은 정보의 길이를 구해준다
		i++;
	Gu = new char[i+1];//클래스 변수에 길이만큼 메모리 할당 한다
	memset(Gu,NULL,i+1);//배열 초기화 한다
	strcpy(Gu,name);//값을 복사한다
}

void DongVertex::SetDongName(char *name)//동 이르을 저장한다
{
	int i=0;
	while(name[i]!=NULL)//입력받은 정보의 길이를 구해준다
		i++;
	DongName = new char[i+1];//클래스 변수에 길이만큼 메모리 할당 한다
	memset(DongName,NULL,i+1);//배열 초기화 한다
	strcpy(DongName,name);//값을 복사한다
}

void DongVertex::SetView(char *view)//남방관제소 여부 저장
{
	int i=0;
	while(view[i]!=NULL)//입력받은 정보의 길이를 구해준다
		i++;
	pView = new char[i+1];//클래스 변수에 길이만큼 메모리 할당 한다
	memset(pView,NULL,i+1);//배열 초기화 한다
	strcpy(pView,view);//값을 복사한다
}

void DongVertex::SetdongNext(DongVertex *pNode)//동 next를 저장
{
	pNext = pNode;
}

char *DongVertex::GetguName()//구이름 반환
{
	return Gu;
}

char *DongVertex::GetDongName()//동이름 반환
{
	return DongName;
}

char *DongVertex::GetView()//남방관제소 여부 반환
{
	return pView;
}

DongVertex *DongVertex::GetdongNext()// 동 next 반환
{
	return pNext;
}

void DongVertex::SetdongedgHead(DongEdge *pNode)//동의 edge 헤더를 저장한다
{
	dongedgHead = pNode;
}

DongEdge *DongVertex::GetdongedgHead()//동의 edge를 반환한다
{
	return dongedgHead;
}

void DongVertex::SetMstflag(int num)//mst 배열 index 값 저장
{
	Mstflag = num;
}

int DongVertex::GetMstflag()//mst 배열 index 값 반환
{
	return Mstflag;
}