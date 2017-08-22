#pragma once
#include "User.h"//헤더파일 선언

class Queue_//queue 클래스 선언
{
private://private 멤버변수 선언
	User* m_pHead;
public://public 멤버 함수 선언
	Queue_(void);
	~Queue_(void);
	bool IsEmpty();
	bool Push(User *pNode);
	User *Pop();
};

