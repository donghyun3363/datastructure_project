#pragma once
class NumNode//NumNode 클래스를 정의한다
{
private://private 멤버 변수 선언
	char *m_Num;
	char *m_Finish;
	char *m_Item;
	char *m_Treat;
	NumNode *pNext;
	NumNode *CircularNext;
public://public 멤버 변수를 선언한다
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

