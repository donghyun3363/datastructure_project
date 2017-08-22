#pragma once

class GuEdge//GuEdge 클래스
{
private://private 멤버 변수 선언
	char *FromGu;
	char *ToGu;
	int pDis;
	GuEdge *pNext;

public://public 멤버 함수 선언
	GuEdge(void);
	~GuEdge(void); 
	void SetfromGu(char *name);
	void SettoGu(char *name);
	void SetDis(int dis);
	void SetGuEdgeNext(GuEdge *pNode);

	char *GetfromGu();
	char *GettoGu();
	int Getdis();
	GuEdge *GetGuEdgeNext();
};

