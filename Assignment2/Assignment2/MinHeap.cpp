#include "MinHeap.h"
#include <iostream>//�����������

MinHeap::MinHeap(void)//������
{
	memset(Minheap,NULL,sizeof(Minheap));
	index = 0;//��� ������ �ʱ�ȭ
}

MinHeap::~MinHeap(void)//�Ҹ���
{	
	memset(Minheap,NULL,sizeof(Minheap));
	index = 0;//��� ������ �ʱ�ȭ
}

bool MinHeap::pushMinHeap(MemoNode *pNode)//push �Լ�
{
	int pCur=0;
	pCur = ++index;//index���� �������� ���� pCur �������Ѵ�
	while( (pCur != 1) &&( strcmp(pNode->GetTime(), (Minheap[pCur/2])->GetTime() )<0 ) )
	{
		//1�� ��ġ�ų� �� ���� ���������� �ݺ��ϴ� while��
		Minheap[pCur] = Minheap[pCur/2];//���� �迭�� �����ٲ��ְ�
		pCur = (pCur/2);//���� index ���� �ٲ��ְ�
	}
	Minheap[pCur] = pNode;//���������� �� �ڸ��� ���ο� ��带 �־��ش�
	return true;//����ȯ
}

MemoNode *MinHeap::popMinHeap()//pop �Լ�
{
	int par, child;
	MemoNode *temp = NULL;
	MemoNode *item = NULL;//�ӽ� �������� �������ش�

	item = Minheap[1];
	temp = Minheap[index--];//Root ���� return �ϱ����� �����صд�

	par = 1;
	child = 2;//parent, child ������ 1,2�� �־��ش�

	while(child <= index)//child�� index���� ���������� �ݺ��Ѵ� 
	{
		if( (child <= index) && ( strcmp(Minheap[child]->GetTime(), (Minheap[child+1])->GetTime() ) > 0) )
			child++;
		if( strcmp(temp->GetTime(), Minheap[child]->GetTime() ) < 0 )
			break;
		Minheap[par] = Minheap[child];
		par = child;
		child = (child * 2);
	}//temp�� �ڸ��� ã���ֱ� ���� while ���̴�.

	Minheap[par] = temp;//temp ��ġ�� �������ش�
	return item;//Root �� ��ȯ
}

bool MinHeap::Heap_IsEmpty()//heap�� ����ִ��� äũ���ش�
{
	if(index==0)//����ִٸ�
	{
		memset(Minheap,NULL,sizeof(Minheap));//�迭�ʱ�ȭ
		return true;//����ȯ
	}
	else//���� �ִٸ� 
		return false;//���� ��ȯ
}
