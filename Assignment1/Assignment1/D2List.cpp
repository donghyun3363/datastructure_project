#include "D2List.h"
#include <iostream>//헤더파일 선언

using namespace std;//이름 공간에 std 저장후 사용

D2List::D2List(void)//생성자
{
	pHead=NULL;
}

D2List::~D2List(void)//소멸자
{
}

RegionNode *D2List::GetHead()//pHead를 반환한다.
{
	return pHead;
}

bool D2List::pInsert(RegionNode *pNode)//2D에서 부모노드들을 연결해준다.
{
	RegionNode *temp=pHead;//temp에 head를 넣어준다

	if(pHead==NULL)//head가 비어있다면
	{
		pHead=pNode;//pNode를 head로 지정해 준다
		return true; //true 반환하고 함수 종료
	}
	else//저장되어있는 노드가 있다면
	{
		while(temp->GetNext() != NULL )//들어갈 자리를 찾는 반복문
			temp=temp->GetNext();

		temp->SetNext(pNode);//맨 마지막에 pNode를 연결해준다
		return true;//true를 반환하고 함수 종료
	}
	return false;// pNode가 자리를 못찾기 때문에 false 반환
}

bool D2List::cInsert(char *Rnum, NumNode *cNode)//2D에서 자식노드들을 연결해준다.
{
	RegionNode *Rtemp=pHead;
	NumNode *cHead=NULL;
	NumNode *temp=NULL;
	NumNode *pretemp=NULL;

	while(Rtemp !=NULL)//동일 지역 코드 검사
	{
		if(strcmp( Rnum, Rtemp->GetRegionNumber() ) == 0)//동일한 지역 코드를 찾는다면
		{
			cHead=Rtemp->GetN_Head();//cHead에 해당지역코드의 운송장번호 head를 저장한다
			break;//while문 종료
		}
		Rtemp = Rtemp->GetNext();
	}

	int con=0;
	if(cHead==NULL)//입력되어있는 운송장 번호 노드가 없다면
	{
		Rtemp->SetN_Head(cNode);//헤더로 지정해준다
		con++;//con변수 증가
	}

	else//저장되어있는 노드가 있다면
	{
		temp = cHead;//temp에 자식노드들의 헤더포인터를 넣어준다
		if( cNode->GetNum()[10] < cHead->GetNum()[10])//헤더에 저장되어있는 물품 정보보다 빠르다면
		{
			cNode->SetNext(cHead);//헤더를 바꿔준다
			Rtemp->SetN_Head(cNode);
			con++;//카운터 증가
		}

		else if(cNode->GetNum()[10] == cHead->GetNum()[10])//헤더에 저장되어있는 물품정보랑 같다면
		{
			if(cNode->GetNum()[11]=='1') //취급 주의라면
			{
				cNode->SetNext(cHead);//헤더를 바꿔준다
				Rtemp->SetN_Head(cNode);
				con++;//카운터 증가
			}
			else//취급 주의가 아니라면
			{
				cNode->SetNext( cHead->GetNext() );//헤더 다음 자리에 위치시킨다.
				cHead->SetNext(cNode);
				con++;//카운터 증가
			}
		}

		else//헤더에 저장되어있는 물품정보 보다 느리다면
		{
			pretemp=cHead;//이전임시 포인터에 헤더값을 넣어준다
			while(1)//현재 노드의 자리를 찾을때까지 반복한다
			{
				if( pretemp->GetNext() == NULL )//마지막 노드까지 간다면
				{
					pretemp->SetNext(cNode);//마지막에 입력 받은 노드를 연결해준다
					con++;//카운터 증가
					break;//무한루프 종료
				}

				temp = pretemp->GetNext();//임시포인터에 이전임시포인터 다음노드를 저장한다
				if( cNode->GetNum()[10] < temp->GetNum()[10]) //입력되는 노드의 물품정보가 더 빠르다면
				{
					cNode->SetNext( temp );//현재노드의 next자리에 임시노드의 값을 넣어준다
					pretemp->SetNext( cNode );//이전임시노드의 next값에 현재노드의 주소값을 넣어준다
					con++;//카운터 증가
					break;//무한루프 종료
				}
				else if( cNode->GetNum()[10] == temp->GetNum()[10])//물품 정보가 같다면
				{
					if(cNode->GetNum()[11]=='1')//취급 주위물품이라면
					{
						cNode->SetNext( temp );//현재노드의 next자리에 임시노드의 값을 넣어준다
						pretemp->SetNext( cNode );//이전임시노드의 next값에 현재노드의 주소값을 넣어준다
						con++;//카운터 증가
						break;//무한루프 종료
					}
					else//취급주의가 아니라면
					{
						cNode->SetNext( temp->GetNext() );//임시 노드 다음에 위치시킨다.
						temp->SetNext(cNode);
						con++;//카운터 증가
						break;
					}
				}
				pretemp=pretemp->GetNext();//이전임시노드는 다음노드를 가리키도록한다
			}
		}
	}

	if(con==0)//Insert가 이루어 지지 않았다면
		return false;//거짓 반환
	else//Insert가 이루어 졌다면       
		return true;//참 반환
}

bool D2List::Delete(char *num, char *re)
{
	RegionNode *re_temp = pHead;
	NumNode *cHead = NULL;
	NumNode *temp = NULL ;
	NumNode *pretemp = NULL;
	while(re_temp !=NULL)
	{
		if(strcmp( re_temp->GetRegionNumber(), re)==0)
		{
			cHead = re_temp->GetN_Head();
			temp=re_temp->GetN_Head();
			pretemp=re_temp->GetN_Head();
			break;
		}
		re_temp=re_temp->GetNext();
	}

	while(temp!=NULL)//리스트 마지막까지 반복한다
	{
		if( strcmp( cHead->GetNum(),num) == 0 )//헤더에 저장되어있는 이름과 같다면
		{
			re_temp->SetN_Head( (re_temp->GetN_Head())->GetNext() );
			delete temp;
			return true;
		}
		else if( ( strcmp( temp->GetNum(), num) == 0 ) && ( temp->GetNext()==NULL ) )//마지막 노드의 이름과 같다면
		{
			pretemp->SetNext(NULL);//마지막 노드이전노드의 next 값에 NULL를 넣어준다
			delete temp;
			return true;//참 반환
		}

		else if( strcmp( temp->GetNum(), num)==0 )//가운데 노드에 저장되어있는 이름과 같다면
		{
			pretemp->SetNext( temp->GetNext() );//pretemp의 다음 노드로 temp의 다음 노드를 넣어준다
			delete temp;
			return true;//참 반환
		}

		pretemp=temp;//pretemp에 temp를 넣어준다
		temp = temp->GetNext();//temp에 temp다음 노드를 넣어준다
	}
}

void D2List::Pdelete(RegionNode *del)
{
	RegionNode *temp=pHead;;
	RegionNode *pretemp=pHead;
	while(temp!=NULL)
	{
		if(del == pHead)
			pHead = pHead->GetNext();
		else if(temp==del)
		{
			pretemp->SetNext(temp->GetNext());
		}
		pretemp = temp;
		temp= temp->GetNext();
	}
}