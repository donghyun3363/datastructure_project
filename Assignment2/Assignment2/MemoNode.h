#pragma once

class MemoNode//MemoNode Ŭ���� ����
{
private://private ��� ���� ����
	char *pTime;
	char pMemo[500];
	char *pWho;
	MemoNode *pNext;
public://public ��� �Լ� ����
	MemoNode(void);
	~MemoNode(void);
	void SetTime(char *time);
	void SetWho(char *man);
	void SetWrite(char *memo);
	void SetNext(MemoNode *pNode);

	char *GetTime();
	char *GetMemo();
	char *GetWho();
	MemoNode *GetNext();
};

