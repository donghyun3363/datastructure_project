#pragma once

class GuEdge//GuEdge Ŭ����
{
private://private ��� ���� ����
	char *FromGu;
	char *ToGu;
	int pDis;
	GuEdge *pNext;

public://public ��� �Լ� ����
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

