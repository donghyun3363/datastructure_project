#pragma once
class User;//헤더파일 상호참조

class Linked// 연결노드
{
private://private 변수 선언
	Linked *pNext;
	User *pDown;
public://public 멤버 함수 선언
	Linked(void);
	~Linked(void);
	void SetNext(Linked *Node);
	void SetDown(User *Node);
	Linked *GetNext();
	User *GetDown();
};
