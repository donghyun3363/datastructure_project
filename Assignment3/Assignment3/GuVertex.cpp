#include "GuVertex.h"
#include <iostream>//헤더파일 참조

GuVertex::GuVertex(void)//생성자 변수 초기화
{
	GuName = NULL;
	pNext = NULL;
	edgHead = NULL;
	dongHead = NULL;
	MstHead = NULL;
	shflag = 0;
}

GuVertex::~GuVertex(void)//소멸자
{
	delete []GuName;
}

void GuVertex::SetGuName(char *name)//구이름 저장
{
	int i=0;
	while(name[i]!=NULL)//입력받은 정보의 길이를 구해준다
		i++;
	GuName = new char[i+1];//클래스 변수에 길이만큼 메모리 할당 한다
	memset(GuName,NULL,i+1);//배열 초기화 한다
	strcpy(GuName,name);//값을 복사한다
}

char *GuVertex::GetGuName()//구이름 반환
{
	return GuName;
}

void GuVertex::SetGuNext(GuVertex *pNode)//구 next 저장
{
	pNext = pNode;
}

GuVertex *GuVertex::GetGuNext()//구 next 반환
{
	return pNext;
}

void GuVertex::SetGuedgHead(GuEdge *pNode)//구 edge 헤더를 저장한다
{
	edgHead = pNode;
}

GuEdge *GuVertex::GetGuedgHead()//구 edge 헤더를 반환한다
{
	return edgHead;
}

void GuVertex::SetDongHead(DongVertex *pNode)//동의 헤더를 저장한다
{
	dongHead = pNode;
}

DongVertex *GuVertex::GetDongHead()//동의 헤더를 반환한다
{
	return dongHead;
}

void GuVertex::SetMstHead(DongVertex *pNode)//동의 MST 헤더를 저장한다
{
	MstHead = pNode;
}

DongVertex *GuVertex::GetMstHead()//동의 MST 헤더를 반환한다
{
	return MstHead;
}

void GuVertex::SetShortflag(int num)
{
	shflag = num;
}

int GuVertex::GetShortflag()
{
	return shflag;
}
