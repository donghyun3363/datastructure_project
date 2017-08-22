#pragma once
#include "User.h"
#include "AVL.h"
#include "D2List.h"
#include "D1Memo.h"
#include "MemoNode.h"
#include "Queue_.h"
#include "MinHeap.h"//참조해야하는 헤더파일 선언
#include "Leave.h"

class Manager//Manager 클래스 생성
{
private://private 변수로 각 클래스 객체를 생성한다
	AVL avl;
	D2List List;
	D1Memo Line;
	Queue_ Que;
	MinHeap heap;
	Leave Del;

public://public으로 멤버 함수 선언한다
	Manager(void);
	~Manager(void);
	bool Load_User(char *file);
	bool Load_Friend(char *file);
	bool Load_Memo(char *file);
	bool Save_User(char *file);
	bool Save_Friend(char *file);
	bool Save_Memo(char *file);
	bool TimeLine(char *num);
	bool FriendList(char *num);
	char *ALARM(User *mNode, char *before, char *time);
	bool INTIMACY(char *me, char *target);
	bool Update_User(char *file);
	bool Update_Friend(char *file);
	bool Update_Memo(char *file);
	bool EXIT();
};

