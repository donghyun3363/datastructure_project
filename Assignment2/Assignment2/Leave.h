#pragma once
class User;//User Node를 상호 참조
class Leave//클래스 생성
{
private://private 멤버 변수 선언
	User *pRoot;

public://public 멤버 함수를 선언한다
	Leave(void);
	~Leave(void);
	bool Insert(User *pNode);
	bool Delete();
};

