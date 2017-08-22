#pragma once
#include "Mechanic.h"//헤더파일을 참조한다

class LinkedList//LinkedList 클래스 생성
{
private://private 멤버 변수 선언
	Mechanic *pHead;

public://public 멤버 함수 선언
	LinkedList(void);
	~LinkedList(void);

	void SetHead();
	Mechanic *GetMechanicHead();
	bool InsertMechanic(Mechanic *node);
	bool CheckMechanic(char *gu);
};

