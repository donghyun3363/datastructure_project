#pragma once
class Mechanic//Mechanic Ŭ���� ����
{
private://priate ��� ����
	char *Gu;
	char *Name;
	int dis;
	Mechanic *pNext;

public://public ��� �Լ�
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

