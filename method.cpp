#ifndef method_H			//method.cpp
#define method_H
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<iostream>
#include"pos.h"
using namespace std;
inline void Set_mouse(int x,int y)
{
	HANDLE h =GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=x;pos.Y=y;
	SetConsoleCursorPosition(h,pos);
}
inline void Set_mouse(pos p)
{
	HANDLE h =GetStdHandle(STD_OUTPUT_HANDLE);
	COORD ps;
	ps.X=p.ix;ps.Y=p.iy;
	SetConsoleCursorPosition(h,ps);
}

void EXIT()				//退出游戏提示 
{
	cout<<"\a";			//提示音 
	int ret=MessageBox(NULL,TEXT("退出游戏？"),TEXT("王者光耀"),MB_YESNO|MB_ICONQUESTION);
	if(ret==IDYES)exit(0);
}
void Hide_mouse()				//绘图隐藏光标 
{
	CONSOLE_CURSOR_INFO mouse={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&mouse);
}
#endif
