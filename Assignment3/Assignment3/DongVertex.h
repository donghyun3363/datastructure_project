#pragma once
#include "DongEdge.h"//헤더파일 참조

class DongVertex//DongVertex 클래스
{
private://private 멤버 변수 선언
	char *Gu;
	char *DongName;
	char *pView;
	int Mstflag;
	DongVertex *pNext;
	DongEdge *dongedgHead;

public://public 멤버 함수 선언
	DongVertex(void);
	~DongVertex(void);
	void SetguName(char *name);
	void SetDongName(char *name);
	void SetView(char *view);
	void SetdongNext(DongVertex *pNode);
	void SetdongedgHead(DongEdge *pNode);
	void SetMstflag(int num);

	int GetMstflag();
	char *GetguName();
	char *GetDongName();
	char *GetView();
	DongVertex *GetdongNext();
	DongEdge *GetdongedgHead();
};
