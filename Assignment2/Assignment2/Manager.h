#pragma once
#include "User.h"
#include "AVL.h"
#include "D2List.h"
#include "D1Memo.h"
#include "MemoNode.h"
#include "Queue_.h"
#include "MinHeap.h"//�����ؾ��ϴ� ������� ����
#include "Leave.h"

class Manager//Manager Ŭ���� ����
{
private://private ������ �� Ŭ���� ��ü�� �����Ѵ�
	AVL avl;
	D2List List;
	D1Memo Line;
	Queue_ Que;
	MinHeap heap;
	Leave Del;

public://public���� ��� �Լ� �����Ѵ�
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

