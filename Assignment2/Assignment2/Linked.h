#pragma once
class User;//������� ��ȣ����

class Linked// ������
{
private://private ���� ����
	Linked *pNext;
	User *pDown;
public://public ��� �Լ� ����
	Linked(void);
	~Linked(void);
	void SetNext(Linked *Node);
	void SetDown(User *Node);
	Linked *GetNext();
	User *GetDown();
};
