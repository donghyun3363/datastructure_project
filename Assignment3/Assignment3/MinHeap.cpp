#include "MinHeap.h"
#include <iostream>//헤더파일참조
using namespace std;

MinHeap::MinHeap(void)//생성자 멤버 변수들 초기화
{
	memset(Minheap,NULL,sizeof(Minheap));
	index = 0;
}


MinHeap::~MinHeap(void)//소멸자 멤버 변수들 초기화
{
	memset(Minheap,NULL,sizeof(Minheap));
	index = 0;
}

bool MinHeap::pushMinHeap(DongEdge *pNode)//push 함수
{
	int pCur=0;
	pCur = ++index;//index값을 증가시켜 현재 pCur 값으로한다

	while( (pCur != 1) &&  ( (pNode->GetLossrate()) < ((Minheap[pCur/2])->GetLossrate())) )//부모 노드보다 작다면 반복한다
	{
		Minheap[pCur] = Minheap[pCur/2];//현재 배열의 값을바꿔주고
		pCur = (pCur/2);//현재 index 값을 바꿔주고
	}

	Minheap[pCur] = pNode;//최종적으로 들어갈 자리에 새로운 노드를 넣어준다
	return true;//참반환
}

DongEdge *MinHeap::popMinHeap()//pop 함수
{
	int par, child;
	DongEdge *temp = NULL;
	DongEdge *item = NULL;//임시 변수들을 지정해준다

	item = Minheap[1];
	temp = Minheap[index--];//Root 값을 return 하기위해 저장해둔다

	par = 1;
	child = 2;//parent, child 변수에 1,2를 넣어준다

	while(child <= index)//child가 index보다 작을때까지 반복한다 
	{
		if(  (child <= index) && ( (Minheap[child]->GetLossrate()) > (Minheap[child+1])->GetLossrate() ) )
			child++;
		if( (temp->GetLossrate()) <(Minheap[child]->GetLossrate() )  )
			break;
		Minheap[par] = Minheap[child];
		par = child;
		child = (child * 2);
	}//temp의 자리를 찾아주기 위한 while 문이다.

	Minheap[par] = temp;//temp 위치를 지정해준다
	return item;//Root 값 반환
}

bool MinHeap::Heap_IsEmpty()//heap이 비어있는지 채크해준다
{
	if(index==0)//비어있다면
	{
		memset(Minheap,NULL,sizeof(Minheap));//배열초기화
		return true;//참반환
	}
	else//값이 있다면 
		return false;//거짓 반환
}

bool MinHeap::CheckEdge(DongEdge *pNode)//이미 양 방향중 한방향이 heap에 존재하는 edge인지 확인한다
{
	int check =0;
	int i=0;//index 값 확인 하기
	if(index == 0 )//맨 처음 값이라면
		return true;//true 반환

	while( i != index )//heap의 끝까지 반복한다
	{
		i++;
		if( (strcmp( pNode->GettoDong(), (Minheap[i])->GetfromDong() ) == 0) && (strcmp(pNode->GetfromDong(), (Minheap[i])->GettoDong()) == 0) )// from to 로 heap에 존재 하는지 확인 한다
			check++;//check 수 증가
	}

	if(check == 0)//역방향 edge가 존재 하지 않는다면
		return true;//true 반환

	else//역방향 edge가 존재 한다면 
		return false;//false 반환
}
