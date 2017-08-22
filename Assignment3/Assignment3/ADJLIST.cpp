#include "ADJLIST.h"
#include <iostream>//������� ����


ADJLIST::ADJLIST(void)//������
{
	GuHead = NULL;
}

ADJLIST::~ADJLIST(void)//�Ҹ���
{
}

void ADJLIST::SetHead()
{
	GuHead = NULL;
}

GuVertex *ADJLIST::GetGuHead()//������� �� head�� ��ȯ�Ѵ�
{
	return GuHead;
}

bool ADJLIST::Guinsert(GuVertex *pNode)//1���� �� Vertex ����
{
	GuVertex *temp = GuHead;//�ӽ������� ������ �� ����� �־��ش�

	if(GuHead==NULL)//����� ����ִٸ�
	{
		GuHead = pNode;
		return true;//����� ������ �� ��ȯ
	}

	while( temp->GetGuNext() != NULL )//����Ʈ�� ������ while���� �ݺ��Ѵ�
		temp = temp->GetGuNext();

	temp->SetGuNext(pNode);//������ ��ġ�� ����
	return true;//�� ��ȯ
}

GuVertex *ADJLIST::SearchGuVertex(char *Gu)//�� �̸����� �� ã��
{
	GuVertex *temp = GuHead;//�ӽ������� ������ �� ����� �־��ش�

	while( temp != NULL )//�� ����Ʈ�� �˻��Ѵ�
	{
		if( strcmp(temp->GetGuName(), Gu) == 0 )//�̸��� ���� ���� �߰ߵȴٸ�
			return temp;//�ش� �� ��ȯ
		temp = temp->GetGuNext();//���� ���� ����Ų��
	}

	return NULL;//ã�±��� ������ NULL ��ȯ
}

GuVertex *ADJLIST::SearchGuVertex(int num)//�� flage�� �� ã��
{
	GuVertex *temp = GuHead;//�ӽ������� ������ �� ����� �־��ش�

	while( temp != NULL )//�� ����Ʈ�� �˻��Ѵ�
	{
		if( num == temp->GetShortflag() )//flage�� ���� ���� �߰ߵȴٸ�
			return temp;//�ش� �� ��ȯ
		temp = temp->GetGuNext();//���� ���� ����Ų��
	}

	return NULL;//ã�±��� ������ NULL ��ȯ
}

bool ADJLIST::GuEdgeinsert(GuVertex *from, GuEdge *to)//�ش��ϴ� ���� Edge�� �������ش�.
{
	GuEdge *edgtemp = from->GetGuedgHead();//�ӽ������� ������ �� edge ����� �־��ش�

	if(edgtemp == NULL)//edge�� ����� edge�� ���ٸ�
	{
		from->SetGuedgHead(to);//����� ������ 
		return true;//����ȯ
	}

	else//����� edge�� ���� �Ѵٸ�
	{
		while( edgtemp->GetGuEdgeNext() != NULL )//edge�� ������ ���� �ݺ��Ѵ�
			edgtemp = edgtemp->GetGuEdgeNext();

		edgtemp->SetGuEdgeNext(to);//�� �������� edge�� �������ش�
		return true;//����ȯ
	}

	return false;//������ ������ �ʾҴٸ� ���� ��ȯ
}

GuEdge *ADJLIST::SearchGuEdge(GuVertex *from, char *to)//�ش��ϴ� ���� ���� �̸��� ������ �ִ� edge�� �ִ��� ã���ش�
{
	GuEdge *Edgtemp = from->GetGuedgHead();//�ӽ������� ������ �� edge ����� �־��ش�

	while( Edgtemp != NULL )//edge ����Ʈ�� �˻��Ѵ�
	{
		if( strcmp(Edgtemp->GettoGu(), to) == 0 )//to�� ���� edge�� �߰ߵȴٸ�
			return Edgtemp;//�ش� edge ��ȯ
		Edgtemp = Edgtemp->GetGuEdgeNext();//���� edge�� ����Ų��
	}

	return NULL;//ã�� edge�� ������ NULL ��ȯ
}

bool ADJLIST::Donginsert(GuVertex *Gu, DongVertex *pNode)//���� �� Vertex ����
{
	DongVertex *temp = Gu->GetDongHead();

	if(temp == NULL)//��������Ʈ�� ����ִٸ�
	{
		pNode->SetdongNext(pNode);
		Gu->SetDongHead(pNode);//�ڱ� �ڽ� ��带 next�� ����
		return true;//����ȯ
	}

	else//����Ǿ��ִ� ��尡 �ִٸ�
	{
		DongVertex *pCur = temp->GetdongNext();

		while(pCur->GetdongNext() != temp)//������ �����
			pCur = pCur->GetdongNext();

		pCur->SetdongNext(pNode);//������ ��忡 �־��ش�
		pNode->SetdongNext(temp);//next �ڸ��� ����� �־��ش�
		return true;//����ȯ
	}
	return false;//������� ���� �� �ڸ��� ã�� ���߱� ������ false ��ȯ
}

DongVertex *ADJLIST::SearchDongVertex(GuVertex *Gu, char *name)//�ش��ϴ� ���� ���� �̸��� ������ �ִ� ���� �ִ��� ã���ش�
{
	DongVertex *temp = Gu->GetDongHead();//���� �� ����� ��ȯ�Ѵ�

	if(temp !=NULL)//����� ���� ���� �Ѵٸ�
	{
		do//��������Ʈ�� ��ȸ�ϱ����� do while��
		{
			if( strcmp( temp->GetDongName(), name ) == 0 )//���� �̸��� ������ �ִ� ���� ���� �Ѵٸ�
				return temp;//�׵� ��ȯ
			temp = temp->GetdongNext();//���� ���� ����Ų��

		}while(temp != Gu->GetDongHead() );//�ѹ��� �������� �ݺ��Ѵ�
	}

	return NULL;//ã�±��� ���ٸ� NULL ��ȯ
}

void ADJLIST::SetDongHead(GuVertex *Gu)//����� �� ������ Mst�� ���� flag ���� �����Ѵ�
{
	DongVertex *tempDong = Gu->GetDongHead();//�ӽ� ������  ������ ���� ������� ��ȯ�Ѵ�
	int flag = 0;//flag ����

	if(tempDong != NULL)//����Ǿ��ִ� ���� �����Ѵٸ�
	{
		do//���� ������ �ݺ��Ѵ�
		{
			if( strcmp(tempDong->GetView(), "O") == 0)//���� �����Ұ� �����Ѵٸ�
			{
				Gu->SetDongHead(tempDong);//����� �������ְ� 
				break;//�ݺ��� ����
			}
			tempDong = tempDong->GetdongNext();//���� ���� ����Ų��
		}while(tempDong != Gu->GetDongHead() );//������ũ�帮�� ó���� ������ �ݺ��Ѵ�
	}

	// �÷��� ����
	tempDong = Gu->GetDongHead();//�ӽ� ������  ������ ���� ������� ��ȯ�Ѵ�
	if(tempDong != NULL )//����Ǿ��ִ� ���� �����Ѵٸ�
	{
		do//���� ������ �ݺ��Ѵ�
		{
			tempDong->SetMstflag(flag);
			tempDong = tempDong->GetdongNext();
			flag++;//����� �� ���� flag ���� �����ϰ� flag ���� 1�� ������Ų��
		}while(tempDong != Gu->GetDongHead() );//������ũ�帮�� ó���� ������ �ݺ��Ѵ�
	}

}

bool ADJLIST::DongEdgeinsert(DongVertex *from, DongEdge *to)//�ش��ϴ� ���� edge�� �������ش�
{
	DongEdge *edgtemp = from->GetdongedgHead();//�ӽ������� ������ ��  edge�� ����� �־��ش�

	if(edgtemp == NULL)//edge�� ����� edge�� ���ٸ�
	{
		from->SetdongedgHead(to);//����� ������ 
		return true;//����ȯ
	}

	else//����� edge�� ���� �Ѵٸ�
	{
		while( edgtemp->GetDongEdgeNext() != NULL )//edge�� ������ ���� �ݺ��Ѵ�
			edgtemp = edgtemp->GetDongEdgeNext();

		edgtemp->SetDongEdgeNext(to);//�� �������� edge�� �������ش�
		return true;//����ȯ
	}

	return false;//������ ������ �ʾҴٸ� ���� ��ȯ
}

DongEdge *ADJLIST::SearchDongEdge(DongVertex *from, char *to)//�ش��ϴ� ���� ���� �̸��� ������ �ִ� edge�� �ִ��� ã���ش�
{
	DongEdge *edgtemp = from->GetdongedgHead();//�ӽ������� ������ �� edge ����� �־��ش�

	while( edgtemp != NULL )//edge ����Ʈ�� �˻��Ѵ�
	{
		if(strcmp(edgtemp->GettoDong(), to) == 0 )//to�� ���� edge�� �߰ߵȴٸ�
			return edgtemp;//�ش� edge ��ȯ
		edgtemp = edgtemp->GetDongEdgeNext();//���� edge�� ����Ų��
	}

	return NULL;//ã�� edge�� ������ NULL ��ȯ
}

int ADJLIST::CountDong(GuVertex *Gu)//�ش籸�� �� ������ ī���� ���ش�
{
	int count=0;//������ ���� int�� ����
	DongVertex *tempDong = Gu->GetDongHead();//�ӽ� �� vertex�� ����� �־��ش�

	if(tempDong !=NULL)//����Ǿ��ִ� ���� �ִٸ�
	{
		do//���� ������ �ݺ��Ѵ�
		{
			count++;//ī���� ����
			tempDong = tempDong->GetdongNext();//���� ���� ����Ų��
		}while(tempDong != Gu->GetDongHead() );//ó������ ���ƿö����� �ݺ��Ѵ�
	}
	return count;//ī���� ��ȯ
}

int ADJLIST::CountGu()//���� ������ ī���� �ϴ� �Լ�
{
	GuVertex *tempGu = GuHead;
	int count = 0;

	while(tempGu != NULL)//���� ������ �ݺ��Ѵ�
	{
		count++;
		tempGu = tempGu->GetGuNext();
	}
	return count;//ī���� �� ��ȯ�Ѵ�
}

int ADJLIST::CountMSTEdge(GuVertex *Gu)//MST edge�� ī�����Ѵ�
{
	DongVertex *Dong = NULL;
	DongEdge *Edge = NULL;
	int count = 0;//�ӽ� ���� ����

	if(Gu != NULL)//�ش��ϴ� ���� �����Ѵٸ�
	{
		Dong = Gu->GetDongHead();//���� ������� ��ȯ�Ѵ�

		while(1)//���� �ݺ��ϱ����� ���ѷ���
		{
			if(Dong == NULL)//����� ���� ���ٸ� 
				break;
			Edge = Dong->GetdongedgHead();//���� edge ����� ��ȯ�Ѵ�
			while( Edge != NULL )//edge�� ������ �ݺ��Ѵ�
			{
				if(Edge->GetMst()==1)
					count++;
				Edge = Edge->GetDongEdgeNext();//���� edge�� ����Ų��
			}

			Dong = Dong->GetdongNext();//���� ��������Ų��
			if(Dong == Gu->GetDongHead())//��������Ʈ �ݺ��� �����ٸ�
				break;//���ѷ�������
		}
	}

	return count;
}