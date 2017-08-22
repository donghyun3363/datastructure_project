#include "Mechanic.h"
#include <iostream>//헤더파일 참조

Mechanic::Mechanic(void)//생성자
{
	Gu = NULL;
	Name = NULL;
	pNext = NULL;
	dis = 0;
}

Mechanic::~Mechanic(void)//소멸자
{
	delete []Gu;
	delete []Name;
}

void Mechanic::SetMechanicGu(char *gu)//구 저장
{
	int i=0;
	while(gu[i]!=NULL)//입력받은 정보의 길이를 구해준다
		i++;
	Gu = new char[i+1];//클래스 변수에 길이만큼 메모리 할당 한다
	memset(Gu,NULL,i+1);//배열 초기화 한다
	strcpy(Gu,gu);//값을 복사한다
}

char *Mechanic::GetMechanicGu()//구 반환
{
	return Gu;
}

void Mechanic::SetMechanicName(char *name)//정비사 이름 저장
{
	int i=0;
	while(name[i]!=NULL)//입력받은 정보의 길이를 구해준다
		i++;
	Name = new char[i+1];//클래스 변수에 길이만큼 메모리 할당 한다
	memset(Name,NULL,i+1);//배열 초기화 한다
	strcpy(Name,name);//값을 복사한다
}
char *Mechanic::GetMechanicName()//정비사 이름 반환
{
	return Name;
}

void Mechanic::SetMechanicNext(Mechanic *node)//다음 정비사를 가리킨다
{
	pNext = node;
}

Mechanic *Mechanic::GetMechanicNext()//다음 정비사를 반환한다
{
	return pNext;
}

void Mechanic::SetDistence(int num)//정비사의 거리를 저장한다
{
	dis = num;
}

int Mechanic::GetDistence()//정비사의 거리 반환한다
{
	return dis;
}