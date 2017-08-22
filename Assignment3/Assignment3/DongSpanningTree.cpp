#include "DongSpanningTree.h"
#include <iostream>//헤더파일 참조

DongSpanningTree::DongSpanningTree()//생성자
{
	parent = NULL;
}

DongSpanningTree::~DongSpanningTree(void)//소멸자
{

}

int DongSpanningTree::find(int v)//인덱스 값을 바꿔주는 함수
{
	if(v==parent[v])//인덱스 값과 배열 값이 같다면 바로 그 값을 반환한다
		return v;
	else //인덱스 값과 배열 값이 다를 때 재귀 함수를 이용하여 가장 작은 값을 찾는다
		return (parent[v] = find(parent[v]));
}

void DongSpanningTree::Union(int v, int w)//사이클이 안될경우 배열 값을 바꿔주는 함수
{
	if( v >w )//더 작은 배열 값으로 바꿔준다
		parent[find(v)] = w;
	else//더큰 배열 값으로 바꿔준다
		parent[find(w)] = v;
}

bool DongSpanningTree::MST(GuVertex *pGu, int num)//MST 구성함수
{
	int i=0;
	parent = new int[num+1];//입력 받은 수만큼 동적 할당
	memset(parent, 0, sizeof(num+1));//배열 초기화

	while(i!=num)//배열 값을 index값과 동일 하게 넣어준다
	{
		parent[i]=i;
		i++;//배열 전체 반복
	}

	DongVertex *tempDong = pGu->GetDongHead();//동의 헤더를 반환한다
	pGu->SetMstHead( pGu->GetDongHead() );//MST 헤더를 지정해준다

	DongEdge *tempEdge = NULL;
	DongEdge *reverEdge = NULL;//동 edge 임시 변수 선언

	DongVertex *from = NULL;
	DongVertex *to = NULL;//동 vertex 임시 변수 선언

	if(tempDong != NULL )//저장되어있는 동이 있다면
	{
		do//동의 끝까지 반복한다
		{
			tempEdge = tempDong->GetdongedgHead();//동의 edge 헤더를 반환한다
			while( tempEdge != NULL )//edge의 끝까지 반복한다
			{
				if(tempEdge->GetBroken() == 0)//깨진 pipe가 아니라면 Push해준다
				{
					if( Heap.CheckEdge(tempEdge) ) //양 방향이므로 한방향 edge만 heap에 넣어준다
						Heap.pushMinHeap(tempEdge);//heap에 넣어준다
				}
				tempEdge = tempEdge->GetDongEdgeNext();//다음 edge를 가리킨다
			}
			tempDong = tempDong->GetdongNext();
		}while(tempDong != pGu->GetDongHead() );//push heap

		///////////////////////////////////////////////////////////////////pop Heap
		tempEdge=NULL;

		if( !(Heap.Heap_IsEmpty()) )//heap이 비어있지 않다면
		{
			while(1)//heap이 빌때까지 무한 반복한다
			{
				tempEdge = Heap.popMinHeap();//heap에서 pop 한다

				from = ADJList.SearchDongVertex(pGu, tempEdge->GetfromDong());
				to = ADJList.SearchDongVertex(pGu, tempEdge->GettoDong());//from, to 동 vertex를 반환 받는다

				reverEdge = ADJList.SearchDongEdge( to, tempEdge->GetfromDong() );//temp의 반대 방향 edge도 찾아준다

				if( find(from->GetMstflag()) != find(to->GetMstflag()) )//인접 리스트가 사이클인지 확인 해준다
				{
					Union(from->GetMstflag(), to->GetMstflag() );//사이클이 안돌경우 인덱스 값을 바꿔준다
					tempEdge->SetMst(1);
					reverEdge ->SetMst(1);//MST flag에 값을 준다
				}
				if( Heap.Heap_IsEmpty() )// heap이 비어있다면
				{
					int Jung = num;//정점의 수
					int gan = ( ADJList.CountMSTEdge(pGu) ) / 2;//간선의 수

					if(Jung == gan+1)
					{
						delete []parent;//배열삭제
						return true;//참반환
					}
					else
					{
						delete []parent;//배열삭제
						return false;//거짓 반환
					}

				}

			}
		}

	}

}


