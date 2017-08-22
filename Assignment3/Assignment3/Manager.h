#pragma once
#include "ADJLIST.h"
#include "GuVertex.h"
#include "GuEdge.h"
#include "DongVertex.h"
#include "DongEdge.h"
#include "Mechanic.h"
#include "LinkedList.h"
#include "DongSpanningTree.h"//������� ����

class Manager//Manager Ŭ���� ����
{
private://private  ��� ���� ����
	ADJLIST ADJList;
	LinkedList MechanicList;
	DongSpanningTree DoMst;
	int Short[3][100];

public://public ��� �Լ� ����
	Manager(void);
	~Manager(void);
	bool Load_gu(char *file1, char *file2);
	bool Load_dong(char *file1, char *file2);
	bool Load_Mehanic(char *file);
	bool DongMst();//LOAD

	bool Update(char *file);

	bool Pipe_Broken(char *gu, char *from, char *to);
	bool Pipe_Repair(char *gu);

	bool Print_Map();
	bool Print_Gu(char *gu);
	bool Print_Mechanic();

	bool Save_Gu();
	bool Save_Dong();
	bool Save_Mechanic();

	bool FinishShortestPath();
	Mechanic *ShortestPath(GuVertex *Gu);
	int MinDis();

	bool EXIT();
};

