#include "MinHeap.h"
#include <iostream>//�����������
using namespace std;

MinHeap::MinHeap(void)//������ ��� ������ �ʱ�ȭ
{
	memset(Minheap,NULL,sizeof(Minheap));
	index = 0;
}


MinHeap::~MinHeap(void)//�Ҹ��� ��� ������ �ʱ�ȭ
{
	memset(Minheap,NULL,sizeof(Minheap));
	index = 0;
}

bool MinHeap::pushMinHeap(DongEdge *pNode)//push �Լ�
{
	int pCur=0;
	pCur = ++index;//index���� �������� ���� pCur �������Ѵ�

	while( (pCur != 1) &&  ( (pNode->GetLossrate()) < ((Minheap[pCur/2])->GetLossrate())) )//�θ� ��庸�� �۴ٸ� �ݺ��Ѵ�
	{
		Minheap[pCur] = Minheap[pCur/2];//���� �迭�� �����ٲ��ְ�
		pCur = (pCur/2);//���� index ���� �ٲ��ְ�
	}

	Minheap[pCur] = pNode;//���������� �� �ڸ��� ���ο� ��带 �־��ش�
	return true;//����ȯ
}

DongEdge *MinHeap::popMinHeap()//pop �Լ�
{
	int par, child;
	DongEdge *temp = NULL;
	DongEdge *item = NULL;//�ӽ� �������� �������ش�

	item = Minheap[1];
	temp = Minheap[index--];//Root ���� return �ϱ����� �����صд�

	par = 1;
	child = 2;//parent, child ������ 1,2�� �־��ش�

	while(child <= index)//child�� index���� ���������� �ݺ��Ѵ� 
	{
		if(  (child <= index) && ( (Minheap[child]->GetLossrate()) > (Minheap[child+1])->GetLossrate() ) )
			child++;
		if( (temp->GetLossrate()) <(Minheap[child]->GetLossrate() )  )
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

bool MinHeap::CheckEdge(DongEdge *pNode)//�̹� �� ������ �ѹ����� heap�� �����ϴ� edge���� Ȯ���Ѵ�
{
	int check =0;
	int i=0;//index �� Ȯ�� �ϱ�
	if(index == 0 )//�� ó�� ���̶��
		return true;//true ��ȯ

	while( i != index )//heap�� ������ �ݺ��Ѵ�
	{
		i++;
		if( (strcmp( pNode->GettoDong(), (Minheap[i])->GetfromDong() ) == 0) && (strcmp(pNode->GetfromDong(), (Minheap[i])->GettoDong()) == 0) )// from to �� heap�� ���� �ϴ��� Ȯ�� �Ѵ�
			check++;//check �� ����
	}

	if(check == 0)//������ edge�� ���� ���� �ʴ´ٸ�
		return true;//true ��ȯ

	else//������ edge�� ���� �Ѵٸ� 
		return false;//false ��ȯ
}
