#pragma once
#include "Linked.h"
#include "User.h"//헤더파일 참조

class D2List//2D 연결 클레스
{
private://private 변수로 헤더를 선언한다
	Linked *pHead;

public://public 멤버 함수 선언
	D2List(void);
	~D2List(void);
	bool Insert(User *MeNode, User *FriNode);
	int SearchFri(User *Node, char *friName);
	bool SearchFri(User *MeNode, User *friNode);
	bool DeleteFrt(User *MeNode, User *friNode);

};