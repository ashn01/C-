#include "Game.h"

Game::Game()
{
	srand((unsigned)time(NULL)); // �����ϰ� ������ֽʽÿ�
	stage = 0; // ó�� �ܰ�
}
int Game::Start(Map *m, View *v)
{
	system("cls");
	Reset();
	m->GetMap(stage); // ���� ����
	SetFood(m,v);// �ʿ� �� �Ѹ�
	Born(m); // �� �Ӹ� ź��
	v->ShowMap(m); // ���� ����


	HoldTime(); // ���� ������ ����ð� - �ʱ�ð� = ����ð�
	while(true)
	{
		v->ShowPlayTime(PlayTime()); // ����ð� ǥ��
		v->ShowLocation(GetX(),GetY()); // ���� ��ǥ ǥ��
		
		if(GetAsyncKeyState(VK_UP) && direction != 2){ // upŰ�� ������ ���� ���ٰ� �ٷ� �Ʒ��� ��������
				Up(m,v);
		}
		else if(GetAsyncKeyState(VK_DOWN) && direction != 1){ // downŰ�� ������ �Ʒ��� ���ٰ� �ٷ� ���� ��������
				Down(m,v);
		}
		else if(GetAsyncKeyState(VK_LEFT) && direction != 4){ // leftŰ�� ������ �������� ���ٰ� �ٷ� ���������� ��������
				Left(m,v);
		}
		else if(GetAsyncKeyState(VK_RIGHT) && direction != 3){ // rightŰ�� ������ ���������� ���ٰ� �ٷ� �������� ��������
				Right(m,v);
		}
		else
			Move(m,v);
		
		if(gameCon == 0 || gameCon == 2) // ���� ���Ḧ ���Ѵٸ�
			return gameCon; // ���� �����
		else if(gameCon == 1) // �ٽ� �ϱ� ���Ѵٸ�
			return gameCon; // �ٽ� ����
		else if(foodCount == 0) // ���� �� �ĸ�����
		{
			stage++; // �ܰ� ����
			v->StageClear(stage);
			break;
		}

		if(stage >= 5) // �¸�
		{
			Stop(v,true);
		}

		SpeedUp(); 
		Sleep(MoveSpeed);
	}
	return -1; // �������� ��
}
void Game::Stop(View *v, bool win)
{
	if(!win) // ���� ������
		v->GameSet(); // �ٽý��� ���� ����
	else
		v->Win();
	while(true)
	{
		if(GetAsyncKeyState(VK_F1)) // F1 Ű
		{
			gameCon = win ? 2 : 1; // ���� �¸��� �θ����̸� 2�� ������ ���̿�, �������� �θ����̸� 1�� ������ ���ܴ̿�.
			break;
		}
		else if(GetAsyncKeyState(VK_ESCAPE)) // ESC Ű
		{
			gameCon = 0;
			break;
		}
	}
}
void Game::Reset()
{
	foodCount=0; // �Ѹ� ���� ���� �ʱ�ȭ
	MoveSpeed = 250; // �⺻ �ӵ�
	watch = 0; // ����
	flowWatch = 0; // �帣�� �ð�
	direction = -1; // �Ӹ��� ���ϴ� ����
	bodyLen = 0; // ������
	eat = 0; // ���� ����
	gameCon = -1; // -1 �ʱ�ȭ
}
void Game::SpeedUp() // 10�� ���� ������ �ӵ� ����
{
	if(MoveSpeed >50) // �ְ� �ӵ� ����
		flowWatch%5==0 ? MoveSpeed-=3 : 1;
}
void Game::SetFood(Map *m,View *v) // �� ��ġ ����
{
	int temp; // �����ϰ� �ѷ���
	for(int i=0;i<MAP_X;i++)
	{
		for(int j=0;j<MAP_X;j++)
		{
			temp = rand()%14+1;
			if(temp == 7 && m->GetMapValue(i,j) == 0) // �ش� �迭�� ����ִٸ�
			{
				m->SetMapValue(i,j, 4); // �װ��� ���� �ֱ�
				foodCount++; // �Ѹ� ���� ���� ����
				
			}
		}
	}
}
void Game::Born(Map *m) // �Ӹ���ǥ ����
{
	while(true){
		h_x = rand()%20+1;
		h_y = rand()%20+1;
		if(m->GetMapValue(h_x,h_y) ==0)
		{
			m->SetMapValue(h_x,h_y,2);
			break;
		}
	}

}
int Game::HoldTime()
{
	watch = GetTickCount();
	return watch;
}

int Game::PlayTime()
{
	flowWatch =(GetTickCount()-watch)/1000;
	return flowWatch;
}
int Game::GetX()
{
	return h_x;
}

int Game::GetY()
{
	return h_y;
}

void Game::Up(Map *m, View *v)
{
	direction = 1;
	this->Moving(m,v,h_x,h_y-1);
}

void Game::Down(Map *m, View *v)
{
	direction = 2;
	this->Moving(m,v,h_x,h_y+1);
}

void Game::Left(Map *m, View *v)
{
	direction = 3;
	this->Moving(m,v,h_x-1,h_y);
}

void Game::Right(Map *m, View *v)
{
	direction = 4;
	this->Moving(m,v,h_x+1,h_y);
}

void Game::Move(Map *m, View *v)
{
	if(direction!=-1) // �̵��Ұ� ���°� �ƴϰ�
	{
		switch(direction)
		{
		case 1: this->Up(m,v); break;
		case 2: this->Down(m,v); break;
		case 3: this->Left(m,v); break;
		case 4: this->Right(m,v); break;
		default: break;
		}
	}else 
	{}
}

void Game::Moving(Map *m, View *v, int _h_x, int _h_y)
{
	if(m->GetMapValue(_h_x,_h_y) != 1) // �渷�� �ƴϸ�
	{
		if(m->GetMapValue(_h_x,_h_y) == 4) // ��Ž
		{
			m->SetMapValue(h_x,h_y,3); // ������ġ ��
			for(int i=bodyLen;i>0;i--) // sp[0]�� �Ӹ� �ٷ� �޸�
			{
				sp[i].x=sp[i-1].x; 
				sp[i].y=sp[i-1].y;
			} // �� for���� sp[0]���� sp[bodyLen] �������ٰ� ��ĭ�� �з� �ִ°��� 
			sp[0].x = h_x; // �޸����ٰ� �Ӹ� ��ǥ�� ����
			sp[0].y = h_y; // sp[0]�� �Ӹ� �ٷ� ������° �̹Ƿ� �Ӹ��� ��ǥ�� ����

			m->SetMapValue(_h_x,_h_y,2); // �Ӹ��� ���� ��ġ
			v->Head(_h_x,_h_y); // �Ӹ��� �� ��ġ�� �׸�
			for(int i=0;i<=bodyLen;i++) // �� ���̸�ŭ �� ��ǥ�� �׸��� �׸�
			{
				v->SetColor((i+flowWatch)%6+9,0);
				v->Body(sp[i].x,sp[i].y); // �� �׸���
				m->SetMapValue(sp[i].x,sp[i].y,3); // �迭�� ���ֱ�
			}
			v->SetColor(15,0); // �۾� �� �ʱ�ȭ
			eat++; // �Ծ���
			foodCount--; // ���� �� ����
			bodyLen++; // �� ���� ��
			v->Eat_N_RemainingFood(eat,foodCount); // ���� �� �������� �������� ǥ���Ѵ�.
		}
		else if(m->GetMapValue(_h_x,_h_y) != 3) // �䵵 �ƴϰ� �ڻ쵵 �ƴϸ�
		{
			m->SetMapValue(h_x,h_y,0); // ���� ��ġ �迭�� ��������
			m->SetMapValue(_h_x,_h_y,2); // �Ӹ��� ������ġ�迭�� ����
			v->SetColor(GetTickCount()%6+9,0); // ����
			v->Head(_h_x,_h_y); // �Ӹ��� �׸�
			if(bodyLen>0) // �� �ϳ��� �ĸ�����
			{
				v->Clear(sp[bodyLen-1].x,sp[bodyLen-1].y); // ���� ����
				m->SetMapValue(sp[bodyLen-1].x,sp[bodyLen-1].y,0); // �Ӹ� �ٷ� ���� �Ϳ� ����
				for(int i=bodyLen;i>0;i--) // ���� ���� ��ĭ�� ��
				{
					sp[i].x=sp[i-1].x;
					sp[i].y=sp[i-1].y;
				}
				sp[0].x = h_x; // ���� ���� �Ӹ� �ٷ� �޸�
				sp[0].y = h_y;

				for(int i=0;i<bodyLen;i++) // �� ���� ��ŭ
				{
					v->SetColor((i+GetTickCount())%6+9,0);
					v->Body(sp[i].x,sp[i].y); // ���� �׷��� �� ������ ��ǥ��
					m->SetMapValue(sp[i].x,sp[i].y,3); // �迭 ä���
				}
				
			}
			else // �� ������
				v->Clear(h_x,h_y); // �� �� ����
		}
		else // �ڱ� �ڽ��� ����
		{
			Stop(v);
		}
		
	}
	else // ���� ����
	{
		Stop(v);
	}
	h_y=_h_y; // �Ӹ� ��ǥ�� �̵�
	h_x=_h_x;
	v->SetColor(15,0); // �۾� �� �ʱ�ȭ
}