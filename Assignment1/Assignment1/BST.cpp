#include "BST.h"
#include<iostream> // 해더파일 선언

BST::BST()//생성자
{
	pRoot=NULL;
}

BST::~BST(void)//소멸자
{
}

RegionNode *BST::GetRoot() // pRoot를 반환한다
{
	return pRoot;
}

bool BST::BSTInsert(RegionNode *pNode) //BST insert 함수 
{
	return BSTinsert_position(pRoot,pNode); //BSTinsert_position 함수 호출
}

bool BST::BSTinsert_position(RegionNode *current, RegionNode *pNode)
{
	int currenttemp, pNodetemp;//지역코드를 임시로 저장한다
	if(pRoot==NULL)//root가 비어있다면 
	{
		pRoot=pNode;//pNode를 root에 넣어준다
		return true;//함수 종료
	}

	currenttemp = atoi ( current->GetRegionNumber() );
	pNodetemp = atoi ( pNode->GetRegionNumber() ); // 정수로 형 변환 해준다

	if(currenttemp > pNodetemp)//값을 비교해 들어갈 자리를 찾는다
	{
		if(current->GetLeftNext() == NULL)//pNode가 들어갈 자리를 찾는다면
		{
			current->SetLeftNext(pNode);//노드를 연결해준다
			return true;//참반환
		}
		return BSTinsert_position(current->GetLeftNext(),pNode);//재귀함수 호출
	}
	else if(currenttemp < pNodetemp)//값을 비교해 들어갈 자리를 찾는다
	{
		if(current->GetRightNext()==NULL)//pNode가 들어갈 자리를 찾는다면
		{
			current->SetRightNext(pNode);//노드를 연결해준다
			return true;
		}
		return BSTinsert_position(current->GetRightNext(),pNode);//재귀함수 호출
	}

	return false;//거짓반환
}

RegionNode *BST::Serch(char *Num)//운송장 번호로 해당 노드를 찾는다
{
	RegionNode *temp = pRoot;//temp에 root 노드를 넣어준다.
	while(temp !=NULL )//노드의 마지막 까ㅣ 반복한다
	{
		if( strcmp(temp->GetRegionNumber(), Num ) ==0 ) //운송장 번호가 일치한다면 temp 반환
			return temp;
		if( strcmp( temp->GetRegionNumber(), Num ) == 1)//temp가 num보다 크다면 temp에 temp->GetLeftNext()를 넣어준다
			temp=temp->GetLeftNext();
		else                            //temp가 num보다 작다면 temp에 temp->GetRightNext()를 넣어준다
			temp = temp->GetRightNext();
	}
	return NULL;//찾는 노드가 없다면 NULL 반환
}

bool BST::Delete(RegionNode *pNode)
{
	RegionNode *par = pRoot; // 클래스 포인터 변수 선언
	RegionNode *del = pRoot;
	RegionNode *pretemp = NULL;
	RegionNode *temp = NULL;

	while( del != NULL )
	{
		if( strcmp(del->GetRegionNumber(), pNode->GetRegionNumber() ) ==0 ) //지역번호가 일치하는 node가 존재 한다면
		{
			if( (del->GetLeftNext() != NULL) && (del->GetRightNext() != NULL) ) // 삭제해야되는노드의 자식노드가 둘다 존재 한다면 
			{
				if(del==pRoot) //지워야 하는 노드가 Root 라면
				{
					temp = del->GetLeftNext(); //왼쪽 subtree에서 가장 큰 값 temp를 찾는다.
					pretemp = del->GetLeftNext();
					while(temp->GetRightNext() != NULL)//temp의 rightNext가 NULL일때 까지 내려간다
					{
						pretemp = temp;
						temp = temp->GetRightNext();
					}
					pretemp->SetRightNext( temp->GetLeftNext() );//temp를 Root 자리에 위치시키기 위해 연결다시지정해준다
					temp->SetLeftNext( del->GetLeftNext() );
					temp->SetRightNext( del->GetRightNext() );
					pRoot=temp;//Root를 바꿔준다
					delete del;//del 을 지워준다
					return true;
				}
				else //Root가 아니라면
				{
					temp = del->GetLeftNext();//왼쪽 subtree에서 가장 큰 값 temp를 찾는다.
					pretemp = del->GetLeftNext();
					while(temp->GetRightNext() != NULL)//temp의 rightnext가 NULL일때 까지 내려간다
					{
						pretemp = temp;
						temp = temp->GetRightNext();
					}
					pretemp->SetRightNext( temp->GetLeftNext() );//temp를 del 자리에 위치시키기 위해 연결다시지정해준다
					temp->SetLeftNext( del->GetLeftNext() );
					temp->SetRightNext( del->GetRightNext() );

					if(par->GetLeftNext()==del)//del의 위치를 부모노드로 부터 다시한번 확인한다
					{
						par->SetLeftNext(temp);//연결해주고 
						delete del;//삭제한다
						return true;
					}
					else if(par->GetRightNext()==del)
					{
						par->SetRightNext(temp);//연결해주고
						delete del;//삭제한다
						return true;
					}
				}
			}

			else if((del->GetLeftNext() != NULL) && (del->GetRightNext() == NULL) ) //자식노드가 left만 존재할때
			{
				if(del==pRoot) //지워야 하는 노드가 Root 라면
				{
					temp = del->GetLeftNext(); //왼쪽 subtree에서 가장 큰 값 temp를 찾는다.
					pretemp = del->GetLeftNext();
					while(temp->GetRightNext() != NULL)//temp의 rightnext가 NULL일때 까지 내려간다
					{
						pretemp = temp;
						temp = temp->GetRightNext();
					}
					pretemp->SetRightNext( temp->GetLeftNext() );//temp를 Root 자리에 위치시키기 위해 연결다시지정해준다
					temp->SetLeftNext( del->GetLeftNext() );
					pRoot=temp;//Root를 바꿔준다
					delete del;//삭제한다
					return true;
				}
				else //Root가 아니라면
				{
					temp = del->GetLeftNext();//왼쪽 subtree에서 가장 큰 값 temp를 찾는다.
					pretemp = del->GetLeftNext();
					while(temp->GetRightNext() != NULL)//temp의 rightnext가 NULL일때 까지 내려간다
					{
						pretemp = temp;
						temp = temp->GetRightNext();
					}
					pretemp->SetRightNext( temp->GetLeftNext() );//temp를 del 자리에 위치시키기 위해 연결다시지정해준다
					temp->SetLeftNext( del->GetLeftNext() );

					if(par->GetLeftNext()==del)//del의 위치를 부모노드로 부터 다시한번 확인한다
					{
						par->SetLeftNext(temp);//연결해주고 
						delete del;//삭제한다
						return true;
					}
					else if(par->GetRightNext()==del)
					{
						par->SetRightNext(temp);
						delete del;
						return true;
					}
				}
			}

			else if( (del->GetLeftNext() == NULL) && (del->GetRightNext() != NULL) )//자식노드가 righr만 존재할때
			{
				if(del==pRoot) //지워야 하는 노드가 Root 라면
				{
					temp = del->GetRightNext(); //오른쪽 subtree에서 가장 작은 값 temp를 찾는다.
					pretemp = del->GetRightNext();
					while(temp->GetLeftNext() != NULL)//temp의 leftnext가 NULL일때 까지 내려간다
					{
						pretemp = temp;
						temp = temp->GetLeftNext();
					}
					pretemp->SetLeftNext( temp->GetRightNext() );//temp를 Root 자리에 위치시키기 위해 연결다시지정해준다
					temp->SetRightNext( del->GetRightNext() );
					pRoot=temp;//Root를 바꿔준다
					delete del;//삭제한다
					return true;
				}
				else //Root가 아니라면
				{
					temp = del->GetRightNext(); //오른쪽 subtree에서 가장 작은 값 temp를 찾는다.
					pretemp = del->GetRightNext();
					while(temp->GetLeftNext() != NULL)//temp의 leftnext가 NULL일때 까지 내려간다
					{
						pretemp = temp;
						temp = temp->GetLeftNext();
					}
					pretemp->SetLeftNext( temp->GetRightNext() );//temp를 Root 자리에 위치시키기 위해 연결다시지정해준다
					temp->SetRightNext( del->GetRightNext() );

					if(par->GetRightNext()==del)//del의 위치를 부모노드로 부터 다시한번 확인한다
					{
						par->SetRightNext(temp);//연결해주고 
						delete del;//삭제한다
						return true;
					}
					else if(par->GetLeftNext()==del)
					{
						par->SetLeftNext(temp);
						delete del;
						return true;
					}
				}
			}

			else//자식 노드가 없는 경우
			{
				if(del==pRoot)//지워야 하는 노드가 Root 일때
				{
					pRoot=NULL;//Root에 NULL
					delete del;//del을 지운다
					return true;
				}
				else//Root 노드가 아닐때
				{
					if(par->GetLeftNext()==del) //지워야 하는 노드가 부모노드의 어디에 위치하는지 파악한다
					{
						par->SetLeftNext(NULL);//연결해주고
						delete del;//삭제한다
						return true;
					}
					else if(par->GetRightNext()==del)
					{
						par->SetRightNext(NULL);
						delete del;
						return true;
					}
				}
			}

		}
		par = del;//par는 현재 del을 넣어준다
		if( strcmp( del->GetRegionNumber(), pNode->GetRegionNumber() ) == 1)//del을 다음 노드로 바꿔준다
			del = del->GetLeftNext();
		else
			del = del->GetRightNext();
	}
	return 0;
}