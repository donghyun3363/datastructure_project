#pragma once
#include "DongEdge.h"//������� ����

class DongVertex//DongVertex Ŭ����
{
private://private ��� ���� ����
	char *Gu;
	char *DongName;
	char *pView;
	int Mstflag;
	DongVertex *pNext;
	DongEdge *dongedgHead;

public://public ��� �Լ� ����
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
