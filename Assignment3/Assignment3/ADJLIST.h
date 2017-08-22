#pragma once
#include "GuVertex.h"
#include "GuEdge.h"
#include "DongVertex.h"
#include "DongEdge.h"//������� ����

class ADJLIST//��������Ʈ Ŭ����
{
private://private ���� ���� ����� ������
	GuVertex *GuHead;

public://public ��� �Լ� ����
	ADJLIST(void);
	~ADJLIST(void);

	GuVertex *GetGuHead();
	void SetHead();
	void SetDongHead(GuVertex *Gu);

	bool Guinsert(GuVertex *pNode);
	GuVertex *SearchGuVertex(char *Gu);
	GuVertex *SearchGuVertex(int num);

	bool GuEdgeinsert(GuVertex *from, GuEdge *to);
	GuEdge *SearchGuEdge(GuVertex *from, char *to);

	bool Donginsert(GuVertex *Gu, DongVertex *pNode);
	DongVertex *SearchDongVertex(GuVertex *Gu, char *name);

	bool DongEdgeinsert(DongVertex *from, DongEdge *to);
	DongEdge *SearchDongEdge(DongVertex *from, char *to);
	int CountMSTEdge(GuVertex *Gu);

	int CountDong(GuVertex *Gu);
	int CountGu();

};