#pragma once
#include "GuEdge.h"
#include "DongVertex.h"//헤더파일 참조

class GuVertex//GuVertex 클래스 생성
{
private://멤버 변수 선언
	char *GuName;
	int shflag;
	GuVertex *pNext;
	GuEdge *edgHead;
	DongVertex *dongHead;
	DongVertex *MstHead;

public://멤버 함수 선언
	GuVertex(void);
	~GuVertex(void);
	void SetGuName(char *name);
	char *GetGuName();

	void SetGuedgHead(GuEdge *pNode);
	GuEdge *GetGuedgHead();

	void SetDongHead(DongVertex *pNode);
	DongVertex *GetDongHead();

	void SetGuNext(GuVertex *pNode);
	GuVertex *GetGuNext();

	void SetMstHead(DongVertex *pNode);
	DongVertex *GetMstHead();

	void SetShortflag(int num);
	int GetShortflag();
};

