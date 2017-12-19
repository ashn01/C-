#include "View.h"

View::View()
{
	foodType="♡"; 
	foodSelect=0;
}
void gotoxy(int x, int y)
{
	COORD Pos = {x , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
int View::ShowMain()
{
	gotoxy(0,2);
	cout << "□□■■■□□□■■□□□■■□□□■■■□□□■■□□□■■□■■■■■■■\n";
	cout << "□■■■■■□□■■□□□■■□□■■■■■□□■■□□□■■□■■■■■■■\n";
	cout << "■■■□■■■□■■□□■■■□□■■□■■□□■■□□■■■□■■□□□□□\n";
	cout << "■■□□□□□□■■□□■■■□□■■□■■□□■■□■■■□□■■□□□□□\n";
	cout << "■■□□□□□□■■□■■■■□■■■□■■■□■■■■■□□□■■□□□□□\n";
	cout << "■■■■□□□□■■□■□■■□■■□□□■■□■■■■□□□□■■■■■■■\n";
	cout << "□■■■■■□□■■□■□■■□■■□□□■■□■■■□□□□□■■■■■■■\n";
	cout << "□□□□■■■□■■□■□■■□■■■■■■■□■■■■□□□□■■□□□□□\n";
	cout << "□□□□□■■□■■■■□■■□■■■■■■■□■■■■■□□□■■□□□□□\n";
	cout << "□□□□□■■□■■■□□■■□■■□□□■■□■■□■■■□□■■□□□□□\n";
	cout << "■■■□■■■□■■■□□■■□■■□□□■■□■■□□■■■□■■□□□□□\n";
	cout << "□■■■■■□□■■□□□■■□■■□□□■■□■■□□□■■□■■■■■■■\n";
	cout << "□□■■■□□□■■□□□■■□■■□□□■■□■■□□□■■□■■■■■■■\n";
	gotoxy(25,16);
	cout << "1. 게임 시작하기";
	gotoxy(25,18);
	cout << "2. 먹이모양 바꾸기";
	gotoxy(25,20);
	cin>>ans;
	system("cls");
	return ans;
}

void View::ShowMap(Map* m) 
{
	for(int i=0;i<MAP_X;i++)
	{
		for(int j=0;j<MAP_X;j++)
		{
			
			if(m->GetMapValue(j,i) == 1) 
				cout<<"□";
			else if(m->GetMapValue(j,i) == 2) 
				cout<<"◈";
			else if(m->GetMapValue(j,i) == 3) 
				cout<<"▣";
			else if(m->GetMapValue(j,i) == 4) 
			{
				SetColor(12,0);
				cout<<foodType;
				SetColor(15,0);
			}
			else if(m->GetMapValue(j,i) == 0) 
				cout<<"  ";
		}
		cout<<endl;
	}
	gotoxy(56,2);
	cout<<"진행시간 : ";
	gotoxy(56,4);
	cout<<"현재좌표 : ";
	gotoxy(56,6);
	cout<<"먹은 밥 : ";
	gotoxy(56,8);
	cout<<"남은 밥 : ";
}

void View::SelectFood()
{
	system("cls"); 

	gotoxy(23,10);     
	cout << "1.♡";
	gotoxy(23,12);
	cout << "2.♣";
	gotoxy(23,14);
	cout << "3.▨";
	gotoxy(23,16);
	cout << "4.◑";
	gotoxy(23,18);
	cin>>foodSelect;

	switch(foodSelect)
	{
	case 1: foodType="♡"; break;
	case 2: foodType="♣"; break;
	case 3: foodType="▨"; break;
	case 4: foodType="◑"; break;
	default: foodType="♡"; break;

	}
	system("cls");
}
void View::ShowPlayTime(int time)
{
	gotoxy(67,2);
	cout<<time/60<<" : "<<time%60<<"  ";
	NoBlink();
}

void View::ShowLocation(int h_x, int h_y)
{
	gotoxy(67,4);
	cout<<h_x<<", "<<h_y<<"   "; 
	NoBlink();
}

void View::Eat_N_RemainingFood(int eat, int remainingfood)
{
	gotoxy(67,6);
	cout<<eat<<"  ";
	gotoxy(67,8);
	cout<<remainingfood<<"  ";
	NoBlink();
}
void View::Head(int x, int y)
{
	gotoxy(x*2,y);
	cout<<"◈";
	NoBlink();
}
void View::Clear(int x, int y)
{
	gotoxy(x*2,y);
	cout<<"  ";
	NoBlink();
}
void View::Body(int x, int y)
{
	gotoxy(x*2,y);
	cout<<"▣";
	NoBlink();
}

void View::GameSet()
{
	gotoxy(56,12);
	cout<<"게임 오버";
	gotoxy(0,24);
	cout<<"다시 시작 F1 , 종료 ESC";
	NoBlink();
}

void View::NoBlink()
{
	gotoxy(79,24);
}
void View::SetColor(int color,int bgcolor)
{
    color &= 0xf;
    bgcolor &= 0xf;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}
void View::StageClear(int stage)
{
	char sc[16]="Stage Clear !!!";
	int count=0;
	while(true)
	{
		count++;
		gotoxy(15,7);
		cout<<stage;
		for(int i=0;i<16;i++)
		{
			SetColor((i+count)%6+9,0);
			cout<<sc[i];
		}
		if(count>80)
			break;
		Sleep(100);
	}
	SetColor(15,0);
}
void View::Win()
{
	char sc[6] = "Win!!";
	int count=0;

	while(true)
	{
		count++;
		gotoxy(19,7);
		for(int i=0;i<6;i++)
		{
			SetColor((i+count)%6+9,0);
			cout<<sc[i];
		}
		if(count>80)
			break;
		Sleep(100);
	}
	SetColor(15,0);
	gotoxy(0,24);
	cout<<"처음 화면 F1 , 종료 ESC";
}