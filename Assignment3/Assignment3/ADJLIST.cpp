#include "ADJLIST.h"
#include <iostream>//헤더파일 참조


ADJLIST::ADJLIST(void)//생성자
{
	GuHead = NULL;
}

ADJLIST::~ADJLIST(void)//소멸자
{
}

void ADJLIST::SetHead()
{
	GuHead = NULL;
}

GuVertex *ADJLIST::GetGuHead()//서울시의 구 head를 반환한다
{
	return GuHead;
}

bool ADJLIST::Guinsert(GuVertex *pNode)//1차원 구 Vertex 연결
{
	GuVertex *temp = GuHead;//임시포인터 변수에 구 헤더를 넣어준다

	if(GuHead==NULL)//헤더가 비어있다면
	{
		GuHead = pNode;
		return true;//헤더로 지정후 참 반환
	}

	while( temp->GetGuNext() != NULL )//리스트의 끝까지 while문을 반복한다
		temp = temp->GetGuNext();

	temp->SetGuNext(pNode);//마지막 위치에 연결
	return true;//참 반환
}

GuVertex *ADJLIST::SearchGuVertex(char *Gu)//구 이름으로 구 찾기
{
	GuVertex *temp = GuHead;//임시포인터 변수에 구 헤더를 넣어준다

	while( temp != NULL )//구 리스트를 검사한다
	{
		if( strcmp(temp->GetGuName(), Gu) == 0 )//이름이 같은 구가 발견된다면
			return temp;//해당 구 반환
		temp = temp->GetGuNext();//다음 구를 가리킨다
	}

	return NULL;//찾는구가 없으면 NULL 반환
}

GuVertex *ADJLIST::SearchGuVertex(int num)//구 flage로 구 찾기
{
	GuVertex *temp = GuHead;//임시포인터 변수에 구 헤더를 넣어준다

	while( temp != NULL )//구 리스트를 검사한다
	{
		if( num == temp->GetShortflag() )//flage가 같은 구가 발견된다면
			return temp;//해당 구 반환
		temp = temp->GetGuNext();//다음 구를 가리킨다
	}

	return NULL;//찾는구가 없으면 NULL 반환
}

bool ADJLIST::GuEdgeinsert(GuVertex *from, GuEdge *to)//해당하는 구의 Edge를 연결해준다.
{
	GuEdge *edgtemp = from->GetGuedgHead();//임시포인터 변수에 구 edge 헤더를 넣어준다

	if(edgtemp == NULL)//edge에 저장된 edge가 없다면
	{
		from->SetGuedgHead(to);//헤더로 지정후 
		return true;//참반환
	}

	else//저장된 edge가 존재 한다면
	{
		while( edgtemp->GetGuEdgeNext() != NULL )//edge의 마지막 까지 반복한다
			edgtemp = edgtemp->GetGuEdgeNext();

		edgtemp->SetGuEdgeNext(to);//맨 마지막에 edge를 연결해준다
		return true;//참반환
	}

	return false;//위에서 끝나지 않았다면 거짓 반환
}

GuEdge *ADJLIST::SearchGuEdge(GuVertex *from, char *to)//해당하는 구에 다음 이름을 가지고 있는 edge가 있는지 찾아준다
{
	GuEdge *Edgtemp = from->GetGuedgHead();//임시포인터 변수에 구 edge 헤더를 넣어준다

	while( Edgtemp != NULL )//edge 리스트를 검사한다
	{
		if( strcmp(Edgtemp->GettoGu(), to) == 0 )//to가 같은 edge가 발견된다면
			return Edgtemp;//해당 edge 반환
		Edgtemp = Edgtemp->GetGuEdgeNext();//다음 edge를 가리킨다
	}

	return NULL;//찾는 edge가 없으면 NULL 반환
}

bool ADJLIST::Donginsert(GuVertex *Gu, DongVertex *pNode)//원형 동 Vertex 연결
{
	DongVertex *temp = Gu->GetDongHead();

	if(temp == NULL)//원형리스트가 비어있다면
	{
		pNode->SetdongNext(pNode);
		Gu->SetDongHead(pNode);//자기 자신 노드를 next로 연결
		return true;//참반환
	}

	else//저장되어있는 노드가 있다면
	{
		DongVertex *pCur = temp->GetdongNext();

		while(pCur->GetdongNext() != temp)//마지막 노드라면
			pCur = pCur->GetdongNext();

		pCur->SetdongNext(pNode);//마지막 노드에 넣어준다
		pNode->SetdongNext(temp);//next 자리에 헤더를 넣어준다
		return true;//참반환
	}
	return false;//여기까지 오면 들어갈 자리를 찾지 못했기 때문에 false 반환
}

DongVertex *ADJLIST::SearchDongVertex(GuVertex *Gu, char *name)//해당하는 구에 다음 이름을 가지고 있는 동이 있는지 찾아준다
{
	DongVertex *temp = Gu->GetDongHead();//구의 동 헤더를 반환한다

	if(temp !=NULL)//저장된 동이 존재 한다면
	{
		do//원형리스트를 순회하기위한 do while문
		{
			if( strcmp( temp->GetDongName(), name ) == 0 )//다음 이름을 가지고 있는 동이 존재 한다면
				return temp;//그동 반환
			temp = temp->GetdongNext();//다음 동을 가리킨다

		}while(temp != Gu->GetDongHead() );//한바퀴 돌때까지 반복한다
	}

	return NULL;//찾는구가 없다면 NULL 반환
}

void ADJLIST::SetDongHead(GuVertex *Gu)//헤더의 재 지정과 Mst를 위한 flag 값을 저장한다
{
	DongVertex *tempDong = Gu->GetDongHead();//임시 포인터  변수에 구의 동헤더를 반환한다
	int flag = 0;//flag 변수

	if(tempDong != NULL)//저장되어있는 동이 존재한다면
	{
		do//동의 끝까지 반복한다
		{
			if( strcmp(tempDong->GetView(), "O") == 0)//난방 관제소가 존재한다면
			{
				Gu->SetDongHead(tempDong);//헤더로 지정해주고 
				break;//반복문 종료
			}
			tempDong = tempDong->GetdongNext();//다음 동을 가리킨다
		}while(tempDong != Gu->GetDongHead() );//원형링크드리스 처음의 노드까지 반복한다
	}

	// 플레그 세팅
	tempDong = Gu->GetDongHead();//임시 포인터  변수에 구의 동헤더를 반환한다
	if(tempDong != NULL )//저장되어있는 동이 존재한다면
	{
		do//동의 끝까지 반복한다
		{
			tempDong->SetMstflag(flag);
			tempDong = tempDong->GetdongNext();
			flag++;//헤더의 동 부터 flag 값을 저장하고 flag 값을 1씩 증가시킨다
		}while(tempDong != Gu->GetDongHead() );//원형링크드리스 처음의 노드까지 반복한다
	}

}

bool ADJLIST::DongEdgeinsert(DongVertex *from, DongEdge *to)//해당하는 동의 edge를 연결해준다
{
	DongEdge *edgtemp = from->GetdongedgHead();//임시포인터 변수에 동  edge의 헤더를 넣어준다

	if(edgtemp == NULL)//edge에 저장된 edge가 없다면
	{
		from->SetdongedgHead(to);//헤더로 지정후 
		return true;//참반환
	}

	else//저장된 edge가 존재 한다면
	{
		while( edgtemp->GetDongEdgeNext() != NULL )//edge의 마지막 까지 반복한다
			edgtemp = edgtemp->GetDongEdgeNext();

		edgtemp->SetDongEdgeNext(to);//맨 마지막에 edge를 연결해준다
		return true;//참반환
	}

	return false;//위에서 끝나지 않았다면 거짓 반환
}

DongEdge *ADJLIST::SearchDongEdge(DongVertex *from, char *to)//해당하는 동에 다음 이름을 가지고 있는 edge가 있는지 찾아준다
{
	DongEdge *edgtemp = from->GetdongedgHead();//임시포인터 변수에 동 edge 헤더를 넣어준다

	while( edgtemp != NULL )//edge 리스트를 검사한다
	{
		if(strcmp(edgtemp->GettoDong(), to) == 0 )//to가 같은 edge가 발견된다면
			return edgtemp;//해당 edge 반환
		edgtemp = edgtemp->GetDongEdgeNext();//다음 edge를 가리킨다
	}

	return NULL;//찾는 edge가 없으면 NULL 반환
}

int ADJLIST::CountDong(GuVertex *Gu)//해당구의 동 갯수를 카운터 해준다
{
	int count=0;//갯수를 위한 int형 변수
	DongVertex *tempDong = Gu->GetDongHead();//임시 동 vertex에 헤더를 넣어준다

	if(tempDong !=NULL)//저장되어있는 동이 있다면
	{
		do//동의 끝까지 반복한다
		{
			count++;//카운터 증가
			tempDong = tempDong->GetdongNext();//다음 동을 가리킨다
		}while(tempDong != Gu->GetDongHead() );//처음으로 돌아올때까지 반복한다
	}
	return count;//카운터 반환
}

int ADJLIST::CountGu()//구의 갯수를 카운터 하는 함수
{
	GuVertex *tempGu = GuHead;
	int count = 0;

	while(tempGu != NULL)//구의 끝까지 반복한다
	{
		count++;
		tempGu = tempGu->GetGuNext();
	}
	return count;//카운터 값 반환한다
}

int ADJLIST::CountMSTEdge(GuVertex *Gu)//MST edge를 카운터한다
{
	DongVertex *Dong = NULL;
	DongEdge *Edge = NULL;
	int count = 0;//임시 변수 선언

	if(Gu != NULL)//해당하는 구가 존재한다면
	{
		Dong = Gu->GetDongHead();//구의 동헤더를 반환한다

		while(1)//동을 반복하기위한 무한루프
		{
			if(Dong == NULL)//저장된 동이 없다면 
				break;
			Edge = Dong->GetdongedgHead();//동에 edge 헤더를 반환한다
			while( Edge != NULL )//edge의 끝까지 반복한다
			{
				if(Edge->GetMst()==1)
					count++;
				Edge = Edge->GetDongEdgeNext();//다음 edge를 가리킨다
			}

			Dong = Dong->GetdongNext();//다음 동을가리킨다
			if(Dong == Gu->GetDongHead())//원형리스트 반복이 끝났다면
				break;//무한루프종료
		}
	}

	return count;
}