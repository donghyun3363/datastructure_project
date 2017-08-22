#include "MinHeap.h"
#include <iostream>//헤더파일참조

MinHeap::MinHeap(void)//생성자
{
	memset(Minheap,NULL,sizeof(Minheap));
	index = 0;//멤버 변수들 초기화
}

MinHeap::~MinHeap(void)//소멸자
{	
	memset(Minheap,NULL,sizeof(Minheap));
	index = 0;//멤버 변수들 초기화
}

bool MinHeap::pushMinHeap(MemoNode *pNode)//push 함수
{
	int pCur=0;
	pCur = ++index;//index값을 증가시켜 현재 pCur 값으로한다
	while( (pCur != 1) &&( strcmp(pNode->GetTime(), (Minheap[pCur/2])->GetTime() )<0 ) )
	{
		//1의 위치거나 더 작지 않을때까지 반복하는 while문
		Minheap[pCur] = Minheap[pCur/2];//현재 배열의 값을바꿔주고
		pCur = (pCur/2);//현재 index 값을 바꿔주고
	}
	Minheap[pCur] = pNode;//최종적으로 들어갈 자리에 새로운 노드를 넣어준다
	return true;//참반환
}

MemoNode *MinHeap::popMinHeap()//pop 함수
{
	int par, child;
	MemoNode *temp = NULL;
	MemoNode *item = NULL;//임시 변수들을 지정해준다

	item = Minheap[1];
	temp = Minheap[index--];//Root 값을 return 하기위해 저장해둔다

	par = 1;
	child = 2;//parent, child 변수에 1,2를 넣어준다

	while(child <= index)//child가 index보다 작을때까지 반복한다 
	{
		if( (child <= index) && ( strcmp(Minheap[child]->GetTime(), (Minheap[child+1])->GetTime() ) > 0) )
			child++;
		if( strcmp(temp->GetTime(), Minheap[child]->GetTime() ) < 0 )
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
