#pragma once

class MemoNode//MemoNode 클래스 생성
{
private://private 멤버 변수 선언
	char *pTime;
	char pMemo[500];
	char *pWho;
	MemoNode *pNext;
public://public 멤버 함수 선언
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

