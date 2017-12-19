#include "Game.h"

Game::Game()
{
	srand((unsigned)time(NULL)); // 랜덤하게 만들어주십시오
	stage = 0; // 처음 단계
}
int Game::Start(Map *m, View *v)
{
	system("cls");
	Reset();
	m->GetMap(stage); // 맵을 읽음
	SetFood(m,v);// 맵에 밥 뿌림
	Born(m); // 뱀 머리 탄생
	v->ShowMap(m); // 맵을 찍음


	HoldTime(); // 게임 시작전 진행시간 - 초기시간 = 진행시간
	while(true)
	{
		v->ShowPlayTime(PlayTime()); // 진행시간 표시
		v->ShowLocation(GetX(),GetY()); // 현재 좌표 표시
		
		if(GetAsyncKeyState(VK_UP) && direction != 2){ // up키를 눌렀고 위로 가다가 바로 아래로 못가게함
				Up(m,v);
		}
		else if(GetAsyncKeyState(VK_DOWN) && direction != 1){ // down키를 눌렀고 아래로 가다가 바로 위로 못가게함
				Down(m,v);
		}
		else if(GetAsyncKeyState(VK_LEFT) && direction != 4){ // left키를 눌렀고 왼쪽으로 가다가 바로 오른쪽으로 못가게함
				Left(m,v);
		}
		else if(GetAsyncKeyState(VK_RIGHT) && direction != 3){ // right키를 눌렀고 오른쪽으로 가다가 바로 왼쪽으로 못가게함
				Right(m,v);
		}
		else
			Move(m,v);
		
		if(gameCon == 0 || gameCon == 2) // 게임 종료를 원한다면
			return gameCon; // 게임 종료다
		else if(gameCon == 1) // 다시 하길 원한다면
			return gameCon; // 다시 시작
		else if(foodCount == 0) // 밥을 다 쳐먹으면
		{
			stage++; // 단계 증가
			v->StageClear(stage);
			break;
		}

		if(stage >= 5) // 승리
		{
			Stop(v,true);
		}

		SpeedUp(); 
		Sleep(MoveSpeed);
	}
	return -1; // 쓸데없는 값
}
void Game::Stop(View *v, bool win)
{
	if(!win) // 게임 정지시
		v->GameSet(); // 다시시작 여부 물음
	else
		v->Win();
	while(true)
	{
		if(GetAsyncKeyState(VK_F1)) // F1 키
		{
			gameCon = win ? 2 : 1; // 만약 승리로 부른것이면 2를 리턴할 것이요, 죽음으로 부른것이면 1을 리턴할 것이외다.
			break;
		}
		else if(GetAsyncKeyState(VK_ESCAPE)) // ESC 키
		{
			gameCon = 0;
			break;
		}
	}
}
void Game::Reset()
{
	foodCount=0; // 뿌린 밥의 갯수 초기화
	MoveSpeed = 250; // 기본 속도
	watch = 0; // 고정
	flowWatch = 0; // 흐르는 시간
	direction = -1; // 머리가 향하는 방향
	bodyLen = 0; // 몸길이
	eat = 0; // 먹은 갯수
	gameCon = -1; // -1 초기화
}
void Game::SpeedUp() // 10초 지날 때마다 속도 증가
{
	if(MoveSpeed >50) // 최고 속도 제한
		flowWatch%5==0 ? MoveSpeed-=3 : 1;
}
void Game::SetFood(Map *m,View *v) // 밥 위치 지정
{
	int temp; // 랜덤하게 뿌려줌
	for(int i=0;i<MAP_X;i++)
	{
		for(int j=0;j<MAP_X;j++)
		{
			temp = rand()%14+1;
			if(temp == 7 && m->GetMapValue(i,j) == 0) // 해당 배열이 비어있다면
			{
				m->SetMapValue(i,j, 4); // 그곳에 먹이 넣기
				foodCount++; // 뿌린 밥의 갯수 증가
				
			}
		}
	}
}
void Game::Born(Map *m) // 머리좌표 지정
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
	if(direction!=-1) // 이동불가 상태가 아니고
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
	if(m->GetMapValue(_h_x,_h_y) != 1) // 길막이 아니면
	{
		if(m->GetMapValue(_h_x,_h_y) == 4) // 밥탐
		{
			m->SetMapValue(h_x,h_y,3); // 현재위치 몸
			for(int i=bodyLen;i>0;i--) // sp[0]은 머리 바로 뒷몸
			{
				sp[i].x=sp[i-1].x; 
				sp[i].y=sp[i-1].y;
			} // 위 for문은 sp[0]에서 sp[bodyLen] 까지에다가 한칸씩 밀려 넣는거임 
			sp[0].x = h_x; // 뒷몸에다가 머리 좌표를 넣음
			sp[0].y = h_y; // sp[0]을 머리 바로 다음번째 이므로 머리의 좌표를 넣음

			m->SetMapValue(_h_x,_h_y,2); // 머리의 다음 위치
			v->Head(_h_x,_h_y); // 머리를 그 위치에 그림
			for(int i=0;i<=bodyLen;i++) // 몸 길이만큼 그 좌표에 그림을 그림
			{
				v->SetColor((i+flowWatch)%6+9,0);
				v->Body(sp[i].x,sp[i].y); // 몸 그리기
				m->SetMapValue(sp[i].x,sp[i].y,3); // 배열에 값넣기
			}
			v->SetColor(15,0); // 글씨 색 초기화
			eat++; // 먹었다
			foodCount--; // 남은 밥 감소
			bodyLen++; // 몸 길이 늚
			v->Eat_N_RemainingFood(eat,foodCount); // 현재 밥 먹은량과 남은량을 표시한다.
		}
		else if(m->GetMapValue(_h_x,_h_y) != 3) // 밥도 아니고 자살도 아니면
		{
			m->SetMapValue(h_x,h_y,0); // 현재 위치 배열을 공란으로
			m->SetMapValue(_h_x,_h_y,2); // 머리를 다음위치배열에 넣음
			v->SetColor(GetTickCount()%6+9,0); // 색깔
			v->Head(_h_x,_h_y); // 머리를 그림
			if(bodyLen>0) // 뭐 하나라도 쳐먹으면
			{
				v->Clear(sp[bodyLen-1].x,sp[bodyLen-1].y); // 꼬리 지움
				m->SetMapValue(sp[bodyLen-1].x,sp[bodyLen-1].y,0); // 머리 바로 전의 것에 공란
				for(int i=bodyLen;i>0;i--) // 위와 동일 한칸씩 밂
				{
					sp[i].x=sp[i-1].x;
					sp[i].y=sp[i-1].y;
				}
				sp[0].x = h_x; // 위와 동일 머리 바로 뒷몸
				sp[0].y = h_y;

				for(int i=0;i<bodyLen;i++) // 몸 길이 만큼
				{
					v->SetColor((i+GetTickCount())%6+9,0);
					v->Body(sp[i].x,sp[i].y); // 몸을 그려줌 그 저장한 좌표에
					m->SetMapValue(sp[i].x,sp[i].y,3); // 배열 채우기
				}
				
			}
			else // 몸 종범시
				v->Clear(h_x,h_y); // 몸 걍 지움
		}
		else // 자기 자신을 먹음
		{
			Stop(v);
		}
		
	}
	else // 벽에 박음
	{
		Stop(v);
	}
	h_y=_h_y; // 머리 좌표를 이동
	h_x=_h_x;
	v->SetColor(15,0); // 글씨 색 초기화
}