#pragma once
class DongEdge//DongEdge Ŭ����
{
private://private ��� ���� ����
	char *GuName;
	char *FromDong;
	char *ToDong;
	int Lossrate;
	int Mst;
	int Broken;
	DongEdge *pNext;

public://public ��� �Լ� ����
	DongEdge(void);
	~DongEdge(void);

	void SetGuName(char *name);
	void SetfromDong(char *name);
	void SettoDong(char *name);
	void SetLossrate(int rate);
	void SetDongEdgeNext(DongEdge *pNode);
	void SetMst(int num);
	void SetBroken(int num);

	int GetMst();
	char *GetGuName();
	char *GetfromDong();
	char *GettoDong();
	int GetLossrate();
	int GetBroken();
	DongEdge *GetDongEdgeNext();
};