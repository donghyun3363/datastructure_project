#pragma once
class NumNode//NumNode Ŭ������ �����Ѵ�
{
private://private ��� ���� ����
	char *m_Num;
	char *m_Finish;
	char *m_Item;
	char *m_Treat;
	NumNode *pNext;
	NumNode *CircularNext;
public://public ��� ������ �����Ѵ�
	NumNode(void);
	~NumNode(void);
	char *GetNum();
	char *GetFinish();
	char *GetItem();
	char *GetTreat();
	NumNode *GetCirNext();
	NumNode *GetNext();
	void SetNext(NumNode *pNode);
	void SetCirNext(NumNode *pNode);
	void SetNum(char *num);
	void SetFinish(char *finish);
	void SetItem(char *item);
	void SetTreat(char *treat);
};

