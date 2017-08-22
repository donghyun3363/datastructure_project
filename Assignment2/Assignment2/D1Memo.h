#pragma once
#include "MemoNode.h"
#include "User.h"//헤더파일 참조 선언

class D1Memo//D1Memo 클래스 생성
{
private://private 멤버 변수 선언
	MemoNode *pHead;
public://public 멤버 변수 선언
	D1Memo(void);
	~D1Memo(void);
	bool MemoInsert(User *MeNode, MemoNode *pNode);
	bool MemoSearch(User *MeNode, char *time );
	bool MemoDelete(User *MeNode, char *time );
};

