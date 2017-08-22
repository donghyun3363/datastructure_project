#pragma once
class Mechanic//Mechanic 클래스 생성
{
private://priate 멤버 변수
	char *Gu;
	char *Name;
	int dis;
	Mechanic *pNext;

public://public 멤버 함수
	Mechanic(void);
	~Mechanic(void);

	void SetMechanicGu(char *gu);
	char *GetMechanicGu();

	void SetMechanicName(char *name);
	char *GetMechanicName();

	void SetMechanicNext(Mechanic *node);
	Mechanic *GetMechanicNext();

	void SetDistence(int num);
	int GetDistence();
};

