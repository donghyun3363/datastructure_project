#pragma once
#include "GuEdge.h"
#include "DongVertex.h"//������� ����

class GuVertex//GuVertex Ŭ���� ����
{
private://��� ���� ����
	char *GuName;
	int shflag;
	GuVertex *pNext;
	GuEdge *edgHead;
	DongVertex *dongHead;
	DongVertex *MstHead;

public://��� �Լ� ����
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

