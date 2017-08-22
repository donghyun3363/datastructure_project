#include "AVL.h"
#include <iostream>//헤더파일 선언

using namespace std;//이름공간에 std 저장후 사용

AVL::AVL(void)//생성자
{
	NameRoot = NULL;
	NumberRoot = NULL;
}

AVL::~AVL(void)//소멸자
{
	NameRoot = NULL;
	NumberRoot = NULL;
}

User *AVL::GetNameRoot()//Name AVL의 헤더를 반환한다
{
	return NameRoot;
}

User *AVL::GetNumRoot()//Number AVL의 헤더를 반환한다
{
	return NumberRoot;
}

bool AVL::NameAVL(User *pNode)//이름 기준 AVL TREE
{
	User *Cur = NameRoot;
	User *pCur = NULL;
	User *Break = NULL;
	User *pBreak = NULL;//AVL을 위한 포인터 변수 선언

	if(NameRoot==NULL)//저장되어있는 노드가 없다면
	{
		NameRoot=pNode;//헤더로 지정후 참 반환
		return true;
	}

	while(Cur!=NULL)//들어갈 위치를 찾아주기 위한 반복문
	{
		if( Cur->Getbf() )//벨런스가 깨진 노드를 찾아준다
		{
			Break = Cur;
			pBreak = pCur;//Break, pBreak에 저장한다
		}

		if( strcmp( Cur->GetName(), pNode->GetName() ) > 0)//새로운 노드의 이름이 더 빠르다면
		{
			pCur = Cur;
			Cur = Cur->GetNameLeft();//left next를 저장
		}
		else if(strcmp( Cur->GetName(), pNode->GetName() ) < 0)//새로운 노드의 이름이 더 느리다면
		{
			pCur = Cur;
			Cur = Cur->GetNameRight();//right next를 저장
		}
		else if(strcmp( Cur->GetName(), pNode->GetName() ) == 0)//새로운 노드의 이름이 같다면
		{
			if(strcmp( Cur->GetNumber(), pNode->GetNumber() ) > 0)//학번이 더 빠르다면
			{
				pCur = Cur;
				Cur = Cur->GetNameLeft();//left next를 저장
			}
			else//학번이 더 느리다면
			{
				pCur = Cur;
				Cur = Cur->GetNameRight();//right next를 저장
			}
		}
	}
	//새로운 노드가 들어가야 할 위치에 저장해준다.
	if( strcmp( pCur->GetName(), pNode->GetName() ) > 0)//왼쪽 sub tree에 저장
		pCur->SetNameLeft(pNode);
	else if(strcmp( pCur->GetName(), pNode->GetName() ) < 0)//오른쪽 sub tree에 저장
		pCur->SetNameRight(pNode);
	else//동명이인 예외처리
	{
		if(strcmp( pCur->GetNumber(), pNode->GetNumber() ) > 0)//학번에 따라 왼쪽 sub tree에 저장
			pCur->SetNameLeft(pNode);
		else//오른쪽 sub tree에 저장
			pCur->SetNameRight(pNode);
	}

	Cur = NameRoot;//Cur을 Root로 지정
	if( ( pNode == NameRoot->GetNameLeft() ) || ( pNode == NameRoot->GetNameRight() ) )//저장되어있는 노드의 수가 적을때 예외처리
	{
		if( (strcmp(Cur->GetName(),pNode->GetName() ) < 0) && (Cur->GetNameLeft() == NULL) )//root에서 오른쪽 sub tree만 존재 한다면
			Cur->Setbf(-1);//blance factor에 -1 저장
		else if( (strcmp( Cur->GetName(),pNode->GetName() ) > 0) && (Cur->GetNameRight() == NULL) )//root에서 왼쪽 sub tree만 존재 한다면
			Cur->Setbf(1);//blance factor에 1 저장
		else
			Cur->Setbf(0);//둘다 있으면 0저장
		return true;//참 반환
	}

	else if( (pCur == NameRoot->GetNameRight()) || (pCur == NameRoot->GetNameLeft()) )//저장되어있는 노드의 수가 적을때 예외처리
	{
		if( (NameRoot->GetNameLeft()!=NULL) && (NameRoot->GetNameRight() !=NULL ) )//root의 sub tree가 둘다 존재한다면
		{
			Cur = NameRoot;
			while(Cur !=pNode )//insert된 노드까지 반복하는 while문
			{
				if( strcmp( Cur->GetName(), pNode->GetName() ) > 0)//왼쪽 sub tree라면
				{
					Cur->Setbf(1);//blance factor 다시 지정
					Cur = Cur->GetNameLeft();
				}
				else if(strcmp( Cur->GetName(), pNode->GetName() ) < 0)//오른쪽 sub tree라면
				{
					Cur->Setbf(-1);//blance factor 다시 지정
					Cur = Cur->GetNameRight();
				}
				else if(strcmp( Cur->GetName(), pNode->GetName() ) == 0)//이름이 같다면 학번 비교
				{
					if(strcmp( Cur->GetNumber(), pNode->GetNumber() ) > 0)//왼쪽 sub tree라면
					{
						Cur->Setbf(1);//blance factor 다시 지정
						Cur = Cur->GetNameLeft();
					}
					else//오른쪽 sub tree라면
					{
						Cur->Setbf(-1);//blance factor 다시 지정
						Cur = Cur->GetNameRight();
					}
				}
			}
			return true;//참반환
		}
	}

	if(Break==NULL)//들어갈 노드의 상위 sub tree가 모두 blance가 유지되고 있다면
	{
		Cur=NameRoot;//Cur을 Root로 지정
		while(Cur !=pNode) //새로운 노드가 들어가고나서 blance를 다시 지정해준다
		{
			if( strcmp( Cur->GetName(), pNode->GetName() ) > 0)//왼쪽 sub tree라면
			{
				Cur->Setbf(1);//blance factor 다시 지정
				Cur = Cur->GetNameLeft();
			}
			else if(strcmp( Cur->GetName(), pNode->GetName() ) < 0)//오른쪽 sub tree라면
			{
				Cur->Setbf(-1);//blance factor 다시 지정
				Cur = Cur->GetNameRight();
			}
			else if(strcmp( Cur->GetName(), pNode->GetName() ) == 0)//이름이 같다면 학번 비교
			{
				if(strcmp( Cur->GetNumber(), pNode->GetNumber() ) > 0)//왼쪽 sub tree라면
				{
					Cur->Setbf(1);//blance factor 다시 지정
					Cur = Cur->GetNameLeft();
				}
				else//오른쪽 sub tree라면
				{
					Cur->Setbf(-1);//blance factor 다시 지정
					Cur = Cur->GetNameRight();
				}
			}
		}
		return true;//참반환
	}

	int check=0;//Right,Left인지를 구분해준다.
	User *b,*c;//blance를 마추기 위한 User 포인터와 check 변수

	if(strcmp( Break->GetName(), pNode->GetName() ) < 0)//blance 가 깨진 노드의 오른쪽 sub tree에 새로운 노드가 들어갔다면
	{
		b=Break->GetNameRight();
		Cur=Break->GetNameRight();
		check = -1;//다음의 값들을 바꿔준다
	}
	else//blance 가 깨진 노드의 왼쪽 sub tree에 새로운 노드가 들어갔다면
	{
		b=Break->GetNameLeft();
		Cur=Break->GetNameLeft();
		check = 1;//다음의 값들을 바꿔준다
	}

	while(Cur != pNode)//새로 삽입된 노드의 부모노드들의 blance factor를 다시 지정해준다
	{
		if( strcmp(Cur->GetName(), pNode->GetName() )  < 0)//오른쪽 sub tree라면
		{
			Cur->Setbf(-1);
			Cur=Cur->GetNameRight();//값을 지정해준다
		}
		else if(strcmp(Cur->GetName(), pNode->GetName() )  > 0)//왼쪽 sub tree라면
		{
			Cur->Setbf(1);
			Cur= Cur->GetNameLeft();//값을 지정해준다
		}
		else//이름이 같다면 => 학번 비교
		{
			if(strcmp( Cur->GetNumber(), pNode->GetNumber() ) < 0)//오른쪽 sub tree라면
			{
				Cur->Setbf(-1);
				Cur=Cur->GetNameRight();//값을 지정해준다
			}
			else//왼쪽 sub tree라면 
			{
				Cur->Setbf(1);
				Cur= Cur->GetNameLeft();//값을 지정해준다
			}
		}
	}

	if( !(Break->Getbf()) || !(Break->Getbf() + check) )//노드의 이동이 없어도 되는 경우라면
	{
		Break->Setbf( (Break->Getbf() + check) );//blance factor 다시 지정후 
		return true;//참반환
	}

	if(check ==1 )//왼쪽 sub tree라면
	{
		if(b->Getbf() ==1 )// LL 구조라면
		{
			Break->SetNameLeft( b->GetNameRight() );
			b->SetNameRight(Break);
			Break->Setbf(0);
			b->Setbf(0);//노드들의 위치를 바꿔주고 blance factor를 다시 지정해준다
		}
		else// LR 구조라면
		{
			c = b->GetNameRight();
			b->SetNameRight( c->GetNameLeft() );
			Break->SetNameLeft( c->GetNameRight() );
			c->SetNameLeft(b);
			c->SetNameRight(Break);//노드들의 위치를 바꿔서 지정해준다

			if(c->Getbf() == 1)//각 경우에 따라 blance factor를 다시 지정해준다
			{
				Break->Setbf(-1);
				b->Setbf(0);
			}
			else if(c->Getbf() == -1)
			{
				b->Setbf(1);
				Break->Setbf(0);
			}
			else if(c->Getbf() == 0)
			{
				b->Setbf(0);
				Break->Setbf(0);
			}
			c->Setbf(0);//blance factor를 다시 지정해준다
			b=c;
		}
	}

	else//오른쪽 sub tree라면
	{
		if(b->Getbf() == -1 )// RR 구조라면
		{
			Break->SetNameRight( b->GetNameLeft() );
			b->SetNameLeft(Break);
			Break->Setbf(0);
			b->Setbf(0);//노드들의 위치를 바꿔주고 blance factor를 다시 지정해준다
		}
		else// RL 구조라면
		{
			c = b->GetNameLeft();
			b->SetNameLeft( c->GetNameRight() );
			Break->SetNameRight( c->GetNameLeft() );
			c->SetNameRight(b);
			c->SetNameLeft(Break);//노드들의 위치를 바꿔서 지정해준다

			if(c->Getbf() == 1)//각 경우에 따라 blance factor를 다시 지정해준다
			{
				Break->Setbf(0);
				b->Setbf(-1);
			}
			else if(c->Getbf() == -1)
			{
				b->Setbf(0);
				Break->Setbf(1);
			}
			else if(c->Getbf() == 0)
			{
				b->Setbf(0);
				Break->Setbf(0);
			}
			c->Setbf(0);//blance factor를 다시 지정해준다
			b=c;
		}
	}

	if( !(pBreak) )//깨진 노드가 Root라면
		NameRoot = b;//Root 다시지정
	else if(Break == pBreak->GetNameLeft() )//깨진 노드들의 blance를 마추고 상위 노드와 연결해준다
		pBreak->SetNameLeft(b);//연결
	else
		pBreak->SetNameRight(b);//연결

	return true;//참반환
}

bool AVL::NumberAVL(User *pNode)//학번 기준 AVL TREE
{
	User *Cur = NumberRoot;
	User *pCur = NULL;
	User *Break = NULL;
	User *pBreak = NULL;//AVL을 위한 포인터 변수 선언

	if(NumberRoot==NULL)//저장되어있는 노드가 없다면
	{
		NumberRoot=pNode;//헤더로 지정후 참 반환
		return true;
	}

	while(Cur!=NULL)//들어갈 위치를 찾아주기 위한 반복문
	{
		if( Cur->Getbf() )//벨런스가 깨진 노드를 찾아준다
		{
			Break = Cur;
			pBreak = pCur;//Break, pBreak에 저장한다
		}

		if( strcmp( Cur->GetNumber(), pNode->GetNumber() ) > 0)//새로운 노드의 학번이 빠르다면
		{
			pCur = Cur;
			Cur = Cur->GetNumLeft();//left next를 저장
		}
		else //새로운 노드의 학번이 더 느리다면
		{
			pCur = Cur;
			Cur = Cur->GetNumRight();//right next를 저장
		}
	}
	//새로운 노드가 들어가야 할 위치에 대입해준다.
	if( strcmp( pCur->GetNumber(), pNode->GetNumber() ) > 0)//왼쪽 sub tree에 저장
		pCur->SetNumLeft(pNode);
	else//오른쪽 sub tree에 저장
		pCur->SetNumRight(pNode);

	Cur = NumberRoot;//Cur을 Root로 지정
	if( ( pNode == NumberRoot->GetNumLeft() ) || ( pNode == NumberRoot->GetNumRight() ) )//저장되어있는 노드의 수가 적을때 예외처리
	{
		if( (strcmp(Cur->GetNumber(),pNode->GetNumber() ) < 0) && (Cur->GetNumLeft() == NULL) )//root에서 오른쪽 sub tree만 존재 한다면
			Cur->SetNbf(-1);//blance factor에 -1 저장
		else if( (strcmp( Cur->GetNumber(), pNode->GetNumber() ) > 0) && (Cur->GetNumRight() == NULL) )//root에서 왼쪽 sub tree만 존재 한다면
			Cur->SetNbf(1);//blance factor에 1 저장
		else
			Cur->SetNbf(0);//둘다 있으면 0저장
		return true;//참 반환
	}

	else if( (pCur == NumberRoot->GetNumRight()) || (pCur == NumberRoot->GetNumLeft()) )//저장되어있는 노드의 수가 적을때 예외처리
	{
		if( (NumberRoot->GetNumLeft()!=NULL) && (NumberRoot->GetNumRight() !=NULL ) )//root의 sub tree가 둘다 존재한다면
		{
			Cur = NumberRoot;
			while(Cur !=pNode )//insert된 노드까지 반복하는 while문
			{
				if( strcmp( Cur->GetNumber(), pNode->GetNumber() ) > 0)//왼쪽 sub tree라면
				{
					Cur->SetNbf(1);//blance factor 다시 지정                                                           
					Cur = Cur->GetNumLeft();
				}
				else if(strcmp( Cur->GetNumber(), pNode->GetNumber() ) < 0)//오른쪽 sub tree라면
				{
					Cur->SetNbf(-1);//blance factor 다시 지정
					Cur = Cur->GetNumRight();
				}
			}
			return true;//참반환
		}
	}

	if(Break==NULL)//들어갈 노드의 상위 sub tree가 모두 blance가 유지되고 있다면
	{
		Cur=NumberRoot;
		while(Cur !=pNode) //새로운 노드가 들어가고나서 blance를 다시 지정해준다
		{
			if( strcmp( Cur->GetNumber(), pNode->GetNumber() ) > 0)//왼쪽 sub tree라면
			{
				Cur->SetNbf(1);//blance factor 다시 지정
				Cur = Cur->GetNumLeft();
			}
			else if(strcmp( Cur->GetNumber(), pNode->GetNumber() ) < 0)//오른쪽 sub tree라면
			{
				Cur->SetNbf(-1);//blance factor 다시 지정
				Cur = Cur->GetNumRight();
			}
		}
		return true;//참반환
	}

	int check=0;//Right,Left인지를 판단하는 변수
	User *b,*c;//blance를 마추기 위한 User 포인터와 check 변수

	if(strcmp( Break->GetNumber(), pNode->GetNumber() ) < 0)//blance 가 깨진 노드의 오른쪽 sub tree에 새로운 노드가 들어갔다면
	{
		b=Break->GetNumRight();
		Cur=Break->GetNumRight();
		check = -1;//다음의 값들을 바꿔준다
	}
	else//blance 가 깨진 노드의 왼쪽 sub tree에 새로운 노드가 들어갔다면
	{
		b=Break->GetNumLeft();
		Cur=Break->GetNumLeft();
		check = 1;//다음의 값들을 바꿔준다
	}

	while(Cur != pNode)//새로 삽입된 노드의 부모노드들의 blance factor를 다시 지정해준다
	{
		if( strcmp(Cur->GetNumber(), pNode->GetNumber() )  < 0)//오른쪽 sub tree라면
		{
			Cur->SetNbf(-1);
			Cur=Cur->GetNumRight();//값을 지정해준다
		}
		else//왼쪽 sub tree라면
		{
			Cur->SetNbf(1);
			Cur= Cur->GetNumLeft();//값을 지정해준다
		}
	}

	if( !(Break->GetNbf()) || !(Break->GetNbf() + check) )//노드의 이동이 없어도 되는 경우라면
	{
		Break->SetNbf( (Break->GetNbf()+check) );//blance factor 다시 지정후 
		return true;//참반환
	}

	if(check ==1 )//왼쪽 sub tree라면
	{
		if(b->GetNbf() ==1 )// LL 구조라면
		{
			Break->SetNumLeft( b->GetNumRight() );
			b->SetNumRight(Break);
			Break->SetNbf(0);
			b->SetNbf(0);//노드들의 위치를 바꿔주고 blance factor를 다시 지정해준다
		}
		else// LR 구조라면
		{
			c = b->GetNumRight();
			b->SetNumRight( c->GetNumLeft() );
			Break->SetNumLeft( c->GetNumRight() );
			c->SetNumLeft(b);
			c->SetNumRight(Break);//노드들의 위치를 바꿔서 지정해준다

			if(c->GetNbf() == 1)//각 경우에 따라 blance factor를 다시 지정해준다
			{
				Break->SetNbf(-1);
				b->SetNbf(0);
			}
			else if(c->GetNbf() == -1)
			{
				b->SetNbf(1);
				Break->SetNbf(0);
			}
			else if(c->GetNbf() == 0)
			{
				b->SetNbf(0);
				Break->SetNbf(0);
			}
			c->SetNbf(0);//blance factor를 다시 지정해준다
			b=c;
		}
	}

	else//오른쪽 sub tree라면
	{
		if(b->GetNbf() == -1 )// RR 구조라면
		{
			Break->SetNumRight( b->GetNumLeft() );
			b->SetNumLeft(Break);
			Break->SetNbf(0);
			b->SetNbf(0);//노드들의 위치를 바꿔주고 blance factor를 다시 지정해준다
		}
		else// RL 구조라면
		{
			c = b->GetNumLeft();
			b->SetNumLeft( c->GetNumRight() );
			Break->SetNumRight( c->GetNumLeft() );
			c->SetNumRight(b);
			c->SetNumLeft(Break);//노드들의 위치를 바꿔서 지정해준다

			if(c->GetNbf() == 1)//각 경우에 따라 blance factor를 다시 지정해준다
			{
				Break->SetNbf(0);
				b->SetNbf(-1);
			}
			else if(c->GetNbf() == -1)
			{
				b->SetNbf(0);
				Break->SetNbf(1);
			}
			else if(c->GetNbf() == 0)
			{
				b->SetNbf(0);
				Break->SetNbf(0);
			}
			c->SetNbf(0);//blance factor를 다시 지정해준다
			b=c;
		}
	}

	if( !(pBreak) )//깨진 노드가 Root라면
		NumberRoot = b;//Root 다시지정
	else if(Break == pBreak->GetNumLeft() )//깨진 노드들의 blance를 마추고 상위 노드와 연결해준다
		pBreak->SetNumLeft(b);//연결
	else
		pBreak->SetNumRight(b);//연결

	return true;//참반환

}

User *AVL::NumSearch(char *Num)//학번으로 해당 노드를 찾는다
{
	User *temp = NumberRoot;//temp에 NumberRoot 노드를 넣어준다.

	if(temp==NULL)//저장되어있는 정보가 없다면
	{
		cout<<"저장되어있는 데이터가 없습니다"<<endl;
		return NULL;//해당문구 출력 거짓 반환
	}

	while( temp !=NULL )//노드의 마지막 까지 반복한다
	{
		if( strcmp(temp->GetNumber(), Num ) == 0 ) //학번이 일치한다면 temp 반환
			return temp;
		if( strcmp( temp->GetNumber(), Num ) > 0)//temp가 num보다 크다면 temp에 왼쪽 sub tree를 넣어준다
			temp = temp->GetNumLeft();
		else                            //temp가 num보다 작다면 temp에 오른쪽 sub tree를 넣어준다
			temp = temp->GetNumRight();
	}
	return NULL;//찾는 노드가 없다면 NULL 반환
}

bool AVL::CheckSameName(char *Name)//동명이인 check 함수
{
	User *temp = NameRoot;//temp에 NameRoot 노드를 넣어준다.
	User *temp2 = NULL;
	int check =0;

	if(temp==NULL)//저장되어있는 정보가 없다면
	{
		cout<<"저장되어있는 데이터가 없습니다"<<endl;
		return false;//해당문구 출력 거짓 반환
	}

	while( temp !=NULL )//노드의 마지막 까지 반복한다
	{
		if( strcmp(temp->GetName(), Name ) == 0 ) //이름이 일치한다면 그 노드의 sub tree를 확인한다
		{
			temp2 = temp->GetNameLeft();//왼쪽 sub tree
			while( temp2 !=NULL )//노드의 마지막 까지 반복한다
			{
				if( strcmp(temp2->GetName(), Name ) == 0 ) //동명이인이 존재한다면
					return true;//참반환
				if( strcmp( temp2->GetName(), Name ) > 0)//temp2의 이름보다 빠르다면
					temp2 = temp2->GetNameLeft();//left sub tree 접근
				else                           //temp2의 이름보다 느리다면
					temp2 = temp2->GetNameRight();//right sub tree 접근
			}

			temp2 = temp->GetNameRight();//오른쪽 sub tree
			while( temp2 !=NULL )//노드의 마지막 까지 반복한다
			{
				if( strcmp(temp2->GetName(), Name ) == 0 )//동명이인이 존재한다면
					return true;//참반환
				if( strcmp( temp2->GetName(), Name ) > 0)//temp2의 이름보다 빠르다면
					temp2 = temp2->GetNameLeft();//left sub tree 접근
				else                            //temp2의 이름보다 느리다면
					temp2 = temp2->GetNameRight();//right sub tree 접근
			}
			return false;//동일한 이름의 sub tree안에 동명이인이 없으므로 false 반환
		}
		if( strcmp( temp->GetName(), Name ) > 0)//temp1의 이름보다 빠르다면
			temp = temp->GetNameLeft();//left sub tree 접근
		else                            //temp2의 이름보다 느리다면
			temp = temp->GetNameRight();//right sub tree 접근
	}
	return false;
}

User *AVL::NameSearch(char *Name)//이름으로 해당유저를 찾아 반환한다
{
	User *temp = NameRoot;//temp에 NameRoot 노드를 넣어준다.
	if(temp==NULL)//저장되어있는 정보가 없다면
	{
		cout<<"저장되어있는 데이터가 없습니다"<<endl;
		return NULL;//해당문구 출력 거짓 반환
	}

	while( temp !=NULL )//노드의 마지막 까지 반복한다
	{
		if( strcmp(temp->GetName(), Name ) == 0 ) //이름이 일치한다면 temp 반환
			return temp;
		if( strcmp( temp->GetName(), Name ) > 0)//temp의 이름보다 빠르다면
			temp = temp->GetNameLeft();//left sub tree 접근
		else                            //temp2의 이름보다 느리다면
			temp = temp->GetNameRight();//right sub tree 접근
	}
	return NULL;//찾는 값이 없으면 NULL 반환
}

User *AVL::NameSearch(char *Name, char *Num)//동명이인의 유저노드를 반환 하고 싶을때 사용
{
	User *temp = NameRoot;//temp에 NameRoot 노드를 넣어준다.
	User *temp2 = NULL;
	int check =0;
	if(temp==NULL)//저장되어있는 정보가 없다면
	{
		cout<<"저장되어있는 데이터가 없습니다"<<endl;
		return NULL;//해당문구 출력 거짓 반환
	}

	while( temp !=NULL )//노드의 마지막 까지 반복한다
	{
		if( strcmp(temp->GetName(), Name ) == 0 ) //이름이 일치한다면 sub tree 접근
		{
			temp2 = temp->GetNameLeft();//왼쪽 sub tree
			while( temp2 !=NULL )//노드의 마지막 까지 반복한다
			{
				if( (strcmp(temp2->GetName(), Name ) == 0) && (strcmp(temp2->GetNumber(),Num)!=0) )//동명이인이라면
					return temp2;//동명이인 노드 반환
				if( strcmp( temp2->GetName(), Name ) > 0)//temp2의 이름보다 빠르다면
					temp2 = temp2->GetNameLeft();//left sub tree 접근
				else                             //temp2의 이름보다 느리다면
					temp2 = temp2->GetNameRight();//right sub tree 접근
			}
			temp2 = temp->GetNameRight();//오른쪽 sub tree
			while( temp2 !=NULL )//노드의 마지막 까지 반복한다
			{
				if( (strcmp(temp2->GetName(), Name ) == 0) && (strcmp(temp2->GetNumber(),Num)!=0) )//동명이인이라면
					return temp2;//동명이인 노드 반환
				if( strcmp( temp2->GetName(), Name ) > 0)//temp2의 이름보다 빠르다면
					temp2 = temp2->GetNameLeft();//left sub tree 접근
				else                            //temp2의 이름보다 느리다면
					temp2 = temp2->GetNameRight();//right sub tree 접근
			}
			return NULL;//찾는 값이 없으면 NULL 반환
		}
		if( strcmp( temp->GetName(), Name ) > 0)//temp의 이름보다 빠르다면
			temp = temp->GetNameLeft();//left sub tree 접근
		else                           //temp의 이름보다 느리다면
			temp = temp->GetNameRight();//right sub tree 접근
	}
}
#ifdef aa//삭제를 구현 하지 못하였습니다.
bool AVL::NumberDelete(User *pNode)
{
}

bool AVL::NameDelete(User *pNode)
{

	int found = false;
	User *p=NameRoot;
	User *q = NULL;
	User *r = NULL;
	User *s = NULL;
	User *t = NULL;

	while ( p && (!found) ) 
	{
		if ( strcmp(p->GetName(),pNode->GetName())==0 ) 
			found = true;
		else 
		{
			q = p;
			if ( strcmp(p->GetName(), pNode->GetName()) > 0 )
				p = p->GetNameLeft();
			else
				p = p->GetNameRight();
		}
	}

	if (!p) 
		return;

	if ( p->GetNameLeft() == NULL ) 
		r = p->GetNameRight();
	else 
	{
		if ( p->GetNameRight() == NULL ) 
			r = p->GetNameLeft(); 
		else 
		{ /* node with two children */
			t = p; /* find smallest node in right subtree */
			r = p->GetNameRight();
			s = r->GetNameLeft();
			while (s) 
			{
				t = r; /* parent of replacing node */
				r = s; /* replacing node */
				s = r->GetNameLeft(); 
				/* lf child of replacing node*/
			}
			if (t != p)
			{ /* r is not right child of p */
				t->SetNameLeft(r->GetNameRight());
				r->SetNameRight(p->GetNameRight();
			}
			r->SetNameLeft(p->GetNameLeft());
		}
	}

	if (!q) 
		NameRoot = r; /* root is replaced by r */
	else if (p == q->GetNameLeft() ) 
		q->SetNameLeft(r);
	else 
		q->SetNameRight(r);

	Del.Delete(p);

	while (p != y)
	{
		// Is tree unbalanced?
		if (!(a->bf || !(a->bf+d)) 
		{ // tree still balanced
			a->bf+=d; return;
		}
		if (d == 1) 
		{ // left imbalance
			if (b->bf == 1) 
			{ // rotation type LL
				a->leftChild = b->rightChild;
				b->rightChild = a; a->bf = 0; b->bf = 0;
			} 
			else
			{ // rotation type LR
				c = b->rightChild;
				b->rightChild = c->leftChild;
				a->leftChild = c->rightChild; 
				c->leftChild = b; 
				c->rightChild = a;
				switch (c->bf) 
				{
				case 1:
					a->bf = -1; b->bf = 0;
					break;
				case -1:
					b->bf = 1; a->bf = 0;
					break; 
				case 0:
					b->bf = 0; a->bf = 0;
					break; 
				}
				c->bf = 0; b = c; // b is the new root
			} // end of LR 
		} // end of left imbalance

	}
}
}*/
#endif