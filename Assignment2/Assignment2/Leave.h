#pragma once
class User;//User Node�� ��ȣ ����
class Leave//Ŭ���� ����
{
private://private ��� ���� ����
	User *pRoot;

public://public ��� �Լ��� �����Ѵ�
	Leave(void);
	~Leave(void);
	bool Insert(User *pNode);
	bool Delete();
};

