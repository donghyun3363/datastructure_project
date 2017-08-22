#include "DongSpanningTree.h"
#include <iostream>//������� ����

DongSpanningTree::DongSpanningTree()//������
{
	parent = NULL;
}

DongSpanningTree::~DongSpanningTree(void)//�Ҹ���
{

}

int DongSpanningTree::find(int v)//�ε��� ���� �ٲ��ִ� �Լ�
{
	if(v==parent[v])//�ε��� ���� �迭 ���� ���ٸ� �ٷ� �� ���� ��ȯ�Ѵ�
		return v;
	else //�ε��� ���� �迭 ���� �ٸ� �� ��� �Լ��� �̿��Ͽ� ���� ���� ���� ã�´�
		return (parent[v] = find(parent[v]));
}

void DongSpanningTree::Union(int v, int w)//����Ŭ�� �ȵɰ�� �迭 ���� �ٲ��ִ� �Լ�
{
	if( v >w )//�� ���� �迭 ������ �ٲ��ش�
		parent[find(v)] = w;
	else//��ū �迭 ������ �ٲ��ش�
		parent[find(w)] = v;
}

bool DongSpanningTree::MST(GuVertex *pGu, int num)//MST �����Լ�
{
	int i=0;
	parent = new int[num+1];//�Է� ���� ����ŭ ���� �Ҵ�
	memset(parent, 0, sizeof(num+1));//�迭 �ʱ�ȭ

	while(i!=num)//�迭 ���� index���� ���� �ϰ� �־��ش�
	{
		parent[i]=i;
		i++;//�迭 ��ü �ݺ�
	}

	DongVertex *tempDong = pGu->GetDongHead();//���� ����� ��ȯ�Ѵ�
	pGu->SetMstHead( pGu->GetDongHead() );//MST ����� �������ش�

	DongEdge *tempEdge = NULL;
	DongEdge *reverEdge = NULL;//�� edge �ӽ� ���� ����

	DongVertex *from = NULL;
	DongVertex *to = NULL;//�� vertex �ӽ� ���� ����

	if(tempDong != NULL )//����Ǿ��ִ� ���� �ִٸ�
	{
		do//���� ������ �ݺ��Ѵ�
		{
			tempEdge = tempDong->GetdongedgHead();//���� edge ����� ��ȯ�Ѵ�
			while( tempEdge != NULL )//edge�� ������ �ݺ��Ѵ�
			{
				if(tempEdge->GetBroken() == 0)//���� pipe�� �ƴ϶�� Push���ش�
				{
					if( Heap.CheckEdge(tempEdge) ) //�� �����̹Ƿ� �ѹ��� edge�� heap�� �־��ش�
						Heap.pushMinHeap(tempEdge);//heap�� �־��ش�
				}
				tempEdge = tempEdge->GetDongEdgeNext();//���� edge�� ����Ų��
			}
			tempDong = tempDong->GetdongNext();
		}while(tempDong != pGu->GetDongHead() );//push heap

		///////////////////////////////////////////////////////////////////pop Heap
		tempEdge=NULL;

		if( !(Heap.Heap_IsEmpty()) )//heap�� ������� �ʴٸ�
		{
			while(1)//heap�� �������� ���� �ݺ��Ѵ�
			{
				tempEdge = Heap.popMinHeap();//heap���� pop �Ѵ�

				from = ADJList.SearchDongVertex(pGu, tempEdge->GetfromDong());
				to = ADJList.SearchDongVertex(pGu, tempEdge->GettoDong());//from, to �� vertex�� ��ȯ �޴´�

				reverEdge = ADJList.SearchDongEdge( to, tempEdge->GetfromDong() );//temp�� �ݴ� ���� edge�� ã���ش�

				if( find(from->GetMstflag()) != find(to->GetMstflag()) )//���� ����Ʈ�� ����Ŭ���� Ȯ�� ���ش�
				{
					Union(from->GetMstflag(), to->GetMstflag() );//����Ŭ�� �ȵ���� �ε��� ���� �ٲ��ش�
					tempEdge->SetMst(1);
					reverEdge ->SetMst(1);//MST flag�� ���� �ش�
				}
				if( Heap.Heap_IsEmpty() )// heap�� ����ִٸ�
				{
					int Jung = num;//������ ��
					int gan = ( ADJList.CountMSTEdge(pGu) ) / 2;//������ ��

					if(Jung == gan+1)
					{
						delete []parent;//�迭����
						return true;//����ȯ
					}
					else
					{
						delete []parent;//�迭����
						return false;//���� ��ȯ
					}

				}

			}
		}

	}

}


