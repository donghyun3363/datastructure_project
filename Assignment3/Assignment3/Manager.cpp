#include "Manager.h"
#include<iostream>
#include<fstream>//������� ����

using namespace std;//�̸� ������ std ������ ���

Manager::Manager(void)//������
{
	for(int i= 0;i<3;i++) // 3*100 �迭 �ʱ�ȭ
	{
		for(int j=0; j<100; j++)
			Short[i][j]=0;
	}
}

Manager::~Manager(void)//�Ҹ���
{

}

bool Manager::Load_gu(char *file1, char *file2)//�� ���� ���� �ε�
{
	ifstream fin;//Gu Vertex ���� ����
	GuVertex *Gu = NULL;

	char str[200];//���پ� �ޱ� ���� �迭 ����
	memset(str,NULL,sizeof(str));//�迭 �ʱ�ȭ

	char *temp1 = NULL;
	char *temp2 = NULL;//���ڿ��� ¥���� ���� char�� �ӽ� ������ ����
	int flag = 0;

	fin.open(file1,ios::in);//�Է� ���� ���ϸ����� ������ �б� ���� �����ش�
	if( !(fin.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	for(int i=0;i<3;i++)//�޸��忡 �ʿ� ���� ������ �����ش�
		fin.getline(str,sizeof(str));
	memset(str,NULL,sizeof(str));//�迭�� NULL�� �ʱ�ȭ

	while( !(fin.eof()) )//������ ������ �ݺ��Ѵ�
	{
		fin.getline(str,sizeof(str));//���Ͽ��� ������ �޾ƿ´�
		if(str[0]==NULL)//Enter�� ���´ٸ� ���� ����
			break;
		temp1 = strtok(str,"	 /");//���� ¥����.

		if( ADJList.SearchGuVertex(temp1) == NULL )//�ش��ϴ� �̸��� ���� ���� ���ٸ�
		{
			Gu = new GuVertex();//�� Vertex �����Ҵ�
			Gu->SetGuName(temp1);//�� �̸��� �־��ش�

			Gu->SetShortflag(flag);//���� �ִ� �Ÿ� flag�� �־��ش�
			flag++;
			if( !(ADJList.Guinsert(Gu)) )//�� ���Ḯ��Ʈ �Լ� ȣ��
				cout<<"�� ���� Insert�� ���� �Ͽ����ϴ�."<<endl;//���� �Ͽ��ٸ� �ش繮�� ���
		}
		else//�̹� ����� �� ���
			cout<<"�����ϴ� ��Vertex �Դϴ�."<<endl;//�ش� ���� ���

		temp1=NULL;//temp�� NULL�� �ʱ�ȭ
		memset(str,NULL,sizeof(str));//�迭���� NULL�� �ʱ�ȭ�Ѵ�
	}
	fin.close();//������ �ݾ��ش�

	///////////////////////////////////////////////////////////////////////////GuEdge
	ifstream fin2;//���� ��Ʈ�� ����
	GuVertex *tempGu = NULL;
	GuEdge *guEdge = NULL;

	char *dis = NULL;//�ӽ� ������ ������ ����
	int dis2 = 0;

	memset(str,NULL,sizeof(str));
	temp1 = NULL;
	temp2 = NULL;//������ �������� �ʱ�ȭ ���ش�

	fin2.open(file2,ios::in);//�� Edge������ open���ش�
	if( !(fin2.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	for(int i=0;i<3;i++)//�޸��忡 �ʿ� ���� ������ �����ش�
		fin2.getline(str,sizeof(str));
	memset(str,NULL,sizeof(str));//�迭�� NULL�� �ʱ�ȭ

	while( !(fin2.eof()) )//������ ������ �ݺ��Ѵ�
	{
		fin2.getline(str,sizeof(str));//���Ͽ��� ������ �޾ƿ´�
		if(str[0]==NULL)//Enter�� ���´ٸ� ���� ����
			break;

		temp1 = strtok(str,"	 /");//from Gu
		temp2 = strtok(NULL,"	 /");//to Gu
		dis = strtok(NULL,"	 /");//�Ÿ�
		dis2 = atoi(dis);

		tempGu = ADJList.SearchGuVertex(temp1);//from�� �ش��ϴ� �� Vertex�� ã���ش�
		if( tempGu != NULL )//from�� �ش��ϴ� ���� ���� �Ѵٸ�
		{
			if( ADJList.SearchGuEdge(tempGu, temp2) == NULL )//����  from, to edge�� ���� ���� �ʴ´ٸ�
			{
				guEdge = new GuEdge();
				guEdge->SetfromGu(temp1);
				guEdge->SettoGu(temp2);
				guEdge->SetDis(dis2);//Gu Edge ������ ���� �������� �����Ѵ�.

				if( !( ADJList.GuEdgeinsert(tempGu, guEdge) ) )
					cout<<"���� ����Ʈ �μ�Ʈ ����"<<endl;
			}
			else//Edge�� ���� �Ѵٸ�
				cout<<"�̹� �����ϴ� �� Edge �Դϴ�."<<endl;//�ش� ���� ���
		}
		else//from�� �ش��ϴ� ���� ���� ���� �ʴ´ٸ�
			cout<<"�������� �ʴ� ��Vertex �Դϴ�."<<endl;//�ش� ���� ���

		tempGu = NULL;
		guEdge = NULL;
		temp1 = NULL;
		temp2 = NULL;
		dis = NULL;
		memset(str,NULL,sizeof(str));//�迭�� ������ �������� NULL�� �ʱ�ȭ�Ѵ�
	}

	fin2.close();//guEdge ������ �ݾ��ش�
	return true;//����ȯ
}

bool Manager::Load_dong(char *file1, char *file2)//�� ���� ���� �ε�
{
	ifstream fin;//���� ��Ʈ�� ����
	GuVertex *tempGu = NULL;
	DongVertex *Dong = NULL;//�ӽ� ������ ���� ����

	char str[200];//���پ� �ޱ� ���� �迭 ����
	memset(str,NULL,sizeof(str));//�迭 �ʱ�ȭ
	char *temp1 = NULL;
	char *temp2 = NULL;
	char *temp3 = NULL;//���ڿ��� ¥���� ���� char�� �ӽ� ������ ����

	fin.open(file1,ios::in);//�Է� ���� ���ϸ����� ������ �б� ���� �����ش�
	if( !(fin.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	for(int i=0;i<3;i++)//�޸��忡 �ʿ� ���� ������ �����ش�
		fin.getline(str,sizeof(str));
	memset(str,NULL,sizeof(str));//�迭�� NULL�� �ʱ�ȭ

	while( !(fin.eof()) )//������ ������ �ݺ��Ѵ�
	{
		fin.getline(str,sizeof(str));//���Ͽ��� ������ �޾ƿ´�
		if(str[0]==NULL)//Enter�� ���´ٸ� ���� ����
			break;
		temp1 = strtok(str,"	 /");//���� ¥����
		temp2 = strtok(NULL,"	 /");//���� ¥����
		temp3 = strtok(NULL,"	 /");//���� ������ ���θ� ¥����

		tempGu = ADJList.SearchGuVertex(temp1);//�� �̸��� �ش��ϴ� Vertex�� ã�´�
		if( tempGu != NULL ) //�����ϴ� �����
		{
			if( ADJList.SearchDongVertex(tempGu, temp2) == NULL )//�̹������ϴ� �� vertex���� Ȯ���Ѵ�
			{
				Dong = new DongVertex();
				Dong->SetguName(temp1);
				Dong->SetDongName(temp2);
				Dong->SetView(temp3);//�� Vertex ������ �ش� �������� �����Ѵ�.

				if( !( ADJList.Donginsert(tempGu, Dong) ) )//���� �������ش�
					cout<<"�� ���� Insert�� ���� �Ͽ����ϴ�."<<endl;
			}

			else//�̹� �����ϴ� �� Vertex���
				cout<<"�̹� �����ϴ� ��vertex �Դϴ�."<<endl;//�ش� ���� ���
		}

		else//���� ���� ���� ���� �ʴ´ٸ�
			cout<<"�������� �ʴ� �� Vertex �Դϴ�."<<endl;//�ش� ���� ���

		temp1 = NULL;
		temp2 = NULL;
		temp3 = NULL;
		tempGu = NULL;
		Dong = NULL;
		memset(str,NULL,sizeof(str));//�迭�� �ӽ� ������ �������� NULL�� �ʱ�ȭ�Ѵ�
	}
	fin.close();//������ �ݾ��ش�

	tempGu = ADJList.GetGuHead();//����� �� Vertex�� ����� ��ȯ �޴´�
	while(tempGu !=NULL)//�� Vertex�� ������ �ݺ��Ѵ�
	{
		ADJList.SetDongHead(tempGu);//��������Լ� ȣ��
		tempGu = tempGu->GetGuNext();//���� ���� ����Ų��
	}//�� ������ ��Vertex ����� ��������ҷ� �ٲٱ� ���� �ݺ����̴�.

	////////////////////////////////////////////////////////////////////////////////////Dongedge
	ifstream fin2;//���� ��Ʈ�� ����

	tempGu = NULL;
	Dong = NULL;
	DongEdge *dongEdge = NULL;

	temp1 = NULL;
	temp2 = NULL;
	temp3 = NULL;
	char *lossrate = NULL;
	int lossrate2 = 0;

	memset(str,NULL,sizeof(str));//�迭�� ������ �������� �ٽ� �ʱ�ȭ

	fin2.open(file2,ios::in);//�Է� ���� ���ϸ����� ������ �б� ���� �����ش�
	if( !(fin2.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	for(int i=0;i<3;i++)//�޸��忡 �ʿ� ���� ������ �����ش�
		fin2.getline(str,sizeof(str));
	memset(str,NULL,sizeof(str));//�迭�� NULL�� �ʱ�ȭ

	while( !(fin2.eof()) )//������ ������ �ݺ��Ѵ�
	{
		fin2.getline(str,sizeof(str));//���Ͽ��� ������ �޾ƿ´�
		if(str[0]==NULL)//Enter�� ���´ٸ� ���� ����
			break;

		temp1 = strtok(str,"	 /");//���� ¥����
		temp2 = strtok(NULL,"	 /");//from ���� ¥����
		temp3 = strtok(NULL,"	 /");//to ���� ¥����
		lossrate = strtok(NULL,"	 /");//�� �սǷ��� ¥����
		lossrate2 = atoi(lossrate);

		tempGu = ADJList.SearchGuVertex(temp1);//�ش��ϴ� ���� ã�´�
		if( tempGu != NULL )//�ش��ϴ� ���� ���� �Ѵٸ�
		{
			Dong = ADJList.SearchDongVertex(tempGu, temp2);//�ش籸�� from ���� �ִ��� ã�´�
			if( Dong != NULL )//���� ���� �Ѵٸ�
			{
				if( ADJList.SearchDongEdge(Dong, temp3) == NULL )//���� edge�� ���� ���� �ʴ´ٸ�
				{
					dongEdge = new DongEdge();
					dongEdge->SetGuName(temp1);
					dongEdge->SetfromDong(temp2);
					dongEdge->SettoDong(temp3);
					dongEdge->SetLossrate(lossrate2);//�� edge�� ���� �Ҵ� �ϰ� �ش� ������ �����Ѵ�

					if( !( ADJList.DongEdgeinsert(Dong, dongEdge) ) )
						cout<<"�� ��������Ʈ insert�� ���� �Ͽ����ϴ�."<<endl;
				}

				else//edge�� �����Ѵٸ�
					cout<<"�̹� �����ϴ� �� Edge �Դϴ�."<<endl;//�ش� ���� ���
			}

			else//���� ���� �ʴ� ��vertex���
				cout<<"�������� �ʴ� �� Vertex �Դϴ�."<<endl;//�ش� ���� ���
		}

		else//�������� �ʴ� �� vertex���
			cout<<"�������� �ʴ� �� Vertex �Դϴ�."<<endl;//�ش� ���� ���

		tempGu = NULL;
		Dong = NULL;
		dongEdge = NULL;
		temp1 = NULL;
		temp2 = NULL;
		temp3 = NULL;
		lossrate = NULL;
		memset(str,NULL,sizeof(str));//�迭�� �ӽ� ������ �������� NULL�� �ʱ�ȭ�Ѵ�
	}

	DongMst();//�ε尡 �Ϸ���� MST �Լ��� ȣ�����ش�.

	fin2.close();//������ �ݾ��ش�
	return true;
}

bool Manager::DongMst()//MST ȣ�� �Լ�
{
	GuVertex *tempGu = ADJList.GetGuHead();//���� ����� ��ȯ�Ѵ�
	int count =0;//���� ������ �ޱ����� int �� ����

	while( tempGu != NULL )//���� ������ �ݺ��Ѵ�
	{
		count = ADJList.CountDong(tempGu);//�ش��ϴ� ���� �� ������ ��ȯ�޴´�

		if( !(DoMst.MST(tempGu, count)) )//MST�� �������� �ʴ´ٸ� 
		{
			Pipe_Repair( tempGu->GetGuName() );//Pipe_Repair �Լ� ȣ��
		}
		tempGu = tempGu->GetGuNext();
		count = 0;//���� ���� ����Ű�� ī���͸� 0���� �ʱ�ȭ �Ѵ�
	}
	return true;//�� ��ȯ
}

bool Manager::Load_Mehanic(char *file)//����� ������ �ε��ϴ� �Լ�
{
	ifstream fin;//���ϰ�ü����
	Mechanic *Per = NULL;
	char str[100];//���پ� �ޱ� ���� �迭 ����
	memset(str,NULL,sizeof(str));//�迭 �ʱ�ȭ

	char *temp1 = NULL;
	char *temp2 = NULL;//���ڿ��� ¥���� ���� char�� �ӽ� ������ ����

	fin.open(file,ios::in);//�Է� ���� ���ϸ����� ������ �б� ���� �����ش�
	if( !(fin.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	for(int i=0;i<3;i++)//�޸��忡 �ʿ� ���� ������ �����ش�
		fin.getline(str,sizeof(str));
	memset(str,NULL,sizeof(str));//�迭�� NULL�� �ʱ�ȭ

	while( !(fin.eof()) )//������ ������ �ݺ��Ѵ�
	{
		fin.getline(str,sizeof(str));//���Ͽ��� ������ �޾ƿ´�
		if(str[0]==NULL)//Enter�� ���´ٸ� ���� ����
			break;

		temp1 = strtok(str,"	 ");//�ٹ����� ¥����
		temp2 = strtok(NULL,"	 ");//����� �̸��� ¥����.

		if( MechanicList.CheckMechanic(temp1) )//������ �ٹ����� ���� ���� �ʴ´ٸ�
		{
			Per = new Mechanic();//���� �Ҵ�
			Per->SetMechanicGu(temp1);
			Per->SetMechanicName(temp2);//���� ������ �־��ش�

			if( !(MechanicList.InsertMechanic(Per)) )//����� ���ῡ ���� �Ͽ��ٸ�
				cout<<"����� ���� Insert�� ���� �Ͽ����ϴ�."<<endl;//�ش繮�� ���
		}

		else//�ٹ����� ���� �ϴٸ�
			cout<<"������ �ٹ��� �Դϴ�."<<endl;//�ش繮�� ���

		temp1 = NULL;
		temp2 = NULL;
		memset(str,NULL,sizeof(str));//�迭���� NULL�� �ʱ�ȭ�Ѵ�
	}

	fin.close();//������ �ݾ��ش�
	return true;
}

bool Manager::Update(char *file)//UPDATE �Լ�
{
	ifstream fin;//���� ��Ʈ�� ����
	GuVertex *Gu = NULL;
	DongVertex *Dong = NULL;
	DongVertex *ReverDong = NULL;

	DongEdge *tempEdge = NULL;
	DongEdge *reverEdge = NULL;//�ӽ� ������ ���� ����

	char str[200];//���پ� �ޱ� ���� �迭 ����
	memset(str,NULL,sizeof(str));//�迭 �ʱ�ȭ

	char *guname = NULL;
	char *fromdong = NULL;
	char *todong = NULL;
	char *lossrate = NULL;//���ڿ��� ¥���� ���� char�� �ӽ� ������ ����

	int lossrate2 = 0;
	memset(str,NULL,sizeof(str));//�迭�� ������ �������� �ٽ� �ʱ�ȭ

	fin.open(file,ios::in);//�Է� ���� ���ϸ����� ������ �б� ���� �����ش�
	if( !(fin.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	for(int i=0;i<3;i++)//�޸��忡 �ʿ� ���� ������ �����ش�
		fin.getline(str,sizeof(str));
	memset(str,NULL,sizeof(str));//�迭�� NULL�� �ʱ�ȭ

	while( !(fin.eof()) )//������ ������ �ݺ��Ѵ�
	{
		fin.getline(str,sizeof(str));//���Ͽ��� ������ �޾ƿ´�
		if(str[0]==NULL)//Enter�� ���´ٸ� ���� ����
			break;

		guname = strtok(str,"	 /");//���� ¥����
		fromdong = strtok(NULL,"	 /");//from ���� ¥����
		todong = strtok(NULL,"	 /");//to ���� ¥����
		lossrate = strtok(NULL,"	 /");//�� �սǷ��� ¥����
		lossrate2= atoi(lossrate); //���ս� int ������ �ٲ��ش�

		Gu = ADJList.SearchGuVertex(guname);//�ش��ϴ� ���� ã�´�
		if( Gu != NULL )//�ش��ϴ� ���� ���� �Ѵٸ�
		{
			Dong = ADJList.SearchDongVertex(Gu, fromdong);//�ش籸�� from ���� �ִ��� ã�´�
			ReverDong = ADJList.SearchDongVertex(Gu, todong);//�ش籸�� to ���� �ִ��� ã�´�

			if( Dong != NULL )//���� ���� �Ѵٸ�
			{
				tempEdge = ADJList.SearchDongEdge(Dong, todong);//edge�� ã���ش�
				if( tempEdge != NULL )//edge ���� �Ѵٸ�
				{
					reverEdge = ADJList.SearchDongEdge(ReverDong, fromdong);//����� ���
					tempEdge->SetLossrate(lossrate2);
					reverEdge->SetLossrate(lossrate2);//�� �սǷ� ����
				}

				else//edge�� ���� ���� �ʴ´ٸ�
				{
					tempEdge = new DongEdge();
					reverEdge = new DongEdge();//������ ������ edge���� �����Ҵ��Ѵ�

					tempEdge->SetGuName(guname);
					tempEdge->SetfromDong(fromdong);
					tempEdge->SettoDong(todong);
					tempEdge->SetLossrate(lossrate2);//�� edge�� ���� �Ҵ� �ϰ� �ش� ������ �����Ѵ�

					reverEdge->SetGuName(guname);
					reverEdge->SetfromDong(todong);
					reverEdge->SettoDong(fromdong);
					reverEdge->SetLossrate(lossrate2);//�� Reveredge�� ���� �Ҵ� �ϰ� �ش� ������ �����Ѵ�

					if( !( ADJList.DongEdgeinsert(Dong, tempEdge) ) )//edge�� ��������Ʈ�� ����
						cout<<"�� ��������Ʈ insert�� ���� �Ͽ����ϴ�."<<endl;

					if( !( ADJList.DongEdgeinsert(ReverDong, reverEdge) ) )//Rever edge�� ��������Ʈ�� ����
						cout<<"�� ��������Ʈ insert�� ���� �Ͽ����ϴ�."<<endl;
				}
			}

			else//���� ���� �ʴ� ��vertex���
				cout<<"�������� �ʴ� �� Vertex �Դϴ�."<<endl;//�ش� ���� ���
		}
		else//�������� �ʴ� �� vertex���
			cout<<"�������� �ʴ� �� Vertex �Դϴ�."<<endl;//�ش� ���� ���

		Gu = NULL;
		Dong = NULL;
		ReverDong = NULL;
		tempEdge = NULL;
		reverEdge = NULL;
		guname = NULL;
		fromdong = NULL;
		todong = NULL;
		lossrate = NULL;
		memset(str,NULL,sizeof(str));//�迭�� �ӽ� ������ �������� NULL�� �ʱ�ȭ�Ѵ�
	}

	Gu = ADJList.GetGuHead();
	while(Gu !=NULL)//��� Edge�� MST ���� 0���� ���ְ� �ٽ� MST �Լ��� ȣ�����ش�
	{
		Dong = Gu->GetDongHead();
		while(1)
		{
			tempEdge = Dong->GetdongedgHead();
			while( tempEdge != NULL )
			{
				tempEdge->SetMst(0);
				tempEdge = tempEdge->GetDongEdgeNext();
			}
			Dong = Dong->GetdongNext();
			if(Dong == Gu->GetDongHead())
				break;
		}
		Gu = Gu->GetGuNext();//��� ����� �ε���� �ݺ��ϸ鼭 MST ���� 0���� ���ش�
	}

	DongMst();//�ε尡 �Ϸ���� MST �Լ��� ȣ�����ش�.

	fin.close();//������ �ݾ��ش�
	return true;
}

bool Manager::Pipe_Broken(char *gu, char *from, char *to)//PIPE BROKEN �Լ�
{
	GuVertex *Gu = ADJList.SearchGuVertex(gu);//�ش��ϴ� ���� ã�´�

	DongVertex *Dong = ADJList.SearchDongVertex(Gu, from);
	DongVertex *ReverDong = ADJList.SearchDongVertex(Gu, to);//from, to �� �ΰ��� ã���ش�

	DongEdge *Edge = ADJList.SearchDongEdge(Dong,to);
	DongEdge *ReverEdge = ADJList.SearchDongEdge(ReverDong, from);//����� edge�� ��� ã���ش�

	if(Gu !=NULL)
	{
		if(Dong != NULL)
		{
			if(Edge != NULL)
			{
				Edge->SetBroken(1);
				ReverEdge->SetBroken(1);//�����ϴ� edge��� BROKEN flag ���� set ���ش�
			}
			else
				cout<<"ã���� �ϴ� Edge�� �����ϴ�."<<endl;
		}
		else
			cout<<"ã���� �ϴ� ���� �����ϴ�."<<endl;
	}
	else
		cout<<"ã�� ���� ���� ���� �ʽ��ϴ�."<<endl;

	Gu = ADJList.GetGuHead();//��� Edge�� MST ���� 0���� ���ְ� �ٽ� MST �Լ��� ȣ�����ش�
	while(Gu !=NULL)
	{
		Dong = Gu->GetDongHead();
		while(1)
		{
			Edge = Dong->GetdongedgHead();
			while( Edge != NULL )
			{
				Edge->SetMst(0);
				Edge = Edge->GetDongEdgeNext();
			}
			Dong = Dong->GetdongNext();
			if(Dong == Gu->GetDongHead())
				break;
		}
		Gu = Gu->GetGuNext();
	}  /////////////////////MST flag ���� 0���� �ٽ� �� �ʱ�ȭ ���� �ش�

	DongMst();//�ε尡 �Ϸ���� MST �Լ��� ȣ�����ش�.

	return true;
}

bool Manager::Pipe_Repair(char *gu)//Pipe_Repair �Լ�
{
	ofstream f("repair_log.txt",ios_base::app);//repair_log.txt������ �����ش�.
	if( !(f.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	GuVertex *Gu = ADJList.SearchGuVertex(gu);
	Mechanic *Man = NULL;
	Man = ShortestPath(Gu);//�ִ� �Ÿ��� ������ ����縦 ã���ش�

	for(int i=0; i<35; i++)
		f<<"==";
	f<<endl<<"			PIPE REPAIR"<<endl;
	for(int i=0; i<35; i++)
		f<<"==";
	f<<endl; 
	f<<Man->GetMechanicName()<<"  /  "<<Gu->GetGuName()<<endl;
	f<<"���� �� ���� �� ����"<<endl;//�ش� ������ ���Ͽ� ������ش�

	DongVertex *Dong = NULL;
	DongEdge *Edge = NULL;//�ӽ� ��, �� ���� ������ ����

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
				if(Edge->GetMst() == 1)//MST edge���
					f<<"	"<<Edge->GetfromDong()<<"  ->  "<<Edge->GettoDong()<<" ( "<<Edge->GetLossrate()<<" ) "<<endl;
				//���� ������ ���Ͽ� ������ش�
				Edge = Edge->GetDongEdgeNext();//���� edge�� ����Ų��
			}
			Dong = Dong->GetdongNext();//���� ��������Ų��
			if(Dong == Gu->GetDongHead())//��������Ʈ �ݺ��� �����ٸ�
				break;//���ѷ�������
		}
	}

	f<<"���� ����"<<endl;//���Ͽ� ���

	int lossrate = 0;
	Dong = NULL;

	if(Gu!=NULL)
	{
		Dong = Gu->GetDongHead();//���� ������� ��ȯ�Ѵ�
		while(1)
		{
			if(Dong == NULL)//����� ���� ���ٸ� 
				break;

			Edge = Dong->GetdongedgHead();//edge�� ã���ش�
			while( Edge != NULL )//edge�� ������ �ݺ��Ѵ�
			{
				lossrate = Edge->GetLossrate();
				if( Edge->GetBroken() == 1 )
				{
					f<<"	[BROKEN]  "<<Edge->GetfromDong()<<"  ->  "<<Edge->GettoDong()<<" ( "<<Edge->GetLossrate()<<" )";

					if( lossrate*2 > 50)//���սǷ��� �������ش�
						Edge->SetLossrate(50);
					else
					{
						lossrate = lossrate*2;
						Edge->SetLossrate(lossrate);
					}

					f<<"  ->  ( "<<Edge->GetLossrate()<<" )"<<endl;//���Ͽ� ���
					Edge->SetBroken(0);//broken flag�� reset ���ش�
				}
				Edge = Edge->GetDongEdgeNext();
			}
			Dong = Dong->GetdongNext();
			if(Dong == Gu->GetDongHead())//��������Ʈ�� ��� ���Ҵٸ�
				break;//���ѷ��� ����
		}
	}

	Gu = ADJList.GetGuHead();//��� Edge�� MST ���� 0���� ���ְ� �ٽ� MST �Լ��� ȣ�����ش�
	while(Gu !=NULL)
	{
		Dong = Gu->GetDongHead();
		while(1)
		{
			Edge = Dong->GetdongedgHead();
			while( Edge != NULL )
			{
				Edge->SetMst(0);
				Edge = Edge->GetDongEdgeNext();
			}
			Dong = Dong->GetdongNext();
			if(Dong == Gu->GetDongHead())
				break;
		}
		Gu = Gu->GetGuNext();
	}

	DongMst();//�ε尡 �Ϸ���� MST �Լ��� ȣ�����ش�.

	f<<"���� �� ���� �� ����"<<endl;

	Gu = ADJList.SearchGuVertex(gu);
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
				if(Edge->GetMst() == 1)//MST edge���
					f<<"	"<<Edge->GetfromDong()<<"  ->  "<<Edge->GettoDong()<<" ( "<<Edge->GetLossrate()<<" ) "<<endl;
				//���� ������ ���Ͽ� ������ش�
				Edge = Edge->GetDongEdgeNext();//���� edge�� ����Ų��
			}
			Dong = Dong->GetdongNext();//���� ��������Ų��
			if(Dong == Gu->GetDongHead())//��������Ʈ �ݺ��� �����ٸ�
				break;//���ѷ�������
		}
	}
	f<<Man->GetMechanicName()<<" ������� �̵����"<<endl;

	int num_to = 0;//������� �̵���θ� ������ֱ� ���� �κ��̴�
	int num_dis = 0;
	GuVertex *toGu = NULL;
	GuEdge *guEdge = NULL;

	f<<Man->GetMechanicGu()<<" ( 0 ) ";
	Gu = ADJList.SearchGuVertex(Man->GetMechanicGu());

	if(strcmp(Man->GetMechanicGu(),gu)==0)//����簡 �ش籸�� ���� ��� ����ó��
	{
		f<<endl;
		f.close();
		return true;//���� �ݾ��ش�
	}
	else
		f<<" -> ";
	while(1)//���������� �Դٸ� ���ѷ��� ����
	{

		num_to = Short[2][Gu->GetShortflag()];
		toGu = ADJList.SearchGuVertex(num_to);
		guEdge = ADJList.SearchGuEdge(Gu,toGu->GetGuName());
		num_dis = num_dis + guEdge->Getdis();
		if(strcmp(toGu->GetGuName(), gu) ==0 )
		{
			f<<toGu->GetGuName()<<" ( "<<num_dis<<" )"<<endl;//���Ͽ����
			Man->SetMechanicGu(toGu->GetGuName());
			break;
		}
		f<<toGu->GetGuName()<<" ( "<<num_dis<<" ) -> ";//���Ͽ����
		Gu = toGu;//���� ��θ� ����Ų��
	}

	f.close();
	return true;//���� �ݾ��ش�
}

bool Manager::Print_Map()//����� �ε���� ������ش�
{
	ofstream f("map.txt",ios_base::app);//map.txt������ �����ش�.
	if( !(f.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	for(int i=0; i<15; i++)
		f<<"==";
	f<<endl<<"	PRINT MAP"<<endl;
	for(int i=0; i<15; i++)
		f<<"==";
	f<<endl; //�ش� ������ ������ش�

	GuVertex *tempGu = ADJList.GetGuHead();//������� �� ����� ��ȯ�޴´�

	if(tempGu==NULL)//����ó��
		f<<"����ÿ� ���� ���� ���� �ʽ��ϴ�"<<endl;

	GuEdge *Edge = NULL;//edge �ӽ� ������ ����

	while(tempGu != NULL)//���� ������ �ݺ��Ѵ�
	{
		Edge = tempGu->GetGuedgHead();//���� edge ����� ��ȯ �޴´�

		while( Edge != NULL )//edge�� ������ �ݺ��Ѵ�
		{
			f<<Edge->GetfromGu()<<"  ->  "<<Edge->GettoGu()<<"  ( "<<Edge->Getdis()<<" )"<<endl;//���Ͽ� ���

			Edge = Edge->GetGuEdgeNext();//����edge�� ����Ų��
		}
		tempGu = tempGu->GetGuNext();//���� ���� ����Ų��
	}

	f.close();//������ �ݾ��ش�
	return true;//�� ��ȯ
}

bool Manager::Print_Gu(char *gu)//�ش籸�� �����ϴ� MST�� ������ش�
{
	ofstream f("pipe.txt",ios_base::app);//pipe.txt������ �����ش�.
	if( !(f.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	for(int i=0; i<22; i++)
		f<<"==";
	f<<endl<<"		PIPE"<<endl;
	for(int i=0; i<22; i++)
		f<<"==";
	f<<endl;//�ش繮���� ���Ͽ� ������ش�

	GuVertex *tempGu = ADJList.SearchGuVertex(gu);//���̸��� �ش��ϴ� ���� ã���ش�

	DongVertex *Dong = NULL;
	DongEdge *Edge = NULL;//�ӽ� ��, �� ���� ������ ����

	if(tempGu != NULL)//�ش��ϴ� ���� �����Ѵٸ�
	{
		Dong = tempGu->GetDongHead();//���� ������� ��ȯ�Ѵ�

		while(1)//���� �ݺ��ϱ����� ���ѷ���
		{
			if(Dong == NULL)//����� ���� ���ٸ� 
				break;
			Edge = Dong->GetdongedgHead();//���� edge ����� ��ȯ�Ѵ�
			while( Edge != NULL )//edge�� ������ �ݺ��Ѵ�
			{
				if(Edge->GetMst() == 1)//MST edge���
					f<<gu<<" : "<<Edge->GetfromDong()<<"  ->  "<<Edge->GettoDong()<<" ( "<<Edge->GetLossrate()<<" ) "<<endl;
				//���� ������ ���Ͽ� ������ش�
				Edge = Edge->GetDongEdgeNext();//���� edge�� ����Ų��
			}

			Dong = Dong->GetdongNext();//���� ��������Ų��
			if(Dong == tempGu->GetDongHead())//��������Ʈ �ݺ��� �����ٸ�
				break;//���ѷ�������
		}
	}

	f.close();//������ �ݾ��ش�
	return true;//�� ��ȯ
}

bool Manager::Print_Mechanic()//����縦 ������ش�
{
	ofstream f("mechanic_list.txt",ios_base::app);//mechanic_list.txt������ �����ش�.
	if( !(f.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	for(int i=0; i<14; i++)
		f<<"==";

	f<<endl<<"	MECHANIC INFO"<<endl;
	for(int i=0; i<14; i++)
		f<<"==";
	f<<endl;//���Ͽ� �ش繮���� ������ش�

	Mechanic *temp = MechanicList.GetMechanicHead();//����� ����Ʈ�� ����� ��ȯ�Ѵ�

	if(temp == NULL)//����ó��
		f<<"����Ǿ��ִ� ����� ����� �����ϴ�"<<endl;

	while(temp != NULL)//temp�� ������ �ݺ��Ѵ�
	{
		f<<"   "<<temp->GetMechanicName()<<"  -  "<<temp->GetMechanicGu()<<endl;//�ش� ������ ������ش�

		temp = temp->GetMechanicNext();//���� ����縦 ����Ų��
	}
	f.close();//������ �ݾ��ش�
	return true;//����ȯ
}

bool Manager::Save_Gu()//�� ���� ���� ����
{
	ofstream f1("gu_vertex.bak",ios::out);//�Է� ���� ���ϸ����� ��üff ����
	if( !(f1.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	GuVertex *gu = ADJList.GetGuHead();//���� ����� ��ȯ�Ѵ�
	if(gu==NULL)
	{
		cout<<"����Ǿ��ִ� ������ �����ϴ�"<<endl;
		f1.close();
		return false;//���� ����Ǿ��ִ� ���̾��ٸ� ȭ�鿡 ��� ���� ��ȯ
	}

	for(int i=0; i<12; i++)
		f1<<"==";
	f1<<endl<<"    ����� �� ��Ī"<<endl;
	for(int i=0; i<12; i++)
		f1<<"==";
	f1<<endl; //�ش� ������ ������ش�

	while(gu != NULL)
	{
		f1<<"	"<<gu->GetGuName()<<endl;
		gu = gu->GetGuNext();
	}
	f1.close();//ȭ�鿡 ������ְ� ������ �ݾ��ش�

	ofstream f2("gu_edge.bak",ios::out);//�Է� ���� ���ϸ����� ��üff ����
	if( !(f2.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	gu = ADJList.GetGuHead();
	GuEdge *Edge = NULL;

	for(int i=0; i<30; i++)
		f2<<"==";
	f2<<endl<<"	from(��)	to(��)		distance(km)"<<endl;
	for(int i=0; i<30; i++)
		f2<<"==";
	f2<<endl; //�ش� ������ ������ش�

	while(gu != NULL)//������� ���� ��edge�� �ݺ��Ѵ�
	{
		Edge = gu->GetGuedgHead();

		while(Edge != NULL)
		{
			f2<<"	"<<Edge->GetfromGu()<<"		"<<Edge->GettoGu()<<"		   "<<Edge->Getdis()<<endl;//���Ͽ� ���
			Edge = Edge->GetGuEdgeNext();//���� edge�� ����Ų��
		}
		gu = gu->GetGuNext();
	}

	f2.close();
	return true;//������ �ݾ��ְ� �� ��ȯ
}

bool Manager::Save_Dong()//�� ����
{
	ofstream f1("dong_vertex.bak",ios::out);//�Է� ���� ���ϸ����� ��üff ����
	if( !(f1.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	GuVertex *gu = ADJList.GetGuHead();
	DongVertex *Dong = NULL;//���� ���� ���� ������ ����

	if(gu==NULL)
	{
		cout<<"����Ǿ��ִ� �� ������ �����ϴ�"<<endl;
		f1.close();
		return false;//����Ǿ��ִ� ���� ���ٸ� ȭ�鿡 ��� ���� ��ȯ
	}

	for(int i=0; i<35; i++)
		f1<<"==";
	f1<<endl<<"	�� ��Ī		�� ��Ī		���� ������ ����(0/X)"<<endl;
	for(int i=0; i<35; i++)
		f1<<"==";
	f1<<endl; //�ش� ������ ������ش�

	while(gu != NULL)//��� ���� ������ش�
	{
		Dong = gu->GetDongHead();
		if(Dong !=NULL)
		{
			do
			{
				f1<<"	"<<gu->GetGuName()<<"		"<<Dong->GetDongName()<<"			"<<Dong->GetView()<<endl;//���Ͽ� ���
				Dong = Dong->GetdongNext();//���� ���� ����Ų��
			}while(Dong != gu->GetDongHead() );
		}
		gu = gu->GetGuNext();
	}

	f1.close();//������ �ݾ��ش�

	ofstream f2("dong_edge.bak",ios::out);//�Է� ���� ���ϸ����� ��üff ����
	if( !(f2.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	gu = ADJList.GetGuHead();
	Dong = NULL;
	DongEdge *Edge = NULL;//�ӽ� ������ ����

	for(int i=0; i<40; i++)
		f2<<"==";
	f2<<endl<<"	�� ��Ī		from(��)	to(��)		�� �սǷ�(%)"<<endl;
	for(int i=0; i<40; i++)
		f2<<"==";
	f2<<endl; //�ش� ������ ������ش�

	while(gu != NULL)//��� �� edge�� ������ֱ� ���� �ݺ���
	{
		Dong = gu->GetDongHead();

		if(Dong != NULL)//����Ǿ��ִ� ���� �����Ѵٸ�
		{
			do//���� ������ �ݺ��Ѵ�
			{
				Edge = Dong->GetdongedgHead();
				while(Edge !=NULL)
				{
					f2<<"	"<<gu->GetGuName()<<"		"<<Edge->GetfromDong()<<"		"<<Edge->GettoDong()<<"		"<<Edge->GetLossrate()<<endl;

					Edge = Edge->GetDongEdgeNext();//���� edge�� ����Ų��
				}
				Dong = Dong->GetdongNext();//���� ���� ����Ų��
			}while(Dong != gu->GetDongHead() );//������ũ�帮��Ʈ ó���� ������ �ݺ��Ѵ�
		}
		gu = gu->GetGuNext();
	}

	f2.close();
	return true;//������ �ݾ��ְ� �� ��ȯ
}

bool Manager::Save_Mechanic()//����� ����� �����Ѵ�
{
	ofstream f("mechanic.bak",ios::out);//mechanic_list.txt������ �����ش�.
	if( !(f.is_open()) )//���� ������ �����ߴٸ�
		return false;//������ ��ȯ�Ѵ�

	for(int i=0; i<22; i++)
		f<<"==";
	f<<endl<<"	�ٹ���		����� �̸�"<<endl;
	for(int i=0; i<22; i++)
		f<<"==";
	f<<endl;//���Ͽ� �ش繮���� ������ش�

	Mechanic *temp = MechanicList.GetMechanicHead();//����� ����Ʈ�� ����� ��ȯ�Ѵ�

	if(temp == NULL)//����ó��
	{
		cout<<"����Ǿ��ִ� ����� ����� �����ϴ�"<<endl;
		return false;
	}

	while(temp != NULL)//temp�� ������ �ݺ��Ѵ�
	{
		f<<"	"<<temp->GetMechanicGu()<<"		 "<<temp->GetMechanicName()<<endl;//�ش� ������ ������ش�
		temp = temp->GetMechanicNext();//���� ����縦 ����Ų��
	}

	f.close();//������ �ݾ��ش�
	EXIT();
	return true;//����ȯ
}

Mechanic *Manager::ShortestPath(GuVertex *Gu)//�ִ� �Ÿ� ���ϴ� �Լ�
{
	for(int i= 0;i<3;i++) // 3*100 �迭 �ʱ�ȭ
	{
		if(i==0)
		{
			for(int j=0; j<100; j++)
				Short[i][j]=100;
		}
		else if(i==1)
		{
			for(int j=0; j<100; j++)
				Short[i][j]=0;
		}
		else
		{
			for(int j=0; j<100; j++)
				Short[i][j]=-1;
		}
	}

	GuVertex *tempGu = NULL;
	GuVertex *toGu = NULL;

	int From = Gu->GetShortflag();
	Short[0][From] = 0;
	Short[1][From] = 1;//������� ������ �������ش�

	GuEdge *tempEdge = Gu->GetGuedgHead();
	while(tempEdge != NULL)
	{
		tempGu = ADJList.SearchGuVertex( tempEdge->GettoGu() );
		Short[0][tempGu->GetShortflag()] = tempEdge->Getdis();
		Short[2][tempGu->GetShortflag()] = From;
		tempEdge = tempEdge->GetGuEdgeNext();
	}//������� ����� ��� �� edge�� �ݺ��ϸ鼭 ���� �������ش�

	while(1)//�ִܰŸ��� ���ϱ� ���� ���ѷ���
	{
		if( FinishShortestPath() )//�Ϸ�Ǿ��ٸ� 
			break;//���ѷ��� ����
		else
		{
			From = MinDis();//����Ǿ��ִ� �Ÿ��� �ּҰ��� index�� ��ȯ�Ѵ�
			tempGu = ADJList.SearchGuVertex(From);
			Short[1][From] = 1;

			tempEdge = tempGu->GetGuedgHead();

			while(tempEdge !=NULL)//tempedge�� ������ �ݺ��Ѵ�
			{
				toGu = ADJList.SearchGuVertex( tempEdge->GettoGu() );
				//�Ÿ� ���� �ٲ��� �Ѵٸ� 
				if( (Short[0][From]) + ( tempEdge->Getdis() ) < Short[0][toGu->GetShortflag()] )
				{
					Short[0][toGu->GetShortflag()] = (Short[0][From]) + ( tempEdge->Getdis() );
					Short[2][toGu->GetShortflag()] = From;//�ٲ��ְ� ��𼭺��� �Դ����� �����Ѵ�
				}
				tempEdge = tempEdge->GetGuEdgeNext();//���� edge�� ����Ų��
			}
		}
	}
	tempGu = NULL;

	Mechanic *tempMan = MechanicList.GetMechanicHead();
	Mechanic *Man = MechanicList.GetMechanicHead();

	while(tempMan !=NULL)//����縦 �ݺ��Ѵ�
	{
		tempGu = ADJList.SearchGuVertex( tempMan->GetMechanicGu() );
		tempMan->SetDistence( Short[0][tempGu->GetShortflag()] );
		//�������� ���� ���� ����� ����縦 ã���ش�
		if( tempMan->GetDistence() < Man->GetDistence() )
			Man = tempMan;

		tempMan = tempMan->GetMechanicNext();
	}

	return Man;//���尡��� ��ġ�� �ִ� ����縦 ��ȯ�Ѵ�
}

bool Manager::FinishShortestPath()//�ִܰ�� �Ϸ� ���θ� �˻��Ѵ�
{
	int column = ADJList.CountGu();
	int con =0;

	for(int i=0;i < column;i++)
	{
		if(Short[1][i]==0)//���� 0�̶�� ī���� ����
			con++;
	}

	if(con==0)// ��� �� �湮 �Ϸ�
		return true;//����ȯ
	else//�湮�� �Ϸ���� �ʾҴٸ�
		return false;//������ȯ
}

int Manager::MinDis()//�Ÿ����� �ּ� ���� ã�� �Լ�
{
	int pivot=100;
	int index;
	int column = ADJList.CountGu();//���� ������ ��ȯ�޴´�

	for(int i=0; i<column;i++)
	{
		//�� ���� ���� ã�� �ȴٸ�
		if( (Short[0][i] > 0) && (Short[0][i] < 100) && (Short[0][i] < pivot) && (Short[1][i] == 0) )
		{
			pivot = Short[0][i];
			index = i;//�� ���� index�� �����ϰ� pivot ���� �ٲ��ش�
		}
	}

	return index;//�ּ� ���� index�� ��ȯ�Ѵ�
}

bool Manager::EXIT()//�Ҹ���
{
	GuVertex *Gu = ADJList.GetGuHead();
	GuVertex *pGu = NULL;

	GuEdge *Edge = NULL;
	GuEdge *pEdge = NULL;

	DongVertex *Dong = NULL;
	DongVertex *pDong = NULL;

	DongEdge *Dong_edge = NULL;
	DongEdge *pDong_edge = NULL;//�Ҹ��� ���� ������ ����

	while(Gu != NULL)//���� ���� ����Ʈ �ΰ��� 1D list�� �ٲ��ش�
	{
		Dong = Gu->GetDongHead();
		if(Dong !=NULL)
		{
			pDong = Dong->GetdongNext();
			while(1)
			{
				if(pDong->GetdongNext() == Dong)//������ �� �����
				{
					pDong->SetdongNext(NULL);//NULL�� �־��ش�
					break;
				}
				pDong = pDong->GetdongNext();
			}
		}
		Gu = Gu->GetGuNext();
	}

	Gu = ADJList.GetGuHead();
	while(Gu != NULL)//�� �� ���� �������� ������ �ش�
	{
		Dong = Gu->GetDongHead();
		while(Dong !=NULL)
		{
			Dong_edge = Dong->GetdongedgHead();
			while(Dong_edge !=NULL)
			{
				pDong_edge = Dong_edge;
				Dong_edge = Dong_edge->GetDongEdgeNext();
				delete pDong_edge;
			}
			pDong = Dong;
			Dong = Dong->GetdongNext();
			delete pDong;
		}
		Gu = Gu->GetGuNext();
	}

	Gu = ADJList.GetGuHead();
	while(Gu != NULL)//���� ���� �������� �������ش�
	{
		Edge = Gu->GetGuedgHead();
		while(Edge !=NULL)
		{
			pEdge = Edge;
			Edge = Edge->GetGuEdgeNext();
			delete pEdge;
		}
		pGu = Gu;
		Gu = Gu->GetGuNext();
		delete pGu;
	}
	ADJList.SetHead();

	Mechanic *temp = MechanicList.GetMechanicHead();//����� ����Ʈ�� ����� ��ȯ�Ѵ�
	Mechanic *ptemp = NULL;

	while(temp != NULL)//����� ����� �������ش�
	{
		ptemp = temp;
		temp = temp->GetMechanicNext();
		delete ptemp;
	}
	MechanicList.SetHead();

	return true;
}

